#ifndef _DSJ_CLASS_RAY_
#define _DSJ_CLASS_RAY_
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

class ray
{
public:
	float point[2];
	float previousPoint[2];
	float components[2];

	float rayGradient;
	float intersection[2];
	bool rayGradientInfinite;

	void calcGradient();

	//Quadrant
	int quadrant;
	float** listSurfs;
	int listElements;

	ray();
	ray(float position[],
		float angle);

	float magnitude;

	float a, b;
	float distance;

	void addTotalDistance();
	int previousSurface;
};

#endif