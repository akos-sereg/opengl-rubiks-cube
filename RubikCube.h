#pragma once

#ifndef _RUBIKCUBE_H_INCLUDED_
#define _RUBIKCUBE_H_INCLUDED_

void setWarning(char* text);
void setInfo(char *info);

using namespace std;

#include <list>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <algorithm>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glut.h"
#include "CubeTransformData.h"
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
#include "CubeModel.h"
#include "CubeTransform.h"
#include "RuleEngine.h"
#include "SolutionStrategy.h"

struct Vertex
{
	unsigned char r, g, b, a;
	float x, y, z;
};

struct cubeSide
{
	double deg, degx, degy, degz;
}; 

class RubikCube
{
	public:
		RubikCube(void);
		void init(void);
		void shutDown(void);
		void refreshCube(void);
		void setColorGrid(int lap, int sorszam, double red, double green, double blue);
		void rotateColorSide(int num);
		void cAddQueue(char *cmd);
		void loadCubeColors();
		void saveCubeColors();
		void updateViewMatrix( void );
		void getRealTimeUserInput( void );
		void render( void );
		void setRotatingStep(int step);
		void setRotatingSpeed(int rotatingSpeed);

	private:
		CubeModel oldCube;
		GeometryProvider* geometryProvider;
		int rotating;
		int rotatingStep;
		int rotatingSpeed;
		int rotatingSpeedCurrent;
		vector3f g_vEye;
		vector3f g_vLook; // Look Vector
		vector3f g_vUp;      // Up Vector
		vector3f g_vRight;   // Right Vector
		vector3f g_vGravity;
		vector3f g_vView;
		POINT  g_ptLastMousePosit;
		POINT  g_ptCurrentMousePosit;
		bool   g_bMousing;
		float  g_fMoveSpeed;
		float g_fMoveSpeed_turn;
		float g_fMoveSpeed_Travel;
		float g_fMoveSpeed_Travel_small;
		int stillRotate;
};

CubeModel* getCube();
RubikCube* getRubikCube();

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif