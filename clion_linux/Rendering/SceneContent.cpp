#include "stdafx.h"
#include "SceneContent.h"

AlgGeom::SceneContent::SceneContent()
{
}

AlgGeom::SceneContent::~SceneContent()
{
	_camera.clear();
	_model.clear();
}

void AlgGeom::SceneContent::addNewCamera(ApplicationState* appState)
{
	_camera.push_back(std::unique_ptr<Camera>(new Camera(appState->_viewportSize.x, appState->_viewportSize.y)));
}

void AlgGeom::SceneContent::addNewModel(Model3D* model)
{	
	_sceneAABB.update(model->getAABB());
	_model.push_back(std::unique_ptr<Model3D>(model));
}

AlgGeom::Model3D* AlgGeom::SceneContent::getModel(Model3D::Component* component)
{
	for (auto& model : _model)
	{
		if (model->belongsModel(component))
			return model.get();
	}

	return nullptr;
}
