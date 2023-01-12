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

class AABB
{
protected:
	vec3	_max, _min;		

public:
	AABB(const vec3& min = vec3(INFINITY), const vec3& max = vec3(-INFINITY));
	AABB(const AABB& aabb);
	virtual ~AABB();
	AABB& operator=(const AABB& aabb);

	vec3 center() const { return (_max + _min) / 2.0f; }
	AABB dot(const mat4& matrix);
	vec3 extent() const { return _max - center(); }
	vec3 max() const { return _max; }
	vec3 min() const { return _min; }
	vec3 size() const { return _max - _min; }

	void update(const AABB& aabb);
	void update(const vec3& point);

	friend std::ostream& operator<<(std::ostream& os, const AABB& aabb);
};

