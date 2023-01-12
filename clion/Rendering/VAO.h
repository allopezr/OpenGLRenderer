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

#include "boost/variant.hpp"

#define NUM_BONES_PER_VERTEX 4
#define RESTART_PRIMITIVE_INDEX 0xFFFFFFFF

namespace PAG
{
	class VAO
	{
	public:
		enum VBO_slots
		{
			VBO_POSITION, VBO_NORMAL, VBO_TEXT_COORD, VBO_TANGENT, VBO_BITANGENT, NUM_VBOS
		};

		enum IBO_slots
		{
			IBO_POINT,
			IBO_LINE,
			IBO_TRIANGLE,
			NUM_IBOS
		};

		struct Vertex
		{
			vec3		_position, _normal;
			vec2		_textCoord;
		};

	private:
		GLuint				_vao;						
		std::vector<GLuint> _vbos;					
		std::vector<GLuint> _ibos;	

	private:
		void defineInterleavedVBO(GLuint vboId);
		void defineNonInterleaveVBO(GLuint vboId, size_t structSize, GLuint elementType, uint8_t slot);

	public:
		VAO(bool interleaved = true);
		virtual ~VAO();

		void drawObject(IBO_slots ibo, GLuint openGLPrimitive, GLuint numIndices);

		template<typename T>
		void setVBOData(VBO_slots vbo, T* geometryData, GLuint size, GLuint changeFrequency = GL_STATIC_DRAW);
		void setVBOData(const std::vector<Vertex>& vertices, GLuint changeFrequency = GL_STATIC_DRAW);
		void setIBOData(IBO_slots ibo, const std::vector<GLuint>& indices, GLuint changeFrequency = GL_STATIC_DRAW);
	};

	template<typename T>
	inline void VAO::setVBOData(VBO_slots vbo, T* geometryData, GLuint size, GLuint changeFrequency)
	{
		glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbos[vbo]);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(T), geometryData, changeFrequency);
	}
}

