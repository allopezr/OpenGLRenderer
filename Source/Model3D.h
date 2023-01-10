#pragma once

#include "AABB.h"
#include "ApplicationState.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "RenderingShader.h"
#include "Texture.h"
#include "TextureList.h"
#include "VAO.h"

#define BINARY_EXTENSION ".bin"
#define FBX_EXTENSION ".fbx"
#define GLTF_EXTENSION ".gltf"
#define OBJ_EXTENSION ".obj"

namespace PAG
{
	class Model3D
	{
		friend class GUI;

	protected:
		struct Material
		{
			vec3		_kdColor, _ksColor;
			float		_metallic, _roughnessK;
			Texture*	_kadTexture;
			bool		_useUniformColor;

			Material() : _kdColor(1.0f, .0f, .0f), _ksColor(.5f), _kadTexture(nullptr), _useUniformColor(true), _metallic(.7f), _roughnessK(.3f) {}
		};

	public:
		struct Component
		{
			bool							_enabled;
			std::string						_name;

			std::vector<VAO::Vertex>		_vertices;
			std::vector<GLuint>				_indices[VAO::NUM_IBOS];
			VAO*							_vao;
			AABB							_aabb;

			Material						_material;

			Component(VAO* vao = nullptr) { _enabled = true; _vao = vao; }
			~Component() { delete _vao; _vao = nullptr; }

			void completeTopology();
			void generateWireframe();
			void generatePointCloud();
		};

	public:
		struct MatrixRenderInformation
		{
			enum MatrixType { MODEL, VIEW, VIEW_PROJECTION };
			
			mat4				_matrix[VIEW_PROJECTION + 1];
			std::vector<mat4>	_heapMatrices[VIEW_PROJECTION + 1];

			MatrixRenderInformation();
			mat4 multiplyMatrix(MatrixType tMatrix, const mat4& matrix) { this->saveMatrix(tMatrix); return _matrix[tMatrix] *= matrix; }
			void saveMatrix(MatrixType tMatrix) { _heapMatrices[tMatrix].push_back(_matrix[tMatrix]); }
			void setMatrix(MatrixType tMatrix, const mat4& matrix) { this->saveMatrix(tMatrix); _matrix[tMatrix] = matrix; }
			void undoMatrix(MatrixType type);
		};

	protected:
		static std::string							CHECKER_PATTERN_PATH;

	protected:
		AABB										_aabb;
		Assimp::Importer							_assimpImporter;
		std::vector<std::unique_ptr<Component>>		_components;
		mat4										_modelMatrix;
		const aiScene*								_scene;

	protected:
		void buildVao(Component* component);
		PAG::Texture* getTexture(const vec4& color, TextureList* textureList);
		void loadModelBinaryFile(const std::string& path);
		Component* processMesh(aiMesh* mesh, const aiScene* scene, const std::string& folder);
		void processNode(aiNode* node, const aiScene* scene, const std::string& folder);
		void writeBinaryFile(const std::string& path);

	public:
		Model3D();
		virtual ~Model3D();

		bool belongsModel(Component* component);
		virtual void draw(RenderingShader* shader, MatrixRenderInformation* matrixInformation, ApplicationState* appState, GLuint primitive);
		AABB getAABB() { return _aabb.dot(_modelMatrix); }
		mat4 getModelMatrix() { return _modelMatrix; }
		Model3D* loadModelOBJ(const std::string& path);
		void moveGeometryToOrigin(const mat4& origMatrix = mat4(1.0f), float maxScale = FLT_MAX);
		void setModelMatrix(const mat4& modelMatrix) { _modelMatrix = modelMatrix; }
		void setTexture(const vec3& color);
		void setTexture(Texture* texture);
	};
}

