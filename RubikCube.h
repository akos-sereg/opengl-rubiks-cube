#pragma once

#ifndef _RUBIKCUBE_H_INCLUDED_
#define _RUBIKCUBE_H_INCLUDED_


void render(void);
int noRotating();
void saveCubeColors();
void loadCubeColors();
void cAddQueue(char *cmd);
void setWarning(char* text);
void setInfo(char *info);
int isTest();
int getOldal();
int getH();
void setH(int hValue);
void incrementH();
double getArany();


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glut.h"
#include "geometry.h"
#include "matrix4x4f.h"
#include "vector3f.h"
#include "CubeTransform.h"
#include "CubeModel.h"
#include "CubeGeometry.h"
#include "Rules.h"
#include "SolutionStrategy.h"

struct Vertex
{
	unsigned char r, g, b, a;
	float x, y, z;
};

//-----------------------------------------------------------------------------
// GLOBALS
//-----------------------------------------------------------------------------

SolutionStrategy* getSolutionStrategy();
CubeModel* getCube();
CubeModel* getOldCube();

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void init(void);
void shutDown(void);
void refreshCube(void);
void setColorGrid(int lap, int sorszam, double red, double green, double blue);
void rotateColorSide(int num);
int checkPattern2(int n);

#endif