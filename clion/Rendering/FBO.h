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

#include "Image.h"

namespace PAG
{
	class FBO
	{
	protected:
		GLuint	_id;
		ivec2	_size;

	protected:
		void checkFBOstate();

	public:
		FBO(const uint16_t width, const uint16_t height);
		virtual ~FBO();

		virtual GLuint getId() const { return _id; }
		ivec2 getSize() const { return _size; }

		virtual void bindFBO() = 0;
		virtual void modifySize(const uint16_t width, const uint16_t height);

		void threadedWriteImage(std::vector<GLubyte>* pixels, const std::string& filename, const uint16_t width, const uint16_t height);
	};
}

