#define STRICT
#define WIN32_LEAN_AND_MEAN

#include "RubikCube.h"


CubeModel cube;
CubeModel oldCube;

CubeModel* getCube() 
{
	return &cube;
}

CubeModel* getOldCube()
{
	return &oldCube;
}

char msginfo[256], warning[256];

int stillRotate=0;

double rotSpeed = 3.0;
double rotSpeedCurrent = 3.0;
int test=0;
int Oldal;
int rotatingStep=-1;
int rotating=-1;
int h;
double arany = 1.0;

double getArany()
{
	return arany;
}


int getH()
{
	return h;
}

void setH(int hValue)
{
	h = hValue;
}

void incrementH() 
{
	h++;
}

int getOldal() 
{
	return Oldal;
}

int isTest() 
{
	return test;
}

void setWarning(char* text)
{
	sprintf(warning, text);
}

void setInfo(char *text) 
{
	sprintf(msginfo, text);
}

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


vector3f g_vEye(10.0, 5.0, 10.0);     // Eye Position
vector3f g_vLook(-0.66, -0.28, -0.69); // Look Vector
vector3f g_vUp(0.0f, 1.0f, 0.0f);      // Up Vector
vector3f g_vRight(1.0f, 0.0f, 0.0f);   // Right Vector
vector3f g_vGravity(0.0f, 0.0f, 0.0f);
vector3f g_vView(-0.66, -0.28, -0.69);

int step=0;
struct history
{
	char step[16];
} history[500];

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

HWND  g_hWnd = NULL;
HDC   g_hDC  = NULL;
HGLRC g_hRC  = NULL;

float  g_fElpasedTime;
double g_dCurrentTime;
double g_dLastTime;

double g_fSpeedmodifier = 0.0001f;


Vertex g_lineVertices[] =
{
	{ 255,   0,   0, 255,  0.0f, 0.1f, 0.0f }, // red   = +x Axis (x)
	{ 255,   0,   0, 255,  5.0f, 0.0f, 0.0f },
	{   0, 255,   0, 255,  0.0f, 0.1f, 0.0f }, // green = +z Axis (y)
	{   0, 255,   0, 255,  0.0f, 5.0f, 0.0f },
	{   0,   0, 255, 255,  0.0f, 0.1f, 0.0f }, // blue  = +y Axis (z)
	{   0,   0, 255, 255,  0.0f, 0.0f, 5.0f }
};


struct sideRotate
{
	double deg;
	double rot[4];
	double dist[3];
	int to;
	struct mycolor colors[21];

} sideRotate[9] = { 
	{
		// 1. side
		0.0, {0, 0.0, 0.0, 0.0}, {1.5, 1.5, 2.75}, 1, 
		{ 
			{1.0, 1.0, 1.0}, {1.0, 1.0, 0.0}, {0.5, 0.5, 0.0}, {0.0, 1.0, 0.0},
			{0.0, 0.0, 1.0}, {1.0, 1.0, 0.5}, {0.1, 0.5, 0.5}, {0.5, 0.5, 1.0},
			{1.0, 1.0, 1.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0},
			{1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0},
			{1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0},
			{1.0, 0.0, 0.0}
		}
	}, {
		// 2. side
		0.0, {90.0, 0.0, 1.0, 0.0}, {-1.5, 1.5, 2.75}, 1,
		{}
	},{
		// 3. side
		0.0, {180.0, 0.0, 1.0, 0.0}, {-1.5, 1.5, -0.375}, 1,
		{}
	}, {
		// 4. side
		0.0, {-90.0, 0.0, 1.0, 0.0}, {1.5, 1.5, -0.225}, 1,
		{}
	}, {
		// 5. side
		0.0, {-90.0, 1.0, 0.0, 0.0}, {1.5, -1.5, 2.725}, 1,
		{}
	}, {
		// 6. side
		0.0, {90.0, 1.0, 0.0, 0.0}, {1.5, 1.5, -0.25}, 1,
		{}
	}, {
		// 7. side
		0.0, {90.0, 0.0, 1.0, 0.0}, {-1.5, 1.5, 1.725}, 1,
		{}
	}, {
		// 8. side
		0.0, {0.0, 0.0, 0.0, 0.0}, {1.5, 1.5, 1.740}, 1,
		{}
	}, {
		// 9. side
		0.0, {90.0, 1.0, 0.0, 0.0}, {1.5, 1.5, -1.25}, 1,
		{}
	}
};


