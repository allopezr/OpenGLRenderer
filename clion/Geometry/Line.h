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

/* 
 *	File:   Line.h
 *	Author: lidia
 *
 *	Created on 18 de enero de 2021, 19:39
 */

#include "SegmentLine.h"

class Line : public SegmentLine
{
public:
	/**
	*	@brief Constructor.
	*/
	Line(const Point& a, const Point& b);

	/**
	*	@brief Copy constructor.
	*/
	Line(const Line& s);

	/**
	*	@brief Destructor.
	*/
	virtual ~Line();

	/**
	*	@brief Distance from a point defined by 'vector' to this line.
	*/
	double distancePointLine(Vect2d& v);

	/**
	*	@brief Checks if the specified line intersects with this one.
	*	@param intersection If both lines intersect, then this point is the intersection. Otherwise this point is not valid.
	*/
	//virtual bool intersects(Line& line, Vect2d& intersection);

	/**
	*	@brief Checks if the specified rayline intersects with this line.
	*	@param intersection If rayline and line intersect, then this point is the intersection. Otherwise this point is not valid.
	*/
	//virtual bool intersects(RayLine& rayline, Vect2d& intersection);

	/**
	*	@brief Checks if the specified segment intersects with this line.
	*	@param intersection If line and segment intersect, then this point is the intersection. Otherwise this point is not valid.
	*/
	//virtual bool intersects(SegmentLine& segment, Vect2d& intersection);

	/**
	*	@brief Checks if a segment line generates an incorrect intersection.
	*/
	bool incorrectSegmentIntersection(SegmentLine& l);

	/**
	*	@brief Checks if the parameter t is valid to obtain a point for a line (it's always valid, we just need to override).
	*/
	virtual bool isTValid(double t) { return true; }

	/**
	*	@brief Assignment operator.
	*/
	virtual Line& operator=(const Line& line);

	/**
	*	@brief Overriding cout call.
	*/
	friend std::ostream& operator<<(std::ostream& os, const Line& line);

	/**
	*	@brief Checks if a segment intersects with this line (proper intersection).
	*/
	bool segmentIntersection(SegmentLine& l);
};

