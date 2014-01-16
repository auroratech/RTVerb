#include "rtFunctions.h"
int setQuadrant(float components[])
{
	int quadrant = 0;

	if(components[0] >= 0.0f) // If X is positive and...
	{
		if(components[1] >= 0.0f) 
		{
			quadrant = 0; // Y is positive.
		}
		else
		{
			quadrant = 1; // Y is negative.
		}
	}
	else // If X is negative and...
	{
		if(components[1] >= 0.0f)
		{
			quadrant = 3; // Y is positive.
		}
		else
		{
			quadrant = 2; // Y is negative.
		}
	}

	return quadrant;
}

 void findIntersect(ray* currentRay, surface surfaces[])
 {
 }