int SGN(float num)
{
	if(num == 0) return 0;
	if(num < 1) return -1;
	else return 1;
}

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR     lpCmdLine,
				   int       nCmdShow )
{
	WNDCLASSEX winClass = {0}; 
	MSG        uMsg;

	memset(&uMsg,0,sizeof(uMsg));

	winClass.lpszClassName = "MY_WINDOWS_CLASS";
	winClass.cbSize        = sizeof(WNDCLASSEX);
	winClass.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	winClass.lpfnWndProc   = WindowProc;
	winClass.hInstance     = hInstance;
	winClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winClass.lpszMenuName  = NULL;
	winClass.cbClsExtra    = 0;
	winClass.cbWndExtra    = 0;

	if (!RegisterClassEx(&winClass)) {
		MessageBox(NULL, "Class registration has failed!", "Error!", MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	g_hWnd = CreateWindowEx( NULL, "MY_WINDOWS_CLASS", 
		"Rubik's cube",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0, 800, 600, NULL, NULL, hInstance, NULL );

	if( g_hWnd == NULL )
		return E_FAIL;


	ShowWindow( g_hWnd, nCmdShow );
	UpdateWindow( g_hWnd );

	init();

	while( uMsg.message != WM_QUIT )
	{
		if( PeekMessage( &uMsg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &uMsg );
			DispatchMessage( &uMsg );
		}
		else
		{
			g_dCurrentTime = timeGetTime();
			g_fElpasedTime = (float)((g_dCurrentTime - g_dLastTime) * 0.001);
			g_dLastTime    = g_dCurrentTime;

			//_sleep(40);
			render();
		}
	}

	shutDown(); 

	UnregisterClass( "MY_WINDOWS_CLASS", winClass.hInstance );


	return uMsg.wParam;
}

//-----------------------------------------------------------------------------
// Name: WindowProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT CALLBACK WindowProc( HWND   hWnd, 
							UINT   msg, 
							WPARAM wParam, 
							LPARAM lParam )
{
	switch( msg )
	{
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case 'M':
				cTransformN(rand()%16);
				break;

			case 'N':
				fazis1();
				break;

			case '1': 
				saveCubeColors();
				step = 0;
				rotatingStep = 0;
				stopRotating();
				break;

			case '2': 
				saveCubeColors();
				step=0;
				rotatingStep=0;
				stopRotating();
				
				if(run())
				{
					if(!test)
					{
						startRotating();
						loadCubeColors();
					} else step=0;
					rotatingStep=-1;
				} else sprintf(msginfo, "Error: unable to solve cube");
				break;
			case '9':
				rotSpeed=10.0;
				break;
			case '8':
				rotSpeed=6.0;
				break;
			case '7':
				rotSpeed=3.0;
				break;
			case '6':
				rotSpeed=1.0;
				break;
			case 'V':
				int find;

				if(findPattern(MINTA_FAZIS3) == -1)
				{
					sprintf(msginfo, "Phase 3 validation failed");
					break;
				}
				
				find = findPattern(NAGYT_KIST);
				if(find!=-1) 
				{
					if(rules[find].elofeltetel[0] != RESCUE) 
					{
						setH(0);
						applySolution(find, 0);
					} else 
					{
						incrementH();
						cTransform("6j");
						if(getH()>4) {
							applySolution(find, 0);
							setH(0);
						}

					}
				}
				else 
				{
					cTransform("6j");
				}

			case 'C':
				int i,j,rule_use,old,m;
				int find2;
				if(findPattern(MINTA_FAZIS2) == -1) 
				{
					sprintf(msginfo, "Phase 2 validation failed");
					break;
				}
				
				
				for(old=0; old!=4; old++)
				{
					find2 = findPattern(SAROKFEHER_LE);
					if(find2!=-1)
						applySolution(find2, 0);

					for(j=0; j!=5; j++)
					{
						find = findPattern(FEHER_LENT_POZICIOBAN);
						if(find != -1) 
							applySolution(find, 0);

						cTransform("6j");
					}
				}
				break;

			case 'X':

				for(j=0; j!=4; j++)
				{
					if(fazis2_alul()) continue;
					for(i=0; i!=rulesLen(); i++)
					{
						if(rules[i].group == FEHERET_ALULRA)
						{
							if(checkPattern(i)) 
							{	
								applySolution(i, 0);
								int k;
								for(k=0; k!=4; k++)
								{
									if(fazis2_alul()) break;
									cTransform("6j");
								}
							}
						}
					}
				}

				for(i=0; i!=rulesLen(); i++)
				{
					if(rules[i].group == MINTA_FAZIS2) 
						if(!checkPattern(i)) sprintf(warning, "Broken rule found while running phase 2");
				}
				
				break;

			case 'Q': cTransformN(0); break;
			case 'W': cTransformN(1); break;
			case 'E': cTransformN(2); break;
			case 'R': cTransformN(3); break;
			case 'T': cTransformN(4); break;
			case 'Z': cTransformN(5); break;
			case 'U': cTransformN(6); break;
			case 'I': cTransformN(7); break;
			case 'O': cTransformN(8); break;
			case 'P': cTransformN(9); break;
			case 'A': cTransformN(10); break;
			case 'S': cTransformN(11); break;
			case 'D': cTransformN(12); break;
			case 'F': cTransformN(13); break;
			case 'G': cTransformN(14); break;
			case 'H': cTransformN(15); break;
			case 'J': cTransformN(16); break;
			case 'K': cTransformN(17); break;
			case 'B':
				int s;
				s = findPattern(ALSO1);
				if(s!=-1)
				{
					applySolution(s, 0);
				}
				break;

			case VK_ESCAPE:
				PostQuitMessage(0);
				break;

			case VK_SPACE:
				speed = 0;
				break;

			case VK_F1:
				g_fSpeedmodifier += 0.0001;
				break;

			case VK_F2:
				g_fSpeedmodifier -= 0.0001;
				break;
			}
		}
		break;

	case WM_SIZE:
		{
			int nWidth  = LOWORD(lParam); 
			int nHeight = HIWORD(lParam);
			glViewport(0, 0, nWidth, nHeight);

			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();
			gluPerspective( 45.0f, (float) (800 / 600), 3.0f, 100.0f);

		}
		break;

	case WM_CLOSE:
		{
			PostQuitMessage(0); 
		}

	case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		break;

	default:
		{
			return DefWindowProc( hWnd, msg, wParam, lParam );
		}
		break;
	}

	return 0;
}


