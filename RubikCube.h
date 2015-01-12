
char msginfo[256], warning[256];

double rotSpeed = 3.0;
double rotSpeedCurrent = 3.0;
int test=0;
int Oldal;
int h;
double arany = 1.0;
int rotatingStep=-1;
int rotating=-1;
void render(void);
int noRotating();
void saveCubeColors();
void loadCubeColors();
void cAddQueue(char *cmd);
int stillRotate=0;
int rotated=0;

int showRotating=0;


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
#include "CubeModel.h"
#include "CubeGeometry.h"
#include "CubeTransform.h"
#include "Rules.h"
#include "Strategia.h"


int closeToPlanet;
POINT  g_ptLastMousePosit;
POINT  g_ptCurrentMousePosit;
bool   g_bMousing = false;
float  g_fMoveSpeed = 0.6f;
float g_fMoveSpeed_turn = 1.0f;
float g_fMoveSpeed_Travel = 2;
float g_fMoveSpeed_Travel_small = 1.5;
float speed = 0.0f;
int changed=0;

vector3f g_vEye(10.0, 5.0, 10.0);     // Eye Position
vector3f g_vLook(-0.66, -0.28, -0.69); // Look Vector
vector3f g_vUp(0.0f, 1.0f, 0.0f);      // Up Vector
vector3f g_vRight(1.0f, 0.0f, 0.0f);   // Right Vector
vector3f g_vGravity(0.0f, 0.0f, 0.0f);
vector3f g_vView(-0.66, -0.28, -0.69);

int pathNum;
#define MAXP	1000

struct history
{
	char step[16];
} history[500];

int step=0;

struct path
{
	double x;
	double y;
	double z;
	int count;
} myPath[MAXP];


struct HelpCommands
{
	char *line;
} info[] = {
	{"q,w,e,r,t,z,u,i,o,p,a,s,d,f,g,h,j,k: Rotate commands"},
	{"m: Rotate randomly"},
	{"2: Solve Cube (animated)"},
	{"6,7,8,9: Speed - slower->faster"},
	{"F3: Move towards"},
	{"F4: Move backwards"},
	{"Up, down, left, right: Change moving direction"},
	{"Space: Stop"},
	{""}
};


struct Vertex
{
	unsigned char r, g, b, a;
	float x, y, z;
};

Vertex g_lineVertices[] =
{
	{ 255,   0,   0, 255,  0.0f, 0.1f, 0.0f }, // red   = +x Axis (x)
	{ 255,   0,   0, 255,  5.0f, 0.0f, 0.0f },
	{   0, 255,   0, 255,  0.0f, 0.1f, 0.0f }, // green = +z Axis (y)
	{   0, 255,   0, 255,  0.0f, 5.0f, 0.0f },
	{   0,   0, 255, 255,  0.0f, 0.1f, 0.0f }, // blue  = +y Axis (z)
	{   0,   0, 255, 255,  0.0f, 0.0f, 5.0f }
};




//-----------------------------------------------------------------------------
// GLOBALS
//-----------------------------------------------------------------------------
HWND  g_hWnd = NULL;
HDC   g_hDC  = NULL;
HGLRC g_hRC  = NULL;

float  g_fElpasedTime;
double g_dCurrentTime;
double g_dLastTime;

double g_fSpeedmodifier = 0.0001f;

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void init(void);
void shutDown(void);
void refreshCube(void);
void setColorGrid(int lap, int sorszam, double red, double green, double blue);
void cTransform(char *id);

int checkPattern2(int n);