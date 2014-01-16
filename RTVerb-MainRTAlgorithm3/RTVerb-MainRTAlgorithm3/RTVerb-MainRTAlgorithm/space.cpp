#include "space.h"

space::space()
{
	numOfSurfaces = 0;
	numOfRays = 0;
	defaultSurfaceStartCoords[0] = 0.f;
	defaultSurfaceStartCoords[1] = 0.f;
	defaultSurfaceEndCoords[0] = 0.f;
	defaultSurfaceEndCoords[1] = 0.f;
	intersections = 0;
	raysExist = false;
	sourcePos[0] = 0.f;
	sourcePos[1] = 0.f;
	quadTest = false;
}

space::space(int maxSurfaces, long int maxRays)
{
	numOfSurfaces = 0;
	numOfRays = 0;
	defaultSurfaceStartCoords[0] = 0.f;
	defaultSurfaceStartCoords[1] = 0.f;
	defaultSurfaceEndCoords[0] = 0.f;
	defaultSurfaceEndCoords[1] = 0.f;
	intersections = 0;
	raysExist = false;
	sourcePos[0] = 0.f;
	sourcePos[1] = 0.f;
	quadTest = false;

	numOfSurfaces = maxSurfaces;
	numOfRays = maxRays;
	for(ulong currSurface = 0; currSurface < numOfSurfaces; currSurface++)
	{
		newSurface = new surface(currSurface);
		surfaces.push_back(*newSurface);
		delete newSurface;
	}

	for(ulong currRay = 0; currRay < numOfRays; currRay++)
	{
		newRay = new ray();
		rays.push_back(*newRay);
		delete newRay;
	}
}

void space::createSurface(float x1, float y1, float x2, float y2)
{
	int newSurfaceID = surfaces.size() + 1;
	float point1[2] = {x1,y1};
	float point2[2] = {x2,y2};

	newSurface = new surface(point1, point2, newSurfaceID);
	surfaces.push_back(*newSurface);
	numOfSurfaces = surfaces.size();

	for(ulong currSurface = 0; currSurface < numOfSurfaces; currSurface++)
	{
		surfaces[currSurface].ID = currSurface;
	}

	delete newSurface;
}

void space::createSurface(float point1[], float point2[])
{
	int newSurfaceID = surfaces.size() + 1;
	newSurface = new surface(point1, point2, newSurfaceID);
	surfaces.push_back(*newSurface);
	numOfSurfaces = surfaces.size();

	for(ulong currSurface = 0; currSurface < numOfSurfaces; currSurface++)
	{
		surfaces[currSurface].ID = currSurface;
	}

	delete newSurface;
}

void space::moveSurface(int surfaceID, float x1, float y1, float x2, float y2)
{
	float point1[2] = {x1,y1};
	float point2[2] = {x2,y2};
	surfaces[surfaceID].setPoints(point1, point2);
}

void space::moveSurface(int surfaceID, float point1[], float point2[])
{
	surfaces[surfaceID].setPoints(point1, point2);
}

void space::deleteSurface(int surfaceID)
{
	surfaces.erase(surfaces.begin() + surfaceID);
	numOfSurfaces = surfaces.size();
	for(ulong currSurface = 0; currSurface < numOfSurfaces; currSurface++)
	{
		surfaces[currSurface].ID = currSurface;
	}
}

long space::getNumOfSurfaces()
{
	return numOfSurfaces;
}

long space::getNumOfRays()
{
	return numOfRays;
}

