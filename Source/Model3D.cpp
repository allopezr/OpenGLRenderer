#include "stdafx.h"
#include "Model3D.h"

// Static properties

std::string PAG::Model3D::CHECKER_PATTERN_PATH = "Assets/Textures/Checker.png";

// Public methods

PAG::Model3D::Model3D(): _scene(nullptr), _modelMatrix(1.0f)
{
}

PAG::Model3D::~Model3D()
{
}

bool PAG::Model3D::belongsModel(Component* component)
{
    for (auto& comp : _components)
    {
        if (comp.get() == component)
            return true;
    }

    return false;
}

void PAG::Model3D::draw(RenderingShader* shader, MatrixRenderInformation* matrixInformation, ApplicationState* appState, GLuint primitive)
{
    for (auto& component : _components)
    {
        if (component->_enabled && component->_vao)
        {
            VAO::IBO_slots rendering = VAO::IBO_TRIANGLE;

            switch (primitive)
            {
            case GL_TRIANGLES:
                if (component->_material._useUniformColor)
                {
                    shader->setUniform("Kd", component->_material._kdColor);
                    shader->setSubroutineUniform(GL_FRAGMENT_SHADER, "kadUniform", "getUniformColor");
                }
                else
                {
                    Texture* checkerPattern = TextureList::getInstance()->getTexture(CHECKER_PATTERN_PATH);
                    checkerPattern->applyTexture(shader, 0, "texKdSampler");
                    shader->setSubroutineUniform(GL_FRAGMENT_SHADER, "kadUniform", "getTextureColor");
                }

                shader->setUniform("Ks", component->_material._ksColor);
                shader->setUniform("metallic", component->_material._metallic);
                shader->setUniform("roughnessK", component->_material._roughnessK);
                shader->setUniform("mModelView", matrixInformation->multiplyMatrix(MatrixRenderInformation::VIEW, this->_modelMatrix));

                break;
            case GL_LINES:
                rendering = VAO::IBO_LINE;
                break;
            case GL_POINTS:
                rendering = VAO::IBO_POINT;
                break;
            }
            
            shader->setUniform("mModelViewProj", matrixInformation->multiplyMatrix(MatrixRenderInformation::VIEW_PROJECTION, this->_modelMatrix));
            shader->applyActiveSubroutines();

            component->_vao->drawObject(rendering, primitive, static_cast<GLuint>(component->_indices[rendering].size()));

            matrixInformation->undoMatrix(MatrixRenderInformation::VIEW);
            matrixInformation->undoMatrix(MatrixRenderInformation::VIEW_PROJECTION);
        }
    }
}