void inline drawString (char *s)
{
	unsigned int i;
	for (i=0; i<strlen(s); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, s[i]);
}


//-----------------------------------------------------------------------------
// Name: init()
// Desc: 
//-----------------------------------------------------------------------------
void init( void )
{
	GLuint PixelFormat;

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize      = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion   = 1;
	pfd.dwFlags    = PFD_DRAW_TO_WINDOW |PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 16;
	pfd.cDepthBits = 16;

	g_hDC = GetDC( g_hWnd );
	PixelFormat = ChoosePixelFormat( g_hDC, &pfd );
	SetPixelFormat( g_hDC, PixelFormat, &pfd);
	g_hRC = wglCreateContext( g_hDC );
	wglMakeCurrent( g_hDC, g_hRC );
	glClearColor(0.2, 0.4, 0.1, 0.0);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 45.0f, 800.0f / 600.0f, 3.0f, 100.0f);

}


//-----------------------------------------------------------------------------
// Name : updateViewMatrix() 
// Desc : Builds a view matrix suitable for OpenGL.
//
// Here's what the final view matrix should look like:
//
//  |  rx   ry   rz  -(r.e) |
//  |  ux   uy   uz  -(u.e) |
//  | -lx  -ly  -lz   (l.e) |
//  |   0    0    0     1   |
//
// Where r = Right vector
//       u = Up vector
//       l = Look vector
//       e = Eye position in world space
//       . = Dot-product operation
//
//-----------------------------------------------------------------------------
void updateViewMatrix( void )
{
	matrix4x4f view;
	view.identity();

	g_vLook.normalize();

	g_vRight = vector3f::crossProduct(g_vView, g_vUp);
	g_vRight.normalize();

	g_vUp = vector3f::crossProduct(g_vRight, g_vView);
	g_vUp.normalize();

	view.m[0] =  g_vRight.x;
	view.m[1] =  g_vUp.x;
	view.m[2] = -g_vView.x;
	view.m[3] =  0.0f;

	view.m[4] =  g_vRight.y;
	view.m[5] =  g_vUp.y;
	view.m[6] = -g_vView.y;
	view.m[7] =  0.0f;

	view.m[8]  =  g_vRight.z;
	view.m[9]  =  g_vUp.z;
	view.m[10] = -g_vView.z;
	view.m[11] =  0.0f;

	float f = 1.3;
	
	view.m[12] = -vector3f::dotProduct(g_vRight, g_vEye);
	view.m[13] = -vector3f::dotProduct(g_vUp, g_vEye);
	view.m[14] =  vector3f::dotProduct(g_vView, g_vEye);
	view.m[15] =  1.0f;

	glMultMatrixf( view.m );
}


