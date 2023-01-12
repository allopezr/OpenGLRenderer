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
#include "CameraGuiAdapter.h"
#include "ImGuizmo.h"
#include "SceneContent.h"
#include "Singleton.h"

namespace PAG
{
	class GUI: public Singleton<GUI>
	{
		friend class Singleton<GUI>;

	protected:
		enum MenuButtons { RENDERING, MODELS, CAMERA, LIGHT, SCREENSHOT, NUM_GUI_MENU_BUTTONS };
		enum FileDialog { OPEN_MESH, NONE };
		inline static std::string DEFAULT_DIRECTORY = ".";
		inline static std::vector<std::string> FILE_DIALOG_TEXT { "Choose Model" };
		inline static std::vector<std::string> FILE_DIALOG_EXTENSION { ".obj, .gltf, .fbx" };

		ApplicationState*									_appState;
		CameraGuiAdapter*									_cameraGuiAdapter;
		FileDialog											_fileDialog;
		Model3D::Component*									_modelCompSelected;
		std::string											_path, _lastDirectory;
		bool*												_showMenuButtons;

		// ImGuizmo
		ImGuizmo::OPERATION									_currentGizmoOperation;
		ImGuizmo::MODE										_currentGizmoMode;

	protected:
		void editTransform(ImGuizmo::OPERATION& operation, ImGuizmo::MODE& mode);
		void loadFonts();
		void loadImGUIStyle();
		void processSelectedFile(FileDialog fileDialog, const std::string& filename, SceneContent* sceneContent);
		void renderGuizmo(Model3D::Component* component, SceneContent* sceneContent);
		void showCameraMenu(SceneContent* sceneContent);
		void showFileDialog(SceneContent* sceneContent);
		void showLightMenu(SceneContent* sceneContent);
		void showModelMenu(SceneContent* sceneContent);
		void showRenderingMenu(SceneContent* sceneContent);
		void showScreenshotMenu(SceneContent* sceneContent);

	protected:
		GUI();

	public:
		virtual ~GUI();

		void initialize(GLFWwindow* window, const int openGLMinorVersion);
		void render(SceneContent* sceneContent);

		uint16_t getFrameRate() { return static_cast<uint16_t>(ImGui::GetIO().Framerate); }
		bool isMouseActive() { return ImGui::GetIO().WantCaptureMouse; }
	};
}

