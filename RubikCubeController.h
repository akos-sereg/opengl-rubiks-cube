#pragma once

#ifndef _RUBIKCUBE_H_INCLUDED_
#define _RUBIKCUBE_H_INCLUDED_

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

struct HelpCommands
{
	char *line;
};

struct history
{
	char step[16];
};

class RubikCubeController
{
	public:
		RubikCubeController(void);
		void init(void);
		void shutDown(void);
		void refreshCube(void);
		void setColorGrid(int lap, int sorszam, double red, double green, double blue);
		void rotateColorSide(int num);
		void cAddQueue(char *cmd);                    // Add rotate command to queue
		void loadCubeColors();                        // Restore saved cube (from in-memory oldCube)
		void saveCubeColors();                        // Save active cube's state into in-memory oldCube
		void updateViewMatrix( void );
		void getRealTimeUserInput( void );            // Get mouse and keyboard input while traveling
		void render( void );                          // Render screen
		void setRotatingStep(int step);               // Set queue pointer - animation will be started by pulling the next item from queue
		void setRotatingSpeed(int rotatingSpeed);     // Increase or decrease rotating speed
		void setWarning(char* text);                  // Set warning message to be displayed on the top-left of the screen

	private:
		CubeModel oldCube;                            // Temporary cube we can work on
		GeometryProvider* geometryProvider;           // Provides rendering functions
		int rotating;
		int rotatingStep;
		int rotatingSpeed;
		int rotatingSpeedCurrent;
		vector3f g_vEye;
		vector3f g_vLook;                             // Look Vector
		vector3f g_vUp;                               // Up Vector
		vector3f g_vRight;                            // Right Vector
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
		char warning[256];                            // Warning message to be displayed on screen (bottom right, above commands)
		history history[500];                         // Rotate command queue
};

RubikCubeController* getRubikCubeController();

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif