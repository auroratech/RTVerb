// RTVerb-MainRTAlgorithm.cpp : Defines the entry point for the console application.

//TODO: Figure out how to move away from a wall in the quadrant without sticking to it
//		Look at the quadrant checking system, how do order the points?

#define _USE_MATH_DEFINES
#define MAX_RAYS 512
#define WALLS 4

#include "stdafx.h"
#include <iostream>
#include <math.h>
#include "ray.h"
#include "surface.h"
#include "rtFunctions.h"
#include <time.h>
using namespace std;

int main()
{
	//Define wall positions		   X	Y
	float wall0_startPoint[2]	= {0.f, 7.f};
	float wall0_endPoint[2]	=	  {5.f, 7.f};
	float wall1_startPoint[2]	= {5.f, 0.f};
	float wall1_endPoint[2]	=	  {5.f, 7.f};
	float wall2_startPoint[2]	= {0.f, 0.f};
	float wall2_endPoint[2]	=	  {5.f, 0.f};
	float wall3_startPoint[2]	= {0.f, 0.f};
	float wall3_endPoint[2]	=	  {0.f, 7.f};

	//Source position
	float sourcePos[2] = {2.5f, 2.5f};

	//Rays and walls
	ray* rays[MAX_RAYS];
	surface* walls[WALLS];

	//Float versions of currRay, MAX_RAYS and the ray's angle
	float ray_f = 0.0f;
	float maxRays_f = 0.0f;
	float rayAngle = 0.0f;

	//Create walls and set their start and end points
	walls[0] = new surface(wall0_startPoint, wall0_endPoint, 0);
	walls[1] = new surface(wall1_startPoint, wall1_endPoint, 1);
	walls[2] = new surface(wall2_startPoint, wall2_endPoint, 2);
	walls[3] = new surface(wall3_startPoint, wall3_endPoint, 3);

	//#########################
	//-----Initialise Rays-----
	//#########################

	for(long int currRay = 0; currRay < MAX_RAYS; currRay++)
	{
		ray_f = static_cast<float> (currRay);
		maxRays_f = static_cast<float> (MAX_RAYS);

		//Create ray object and calculate the x and y components of each ray
		rayAngle = (ray_f / MAX_RAYS);

		rays[currRay] = new ray(sourcePos, rayAngle);

		//Work out which quadrant each ray will be travelling in
		rays[currRay]->quadrant = setQuadrant(rays[currRay]->components);			
	}

	//#################
	//-----Render -----
	//#################

	cout << "Rendering...";
	clock_t time = clock();

	for(long int currRay = 0; currRay < 1; currRay++) 
	{
		for(int iteration = 0; iteration < 3; iteration++) 
		{
			/*cout << "Iteration: " << iteration << endl;
			cout << "Current Cx: " << rays[currRay]->components[0] << endl;
			cout << "Current Cy: " << rays[currRay]->components[1] << endl;
			cout << "Current position: (" << rays[currRay]->point[0];
			cout << ", " << rays[currRay]->point[1] << ")" << endl;
			cout << "Current Quad: " << rays[currRay]->quadrant << endl;
			cout << "Previous Surface: " << rays[currRay]->previousSurface << endl; */

			rays[currRay]->findIntersect(walls,WALLS);
			rays[currRay]->findSurfaces(walls,WALLS);

			//cout << "Wall Intersected: " << rays[currRay]->surfIntersected << endl;

			rays[currRay]->reflect(walls,WALLS);
			rays[currRay]->calcGradient();
			rays[currRay]->quadrant = setQuadrant(rays[currRay]->components);
			rays[currRay]->addTotalDistance();

			/*cout << "New position: (" << rays[currRay]->point[0];
			cout << ", " << rays[currRay]->point[1] << ")" << endl;
			cout << "New Cx: " << rays[currRay]->components[0] << endl;
			cout << "New Cy: " << rays[currRay]->components[1] << endl;
			cout << endl;*/

			rays[currRay]->magnitude = rays[currRay]->magnitude - 0.01;
			if(rays[currRay]->magnitude < 0.001)
			{
				break;
			}
		}
	}
	clock_t newTime = clock() - time;

	float resultTime = newTime;
	resultTime = resultTime/CLOCKS_PER_SEC;

	cout << "Done!" << endl;
	cout << "Time: " << resultTime << " seconds" << endl;

	cout << "Ray 5 travelled " << rays[0]->distance << endl;

	return 0;
}