//-----------------------------------------------------------------------------
// Name: getRealTimeUserInput()
// Desc: 
//-----------------------------------------------------------------------------
void getRealTimeUserInput( void )
{
	// Mouse input
	POINT mousePosit;
	GetCursorPos( &mousePosit );
	ScreenToClient( g_hWnd, &mousePosit );

	g_ptCurrentMousePosit.x = mousePosit.x;
	g_ptCurrentMousePosit.y = mousePosit.y;

	matrix4x4f matRotation;

	if( g_bMousing )
	{
		int nXDiff = (g_ptCurrentMousePosit.x - g_ptLastMousePosit.x);
		int nYDiff = (g_ptCurrentMousePosit.y - g_ptLastMousePosit.y);

		if( nYDiff != 0 )
		{
			matRotation.rotate( -(float)nYDiff / 3.0f, g_vRight );
			matRotation.transformVector( &g_vLook );
			matRotation.transformVector( &g_vUp );
		}

		if( nXDiff != 0 )
		{
			matRotation.rotate( -(float)nXDiff / 3.0f, vector3f(0.0f, 1.0f, 0.0f) );
			matRotation.transformVector( &g_vLook );
			matRotation.transformVector( &g_vUp );
		}
	}

	g_ptLastMousePosit.x = g_ptCurrentMousePosit.x;
	g_ptLastMousePosit.y = g_ptCurrentMousePosit.y;

	// Get keyboard input...
	
	unsigned char keys[256];
	GetKeyboardState( keys );

	vector3f tmpLook  = g_vLook;
	vector3f tmpRight = g_vRight;
	vector3f tmpUp = g_vUp;
	vector3f tmpEye = g_vEye;
	vector3f tmpView = g_vView;

	if(speed > 0)
	{
		g_vEye -= tmpLook*-(g_fMoveSpeed_Travel*speed)*g_fElpasedTime;
	} else if(speed < 0)
	{
		g_vEye += (tmpLook*-(g_fMoveSpeed_Travel* (float)abs(speed)))*g_fElpasedTime;
	}


	if(keys[45] & 0x80) speed = 0;

	// Move forward
	if( keys[VK_F3] & 0x80 )
	{
		speed += 0.1;
		g_vEye -= tmpView*-(g_fMoveSpeed_Travel*speed)*g_fElpasedTime;
		g_vLook = g_vView;
	}

	// Move backwards
	if( keys[VK_F4] & 0x80 )
	{
		speed -= 0.1;
		g_vEye += (tmpView*-(g_fMoveSpeed_Travel*  (float)abs(speed)))*g_fElpasedTime;
		g_vLook = g_vView;
	}

	/* -------------------------------------------------------- */ 
	// Move forward (slowly)
	if( keys[VK_F5] & 0x80 )
	{
		speed += 0.001;
		g_vEye -= tmpView*-(g_fMoveSpeed_Travel_small*speed)*g_fElpasedTime;
		g_vLook = g_vView;
	}

	// Move backwards (slowly)
	if( keys[VK_F6] & 0x80 )
	{
		speed -= 0.001;
		g_vEye += (tmpView*-(g_fMoveSpeed_Travel_small*  (float)abs(speed)))*g_fElpasedTime;
		g_vLook = g_vView;
	}
	//-----------------------------------------------------

	// Up Arrow Key - View moves forward
	if( keys[VK_UP] & 0x80 )
	{
		g_vView -= tmpUp*-g_fMoveSpeed_turn*g_fElpasedTime;
	}

	// Down Arrow Key - View moves backward
	if( keys[VK_DOWN] & 0x80 )
	{
		g_vView += (tmpUp*-g_fMoveSpeed_turn)*g_fElpasedTime;
	}

	// Left Arrow Key - View side-steps or strafes to the left
	if( keys[VK_LEFT] & 0x80 )
	{
		g_vView -= (tmpRight*g_fMoveSpeed_turn)*g_fElpasedTime;
	}

	// Right Arrow Key - View side-steps or strafes to the right
	if( keys[VK_RIGHT] & 0x80 )
	{
		g_vView += (tmpRight*g_fMoveSpeed_turn)*g_fElpasedTime;
	}

	// Home Key - View elevates up
	if( keys[VK_HOME] & 0x80 )
		g_vEye.y += g_fMoveSpeed*g_fElpasedTime; 

	// End Key - View elevates down
	if( keys[VK_END] & 0x80 )
		g_vEye.y -= g_fMoveSpeed*g_fElpasedTime;
}



//-----------------------------------------------------------------------------
// Name: shutDown()
// Desc: 
//-----------------------------------------------------------------------------
void shutDown( void )   
{
	if( g_hRC != NULL )
	{
		wglMakeCurrent( NULL, NULL );
		wglDeleteContext( g_hRC );
		g_hRC = NULL;
	}

	if( g_hDC != NULL )
	{
		ReleaseDC( g_hWnd, g_hDC );
		g_hDC = NULL;
	}
}


struct showLap
{
	double deg;
	double x1, y1, z1;
	double x2, y2, z2;
} showLap[] = 
{
	{
		0.0, 0.505, 0.52, 0.6, 0.54, 0.55, 1.5
	},
	{
		90.0, -2.45, 0.55, 0.55, -2.45, 0.55, 1.55
	},
	{
		0.0, 0.505, 0.52, 2.45, 0.54, 0.55, 1.5
	},
	{
		90.0, -2.45, 0.55, 2.40, -2.45, 0.55, 1.55
	},
	{
		90.0, 0.52, 0.55, -0.55, 0.52, 0.55, -1.55
	},
	{
		90.0, 0.52, 0.55, -2.45, 0.52, 0.55, -1.55
	},
	{ 
		90.0, -2.45, 0.55, 0.55, -2.45, 0.55, 2.40
	},
	{
		0.0, 0.505, 0.52, 0.55, 0.54, 0.55, 2.45
	},
	{	
		90.0, 0.52, 0.55, -0.55, 0.52, 0.55, -2.475
	}
};


