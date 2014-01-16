#ifndef _DSJ_CLASS_SPACE
#define _DSJ_CLASS_SPACE
#define _ASTRAL_VERSION 0.27
#define _ASTRAL_SPEED_OF_SOUND 340.29
#include "surface.h"
#include "ray.h"
#include "detector.h"
#include <vector>
#include <math.h>
#define _USING_MATH_DEFINES
#include <iostream>
using namespace std;

//...The final frontier

/*	
	+------------------------------------------------------------+
	| Title: Space												 |
	| Author: Dale Johnson, U1061015							 |
	| Production Year: 2014									     |
	|															 |
	| Description:												 |
	| Space is a class that acts as an area for the surfaces to  |
	| exist in. This allows for the ray tracing functions to	 |
	| simply reference the space and use it's attributes and	 |
	| access information about the surfaces within the space.    |
	+------------------------------------------------------------+
*/

class space
{
typedef long ulong;
private:
	float defaultSurfaceStartCoords[2];
	float defaultSurfaceEndCoords[2];
	ulong numOfSurfaces;
	ulong numOfRays;

	surface* newSurface;
	ray* newRay;
	detector* newListener;

	bool sourceExists;
	bool raysExist;

	float sourcePos[2];

	struct listOfSurfs{
		unsigned int surfaceID;
		float intersection[2];
		bool validIntersection;
	};
	int intersections;
	listOfSurfs* newIntersection;
	listOfSurfs* validSurface;
	listOfSurfs targetSurface;
	bool quadTest;
	

public:
	//Vectors of all the surfaces, possible intersected surfaces and rays
	vector<surface> surfaces;
	vector<listOfSurfs> possibleSurfs;
	vector<listOfSurfs> validSurfs;
	vector<ray> rays;
	vector<detector> listener;
	
	//Constructor
	space();
	space(int maxSurfaces, long int maxRays);

	//Surface manipulation functions
	void createSurface(float x1, float y1, float x2, float y2);
	void createSurface(float point1[], float point2[]);
	void moveSurface(int surfaceID, float x1, float y1, float x2, float y2);
	void moveSurface(int surfaceID, float point1[], float point2[]);
	void deleteSurface(int surfaceID);
	long getNumOfSurfaces();
	long getNumOfRays();

	//Ray manipulation functions
	void createRays(ulong raysToCreate, float startAngle, float endAngle, bool omni);
	void setSourcePos(float x, float y);
	void setRayPos(ulong ray_t, float x, float y);

	//Listener manipulation functions
	void createListener(float x, float y, float radiusSize);
	void setListenerPos(float x, float y);

	//Ray tracing functions
	void findIntersects(ulong ray_t);
	void findValidSurfaces(ulong ray_t);
	void findClosestSurface(ulong ray_t);
	unsigned int getValidSurfaceID();
	void reflect(long ray_t);

	//Access Functions


	//Grand function
	void renderAll(ulong iterations);
	void renderOne(ulong ray_t, ulong iterations);

	~space();
};
#endif