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

#include "stdafx.h"

template<typename T>
class Singleton
{
protected:
	static std::unique_ptr<T> _instance;		

protected:
	Singleton() {};
	~Singleton() {};

public:
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton) = delete;
	static T* getInstance();
};

// Static members initialization

template<typename T>
std::unique_ptr<T> Singleton<T>::_instance;

// Public methods

template<typename T>
T* Singleton<T>::getInstance()
{
	if (!_instance.get())
	{
		_instance = std::unique_ptr<T>(new T());
	}

	return _instance.get();
}