void render( void )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	getRealTimeUserInput();

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	updateViewMatrix();
	
	glDisable( GL_BLEND);
	glEnable( GL_DEPTH_TEST );

	GLfloat LightAmbient[]= {0.8, 0.8, 0.8, 0.8};
	GLfloat LightDiffuse[]= {1.0, 1.0, 1.0, 1.0};
	GLfloat LightPosition[]= { 4.0f, 2.0f, 3.0f, 1.0f};

	int i,j,k;

	if(rotating!=-1)
	{
		if((rotating < 4 || rotating>5) && rotating!=8) glRotatef(showLap[rotating].deg, 0.0, 1.0, 0.0);
		else glRotatef(showLap[rotating].deg, 1.0, 0.0, 0.0);
		glTranslatef(showLap[rotating].x1, showLap[rotating].y1, showLap[rotating].z1);
		renderLap();
		glTranslatef(-showLap[rotating].x1, -showLap[rotating].y1, -showLap[rotating].z1);
		glTranslatef(showLap[rotating].x2, showLap[rotating].y2, showLap[rotating].z2);
		renderLap();
		glTranslatef(-showLap[rotating].x2, -showLap[rotating].y2, -showLap[rotating].z2);
		if((rotating < 4 || rotating > 5) && rotating != 8) glRotatef(-showLap[rotating].deg, 0.0, 1.0, 0.0);
		else glRotatef(-showLap[rotating].deg, 1.0, 0.0, 0.0);
	} else
	{
		glTranslatef(0.52, 0.55, 0.52);
		for(i=0; i!=3; i++)
		{
			renderLap();
			glTranslatef(0.0, 0.0, 0.98);
		}
		glTranslatef(0.0, 0.0, -(3*0.98));
		glTranslatef(-0.52, -0.55, -0.52);
	}

	glPushMatrix();
	{
		renderGrid(10*arany, 0.5*arany);
		refreshCube();

		if(!changed) 
		{
			cube.DefaultColors();
			changed = 1;
		}

		// -------------------- ROTATE --------------
		int snum;
		for(snum=0; snum!=9; snum++)
		{
			if(sideRotate[snum].deg != 0.0)
			{
				glRotatef(sideRotate[snum].rot[0], sideRotate[snum].rot[1], sideRotate[snum].rot[2], sideRotate[snum].rot[3]);
				
				glTranslatef(sideRotate[snum].dist[0]*arany, sideRotate[snum].dist[1]*arany, sideRotate[snum].dist[2]*arany);
				glRotatef(sideRotate[snum].deg, 0.0, 0.0, 1.0);
				renderSide(sideRotate[snum].colors);
				if(sideRotate[snum].deg>0.0) sideRotate[snum].deg -= rotSpeedCurrent;
				else if(sideRotate[snum].deg<0.0) sideRotate[snum].deg += rotSpeed;

				if(sideRotate[snum].deg == 0.0) 
				{
					stillRotate = 0;
					rotating=-1;
					if(rotSpeedCurrent != rotSpeed) rotSpeedCurrent = rotSpeed;
				} else 
				{
					stillRotate = 1;
					rotating = snum;
				}
			}
		}
	}

	glPopMatrix();

	glInterleavedArrays( GL_C4UB_V3F, 0, g_lineVertices );
	glDrawArrays( GL_LINES, 0, 6 );

	int h;
	glColor3f(1.0, 1.0, 1.0);
	sprintf(warning, "Steps (not optimized): %d / %d", rotatingStep+1, step);
	renderTextFull(10.0, 12.0, warning);

	if(rotatingStep == step-1) stopRotating();
	if(rotating==-1 && getRotating())
	{
		setRotated(1);
		rotatingStep++;
		if(getRotated())
		{
			cTransform(history[rotatingStep].step);
			setRotated(0);
		}
	}
	
	i=0;
	glColor3f(1.0, 1.0, 1.0);
	while(strlen(info[i].line))
	{
		sprintf(warning, "%s", info[i].line);
		renderTextFull(10, (12*i) + 24, warning);
		i++;
	}

	SwapBuffers( g_hDC );
}


