/*   Copyright (C) 2023 Lidia Ortega Alvarado, Alfonso Lopez Ruiz
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see https://github.com/AlfonsoLRz/AG2223.
*/

#pragma once

#include "ApplicationState.h"
#include "Camera.h"
#include "FBOScreenshot.h"
#include "GUI.h"
#include "InclDraw2D.h"
#include "InclGeom2D.h"
#include "InputManager.h"
#include "Model3D.h"
#include "RenderingShader.h"
#include "SceneContent.h"
#include "Singleton.h"

namespace PAG
{
	class Renderer : public Singleton<Renderer>, public PAG::ResizeListener, public PAG::ScreenshotListener
	{
		friend class Singleton<Renderer>;

	private:	
		ApplicationState*							_appState;
		SceneContent*								_content;
		GUI*										_gui;
		FBOScreenshot*								_screenshoter;
		RenderingShader*							_triangleShader, *_lineShader, *_pointShader;

	private:
		Renderer();

		void renderLine(Model3D::MatrixRenderInformation* matrixInformation);
		void renderPoint(Model3D::MatrixRenderInformation* matrixInformation);
		void renderTriangle(Model3D::MatrixRenderInformation* matrixInformation);
		void transferLightUniforms(RenderingShader* shader);

	public:
		virtual ~Renderer();
		void createModels();
		void createShaderProgram();
		Camera* getCamera() { return _content->_camera[_appState->_selectedCamera].get(); }
		void prepareOpenGL(uint16_t width, uint16_t height, ApplicationState* appState);
		void removeModel();
		void render(float alpha = 1.0f, bool renderGui = true, bool bindScreenshoter = false);
		virtual void resizeEvent(uint16_t width, uint16_t height);
		virtual void screenshotEvent(const ScreenshotEvent& event);
	};
}

