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
 *	File:   Triangle.h
 *	Author: lidia
 *
 *	Created on 5 de enero de 2021, 13:57
 */

#include "Vect2d.h"

class Triangle
{
protected:
	Vect2d _a, _b, _c;
   
public:   
	friend class DrawTriangle;  //evitar
   
	/**
	*   @brief Constructor . 
	*   @param aa vertex.
	*   @param bb vertex.
	*   @param cc vertex.
	*/
	Triangle (Vect2d &aa, Vect2d &bb, Vect2d &cc);
   
	/**
	*   @brief Copy constructor.
	*   @param t.
	*/  
	Triangle (const Triangle &t);
   
	/**
	*	@brief getter. 
	*	@return vertex A. 
	*/ 
   Vect2d getA() {return _a;} 
   
	/**
	*	@brief getter.
	*   @return vertex B.
	*/
	Vect2d getB() { return _b; } 
  
	/**
	*   @brief getter.
	*   @return vertex C.
	*/
	Vect2d getC() { return _c; }   
};