struct sideCoord
{
	double x;
	double y;
	double z;
} sideCoord[7][10] = 
{
	{ {0.0,0.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0} },
	{ // side 1
		{0.0, 0.0, 0.0},
		{0.5, 2.5, 2.975}, {1.5, 2.5, 2.975}, {2.5, 2.5, 2.975},
		{0.5, 1.5, 2.975}, {1.5, 1.5, 2.975}, {2.5, 1.5, 2.975},
		{0.5, 0.5, 2.975}, {1.5, 0.5, 2.975}, {2.5, 0.5, 2.975}
	}, { // side 2
		{0.0, 0.0, 0.0},
		{2.92, 2.5, 2.5}, {2.92, 2.5, 1.5}, {2.92, 2.5, 0.5},
		{2.92, 1.5, 2.5}, {2.92, 1.5, 1.5}, {2.92, 1.5, 0.5},
		{2.92, 0.5, 2.5}, {2.92, 0.5, 1.5}, {2.92, 0.5, 0.5},
	}, { // side 3
		{0.0, 0.0, 0.0},
		{0.5, 2.5, 0.025}, {1.5, 2.5, 0.025}, {2.5, 2.5, 0.025},
		{0.5, 1.5, 0.025}, {1.5, 1.5, 0.025}, {2.5, 1.5, 0.025},
		{0.5, 0.5, 0.025}, {1.5, 0.5, 0.025}, {2.5, 0.5, 0.025},
	}, { // side 4
		{0.0, 0.0, 0.0},
		{0.025, 2.5, 2.5}, {0.025, 2.5, 1.5}, {0.025, 2.5, 0.5},
		{0.025, 1.5, 2.5}, {0.025, 1.5, 1.5}, {0.025, 1.5, 0.5},
		{0.025, 0.5, 2.5}, {0.025, 0.5, 1.5}, {0.025, 0.5, 0.5},
	}, { // side 5
		{0.0, 0.0, 0.0},
		{0.5, 2.975, 0.5}, {1.5, 2.975, 0.5}, {2.5, 2.975, 0.5},
		{0.5, 2.975, 1.5}, {1.5, 2.975, 1.5}, {2.5, 2.975, 1.5},
		{0.5, 2.975, 2.5}, {1.5, 2.975, 2.5}, {2.5, 2.975, 2.5},
	}, { // side 6
		{0.0, 0.0, 0.0},
		{0.5, 0.025, 0.5}, {1.5, 0.025, 0.5}, {2.5, 0.025, 0.5},
		{0.5, 0.025, 1.5}, {1.5, 0.025, 1.5}, {2.5, 0.025, 1.5},
		{0.5, 0.025, 2.5}, {1.5, 0.025, 2.5}, {2.5, 0.025, 2.5},

	},

};


struct cubeSide
{
	double deg;
	double degx;
	double degy;
	double degz;
} cubeSide[7] = {
	{0.0,  0.0, 0.0, 0.0},
	{90.0, 1.0, 0.0, 0.0},
	{90.0, 0.0, 0.0, 1.0},
	{90.0, 1.0, 0.0, 0.0},
	{90.0, 0.0, 0.0, 1.0},
	{0.0,  0.0, 0.0, 0.0},
	{0.0,  0.0, 0.0, 0.0}
};

void setColorGrid(int lap, int sorszam, double red, double green, double blue)
{
	double x,y,z;
	double fok[4] = { cubeSide[lap].deg, cubeSide[lap].degx, cubeSide[lap].degy, cubeSide[lap].degz };
	x = sideCoord[lap][sorszam].x;
	y = sideCoord[lap][sorszam].y;
	z = sideCoord[lap][sorszam].z;


	glPushMatrix();
	{
		glTranslatef(x*arany, y*arany, z*arany);
		glRotatef(fok[0], fok[1], fok[2], fok[3]);
		renderGridColor(0.8 * arany, red, green, blue);
		glTranslatef(-x*arany, -y*arany, -z*arany);

	}
	glPopMatrix();
}


