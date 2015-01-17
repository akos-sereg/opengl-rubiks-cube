#pragma once

#ifndef _RUBIKCUBE_H_INCLUDED_
#define _RUBIKCUBE_H_INCLUDED_

void setWarning(char* text);
void setInfo(char *info);
int isTest();
int getOldal();
double getArany();

using namespace std;

#include <list>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glut.h"
#include "ISolutionPhase.h"
#include "MovingWhiteCellUpToCenterPhase.h"
#include "MovingTopCornersPhase.h"
#include "MovingCornerWhiteDownPhase.h"
#include "MovingSideCentersPhase.h"
#include "MovingBottomCentersPhase.h"
#include "MovingBottomCornersPhase.h"
#include "CheckSolvedCubePhase.h"
#include "GeometryProvider.h"
#include "matrix4x4f.h"
#include "vector3f.h"
#include "CubeTransform.h"
#include "CubeModel.h"
#include "RuleEngine.h"
#include "SolutionStrategy.h"

struct Vertex
{
	unsigned char r, g, b, a;
	float x, y, z;
};

class RubikCube
{
	public:
		void init(void);
		void shutDown(void);
		void refreshCube(void);
		void setColorGrid(int lap, int sorszam, double red, double green, double blue);
		void rotateColorSide(int num);
		int noRotating();
		void cAddQueue(char *cmd);
		void loadCubeColors();
		void saveCubeColors();
		void updateViewMatrix( void );
		void getRealTimeUserInput( void );
		void render( void );
};

SolutionStrategy* getSolutionStrategy();
CubeModel* getCube();
CubeModel* getOldCube();
RuleEngine* getRuleEngine();
GeometryProvider* getGeometryProvider();
RubikCube* getRubikCube();

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif