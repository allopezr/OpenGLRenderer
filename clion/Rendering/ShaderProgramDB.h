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

#include "RenderingShader.h"
#include "Singleton.h"

namespace PAG
{
	class ShaderProgramDB : public Singleton<ShaderProgramDB>
	{
		friend class Singleton<ShaderProgramDB>;

	private:
		static std::unordered_map<uint8_t, std::string>								RENDERING_SHADER_PATH;
		static std::unordered_map<uint8_t, std::unique_ptr<PAG::RenderingShader>>	_renderingShader;

	public:
		enum RenderingShaderId
		{
			POINT_RENDERING,
			LINE_RENDERING,
			TRIANGLE_RENDERING,
		};

	private:
		ShaderProgramDB();

	public:
		virtual ~ShaderProgramDB();
		RenderingShader* getShader(RenderingShaderId shaderId);
	};
}

