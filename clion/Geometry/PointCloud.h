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
 * File:   PointCloud.h
 * Author: lidia
 *
 * Created on 19 de enero de 2021, 12:46
 */

#include "Point.h"


class PointCloud
{
protected:
	std::vector<Point> _points;

public:
	/**
	*	@brief Default constructor. Creates an empty point cloud.
	*/
	PointCloud();

	/**
	*	@brief Constructor of a point cloud of random form giving the total number of points and the maximum range of those points ((-max_x, max_x), or (-max_y, max_y)).
	*/
	PointCloud(int size, float max_x, float max_y);

	/**
	*	@brief Constructor of a point cloud from the coordinates of points stored in file.
	*/
	PointCloud(const std::string& filename);

	/**
	*	@brief Destructor.
	*/
	~PointCloud();

	/**
	*	@brief Adds a point to the point cloud.
	*/
	void addPoint(Point& p);

	/**
	*	@brief Returns the points that minimizes the distance to any point from the cloud.
	*/
	Point centralPoint();

	/**
	*	@brief Deletes a point identified by its index.
	*/
	void deletePoint(int index);

	/**
	*	@brief Returns the points that defines the edges of the point cloud (min x, max x, min y and max y).
	*/
	void getEdges(Point& minPoint_x, Point& minPoint_y, Point& maxPoint_x, Point& maxPoint_y);

	/**
	*	@brief Returns the point in an specific index.
	*/
	Point getPoint(int position);

	/**
	*	@brief Returns all the available points as a vector.
	*/
	std::vector<Point> getPoints() { return _points; }

	/**
	*	@brief Assignment operator.
	*/
	PointCloud& operator=(const PointCloud& pointCloud);

	/**
	*	@brief Saves the cloud of points in file with the same format used by the constructor.
	*/
	void save(const std::string& filename);

	/**
	*	@brief Returns the size of the point cloud.
	*/
	size_t size() { return _points.size(); }
};

