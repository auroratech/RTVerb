#include "detector.h"

detector::detector()
{
	point[0] = 0.f;
	point[1] = 0.f;
	radius = 0.f;
	components[0] = 0.f;
	components[1] = 1.f;
}

detector::detector(float x, float y, float radiusSize)
{
	point[0] = 0.f;
	point[1] = 0.f;
	radius = radiusSize;
	components[0] = 0.f;
	components[1] = 1.f;
}