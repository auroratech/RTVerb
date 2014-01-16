#define _USE_MATH_DEFINES

#include "stdafx.h"
using namespace std;

//TODO: Add reflect function

int main()
{
	cout << "Astral Engine" << endl;
	cout << "Version: " << _ASTRAL_VERSION << endl;
	cout << "Created by Dale Johnson 2014," << endl;
	cout << "Out on the windy moors of Saddleworth" << endl;
	cout << endl;

	space room;

	room.createRays(512, 0.0, 0.0, true);
	room.setSourcePos(2.f, 3.f);

	room.createSurface(0.f, 8.f, 8.f, 8.f);
	room.createSurface(8.f, 0.f, 8.f, 8.f);
	room.createSurface(0.f, 0.f, 8.f, 0.f);
	room.createSurface(0.f, 0.f, 0.f, 8.f);
	room.createSurface(2.f, 1.f, 6.f, 2.f);

	cout << "Walls: " << room.surfaces.size() << endl;

	clock_t startTime = clock();
	room.renderAll(100);
	clock_t endTime = clock();
	float result = ((float)(endTime - startTime))/CLOCKS_PER_SEC;

	cout << "Program time: " << result << endl;
}