void space::createRays(ulong maxRays, float startAngle, float endAngle, bool omni)
{
	rays.clear();
	float xComp = 0.f;
	float yComp = 0.f;
	float angleDelta = endAngle - startAngle;
	float currAngle = 0.f;

	for(float currRay = 0.f; currRay < maxRays; currRay++)
	{
		newRay = new ray;

		//Calculate ray angle
		if(omni)
		{
			currAngle = startAngle + currRay/maxRays;
		}
		else
		{
			currAngle = startAngle + angleDelta*(currRay/(maxRays - 1.0f));
		}

		//Calculate components, gradient and quadrant (part of gradient func)
		newRay->components[0] = sin(2.f*M_PI*currAngle);
		newRay->components[1] = cos(2.f*M_PI*currAngle);
		newRay->calcGradient();

		//Set source position
		newRay->point[0] = sourcePos[0];
		newRay->point[1] = sourcePos[1];

		rays.push_back(*newRay);
		delete newRay;
	}
	numOfRays = maxRays;
	raysExist = true;
}

void space::setSourcePos(float x, float y)
{
	sourcePos[0] = x;
	sourcePos[1] = y;

	if(raysExist)
	{
		for(ulong currRay = 0; currRay < numOfRays; currRay++)
		{
			rays[currRay].point[0] = sourcePos[0];
			rays[currRay].point[1] = sourcePos[1];
		}
	}
}

void space::setRayPos(ulong ray_t, float x, float y)
{
	if(ray_t < rays.size() && ray_t >= 0)
	{
		rays[ray_t].previousPoint[0] = rays[ray_t].point[0];
		rays[ray_t].previousPoint[1] = rays[ray_t].point[1];
		rays[ray_t].point[0] = x;
		rays[ray_t].point[1] = y;
	}
}

void space::createListener(float x, float y, float radiusSize)
{
	newListener = new detector(x, y, radiusSize);
	listener.push_back(*newListener);
	delete newListener;
}

void space::findIntersects(ulong ray_t)
{
	float ray_m = rays[ray_t].rayGradient;
	float ray_Px = rays[ray_t].point[0];
	float ray_Py = rays[ray_t].point[1];
	float ray_mPx =  ray_m * ray_Px;

	float surface_m = 0.f;
	float surface_Px = 0.f;
	float surface_Py = 0.f;
	float surface_mPx = 0.f;

	float new_m = 0.f;
	float new_point = 0.f;

	bool mayIntersect = true;

	float intersection[2] = {0.f, 0.f};

	possibleSurfs.clear();

	for(int item = 0; item < numOfSurfaces; item++)
	{
		//cout << item << " : ";
		mayIntersect = true;
		if(rays[ray_t].previousSurface == surfaces[item].ID)
		{
			//cout << " Already here!" << endl;
			mayIntersect = false;
		}
		surface_m = surfaces[item].gradient;
		surface_Px = surfaces[item].startPoint[0];
		surface_Py = surfaces[item].startPoint[1];
		surface_mPx = surface_m * surface_Px;

		if(rays[ray_t].rayGradientInfinite
		&& surfaces[item].gradientIsInfinite)
		{
			//Both ray and surface are vertically parralel so
			//they'll NEVER intersect
			//cout << "Both vertically parallel, ";
			mayIntersect = false;
		}

		if(rays[ray_t].rayGradientInfinite == false)
		{
			if(rays[ray_t].rayGradient == surfaces[item].gradient)
			{
				//Both ray and surface are parralel so they'll
				//NEVER intersect
				//cout << "Both parallel, ";
				mayIntersect = false;
			}
		}

		if(mayIntersect != false)
		{
			//If it has been decided that the ray and surface will
			//somehow intersect, continue with finding the intersection
			if(rays[ray_t].rayGradientInfinite)
			{
				intersection[0] = rays[ray_t].point[0];
				intersection[1] = surface_m*(intersection[0]-surface_Px)+surface_Py;
				//cout << "Only ray is infinite, ";
			}
			if(surfaces[item].gradientIsInfinite)
			{
				intersection[0] = surfaces[item].startPoint[0];
				intersection[1] = ray_m*(intersection[0]-ray_Px)+ray_Py;
				//cout << "Only wall is infinite, ";
			}

			//If neither ray or surface have infinite gradients,
			//proceed with normal maths
			if(!rays[ray_t].rayGradientInfinite
			&& !surfaces[item].gradientIsInfinite)
			{
				new_m = ray_m - surface_m;
				new_point = (ray_mPx - surface_mPx) + (surface_Py - ray_Py);
				intersection[0] = new_point/new_m;
				intersection[1] = surface_m * (intersection[0]-surface_Px)+surface_Py;
			}

			//Is the projected intersection within the bounds of the target surface?
			if(intersection[0] >= surfaces[item].startPoint[0]
			&& intersection[0] <= surfaces[item].endPoint[0])
			{
				if(surfaces[item].gradient >= 0)
				{
					if(intersection[1] >= surfaces[item].startPoint[1]
					&& intersection[1] <= surfaces[item].endPoint[1])
					{
						newIntersection = new listOfSurfs;
						newIntersection->surfaceID = surfaces[item].ID;
						newIntersection->intersection[0] = intersection[0];
						newIntersection->intersection[1] = intersection[1];
						possibleSurfs.push_back(*newIntersection);
						delete newIntersection;
						//cout << "+ve Intersection!" << endl;
					}
					else
					{
						//cout << "Out of Y bounds, ";
						mayIntersect = false;
					}
				}
				else if(surfaces[item].gradient < 0)
				{
					if(intersection[1] <= surfaces[item].startPoint[1]
					&& intersection[1] >= surfaces[item].endPoint[1])
					{
						newIntersection = new listOfSurfs;
						newIntersection->surfaceID = surfaces[item].ID;
						newIntersection->intersection[0] = intersection[0];
						newIntersection->intersection[1] = intersection[1];
						possibleSurfs.push_back(*newIntersection);
						delete newIntersection;
						//cout << "-ve Intersection!" << endl;
					}
					else
					{
						//cout << "Out of Y bounds, ";
						mayIntersect = false;
					}
				}
			}
			else
			{
				//cout << "Out of X bounds, ";
				mayIntersect = false;
			}
		}
		if(mayIntersect == false)
		{
			//cout << "no intersection" << endl;
		}
	}
}

