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

#include <chrono>
#include <iostream>

/**
*	@file ChronoUtilities.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 09/05/2019
*/

/**
*	@brief Utilities which help us to measure execution time.
*	@author Alfonso López Ruiz.
*/
namespace ChronoUtilities
{
	//!< Units we can use to return the measured time
	enum TimeUnit: int
	{
		SECONDS = 1000000000, MILLISECONDS = 1000000, MICROSECONDS = 1000, NANOSECONDS = 1
	};

	//!< Private members
	namespace
	{
		std::chrono::high_resolution_clock::time_point _initTime;
	}

	/**
	*	@return Measured time in the selected time unit since the clock was started. By default the time unit is milliseconds.
	*/
	long long getDuration(const TimeUnit timeUnit = ChronoUtilities::MILLISECONDS);

	/**
	*	@brief Starts the clock so we can execute whatever we want and measure the used time.
	*/
	void initChrono();
}

inline long long ChronoUtilities::getDuration(const TimeUnit timeUnit)
{
	std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
	long long measuredTime = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - ChronoUtilities::_initTime).count();
	
	return measuredTime / timeUnit;
}

inline void ChronoUtilities::initChrono()
{
	ChronoUtilities::_initTime = std::chrono::high_resolution_clock::now();
}
