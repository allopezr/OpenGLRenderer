#include "stdafx.h"
#include "Line.h"

#include "RayLine.h"
#include "SegmentLine.h"


Line::Line(const Point & a, const Point & b) : SegmentLine(a, b)
{
}

Line::Line(const Line & s) : SegmentLine(s)
{
}

Line::~Line()
{
}

double Line::distancePointLine(Vect2d& v)
{
	return 0.0;
}

bool Line::incorrectSegmentIntersection(SegmentLine& l)
{
	return false;
}

Line & Line::operator=(const Line & line)
{
	if (this != &line)
	{
		SegmentLine::operator=(line);
	}

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Line& line)
{
	os << "Line --->\n\tPoint A: " << line._orig << "\n\tPoint B: " << line._dest << "\n";

	return os;
}

bool Line::segmentIntersection(SegmentLine& l)
{
	return false;
}