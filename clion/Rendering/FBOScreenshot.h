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

#include "FBO.h"
#include "Image.h"

namespace PAG
{
	class FBOScreenshot : public FBO
	{
	protected:
		GLuint _multisampledFBO, _colorBufferID;
		GLuint _mColorBufferID, _mDepthBufferID;

	public:
		FBOScreenshot(const uint16_t width, const uint16_t height);
		virtual ~FBOScreenshot();

		virtual GLuint getId() const { return _multisampledFBO; }
		PAG::Image* getImage() const;

		virtual void bindFBO();
		virtual void modifySize(const uint16_t width, const uint16_t height);
		void saveImage(const std::string& filename);
	};
}



