#include "ray.h"
#include <iostream>
using namespace std;

ray::ray()
{
	point[0] = 0.0f;
	point[1] = 0.0f;
	previousPoint[0] = point[0];
	previousPoint[1] = point[1];
	components[0] = 1.f;
	components[1] = 0.f;
	rayGradient = components[1]/components[0];

	rayGradientInfinite = false;

	intersection[0] = point[0];
	intersection[1] = point[1];
	listElements = 0;

	previousSurface = -1;

	magnitude = 1.0f;
	a = 0.0f;
	b = 0.0f;
	distance = 0.0f;
	quadrant = 0;
}

ray::ray(float rayPosition[],
		 float angle)
{
	point[0] = 0.0f;
	point[1] = 0.0f;
	point[0] = rayPosition[0];
	point[1] = rayPosition[1];
	previousPoint[0] = point[0];
	previousPoint[1] = point[1];
	components[0] = sin(2.0f*M_PI*angle); //Calculate X component
	components[1] = cos(2.0f*M_PI*angle); //Calculate Y component
	rayGradient = components[1]/components[0];

	if(components[0] == 0 || components[1] == 1)
	{
		rayGradientInfinite = true;
	}
	else
	{
		rayGradientInfinite = false;
	}

	intersection[0] = point[0];
	intersection[1] = point[1];
	listElements = 0;

	previousSurface = -1;

	magnitude = 1.0f;
	a = 0.0f;
	b = 0.0f;
	distance = 0.0f;
}

void ray::calcGradient()
{
	rayGradient = components[1]/components[0];

	if(components[0] == 0 || components[1] == 1)
	{
		rayGradientInfinite = true;
	}
	else
	{
		rayGradientInfinite = false;
	}

	//Set quadrant
	if(components[0] >= 0.f
	&& components[1] >= 0.f)
	{
		quadrant = 0;
	}
	if(components[0] >= 0.f
	&& components[1] < 0.f)
	{
		quadrant = 1;
	}
	if(components[0] < 0.f
	&& components[1] < 0.f)
	{
		quadrant = 2;
	}
	if(components[0] < 0.f
	&& components[1] >= 0.f)
	{
		quadrant = 3;
	}
}

void ray::addTotalDistance()
{
	a = point[0] - previousPoint[0];
	b = point[1] - previousPoint[1];
	a = powf(a,2);
	b = powf(b,2);

	distance = distance + sqrt(a + b);
}
