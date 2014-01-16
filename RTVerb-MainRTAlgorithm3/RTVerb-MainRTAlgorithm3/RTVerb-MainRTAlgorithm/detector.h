#ifndef _DSJ_CLASS_DETECTOR
#define _DSJ_CLASS_DETECTOR
#include <math.h>
using namespace std;

class detector
{
public:
	float point[2];
	float radius;
	float components[2];
	detector();
	detector(float x, float y, float radiusSize);
};

#endif