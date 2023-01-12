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

#include "Singleton.h"
#include "Texture.h"

namespace PAG
{
	class TextureList : public Singleton<TextureList>
	{
		friend class Singleton<TextureList>;

	private:
		struct ColorHash {
			std::size_t operator()(const vec4& color) const
			{
				glm::ivec4 iColor = color * 256.0f;
				return static_cast<size_t>(iColor.x + iColor.y * 256 + iColor.z * 512 + iColor.w + 1024);
			}
		};

		struct ColorEqual {
			bool operator()(const vec4& c1, const vec4& c2) const
			{
				return glm::distance(c1, c2) < glm::epsilon<float>();
			}
		};

	private:
		std::unordered_map<vec4, PAG::Texture*, ColorHash, ColorEqual>	_colorTexture;
		std::unordered_map<std::string, PAG::Texture*>					_imageTexture;

	private:
		TextureList();

	public:
		virtual ~TextureList();

		PAG::Texture* getTexture(const vec4& color);
		PAG::Texture* getTexture(const std::string& path);
		void saveTexture(const vec4& color, PAG::Texture* texture);
		void saveTexture(const std::string& path, PAG::Texture* texture);
	};
}

