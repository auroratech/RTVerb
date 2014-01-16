#ifndef _DSJ_CLASS_SURFACE_
#define _DSJ_CLASS_SURFACE_
#include <math.h>

/*	+------------------------------------------------------------+
	| Title: Surface											 |
	| Author: Dale Johnson, U1061015							 |
	| Production Year: 2013/14									 |
	|															 |
	| Description:												 |
	| Surface object. This is a class that contains the start	 |
	| and end co-ordinates or the surface aswell as its			 |
	| projection components for reflections. It also contains	 |
	| functions for calculating reflection components for any    |
	| ray that intersects the surface.							 |
	+------------------------------------------------------------+
*/

class surface
{
public:
	int ID;
	float gradient;
	bool gradientIsInfinite;
	float startPoint[2];
	float endPoint[2];
	float components[2];
	float normComponents[2];

	//For intersections
	bool possIntersect;

	surface(int surfaceID);
	surface(float startCoords[2], float endCoords[2], int surfaceID);
	void setPoints(float startCoords[2], float endCoords[2]);
	~surface();
};

#endif