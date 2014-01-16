#include "surface.h"

surface::surface(int surfaceID)
{
	ID = surfaceID;
	possIntersect = false;
	startPoint[0] = 0.f;
	startPoint[1] = 0.f;
	endPoint[1] = 0.f;
	endPoint[0] = 0.f;

	gradient = 0.0f;
	gradientIsInfinite = false;

	components[0] = 1.f;
	components[1] = 0.f;

	normComponents[0] = components[1];
	normComponents[1] = components[0]*-1.0f;
}

surface::surface(float startCoords[2], float endCoords[2], int surfaceID)
{
	ID = surfaceID;

	if(startCoords[0] <= endCoords[0])
	{
		//Leave the points alone
		startPoint[0] = startCoords[0];
		startPoint[1] = startCoords[1];
		endPoint[0] = endCoords[0];
		endPoint[1] = endCoords[1];
	}
	else
	{
		//Swap the points
		startPoint[0] = endCoords[0];
		startPoint[1] = endCoords[1];
		endPoint[0] = startCoords[0];
		endPoint[1] = startCoords[1];
	}

	gradient = 0.0f;
	gradientIsInfinite = false;

	float differenceInX = 0.0f;
	float differenceInY = 0.0f;

	differenceInX = endPoint[0] - startPoint[0];
	differenceInY = endPoint[1] - startPoint[1];

	if(differenceInX == 0.0f)
	{
		gradientIsInfinite = true;
		gradient = 0.0f;
	}
	else
	{
		gradient = (differenceInY/differenceInX);
	}
	

	//For reflections
	//Use pythagoras to workout the components of the surface vector
	float a = 0.0f;
	float b = 0.0f;
	float c = 0.0f;

	a = endPoint[0] - startPoint[0];
	b = endPoint[1] - startPoint[1];
	c = powf(a,2) + powf(b,2);
	c = sqrt(c);

	//As the surface vector is a unit vector, where it's magnitude is 1
	//no matter how big the surface is, the components need to be scaled
	//down by the apparent size of the surface vector. Then calculate
	//the components of the normal vector of the surface vector.
	components[0] = a/c;
	components[1] = b/c;

	normComponents[0] = components[1];
	normComponents[1] = components[0]*-1.0f;
}

void surface::setPoints(float startCoords[2], float endCoords[2])
{
	if(startCoords[0] <= endCoords[0])
	{
		startPoint[0] = startCoords[0];
		endPoint[0] = endCoords[0];
		startPoint[1] = startCoords[1];
		endPoint[1] = endCoords[1];
	}
	else
	{
		startPoint[0] = endCoords[0];
		startPoint[1] = endCoords[1];
		endPoint[0] = startCoords[0];
		endPoint[1] = startCoords[1];
	}

	float differenceInX = 0.0f;
	float differenceInY = 0.0f;

	differenceInX = endPoint[0] - startPoint[0];
	differenceInY = endPoint[1] - startPoint[1];

	if(differenceInX == 0.0f)
	{
		gradientIsInfinite = true;
		gradient = 0.0f;
	}
	else
	{
		gradient = (differenceInY/differenceInX);
	}
	

	//For reflections
	//Use pythagoras to workout the components of the surface vector
	float a = 0.0f;
	float b = 0.0f;
	float c = 0.0f;

	a = endPoint[0] - startPoint[0];
	b = endPoint[1] - startPoint[1];
	c = powf(a,2) + powf(b,2);
	c = sqrt(c);

	//As the surface vector is a unit vector, where it's magnitude is 1
	//no matter how big the surface is, the components need to be scaled
	//down by the apparent size of the surface vector. Then calculate
	//the components of the normal vector of the surface vector.
	components[0] = a/c;
	components[1] = b/c;

	normComponents[0] = components[1];
	normComponents[1] = components[0]*-1.0f;
}

surface::~surface()
{
}