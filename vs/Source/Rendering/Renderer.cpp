#include "stdafx.h"
#include "Renderer.h"

#include "ChronoUtilities.h"
#include "DrawMesh.h"
#include "DrawPointCloud.h"
#include "DrawSegment.h"
#include "InputManager.h"
#include "PointCloud.h"
#include "ShaderProgramDB.h"
#include "RandomUtilities.h"
#include "SegmentLine.h"

// Public methods

PAG::Renderer::Renderer(): _appState(nullptr), _content(nullptr), _screenshoter(nullptr), _triangleShader(nullptr), _lineShader(nullptr), _pointShader(nullptr)
{
    _gui = GUI::getInstance();
}

void PAG::Renderer::buildFooScene()
{
    vec2 minBoundaries = vec2(-1.2, -.5), maxBoundaries = vec2(-minBoundaries);

    // Spheric randomized point cloud
    int numPoints = 200, numPointClouds = 6;
    
    for (int pcIdx = 0; pcIdx < numPointClouds; ++pcIdx)
    {
        PointCloud* pointCloud = new PointCloud;
        vec3 sphereCenter = vec3(
            RandomUtilities::getUniformRandom(minBoundaries.x, maxBoundaries.x),
            RandomUtilities::getUniformRandom(minBoundaries.y, maxBoundaries.y),
            RandomUtilities::getUniformRandom(minBoundaries.x, maxBoundaries.x));

        for (int idx = 0; idx < numPoints; ++idx)
        {
            vec3 rand = RandomUtilities::getUniformRandomInUnitSphere() / 3.0f + sphereCenter;
            pointCloud->addPoint(Point(rand.x, rand.y));
        }

        _content->addNewModel((new DrawPointCloud(*pointCloud))->setPointColor(RandomUtilities::getUniformRandomColor()));
        delete pointCloud;
    }

    // Random segments
    int numSegments = 8;

    for (int segmentIdx = 0; segmentIdx < numSegments; ++segmentIdx)
    {
        Point a(RandomUtilities::getUniformRandom(minBoundaries.x, maxBoundaries.x), RandomUtilities::getUniformRandom(minBoundaries.y, maxBoundaries.y));
        Point b(RandomUtilities::getUniformRandom(minBoundaries.x, maxBoundaries.x), RandomUtilities::getUniformRandom(minBoundaries.y, maxBoundaries.y));
        SegmentLine* segment = new SegmentLine(a, b);

        _content->addNewModel((new DrawSegment(*segment))->setLineColor(RandomUtilities::getUniformRandomColor()));
        delete segment;
    }

    // Random triangles
    int numTriangles = 30;
    float alpha = 2 * glm::pi<float>() / static_cast<float>(numTriangles);

    for (int triangleIdx = 0; triangleIdx < numTriangles; ++triangleIdx)
    {
        float rand_b = RandomUtilities::getUniformRandom(.5f, .9f), rand_c = RandomUtilities::getUniformRandom(.6f, .8f);
        Vect2d a(.0f, .0f);
        Vect2d b(glm::cos(alpha * triangleIdx) * rand_b, glm::sin(alpha * triangleIdx) * rand_b);
        Vect2d c(glm::cos(alpha * (triangleIdx + 1)) * rand_c, glm::sin(alpha * (triangleIdx + 1)) * rand_c);
        Triangle* triangle = new Triangle(a, b, c);

        _content->addNewModel((new DrawTriangle(*triangle))->setLineColor(RandomUtilities::getUniformRandomColor())->setTriangleColor(vec4(RandomUtilities::getUniformRandomColor(), 1.0f)));
        delete triangle;
    }
}

void PAG::Renderer::renderLine(Model3D::MatrixRenderInformation* matrixInformation)
{
    _lineShader->use();

    for (auto& model : _content->_model)
    {
        model->draw(_lineShader, matrixInformation, _appState, GL_LINES);
    }
}

void PAG::Renderer::renderPoint(Model3D::MatrixRenderInformation* matrixInformation)
{
    _pointShader->use();

    for (auto& model : _content->_model)
    {
        model->draw(_pointShader, matrixInformation, _appState, GL_POINTS);
    }
}

void PAG::Renderer::renderTriangle(Model3D::MatrixRenderInformation* matrixInformation)
{
    _triangleShader->use();
    this->transferLightUniforms(_triangleShader);
    _triangleShader->setUniform("gamma", _appState->_gamma);

    for (auto& model : _content->_model)
    {
        model->draw(_triangleShader, matrixInformation, _appState, GL_TRIANGLES);
    }
}

void PAG::Renderer::transferLightUniforms(RenderingShader* shader)
{
    shader->setUniform("lightPosition", _appState->_lightPosition);
    shader->setUniform("Ia", _appState->_Ia);
    shader->setUniform("Id", _appState->_Id);
    shader->setUniform("Is", _appState->_Is);
}