struct lapSzinek
{
	struct elem e[21];
} lapSzinek[]=
{
	{
		{
			{2, 7}, {2, 4}, {2, 1}, {4, 7}, {4, 4}, {4, 1}, {6, 9}, {1, 9}, 
			{1, 6}, {1, 3}, {5, 9}, {6, 8}, {1, 8}, {1, 5}, {1, 2}, {5, 8}, 
			{6, 7}, {1, 7}, {1, 4}, {1, 1}, {5, 7}
		}
	},{
		{
			{4, 1}, {4, 4}, {4, 7}, {2, 1}, {2, 4}, {2, 7}, {5, 7}, {1, 1}, 
			{1, 4}, {1, 7}, {6, 7}, {5, 8}, {1, 2}, {1, 5}, {1, 8}, {6, 8}, 
			{5, 9}, {1, 3}, {1, 6}, {1, 9}, {6, 9}
		}
	},{
		{
			{3, 9}, {3, 6}, {3, 3}, {1, 9}, {1, 6}, {1, 3}, {6, 3}, 
			{2, 9}, {2, 6}, {2, 3}, {5, 3}, {6, 6}, {2, 8}, {2, 5}, {2, 2}, 
			{5, 6}, {6, 9}, {2, 7}, {2, 4}, {2, 1}, {5, 9}
		}
	},
	{
		{
			{1, 3}, {1, 6}, {1, 9}, {3, 3}, {3, 6}, {3, 9}, {5, 9}, {2, 1}, 
			{2, 4}, {2, 7}, {6, 9}, {5, 6}, {2, 2}, {2, 5}, {2, 8}, {6, 6},
			{5, 3}, {2, 3}, {2, 6}, {2, 9}, {6, 3}
		}
	},
	{
		{
			{4, 9}, {4, 6}, {4, 3}, {2, 9}, {2, 6}, {2, 3}, {6, 1}, {3, 7}, 
			{3, 4}, {3, 1}, {5, 1}, {6, 2}, {3, 8}, {3, 5}, {3, 2}, {5, 2},
			{6, 3}, {3, 9}, {3, 6}, {3, 3}, {5, 3}
		}
	},
	{
		{
			{2, 3}, {2, 6}, {2, 9}, {4, 3}, {4, 6}, {4, 9}, {5, 3}, {3, 3}, 
			{3, 6}, {3, 9}, {6, 3}, {5, 2}, {3, 2}, {3, 5}, {3, 8}, {6, 2},
			{5, 1}, {3, 1}, {3, 4}, {3, 7}, {6, 1}
		}
	},{
		{
			{1, 7}, {1, 4}, {1, 1}, {3, 7}, {3, 4}, {3, 1}, {6, 7}, {4, 7}, 
			{4, 4}, {4, 1}, {5, 7}, {6, 4}, {4, 8}, {4, 5}, {4, 2}, {5, 4},
			{6, 1}, {4, 9}, {4, 6}, {4, 3}, {5, 1}
		}
	},
	{
		{
			{3, 1}, {3, 4}, {3, 7}, {1, 1}, {1, 4}, {1, 7}, {5, 1}, {4, 3}, 
			{4, 6}, {4, 9}, {6, 1}, {5, 4}, {4, 2}, {4, 5}, {4, 8}, {6, 4},
			{5, 7}, {4, 1}, {4, 4}, {4, 7}, {6, 7}
		}
	},
	{
		{
			{4, 3}, {4, 2}, {4, 1}, {2, 3}, {2, 2}, {2, 1}, {3, 1}, {5, 1}, 
			{5, 4}, {5, 7}, {1, 1}, {3, 2}, {5, 2}, {5, 5}, {5, 8}, {1, 2},
			{3, 3}, {5, 3}, {5, 6}, {5, 9}, {1, 3}
		}
	},{
		{
			{2, 1}, {2, 2}, {2, 3}, {4, 1}, {4, 2}, {4, 3}, {1, 3}, {5, 9}, 
			{5, 6}, {5, 3}, {3, 3}, {1, 2}, {5, 8}, {5, 5}, {5, 2}, {3, 2}, 
			{1, 1}, {5, 7}, {5, 4}, {5, 1}, {3, 1}
		}
	},
	{
		{
			{2, 9}, {2, 8}, {2, 7}, {4, 9}, {4, 8}, {4, 7}, {3, 9}, {6, 3}, 
			{6, 6}, {6, 9}, {1, 9}, {3, 8}, {6, 2}, {6, 5}, {6, 8}, {1, 8},
			{3, 7}, {6, 1}, {6, 4}, {6, 7}, {1, 7}
		}
	},
	{
		{
			{4, 7}, {4, 8}, {4, 9}, {2, 7}, {2, 8}, {2, 9}, {1, 7}, {6, 7}, 
			{6, 4}, {6, 1}, {3, 7}, {1, 8}, {6, 8}, {6, 5}, {6, 2}, {3, 8},
			{1, 9}, {6, 9}, {6, 6}, {6, 3}, {3, 9}
		}
	},
	{
		{
			{3, 8}, {3, 5}, {3, 2}, {1, 8}, {1, 5}, {1, 2}, {6, 2}, {0, 0}, 
			{0, 0}, {0, 0}, {5, 2}, {6, 5}, {0, 0}, {0, 0}, {0, 0}, {5, 5},
			{6, 8}, {0, 0}, {0, 0}, {0, 0}, {5, 8}
		}
	},//0-13. -- 14.
	{
		{
			{1, 2}, {1, 5}, {1, 8}, {3, 2}, {3, 5}, {3, 8}, {5, 8}, {0, 0}, 
			{0, 0}, {0, 0}, {6, 8}, {5, 5}, {0, 0}, {0, 0}, {0, 0}, {6, 5},
			{5, 2}, {0, 0}, {0, 0}, {0, 0}, {6, 2}
		}
	},
	{
		{
			{4, 2}, {4, 5}, {4, 8}, {2, 2}, {2, 5}, {2, 8}, {5, 4}, {0, 0}, 
			{0, 0}, {0, 0}, {6, 4}, {5, 5}, {0, 0}, {0, 0}, {0, 0}, {6, 5},
			{5, 6}, {0, 0}, {0, 0}, {0, 0}, {6, 6}
		}
	},
	{
		{
			{2, 8}, {2, 5}, {2, 2}, {4, 8}, {4, 5}, {4, 2}, {6, 6}, {0, 0}, 
			{0, 0}, {0, 0}, {5, 6}, {6, 5}, {0, 0}, {0, 0}, {0, 0}, {5, 5},
			{6, 4}, {0, 0}, {0, 0}, {0, 0}, {5, 4}
		}
	},
	{
		{
			{2, 6}, {2, 5}, {2, 4}, {4, 6}, {4, 5}, {4, 4}, {3, 6}, {0, 0}, 
			{0, 0}, {0, 0}, {1, 6}, {3, 5}, {0, 0}, {0, 0}, {0, 0}, {1, 5},
			{3, 4}, {0, 0}, {0, 0}, {0, 0}, {1, 4}
		}
	},
	{
		{
			{4, 4}, {4, 5}, {4, 6}, {2, 4}, {2, 5}, {2, 6}, {1, 4}, {0, 0}, 
			{0, 0}, {0, 0}, {3, 4}, {1, 5}, {0, 0}, {0, 0}, {0, 0}, {3, 5},
			{1, 6}, {0, 0}, {0, 0}, {0, 0}, {3, 6}
		}
	}
};

