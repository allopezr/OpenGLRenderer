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

#include <assimp/scene.h>
#include "Image.h"
#include "ShaderProgram.h"

namespace PAG
{
	class Texture
	{
	protected:
		const static GLuint MIN_FILTER;
		const static GLuint MAG_FILTER;
		const static GLuint WRAP_S;
		const static GLuint WRAP_T;
		const static GLuint WRAP_R;

	protected:
		GLuint		_id;
		vec4		_color;
		std::string _filename;

	public:
		Texture(Image* image, const GLuint wrapS = WRAP_S, const GLuint wrapT = WRAP_T, const GLuint minFilter = MIN_FILTER, const GLuint magFilter = MAG_FILTER);
		Texture(const vec4& color);
		virtual ~Texture();

		void applyTexture(PAG::ShaderProgram* shader, const GLint id, const std::string& shaderVariable);

		vec4 getColor() { return _color; }
		std::string getFilename() { return _filename; }
	};
}