PAG::Model3D* PAG::Model3D::loadModelOBJ(const std::string& path)
{
    std::string binaryFile = path.substr(0, path.find_last_of('.')) + BINARY_EXTENSION;

    if (std::filesystem::exists(binaryFile))
    {
        this->loadModelBinaryFile(binaryFile);
    }
    else
    {
        _scene = _assimpImporter.ReadFile(path, aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

        if (!_scene || _scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !_scene->mRootNode)
        {
            std::cout << "ERROR::ASSIMP::" << _assimpImporter.GetErrorString() << std::endl;
            return this;
        }

        std::string shortName = _scene->GetShortFilename(path.c_str());
        std::string folder = path.substr(0, path.length() - shortName.length());

        this->processNode(_scene->mRootNode, _scene, folder);
        this->writeBinaryFile(binaryFile);
    }

    for (auto& component : _components)
    {
        this->buildVao(component.get());
    }

    return this;
}

void PAG::Model3D::moveGeometryToOrigin(const mat4& origMatrix, float maxScale)
{
    AABB aabb = this->getAABB();

    vec3 translate = -aabb.center();
    vec3 extent = aabb.extent();
    float maxScaleAABB = std::max(extent.x, std::max(extent.y, extent.z));
    vec3 scale = (maxScale < FLT_MAX) ? ((maxScale > maxScaleAABB) ? vec3(1.0f) : vec3(maxScale / maxScaleAABB)) : vec3(1.0f);

    _modelMatrix = glm::scale(glm::mat4(1.0f), scale) * glm::translate(glm::mat4(1.0f), translate) * origMatrix;
}

void PAG::Model3D::setTexture(const vec3& color)
{
    for (auto& component : _components)
    {
        component->_material._kdColor = color;
    }
}

void PAG::Model3D::setTexture(Texture* texture)
{
}

// Private methods

void PAG::Model3D::buildVao(Component* component)
{
    VAO* vao = new VAO(true);
    vao->setVBOData(component->_vertices);
    vao->setIBOData(VAO::IBO_POINT, component->_indices[VAO::IBO_POINT]);
    vao->setIBOData(VAO::IBO_LINE, component->_indices[VAO::IBO_LINE]);
    vao->setIBOData(VAO::IBO_TRIANGLE, component->_indices[VAO::IBO_TRIANGLE]);
    component->_vao = vao;
}

PAG::Texture* PAG::Model3D::getTexture(const vec4& color, TextureList* textureList)
{
    Texture* texture = nullptr;

    if (!(texture = textureList->getTexture(color)))
    {
        texture = new Texture(color);
    }
    
    return texture;
}

void PAG::Model3D::loadModelBinaryFile(const std::string& path)
{
    std::ifstream fin(path, std::ios::in | std::ios::binary);
    if (!fin.is_open())
    {
        std::cout << "Failed to open the binary file " << path << "!" << std::endl;
        return;
    }

    size_t numComponents = _components.size();
    fin.read((char*)&numComponents, sizeof(size_t));
    _components.resize(numComponents);

    for (size_t compIdx = 0; compIdx < numComponents; ++compIdx)
    {
        Component* component = new Component;
        size_t numVertices, numIndices;

        fin.read((char*)&numVertices, sizeof(size_t));
        component->_vertices.resize(numVertices);
        fin.read((char*)component->_vertices.data(), sizeof(VAO::Vertex) * numVertices);

        for (int topology = 0; topology < VAO::NUM_IBOS; ++topology)
        {
            fin.read((char*)&numIndices, sizeof(size_t));
            if (numIndices)
            {
                component->_indices[topology].resize(numIndices);
                fin.read((char*)component->_indices[topology].data(), sizeof(GLuint) * numIndices);
            }
        }

        fin.read((char*)&component->_aabb, sizeof(AABB));

        _components[compIdx] = std::unique_ptr<Component>(component);
        _aabb.update(_components[compIdx]->_aabb);
    }
}

PAG::Model3D::Component* PAG::Model3D::processMesh(aiMesh* mesh, const aiScene* scene, const std::string& folder)
{
    std::vector<VAO::Vertex> vertices (mesh->mNumVertices);
    std::vector<GLuint> indices (mesh->mNumFaces * 4);
    AABB aabb;

    // Vertices
    int numVertices = static_cast<int>(mesh->mNumVertices);

    for (int i = 0; i < numVertices; i++)
    {
        VAO::Vertex vertex;
        vertex._position = vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        vertex._normal = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

        if (mesh->mTangents) vertex._tangent = vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
        if (mesh->mBitangents) vertex._bitangent = vec3(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z);
        if (mesh->mTextureCoords[0]) vertex._textCoord = vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);

        vertices[i] = vertex;
        aabb.update(vertex._position);
    }

    // Indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices[i * 4 + j] = face.mIndices[j];

        indices[i * 4 + 3] = RESTART_PRIMITIVE_INDEX;
    }

    Component* component = new Component;
    component->_vertices = std::move(vertices);
    component->_indices[VAO::IBO_TRIANGLE] = std::move(indices);
    component->_aabb = std::move(aabb);
    component->completeTopology();

    return component;
}