void refreshCube()
{
	CubeModel* cubeModel = getCube();

	int i;
	int j;
	int k,l=1;
	for(i=1; i!=7; i++)
	{
		if(sideRotate[i-1].deg > 0.0) continue;
		if(i==1 && g_vEye.z < 2.5) continue;
		else if(i==2 && g_vEye.x < 2.5) continue;
		else if(i==3 && g_vEye.z > 0) continue;
		else if(i==4 && g_vEye.x > 0) continue;
		else if(i==5 && g_vEye.y < 2.5) continue;
		else if(i==6 && g_vEye.y > 0) continue;

		for(j=1; j!=10; j++)
		{
			l=1;
			if(rotating != -1)
			{
				int s = rotating + (rotating-1)+1;

				for(k=0; k!=21; k++)
					if(lapSzinek[s].e[k].side == i && lapSzinek[s].e[k].place==j) 
						l=0;
				if(!l) continue;
			}

			setColorGrid(i, j, cubeModel->GetCellColor(i, j).Red, cubeModel->GetCellColor(i, j).Green, cubeModel->GetCellColor(i, j).Blue);
		}
	}
}

void saveCubeColors()
{
	CubeModel* cubeModel = getCube();
	CubeModel* oldCubeModel = getOldCube();

	int a,b;
	for(a=1; a!=7; a++) {
		for(b=1; b!=10; b++) {
			oldCubeModel->SetCellColor(a, b, cubeModel->GetCellColor(a, b));
		}
	}
	return;

}

void loadCubeColors()
{
	CubeModel* cubeModel = getCube();
	CubeModel* oldCubeModel = getOldCube();

	int a,b;
	for(a=1; a!=7; a++) 
	{
		for(b=1; b!=10; b++) {
			cubeModel->SetCellColor(a, b, oldCubeModel->GetCellColor(a, b));
		}
	}
	

	int c = 2;

	return;
}


void cAddQueue(char *cmd)
{
	sprintf(history[step].step, "%s", cmd);
	step++;
}


int noRotating()
{

	return stillRotate;

	int snum;
	for(snum=0; snum!=6; snum++)
	{
		if(fabs(sideRotate[snum].deg) < 2.0)
		{
			return 1;

		}
	}
	return 0;
}




void rotateColorSide(int num)
{
	int i;
	int n = num/2;
	//int n=num;

	CubeModel* cubeModel = getCube();
	
	for(i=0; i!=21; i++)
	{
		CubeModel::CubeColor color = cubeModel->GetCellColor(lapSzinek[num].e[i].side, lapSzinek[num].e[i].place);

		sideRotate[n].colors[i].red = color.Red;
		sideRotate[n].colors[i].green = color.Green;
		sideRotate[n].colors[i].blue = color.Blue;
	}
	if((num%2) != 0) sideRotate[n].deg=-90;
	else sideRotate[n].deg=90;

	if(num==8 || num==9 || num==14 || num==15) sideRotate[n].deg = -1 * sideRotate[n].deg;
}