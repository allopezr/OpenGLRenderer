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
#include "Singleton.h"

namespace PAG
{
	class ResizeListener
	{
	public:
		virtual void resizeEvent(uint16_t width, uint16_t height) = 0;
	};

	class ScreenshotListener
	{
	public:
		enum ScreenshotType { RGBA };

		struct ScreenshotEvent
		{
			ScreenshotType _type;
		};

	public:
		virtual void screenshotEvent(const ScreenshotEvent& event) = 0;
	};

	class InputManager: public Singleton<InputManager>
	{
		friend class Singleton<InputManager>;

	private:
		enum Events
		{
			SCREENSHOT,
			BOOM, DOLLY, DOLLY_SPEED_UP, ORBIT_XZ, ORBIT_Y, PAN, RESET, TILT, TRUCK, ZOOM, 	
			ALTER_POINT, ALTER_LINE, ALTER_TRIANGLE,
			NUM_EVENTS
		};

	private:
		static ApplicationState			_applicationState;
		static const vec2				_defaultCursorPosition;						

	private:
		std::vector<ivec2>				_eventKey;
		vec2							_lastCursorPosition;							
		bool							_leftClickPressed, _rightClickPressed;	
		std::vector<GLuint>				_moves;
		float							_movementMultiplier;
		std::vector<float>				_moveSpeed;
		float							_moveSpeedUp;
		GLFWwindow*						_window;

	private:
		// Observer pattern
		std::vector<ResizeListener*>						_resizeListeners;
		std::vector<ScreenshotListener::ScreenshotEvent>	_screenshotEvents;
		std::vector<ScreenshotListener*>					_screenshotListeners;

	private:
		InputManager();
		void buildMoveRelatedBuffers();
		bool checkPanTilt(const float xPos, const float yPos);
		void processPressedKeyEvent(int key, int mods);
		void processReleasedKeyEvent(int key, int mods);

		static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void mouseCursorCallback(GLFWwindow* window, double xpos, double ypos);
		static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	public:
		virtual ~InputManager();
		static ApplicationState* getApplicationState() { return &_applicationState; }
		static void windowRefreshCallback(GLFWwindow* window);
		void init(GLFWwindow* window);

	public:
		void pushScreenshotEvent(const ScreenshotListener::ScreenshotEvent& event);
		void suscribeResize(ResizeListener* listener);
		void suscribeScreenshot(ScreenshotListener* listener);
	};
}