void space::findValidSurfaces(ulong ray_t)
{
	float quadX = rays[ray_t].point[0];
	float quadY = rays[ray_t].point[1];
	validSurfs.clear();
	quadTest = false;

	//cout << "Possible surfs: " << possibleSurfs.size() << endl;

	for(unsigned int item = 0; item < possibleSurfs.size(); item++)
	{
		switch(rays[ray_t].quadrant)
		{
		//Quadrant 0: Above X, above Y
		case 0: if(possibleSurfs[item].intersection[0] >= quadX 
				&& possibleSurfs[item].intersection[1] >= quadY)
				{
					quadTest = true;
				}
				break;
		//Quadrant 1: Above X, below Y
		case 1: if(possibleSurfs[item].intersection[0] >= quadX 
				&& possibleSurfs[item].intersection[1] <= quadY)
				{
					quadTest = true;
				}
				break;
		//Quadrant 2: Below X, below Y
		case 2: if(possibleSurfs[item].intersection[0] <= quadX 
				&& possibleSurfs[item].intersection[1] <= quadY)
				{
					quadTest = true;
				}
				break;
		//Quadrant 3: Below X, above Y
		case 3: if(possibleSurfs[item].intersection[0] <= quadX 
				&& possibleSurfs[item].intersection[1] >= quadY)
				{
					quadTest = true;
				}
				break;
		}//End of quadrant switch

		if(quadTest == true)
		{ 
			validSurface = new listOfSurfs;
			//cout << "Valid surface: " << possibleSurfs[item].surfaceID << endl;
			validSurface->surfaceID = possibleSurfs[item].surfaceID;
			
			validSurface->intersection[0] = possibleSurfs[item].intersection[0];
			validSurface->intersection[1] = possibleSurfs[item].intersection[1];
			validSurfs.push_back(*validSurface);
			delete validSurface;
			quadTest = false;
		}				
	}
}