// Private methods

PAG::Renderer::~Renderer()
{
    delete _screenshoter;
}

void PAG::Renderer::createModels()
{
    auto model = (new DrawMesh())->loadModelOBJ("Assets/Models/Ajax.obj");
    model->moveGeometryToOrigin(model->getModelMatrix(), 10.0f);
    _content->addNewModel(model);

    this->buildFooScene();
}

void PAG::Renderer::createShaderProgram()
{
    _pointShader = ShaderProgramDB::getInstance()->getShader(ShaderProgramDB::POINT_RENDERING);
    _lineShader = ShaderProgramDB::getInstance()->getShader(ShaderProgramDB::LINE_RENDERING);
    _triangleShader = ShaderProgramDB::getInstance()->getShader(ShaderProgramDB::TRIANGLE_RENDERING);
}

void PAG::Renderer::prepareOpenGL(uint16_t width, uint16_t height, ApplicationState* appState)
{
    _appState = appState;
    _appState->_viewportSize = ivec2(width, height);
    _content = new SceneContent{};
    _screenshoter = new FBOScreenshot(width, height);

    // - Establecemos un gris medio como color con el que se borrará el frame buffer.
    // No tiene por qué ejecutarse en cada paso por el ciclo de eventos.
    glClearColor(_appState->_backgroundColor.x, _appState->_backgroundColor.y, _appState->_backgroundColor.z, 1.0f);

    // - Le decimos a OpenGL que tenga en cuenta la profundidad a la hora de dibujar.
    // No tiene por qué ejecutarse en cada paso por el ciclo de eventos.
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_MULTISAMPLE);

    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(RESTART_PRIMITIVE_INDEX);

    glEnable(GL_PROGRAM_POINT_SIZE);

    glEnable(GL_POLYGON_OFFSET_FILL);

    _content->_camera.push_back(std::unique_ptr<Camera>(new Camera(width, height)));
    this->createShaderProgram();
    this->createModels();

    if (_content->_model.size())
    {
        _content->_camera[_appState->_selectedCamera]->track(_content->_model[0].get());
        _content->_camera[_appState->_selectedCamera]->saveCamera();
    }

    // Observer
    InputManager* inputManager = InputManager::getInstance();
    inputManager->suscribeResize(this);
    inputManager->suscribeScreenshot(this);

    this->resizeEvent(_appState->_viewportSize.x, _appState->_viewportSize.y);
}

void PAG::Renderer::removeModel()
{
    if (!_content->_model.empty())
        _content->_model.erase(_content->_model.end() - 1);
}

void PAG::Renderer::resizeEvent(uint16_t width, uint16_t height)
{
    glViewport(0, 0, width, height);

    _appState->_viewportSize = ivec2(width, height);
    _content->_camera[_appState->_selectedCamera]->setRaspect(width, height);
}

void PAG::Renderer::screenshotEvent(const ScreenshotEvent& event)
{
    if (event._type == ScreenshotListener::RGBA)
    {
        const ivec2 size = _appState->_viewportSize;
        const ivec2 newSize = ivec2(_appState->_viewportSize.x * _appState->_screenshotFactor, _appState->_viewportSize.y * _appState->_screenshotFactor);

        this->resizeEvent(newSize.x, newSize.y);
        this->render(.0f, false, true);
        _screenshoter->saveImage(_appState->_screenshotFilenameBuffer);

        this->resizeEvent(size.x, size.y);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}

void PAG::Renderer::render(float alpha, bool renderGui, bool bindScreenshoter)
{
    Model3D::MatrixRenderInformation matrixInformation;
    glm::mat4 bias = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));

    matrixInformation.setMatrix(Model3D::MatrixRenderInformation::VIEW, _content->_camera[0]->getViewMatrix());
    matrixInformation.setMatrix(Model3D::MatrixRenderInformation::VIEW_PROJECTION, _content->_camera[0]->getViewProjectionMatrix());

    if (bindScreenshoter)
    {
        _screenshoter->modifySize(_appState->_viewportSize.x, _appState->_viewportSize.y);
        _screenshoter->bindFBO();
    }

    glClearColor(_appState->_backgroundColor.x, _appState->_backgroundColor.y, _appState->_backgroundColor.z, alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPolygonOffset(1.0f, 1.0f);

    if (_appState->_activeRendering[VAO::IBO_TRIANGLE])
    {
        this->renderTriangle(&matrixInformation);
    }

    if (_appState->_activeRendering[VAO::IBO_LINE])
    {
        this->renderLine(&matrixInformation);
    }

    if (_appState->_activeRendering[VAO::IBO_POINT])
    {
        this->renderPoint(&matrixInformation);
    }

    glPolygonOffset(.0f, .0f);

    if (renderGui)
        _gui->render(_content);

    _appState->_numFps = _gui->getFrameRate();
}
