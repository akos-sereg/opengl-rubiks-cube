#pragma once

#include "RubikCube.h"

struct mycolor 
{
	double red, green, blue;
};

struct SideRotate
{
	double deg, rot[4], dist[3];
	int to;
	struct mycolor colors[21];
};

struct ShowLap
{
	double deg, x1, y1, z1, x2, y2, z2;
};

struct SideCoordinate
{
	double x, y, z;
};

struct CubeCell
{
	int side;
	int place;
};

struct CubeCellColors
{
	struct CubeCell e[21];
};


class CubeTransformData
{
public:
	CubeTransformData(void);
	static SideRotate sideRotate[9];
	static ShowLap showLap[9];
	static SideCoordinate sideCoordinates[7][10];
	static CubeCellColors cellColors[];
	~CubeTransformData(void);

};

