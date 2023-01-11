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

namespace PAG
{
	class Image
	{
	protected:
		std::string					_filename;
		std::vector<unsigned char>	_image;
		unsigned					_width, _height, _depth;

	public:
		Image(const std::string& filename);
		Image(unsigned char* image, const uint16_t width, const uint16_t height, const uint8_t depth);
		~Image();

		void flipImageVertically();
		static void flipImageVertically(std::vector<unsigned char>& image, const uint16_t width, const uint16_t height, const uint8_t depth);
		bool saveImage(const std::string& filename);

		unsigned char* bits() { return _image.data(); }
		int getDepth() const { return _depth; }
		std::string getFilename() { return _filename; }
		int getHeight() const { return _height; }
		int getWidth() const { return _width; }
	};
}