void space::findClosestSurface(ulong ray_t)
{
	long surfID = 0;
	long nearestSurface = 0;
	long numOfValidSurfs = validSurfs.size();

	float deltaX = 0.f;
	float deltaY = 0.f;
	float pointX = 0.f;
	float pointY = 0.f;
	float lowestDx = 10000.f;
	float lowestDy = 10000.f;
	float nearestX = 0.f;
	float nearestY = 0.f;

	nearestSurface = validSurfs[0].surfaceID;
	

	for(ulong item = 0; item < numOfValidSurfs; item++)
	{
		//cout << item << " : ";
		surfID = validSurfs[item].surfaceID;
		pointX = validSurfs[item].intersection[0];
		pointY = validSurfs[item].intersection[1];
		//cout << "VSIX: " << pointX;
		//cout << " VSIY: " << pointY << endl;


		deltaX = abs(pointX - rays[ray_t].point[0]);
		deltaY = abs(pointY - rays[ray_t].point[1]);
		//cout << "Dx: " << deltaX << endl;
		//cout << "Dy: " << deltaY << endl;


		if(deltaX < lowestDx && deltaY < lowestDy)
		{
			lowestDx = deltaX;
			lowestDy = deltaY;
			nearestX = pointX;
			nearestY = pointY;
			nearestSurface = surfID;
		}
	}
	targetSurface.surfaceID = nearestSurface;
	//cout << "Target Surf: " << targetSurface.surfaceID << endl;
	targetSurface.intersection[0] = nearestX;
	targetSurface.intersection[1] = nearestY;
}

unsigned int space::getValidSurfaceID()
{
	return 0; //validSurface.surfaceID;
}

void space::reflect(long ray_t)
{
	float dp1 = 0.f;
	float dp2 = 0.f;
	float proj1x = 0.f;
	float proj1y = 0.f;
	float proj2x = 0.f;
	float proj2y = 0.f;
	float newCX = 0.f;
	float newCY = 0.f;
	int surface_t = targetSurface.surfaceID;
	dp1 = rays[ray_t].components[0]*surfaces[surface_t].components[0] +
		  rays[ray_t].components[1]*surfaces[surface_t].components[1];
	dp2 = rays[ray_t].components[0]*surfaces[surface_t].normComponents[0] +
		  rays[ray_t].components[1]*surfaces[surface_t].normComponents[1];
	proj1x = dp1*surfaces[surface_t].components[0];
	proj1y = dp1*surfaces[surface_t].components[1];
	proj2x = (dp2*surfaces[surface_t].normComponents[0])*-1.f;
	proj2y = (dp2*surfaces[surface_t].normComponents[1])*-1.f;
	newCX = proj1x + proj2x;
	newCY = proj1y + proj2y;

	rays[ray_t].components[0] = newCX;
	rays[ray_t].components[1] = newCY;
	rays[ray_t].calcGradient();
	setRayPos(ray_t,targetSurface.intersection[0], targetSurface.intersection[1]);
	rays[ray_t].addTotalDistance();
	rays[ray_t].previousSurface = surface_t;
}

void space::renderAll(ulong iterations)
{
	for(ulong ray_t = 0; ray_t < numOfRays; ray_t++){
	for(ulong iteration = 0; iteration < iterations; iteration++)
	{
		findIntersects(ray_t);
		findValidSurfaces(ray_t);
		findClosestSurface(ray_t);
		reflect(ray_t);
	}
	}
}

void space::renderOne(ulong ray_t, ulong iterations)
{
	for(ulong iteration = 0; iteration < iterations; iteration++)
	{
		/*cout << "Iter: " << iteration << endl;
		cout << "X: " << rays[ray_t].point[0] << endl;
		cout << "Y: " << rays[ray_t].point[1] << endl;
		cout << "Cx: " << rays[ray_t].components[0] << endl;
		cout << "Cy: " << rays[ray_t].components[1] << endl;*/
		findIntersects(ray_t);
		findValidSurfaces(ray_t);
		findClosestSurface(ray_t);
		reflect(ray_t);
		//cout << endl;
	}
}

space::~space()
{
	surfaces.clear();
	rays.clear();
}