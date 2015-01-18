#pragma once

#include "RubikCube.h"

struct mycolor 
{
	double red;
	double green;
	double blue;
};

struct SideRotate
{
	double deg;
	double rot[4];
	double dist[3];
	int to;
	struct mycolor colors[21];
};

class CubeTransformData
{
public:
	CubeTransformData(void);
	static SideRotate sideRotate[9];
	~CubeTransformData(void);

};

