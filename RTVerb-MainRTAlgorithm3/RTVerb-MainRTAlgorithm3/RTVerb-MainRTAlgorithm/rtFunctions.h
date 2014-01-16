#ifndef _DSJ_RAY_TRACING_FUNCTIONS_
#define _DSJ_RAY_TRACING_FUNCTIONS_
#define _USE_MATH_DEFINES
#include <math.h>
#include "ray.h"
#include "surface.h"

/*	+------------------------------------------------------------+
	| Title: Ray Tracing Functions								 |
	| Author: Dale Johnson, U1061015							 |
	| Production Year: 2013/14									 |
	|															 |
	| Description:												 |
	| These functions are used for ray tracing algorithms. This	 |
	| file contains:											 |
	| - Quadrant Finder											 |
	| - Intersector												 |
	+------------------------------------------------------------+*/

/*  +------------------------------------------------------------+
	| setQuadrant() is used to figure out which quadrant in the |
	| space a ray is travelling in based upon the ray's X and Y  |
	| components.												 |
	+------------------------------------------------------------+*/

int setQuadrant(float components[]);

void findIntersect(ray* currentRay, surface surfaces[]);

#endif