void PAG::Model3D::processNode(aiNode* node, const aiScene* scene, const std::string& folder)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        _components.push_back(std::unique_ptr<Component>(this->processMesh(mesh, scene, folder)));
        _aabb.update(_components[_components.size() - 1]->_aabb);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        this->processNode(node->mChildren[i], scene, folder);
    }
}

void PAG::Model3D::writeBinaryFile(const std::string& path)
{
    std::ofstream fout(path, std::ios::out | std::ios::binary);
    if (!fout.is_open())
    {
        std::cout << "Failed to write the binary file!" << std::endl;
    }

    size_t numComponents = _components.size();
    fout.write((char*)&numComponents, sizeof(size_t));

    for (auto& component: _components)
    {
        size_t numVertices = component->_vertices.size();

        fout.write((char*)&numVertices, sizeof(size_t));
        fout.write((char*)component->_vertices.data(), numVertices * sizeof(VAO::Vertex));

        for (int topology = 0; topology < VAO::NUM_IBOS; ++topology)
        {
            size_t numIndices = component->_indices[topology].size();
            fout.write((char*)&numIndices, sizeof(size_t));
            if (numIndices) 
                fout.write((char*)component->_indices[topology].data(), numIndices * sizeof(GLuint));
        }

        fout.write((char*)(&component->_aabb), sizeof(AABB));
    }

    fout.close();
}

PAG::Model3D::MatrixRenderInformation::MatrixRenderInformation()
{
    for (mat4& matrix : _matrix)
    {
        matrix = mat4(1.0f);
    }
}

void PAG::Model3D::MatrixRenderInformation::undoMatrix(MatrixType type)
{
    if (_heapMatrices[type].empty())
    {
        _matrix[type] = mat4(1.0f);
    }
    else
    {
        _matrix[type] = *(--_heapMatrices[type].end());
        _heapMatrices[type].erase(--_heapMatrices[type].end());
    }
}

void PAG::Model3D::Component::completeTopology()
{
    if (!this->_indices[VAO::IBO_TRIANGLE].empty())
    {
        this->generatePointCloud();
        this->generateWireframe();
    }

    if (!this->_indices[VAO::IBO_LINE].empty())
    {
        this->generatePointCloud();
    }
}

void PAG::Model3D::Component::generateWireframe()
{
    std::unordered_map<int, std::unordered_set<int>> segmentIncluded;
    static auto isIncluded = [&](int index1, int index2) -> bool
    {
        std::unordered_map<int, std::unordered_set<int>>::iterator it;

        if ((it = segmentIncluded.find(index1)) != segmentIncluded.end())
        {
            if (it->second.find(index2) != it->second.end())
            {
                return true;
            }
        }

        if ((it = segmentIncluded.find(index2)) != segmentIncluded.end())
        {
            if (it->second.find(index1) != it->second.end())
            {
                return true;
            }
        }

        return false;
    };

    const size_t numTriangles = this->_indices[VAO::IBO_TRIANGLE].size();

    for (size_t i = 0; i < numTriangles; i += 3)
    {
        for (size_t j = i; (j <= (i + 1)) && (j < numTriangles - 1); ++j)
        {
            if (!isIncluded(this->_indices[VAO::IBO_TRIANGLE][j], this->_indices[VAO::IBO_TRIANGLE][j + 1]))
            {
                this->_indices[VAO::IBO_LINE].push_back(this->_indices[VAO::IBO_TRIANGLE][j]);
                this->_indices[VAO::IBO_LINE].push_back(this->_indices[VAO::IBO_TRIANGLE][j + 1]);
                this->_indices[VAO::IBO_LINE].push_back(RESTART_PRIMITIVE_INDEX);
            }
        }
    }
}

void PAG::Model3D::Component::generatePointCloud()
{
    this->_indices[VAO::IBO_POINT].resize(this->_vertices.size());
    std::iota(this->_indices[VAO::IBO_POINT].begin(), this->_indices[VAO::IBO_POINT].end(), 0);
}
