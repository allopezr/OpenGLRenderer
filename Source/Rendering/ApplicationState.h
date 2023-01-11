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

#include "stdafx.h"
#include "Texture.h"
#include "VAO.h"


namespace PAG
{
	struct ApplicationState
	{
		// Application
		vec3							_backgroundColor;								
		float							_materialScattering;								
		uint16_t						_numFps;											
		uint8_t							_selectedCamera;								
		ivec2							_viewportSize;										

		// Screenshot
		char							_screenshotFilenameBuffer[60];				
		float							_screenshotFactor;										

		// Ligthing
		vec3							_lightPosition, _Ia, _Id, _Is;	
		float							_gamma;

		// Topology
		bool							_activeRendering[VAO::NUM_IBOS];

		ApplicationState()
		{
			_backgroundColor = vec3(.6f);
			_materialScattering = 1.0f;
			_numFps = 0;
			_selectedCamera = 0;
			_viewportSize = vec3(0);

			std::strcpy(_screenshotFilenameBuffer, "ScreenshotRGBA.png");
			_screenshotFactor = 3.0f;

			for (int i = 0; i < VAO::NUM_IBOS; ++i) _activeRendering[i] = i == VAO::IBO_TRIANGLE;

			_lightPosition = vec3(.0f);
			_Ia = vec3(.6f);
			_Id = vec3(1.0f);
			_Is = vec3(1.0f);
			_gamma = 1.3f;
		}
	};
}