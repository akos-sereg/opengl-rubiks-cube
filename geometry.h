struct mycolor 
{
	double red;
	double green;
	double blue;
};

//-----------------------------------------------------------------------------
//           Name: geometry.h
//         Author: Freeglut
//  Last Modified: 01/27/05
//    Description: Data and utility functions for rendering several useful 
//                 geometric shapes. This code is a modified version of the 
//                 code found in "freeglut_teapot.c" and "freeglut_geometry.c", 
//                 which is part of the open source project, Freegut.
//                 http://freeglut.sourceforge.net/
//
//                 See the text below this comment for all the legal licensing 
//                 mumbo-jumbo.
//
// The following functions are defined here:
//
// void renderWireTeapot(GLdouble size);
// void renderSolidTeapot(GLdouble size);
// void renderWireCube(GLdouble size);
// void renderSolidCube(GLdouble size);
void renderGridColor( GLdouble dSize, double red, double green, double blue);
void renderWireCubeColor( GLdouble dSize, double color);
void renderCubeColor( GLdouble dSize, double color);
extern void renderWireSphere(double radius, int slices, int stacks);
// void renderSolidSphere(GLdouble radius, GLint slices, GLint stacks);
// void renderWireCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);
// void renderSolidCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);
// void renderWireTorus(GLdouble innerRadius, GLdouble outerRadius, GLint sides, GLint rings);
// void renderSolidTorus(GLdouble innerRadius, GLdouble outerRadius, GLint sides, GLint rings);
// void renderWireDodecahedron(void);
// void renderSolidDodecahedron(void);
// void renderWireOctahedron(void);
// void renderSolidOctahedron(void);
// void renderWireTetrahedron(void);
// void renderSolidTetrahedron(void);
// void renderWireIcosahedron(void);
// void renderSolidIcosahedron(void);
// void renderWireSierpinskiSponge(int num_levels, GLdouble offset[3], GLdouble scale);
// void renderSolidSierpinskiSponge(int num_levels, GLdouble offset[3], GLdouble scale);
void renderWall( GLdouble dSize);
//-----------------------------------------------------------------------------

#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

/*
 * freeglut_geometry.c
 *
 * Freeglut geometry rendering methods.
 *
 * Copyright (c) 1999-2000 Pawel W. Olszta. All Rights Reserved.
 * Written by Pawel W. Olszta, <olszta@sourceforge.net>
 * Creation date: Fri Dec 3 1999
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * PAWEL W. OLSZTA BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifdef _WIN32
#include <windows.h>
#endif

#include <stdlib.h>
// Do this to access M_PI, which is not officially part of the C/C++ standard.
#define _USE_MATH_DEFINES 
#include <math.h>
#include <GL/gl.h>
//#include "resource.h"

/* -- INTERFACE FUNCTIONS -------------------------------------------------- */

/*
 * Draws a wireframed cube. Code contributed by Andreas Umbach <marvin@dataway.ch>
 */

struct Vertex2
{
	// GL_C4UB_V3F
	unsigned char r, g, b, a;
	float x, y, z;
};



enum BitmapFontType
{
    BITMAP_FONT_TYPE_8_BY_13,
    BITMAP_FONT_TYPE_9_BY_15,
    BITMAP_FONT_TYPE_HELVETICA_10,
    BITMAP_FONT_TYPE_HELVETICA_12,
    BITMAP_FONT_TYPE_HELVETICA_18,
    BITMAP_FONT_TYPE_TIMES_ROMAN_10,
    BITMAP_FONT_TYPE_TIMES_ROMAN_24
};
/*
 * The bitmap font structure
 */

struct BitmapFontData
{
    char*           Name;         /* The source font name             */
    int             Quantity;     /* Number of chars in font          */
    int             Height;       /* Height of the characters         */
    const GLubyte** Characters;   /* The characters mapping           */

    float           xorig, yorig; /* Relative origin of the character */
};


//-----------------------------------------------------------------------------
// Name: beginRenderText()
// Desc: Utility function for using the bitmap-based character fonts defined 
//       above. Call this function to begin rendering text. Call the function 
//       endRenderText to stop.
//-----------------------------------------------------------------------------
void beginRenderText( int nWindowWidth, int nWindowHeight )
{
    // Push back and cache the current state of pixel alignment.
    glPushClientAttrib( GL_CLIENT_PIXEL_STORE_BIT );
    glPixelStorei( GL_UNPACK_SWAP_BYTES, GL_FALSE );
    glPixelStorei( GL_UNPACK_LSB_FIRST, GL_FALSE );
    glPixelStorei( GL_UNPACK_ROW_LENGTH, 0 );
    glPixelStorei( GL_UNPACK_SKIP_ROWS, 0 );
    glPixelStorei( GL_UNPACK_SKIP_PIXELS, 0 );
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

    // Push back and cache the current state of depth testing and lighting
    // and then disable them.
    glPushAttrib( GL_TEXTURE_BIT | GL_DEPTH_TEST | GL_LIGHTING );

    glDisable( GL_TEXTURE_2D );
    glDisable( GL_DEPTH_TEST );
    glDisable( GL_LIGHTING );

    // Push back the current matrices and go orthographic for text rendering.
    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glLoadIdentity();
    glOrtho( 0, (double)nWindowWidth, (double)nWindowHeight, 0, -1, 1 );

    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    glLoadIdentity();
}

//-----------------------------------------------------------------------------
// Name: endRenderText()
// Desc: Utility function for using the bitmap-based character fonts defined 
//       above. Call this function to stop rendering text. The call to 
//       beginRenderText should come first and be paired with this function.
//-----------------------------------------------------------------------------
void endRenderText( void )
{
    // Pop everything back to what ever it was set to before we started 
    // rendering text to the screen.

	
    glMatrixMode( GL_PROJECTION );
    glPopMatrix();

    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();

    glPopClientAttrib();

    glPopAttrib();
}



/* The font structure: */

static const GLubyte Helvetica10_Character_032[] = {  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}; /* " " */
static const GLubyte Helvetica10_Character_097[] = {  5,  0,  0,104,144,144,112, 16,224,  0,  0,  0,  0,  0}; /* "a" */
static const GLubyte Helvetica10_Character_098[] = {  6,  0,  0,176,200,136,136,200,176,128,128,  0,  0,  0}; /* "b" */
static const GLubyte Helvetica10_Character_099[] = {  5,  0,  0, 96,144,128,128,144, 96,  0,  0,  0,  0,  0}; /* "c" */
static const GLubyte Helvetica10_Character_100[] = {  6,  0,  0,104,152,136,136,152,104,  8,  8,  0,  0,  0}; /* "d" */
static const GLubyte Helvetica10_Character_101[] = {  5,  0,  0, 96,144,128,240,144, 96,  0,  0,  0,  0,  0}; /* "e" */
static const GLubyte Helvetica10_Character_102[] = {  4,  0,  0, 64, 64, 64, 64, 64,224, 64, 48,  0,  0,  0}; /* "f" */
static const GLubyte Helvetica10_Character_103[] = {  6,112,  8,104,152,136,136,152,104,  0,  0,  0,  0,  0}; /* "g" */
static const GLubyte Helvetica10_Character_104[] = {  6,  0,  0,136,136,136,136,200,176,128,128,  0,  0,  0}; /* "h" */
static const GLubyte Helvetica10_Character_105[] = {  2,  0,  0,128,128,128,128,128,128,  0,128,  0,  0,  0}; /* "i" */
static const GLubyte Helvetica10_Character_106[] = {  2,  0,128,128,128,128,128,128,128,  0,128,  0,  0,  0}; /* "j" */
static const GLubyte Helvetica10_Character_107[] = {  5,  0,  0,144,144,160,192,160,144,128,128,  0,  0,  0}; /* "k" */
static const GLubyte Helvetica10_Character_108[] = {  2,  0,  0,128,128,128,128,128,128,128,128,  0,  0,  0}; /* "l" */
static const GLubyte Helvetica10_Character_109[] = {  8,  0,  0,146,146,146,146,146,236,  0,  0,  0,  0,  0}; /* "m" */
static const GLubyte Helvetica10_Character_110[] = {  6,  0,  0,136,136,136,136,200,176,  0,  0,  0,  0,  0}; /* "n" */
static const GLubyte Helvetica10_Character_111[] = {  6,  0,  0,112,136,136,136,136,112,  0,  0,  0,  0,  0}; /* "o" */
static const GLubyte Helvetica10_Character_112[] = {  6,128,128,176,200,136,136,200,176,  0,  0,  0,  0,  0}; /* "p" */
static const GLubyte Helvetica10_Character_113[] = {  6,  8,  8,104,152,136,136,152,104,  0,  0,  0,  0,  0}; /* "q" */
static const GLubyte Helvetica10_Character_114[] = {  4,  0,  0,128,128,128,128,192,160,  0,  0,  0,  0,  0}; /* "r" */
static const GLubyte Helvetica10_Character_115[] = {  5,  0,  0, 96,144, 16, 96,144, 96,  0,  0,  0,  0,  0}; /* "s" */
static const GLubyte Helvetica10_Character_116[] = {  4,  0,  0, 96, 64, 64, 64, 64,224, 64, 64,  0,  0,  0}; /* "t" */
static const GLubyte Helvetica10_Character_117[] = {  5,  0,  0,112,144,144,144,144,144,  0,  0,  0,  0,  0}; /* "u" */
static const GLubyte Helvetica10_Character_118[] = {  6,  0,  0, 32, 32, 80, 80,136,136,  0,  0,  0,  0,  0}; /* "v" */
static const GLubyte Helvetica10_Character_119[] = {  8,  0,  0, 40, 40, 84, 84,146,146,  0,  0,  0,  0,  0}; /* "w" */
static const GLubyte Helvetica10_Character_120[] = {  6,  0,  0,136,136, 80, 32, 80,136,  0,  0,  0,  0,  0}; /* "x" */
static const GLubyte Helvetica10_Character_121[] = {  5,128, 64, 64, 96,160,160,144,144,  0,  0,  0,  0,  0}; /* "y" */
static const GLubyte Helvetica10_Character_122[] = {  5,  0,  0,240,128, 64, 32, 16,240,  0,  0,  0,  0,  0}; /* "z" */
static const GLubyte Helvetica10_Character_065[] = {  7,  0,  0,130,130,124, 68, 40, 40, 16, 16,  0,  0,  0}; /* "A" */
static const GLubyte Helvetica10_Character_066[] = {  7,  0,  0,240,136,136,136,240,136,136,240,  0,  0,  0}; /* "B" */
static const GLubyte Helvetica10_Character_067[] = {  8,  0,  0,120,132,128,128,128,128,132,120,  0,  0,  0}; /* "C" */
static const GLubyte Helvetica10_Character_068[] = {  8,  0,  0,240,136,132,132,132,132,136,240,  0,  0,  0}; /* "D" */
static const GLubyte Helvetica10_Character_069[] = {  7,  0,  0,248,128,128,128,248,128,128,248,  0,  0,  0}; /* "E" */
static const GLubyte Helvetica10_Character_070[] = {  6,  0,  0,128,128,128,128,240,128,128,248,  0,  0,  0}; /* "F" */
static const GLubyte Helvetica10_Character_071[] = {  8,  0,  0,116,140,132,140,128,128,132,120,  0,  0,  0}; /* "G" */
static const GLubyte Helvetica10_Character_072[] = {  8,  0,  0,132,132,132,132,252,132,132,132,  0,  0,  0}; /* "H" */
static const GLubyte Helvetica10_Character_073[] = {  3,  0,  0,128,128,128,128,128,128,128,128,  0,  0,  0}; /* "I" */
static const GLubyte Helvetica10_Character_074[] = {  5,  0,  0, 96,144, 16, 16, 16, 16, 16, 16,  0,  0,  0}; /* "J" */
static const GLubyte Helvetica10_Character_075[] = {  7,  0,  0,136,136,144,144,224,160,144,136,  0,  0,  0}; /* "K" */
static const GLubyte Helvetica10_Character_076[] = {  6,  0,  0,240,128,128,128,128,128,128,128,  0,  0,  0}; /* "L" */
static const GLubyte Helvetica10_Character_077[] = {  9,  0,  0,  0,  0,146,  0,146,  0,146,  0,170,  0,170,  0,198,  0,198,  0,130,  0,  0,  0,  0,  0,  0,  0}; /* "M" */
static const GLubyte Helvetica10_Character_078[] = {  8,  0,  0,140,140,148,148,164,164,196,196,  0,  0,  0}; /* "N" */
static const GLubyte Helvetica10_Character_079[] = {  8,  0,  0,120,132,132,132,132,132,132,120,  0,  0,  0}; /* "O" */
static const GLubyte Helvetica10_Character_080[] = {  7,  0,  0,128,128,128,128,240,136,136,240,  0,  0,  0}; /* "P" */
static const GLubyte Helvetica10_Character_081[] = {  8,  0,  2,124,140,148,132,132,132,132,120,  0,  0,  0}; /* "Q" */
static const GLubyte Helvetica10_Character_082[] = {  7,  0,  0,136,136,136,136,240,136,136,240,  0,  0,  0}; /* "R" */
static const GLubyte Helvetica10_Character_083[] = {  7,  0,  0,112,136,136,  8,112,128,136,112,  0,  0,  0}; /* "S" */
static const GLubyte Helvetica10_Character_084[] = {  5,  0,  0, 32, 32, 32, 32, 32, 32, 32,248,  0,  0,  0}; /* "T" */
static const GLubyte Helvetica10_Character_085[] = {  8,  0,  0,120,132,132,132,132,132,132,132,  0,  0,  0}; /* "U" */
static const GLubyte Helvetica10_Character_086[] = {  7,  0,  0, 16, 40, 40, 68, 68, 68,130,130,  0,  0,  0}; /* "V" */
static const GLubyte Helvetica10_Character_087[] = {  9,  0,  0,  0,  0, 34,  0, 34,  0, 34,  0, 85,  0, 73,  0, 73,  0,136,128,136,128,  0,  0,  0,  0,  0,  0}; /* "W" */
static const GLubyte Helvetica10_Character_088[] = {  7,  0,  0,136,136, 80, 80, 32, 80,136,136,  0,  0,  0}; /* "X" */
static const GLubyte Helvetica10_Character_089[] = {  7,  0,  0, 16, 16, 16, 40, 40, 68, 68,130,  0,  0,  0}; /* "Y" */
static const GLubyte Helvetica10_Character_090[] = {  7,  0,  0,248,128, 64, 32, 32, 16,  8,248,  0,  0,  0}; /* "Z" */
static const GLubyte Helvetica10_Character_048[] = {  6,  0,  0,112,136,136,136,136,136,136,112,  0,  0,  0}; /* "0" */
static const GLubyte Helvetica10_Character_049[] = {  6,  0,  0, 64, 64, 64, 64, 64, 64,192, 64,  0,  0,  0}; /* "1" */
static const GLubyte Helvetica10_Character_050[] = {  6,  0,  0,248,128, 64, 48,  8,  8,136,112,  0,  0,  0}; /* "2" */
static const GLubyte Helvetica10_Character_051[] = {  6,  0,  0,112,136,  8,  8, 48,  8,136,112,  0,  0,  0}; /* "3" */
static const GLubyte Helvetica10_Character_052[] = {  6,  0,  0, 16, 16,248,144, 80, 80, 48, 16,  0,  0,  0}; /* "4" */
static const GLubyte Helvetica10_Character_053[] = {  6,  0,  0,112,136,  8,  8,240,128,128,248,  0,  0,  0}; /* "5" */
static const GLubyte Helvetica10_Character_054[] = {  6,  0,  0,112,136,136,200,176,128,136,112,  0,  0,  0}; /* "6" */
static const GLubyte Helvetica10_Character_055[] = {  6,  0,  0, 64, 64, 32, 32, 16, 16,  8,248,  0,  0,  0}; /* "7" */
static const GLubyte Helvetica10_Character_056[] = {  6,  0,  0,112,136,136,136,112,136,136,112,  0,  0,  0}; /* "8" */
static const GLubyte Helvetica10_Character_057[] = {  6,  0,  0,112,136,  8,104,152,136,136,112,  0,  0,  0}; /* "9" */
static const GLubyte Helvetica10_Character_096[] = {  3,  0,  0,  0,  0,  0,  0,  0,128,128, 64,  0,  0,  0}; /* "`" */
static const GLubyte Helvetica10_Character_126[] = {  7,  0,  0,  0,  0,  0,152,100,  0,  0,  0,  0,  0,  0}; /* "~" */
static const GLubyte Helvetica10_Character_033[] = {  3,  0,  0,128,  0,128,128,128,128,128,128,  0,  0,  0}; /* "!" */
static const GLubyte Helvetica10_Character_064[] = { 11, 62,  0, 64,  0,155,  0,164,128,164,128,162, 64,146, 64, 77, 64, 32,128, 31,  0,  0,  0,  0,  0,  0,  0}; /* "@" */
static const GLubyte Helvetica10_Character_035[] = {  6,  0,  0, 80, 80,248, 40,124, 40, 40,  0,  0,  0,  0}; /* "#" */
static const GLubyte Helvetica10_Character_036[] = {  6,  0, 32,112,168, 40,112,160,168,112, 32,  0,  0,  0}; /* "$" */
static const GLubyte Helvetica10_Character_037[] = {  9,  0,  0,  0,  0, 38,  0, 41,  0, 22,  0, 16,  0,  8,  0,104,  0,148,  0,100,  0,  0,  0,  0,  0,  0,  0}; /* "%" */
static const GLubyte Helvetica10_Character_094[] = {  6,  0,  0,  0,  0,  0,136, 80, 80, 32, 32,  0,  0,  0}; /* "^" */
static const GLubyte Helvetica10_Character_038[] = {  8,  0,  0,100,152,152,164, 96, 80, 80, 32,  0,  0,  0}; /* "&" */
static const GLubyte Helvetica10_Character_042[] = {  4,  0,  0,  0,  0,  0,  0,  0,160, 64,160,  0,  0,  0}; /* "*" */
static const GLubyte Helvetica10_Character_040[] = {  4, 32, 64, 64,128,128,128,128, 64, 64, 32,  0,  0,  0}; /* "(" */
static const GLubyte Helvetica10_Character_041[] = {  4,128, 64, 64, 32, 32, 32, 32, 64, 64,128,  0,  0,  0}; /* ")" */
static const GLubyte Helvetica10_Character_045[] = {  7,  0,  0,  0,  0,  0,248,  0,  0,  0,  0,  0,  0,  0}; /* "-" */
static const GLubyte Helvetica10_Character_095[] = {  6,252,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}; /* "_" */
static const GLubyte Helvetica10_Character_061[] = {  5,  0,  0,  0,  0,240,  0,240,  0,  0,  0,  0,  0,  0}; /* "=" */
static const GLubyte Helvetica10_Character_043[] = {  6,  0,  0,  0, 32, 32,248, 32, 32,  0,  0,  0,  0,  0}; /* "+" */
static const GLubyte Helvetica10_Character_091[] = {  3,192,128,128,128,128,128,128,128,128,192,  0,  0,  0}; /* "[" */
static const GLubyte Helvetica10_Character_123[] = {  3, 32, 64, 64, 64, 64,128, 64, 64, 64, 32,  0,  0,  0}; /* "{" */
static const GLubyte Helvetica10_Character_125[] = {  3,128, 64, 64, 64, 64, 32, 64, 64, 64,128,  0,  0,  0}; /* "}" */
static const GLubyte Helvetica10_Character_093[] = {  3,192, 64, 64, 64, 64, 64, 64, 64, 64,192,  0,  0,  0}; /* "]" */
static const GLubyte Helvetica10_Character_059[] = {  3,128, 64, 64,  0,  0,  0,  0, 64,  0,  0,  0,  0,  0}; /* ";" */
static const GLubyte Helvetica10_Character_058[] = {  3,  0,  0,128,  0,  0,  0,  0,128,  0,  0,  0,  0,  0}; /* ":" */
static const GLubyte Helvetica10_Character_044[] = {  3,128, 64, 64,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}; /* "," */
static const GLubyte Helvetica10_Character_046[] = {  3,  0,  0,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}; /* "." */
static const GLubyte Helvetica10_Character_060[] = {  6,  0,  0,  0, 32, 64,128, 64, 32,  0,  0,  0,  0,  0}; /* "<" */
static const GLubyte Helvetica10_Character_062[] = {  6,  0,  0,  0,128, 64, 32, 64,128,  0,  0,  0,  0,  0}; /* ">" */
static const GLubyte Helvetica10_Character_047[] = {  3,  0,  0,128,128, 64, 64, 64, 64, 32, 32,  0,  0,  0}; /* "/" */
static const GLubyte Helvetica10_Character_063[] = {  6,  0,  0, 64,  0, 64, 64, 32, 16,144, 96,  0,  0,  0}; /* "?" */
static const GLubyte Helvetica10_Character_092[] = {  3,  0,  0, 32, 32, 64, 64, 64, 64,128,128,  0,  0,  0}; /* "\" */
static const GLubyte Helvetica10_Character_034[] = {  4,  0,  0,  0,  0,  0,  0,  0,  0,160,160,  0,  0,  0}; /* """ */

/* Missing Characters filled in by John Fay by hand ... */
static const GLubyte Helvetica10_Character_039[] = {  3,  0,  0,  0,  0,  0,  0,  0,128, 64, 64,  0,  0,  0}; /* "'" */
static const GLubyte Helvetica10_Character_124[] = {  3, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,  0,  0}; /* "|" */

static const GLubyte* Helvetica10_Character_Map[] = {Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_032,Helvetica10_Character_033,Helvetica10_Character_034,Helvetica10_Character_035,Helvetica10_Character_036,Helvetica10_Character_037,
 Helvetica10_Character_038,Helvetica10_Character_039,Helvetica10_Character_040,Helvetica10_Character_041,Helvetica10_Character_042,Helvetica10_Character_043,Helvetica10_Character_044,Helvetica10_Character_045,Helvetica10_Character_046,Helvetica10_Character_047,Helvetica10_Character_048,Helvetica10_Character_049,Helvetica10_Character_050,Helvetica10_Character_051,Helvetica10_Character_052,Helvetica10_Character_053,Helvetica10_Character_054,Helvetica10_Character_055,Helvetica10_Character_056,Helvetica10_Character_057,Helvetica10_Character_058,Helvetica10_Character_059,Helvetica10_Character_060,Helvetica10_Character_061,Helvetica10_Character_062,Helvetica10_Character_063,Helvetica10_Character_064,Helvetica10_Character_065,Helvetica10_Character_066,Helvetica10_Character_067,Helvetica10_Character_068,Helvetica10_Character_069,Helvetica10_Character_070,Helvetica10_Character_071,Helvetica10_Character_072,Helvetica10_Character_073,Helvetica10_Character_074,Helvetica10_Character_075,Helvetica10_Character_076,
 Helvetica10_Character_077,Helvetica10_Character_078,Helvetica10_Character_079,Helvetica10_Character_080,Helvetica10_Character_081,Helvetica10_Character_082,Helvetica10_Character_083,Helvetica10_Character_084,Helvetica10_Character_085,Helvetica10_Character_086,Helvetica10_Character_087,Helvetica10_Character_088,Helvetica10_Character_089,Helvetica10_Character_090,Helvetica10_Character_091,Helvetica10_Character_092,Helvetica10_Character_093,Helvetica10_Character_094,Helvetica10_Character_095,Helvetica10_Character_096,Helvetica10_Character_097,Helvetica10_Character_098,Helvetica10_Character_099,Helvetica10_Character_100,Helvetica10_Character_101,Helvetica10_Character_102,Helvetica10_Character_103,Helvetica10_Character_104,Helvetica10_Character_105,Helvetica10_Character_106,Helvetica10_Character_107,Helvetica10_Character_108,Helvetica10_Character_109,Helvetica10_Character_110,Helvetica10_Character_111,Helvetica10_Character_112,Helvetica10_Character_113,Helvetica10_Character_114,Helvetica10_Character_115,
 Helvetica10_Character_116,Helvetica10_Character_117,Helvetica10_Character_118,Helvetica10_Character_119,Helvetica10_Character_120,Helvetica10_Character_121,Helvetica10_Character_122,Helvetica10_Character_123,Helvetica10_Character_124,Helvetica10_Character_125,Helvetica10_Character_126,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,
 Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,
 Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,
 Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,Helvetica10_Character_042,NULL};
const BitmapFontData FontHelvetica10 = { "-adobe-helvetica-medium-r-normal--10-100-75-75-p-56-iso8859-1", 93, 13, Helvetica10_Character_Map, -1.0f, 2.0f };

//-----------------------------------------------------------------------------
// Name: getBitmapFontDataByType()
// Desc: Matches a BitmapFontType with a BitmapFontData structure pointer.
//-----------------------------------------------------------------------------
const BitmapFontData* getBitmapFontDataByType( BitmapFontType font )
{
   /* if( font == BITMAP_FONT_TYPE_8_BY_13 )
        return &FontFixed8x13;
    if( font == BITMAP_FONT_TYPE_9_BY_15 )
        return &FontFixed9x15;*/
    if( font == BITMAP_FONT_TYPE_HELVETICA_10 )
        return &FontHelvetica10;
    /*if( font == BITMAP_FONT_TYPE_HELVETICA_12 )
        return &FontHelvetica12;
    if( font == BITMAP_FONT_TYPE_HELVETICA_18 )
        return &FontHelvetica18;
    if( font == BITMAP_FONT_TYPE_TIMES_ROMAN_10 )
        return &FontTimesRoman10;
    if( font == BITMAP_FONT_TYPE_TIMES_ROMAN_24 )
        return &FontTimesRoman24;
*/
    return 0;
}

//-----------------------------------------------------------------------------
// Name: renderText()
// Desc: Utility function for using the bitmap-based character fonts defined 
//       above. This function must be called in between a call to 
//       beginRenderText and endRenderText. See the example below:
//
//       beginRenderText( nWindowWidth, nWindowHeight );
//       {
//           renderText( 5, 10, "This is a test!", BITMAP_FONT_TYPE_HELVETICA_12 );
//       }
//       endRenderText();
//
//-----------------------------------------------------------------------------
void renderText( float x, float y, BitmapFontType fontType, char *string )
{
	
    glRasterPos2f( x, y );

    const BitmapFontData *font = getBitmapFontDataByType( fontType );
    const unsigned char* face;
    char *c = '\0';

    for( c = string; *c != '\0'; ++c )
    {
        // Find the character face that we want to draw.
        face = font->Characters[*c-1];

        glBitmap( face[0], font->Height,    // The bitmap's width and height
                  font->xorig, font->yorig, // The origin in the font glyph
                  (float)(face[0]), 0.0,    // The raster advance -- inc. x,y
                  (face+1) );               // The packed bitmap data...
    }
	
}



void renderTextFull(float x, float y, char *str)
{
	
	beginRenderText(800, 600);
	{
		renderText(x, y, BITMAP_FONT_TYPE_HELVETICA_10, str);
	}
	endRenderText();
}




void renderWireCube( GLdouble dSize )
{
    double size = dSize * 0.5;

#   define V(a,b,c) glVertex3d( a size, b size, c size );
#   define N(a,b,c) glNormal3d( a, b, c );

    /*
     * PWO: I dared to convert the code to use macros...
     */
    glBegin( GL_LINE_LOOP ); N( 1.0, 0.0, 0.0); V(+,-,+); V(+,-,-); V(+,+,-); V(+,+,+); glEnd();
    glBegin( GL_LINE_LOOP ); N( 0.0, 1.0, 0.0); V(+,+,+); V(+,+,-); V(-,+,-); V(-,+,+); glEnd();
    glBegin( GL_LINE_LOOP ); N( 0.0, 0.0, 1.0); V(+,+,+); V(-,+,+); V(-,-,+); V(+,-,+); glEnd();
    glBegin( GL_LINE_LOOP ); N(-1.0, 0.0, 0.0); V(-,-,+); V(-,+,+); V(-,+,-); V(-,-,-); glEnd();
    glBegin( GL_LINE_LOOP ); N( 0.0,-1.0, 0.0); V(-,-,+); V(-,-,-); V(+,-,-); V(+,-,+); glEnd();
    glBegin( GL_LINE_LOOP ); N( 0.0, 0.0,-1.0); V(-,-,-); V(-,+,-); V(+,+,-); V(+,-,-); glEnd();

#   undef V
#   undef N
}
/*
void renderSide(struct mycolor *colors)
{
	int i, j;
	glTranslatef(-1.0, 0.5, 0.25);
	glPushMatrix();
	{
		glColor4f(0.0, 1.0, 0.0, 1.0);
		for(i=0; i!=3; i++)
		{
			for(j=0; j!=3; j++)
			{
				glTranslatef(0.0, 1.0, 0.0);
				renderWireCubeColor(0.8, 0.2);
				
			}
			glTranslatef(1.0, -3.0, 0.0);
		}
	
	}
	glPopMatrix();

}
*/
void renderSide(struct mycolor *colors )
{
    int i,j,n=0;
	
	glTranslatef((-1.0)*arany, -1.0*arany, -0.25*arany);
	//renderWireCubeColor(0.95, 0.5);
	double dst = 0.5;

	
	for(i=0; i!=3; i++)
	{
		
		//glRotatef(90.0, 0.0, 0.0, 1.0);
		glPushMatrix();
		{
			glTranslatef(1.0*i*arany, (-dst)*arany, 0.0*arany);
			renderGridColor(0.8*arany, colors[n].red, colors[n].green, colors[n].blue);
			n++;
		}
		glPopMatrix();
		//glRotatef(-90.0, 0.0, 0.0, 1.0);
	}
	for(i=0; i!=3; i++)
	{
		//glRotatef(90.0, 0.0, 0.0, 1.0);
		glPushMatrix();
		{
			glTranslatef(1.0*i*arany, (2.0 + dst+0.006)*arany, 0.0);
			renderGridColor(0.8*arany, colors[n].red, colors[n].green, colors[n].blue);
			n++;
		}
		glPopMatrix();
		//glRotatef(-90.0, 0.0, 0.0, 1.0);
	}

	for(j=0; j!=3; j++)
	{
		glPushMatrix();
		{
		glRotatef(90.0, 0.0, 0.0, 1.0);
		glTranslatef(0.0, (dst+0.006)*arany, 0.0);
		renderGridColor(0.8*arany, colors[n].red, colors[n].green, colors[n].blue);
		glTranslatef(0.0, (-dst-0.006)*arany, 0.0);
		glRotatef(-90.0, 0.0, 0.0, 1.0);
		
		n++;
		

		for(i=0; i!=3; i++)
		{
			glTranslatef(0.0, 0.0, 0.0);
			renderCubeColor(1.0*arany, 0.5*arany);
			glRotatef(90.0, 1.0, 0.0, 0.0);
			glTranslatef(0.0, (dst+0.006)*arany, 0.0);
			renderGridColor(0.8*arany, colors[n].red, colors[n].green, colors[n].blue);
			glTranslatef(0.0, (-dst-0.006)*arany, 0.0);
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			
			
			n++;

			glTranslatef(arany*1.0, 0.0, 0.0);
		}
		
		glRotatef(90.0, 0.0, 0.0, 1.0);
		glTranslatef(0.0, (dst-0.006)*arany, 0.0);
		renderGridColor(0.8*arany, colors[n].red, colors[n].green, colors[n].blue);
		glTranslatef(0.0, (-dst+0.006)*arany, 0.0);
		glRotatef(-90.0, 0.0, 0.0, 1.0);
		
		n++;

		glTranslatef(-3.0*arany, arany*1.0, 0.0);
		
		}
		glPopMatrix();
		glTranslatef(0.0, 1.0*arany, 0.0);
		
	}
	
	//glPopMatrix();
	

}

void renderLap()
{
	int i;
	int j;
	glPushMatrix();
	{
		for(i=0; i!=3; i++)
		{
			for(j=0; j!=3; j++)
			{
				renderCubeColor(0.95*arany, 0.5*arany);
				glTranslatef(0.95, 0.0, 0.0);
			}
			glTranslatef(-(3*0.95), 0.95, 0.0);
		}
	}
	glPopMatrix();
}


void renderWireCubeColor( GLdouble dSize, double color)
{
    double size = dSize * 0.5;

#   define V(a,b,c) glVertex3d( a size, b size, c size );
#   define N(a,b,c) glNormal3d( a, b, c );

	double red=0.1;
	double green=0.1;
	double blue=0.1;
    /*
     * PWO: I dared to convert the code to use macros...
     */

	GLenum g = GL_QUADS;
    glBegin(g); glColor3f(red, green, blue); N( 1.0, 0.0, 0.0); V(+,-,+); V(+,-,-); V(+,+,-); V(+,+,+); glEnd();
    glBegin(g); glColor3f(red, green, blue); N( 0.0, 1.0, 0.0); V(+,+,+); V(+,+,-); V(-,+,-); V(-,+,+); glEnd();
    glBegin(g); glColor3f(red, green, blue); N( 0.0, 0.0, 1.0); V(+,+,+); V(-,+,+); V(-,-,+); V(+,-,+); glEnd();
    glBegin(g); glColor3f(red, green, blue); N(-1.0, 0.0, 0.0); V(-,-,+); V(-,+,+); V(-,+,-); V(-,-,-); glEnd();
    glBegin(g); glColor3f(red, green, blue); N( 0.0,-1.0, 0.0); V(-,-,+); V(-,-,-); V(+,-,-); V(+,-,+); glEnd();
    glBegin(g); glColor3f(red, green, blue); N( 0.0, 0.0,-1.0); V(-,-,-); V(-,+,-); V(+,+,-); V(+,-,-); glEnd();

#   undef V
#   undef N
}


void renderCubeColor( GLdouble dSize, double color)
{
    double size = dSize * 0.5;

#   define V(a,b,c) glVertex3d( a size, b size, c size );
#   define N(a,b,c) glNormal3d( a, b, c );

	double red=0.05;
	double green=0.05;
	double blue=0.05;
    /*
     * PWO: I dared to convert the code to use macros...
     */
    glBegin( GL_QUADS ); glColor3f(red, green, blue); N( 1.0, 0.0, 0.0); V(+,-,+); V(+,-,-); V(+,+,-); V(+,+,+); glEnd();
    glBegin( GL_QUADS); glColor3f(red, green, blue); N( 0.0, 1.0, 0.0); V(+,+,+); V(+,+,-); V(-,+,-); V(-,+,+); glEnd();
    glBegin( GL_QUADS ); glColor3f(red, green, blue); N( 0.0, 0.0, 1.0); V(+,+,+); V(-,+,+); V(-,-,+); V(+,-,+); glEnd();
    glBegin( GL_QUADS); glColor3f(red, green, blue); N(-1.0, 0.0, 0.0); V(-,-,+); V(-,+,+); V(-,+,-); V(-,-,-); glEnd();
    glBegin(GL_QUADS); glColor3f(red, green, blue); N( 0.0,-1.0, 0.0); V(-,-,+); V(-,-,-); V(+,-,-); V(+,-,+); glEnd();
    glBegin( GL_QUADS ); glColor3f(red, green, blue); N( 0.0, 0.0,-1.0); V(-,-,-); V(-,+,-); V(+,+,-); V(+,-,-); glEnd();

#   undef V
#   undef N
}




void renderGridColor( GLdouble dSize, double red, double green, double blue)
{
    double size = dSize * 0.5;

#   define V(a,b,c) glVertex3d( a size, b size, c size );
#   define N(a,b,c) glNormal3d( a, b, c );

    /*
     * PWO: I dared to convert the code to use macros...
     */
 //   glBegin( GL_LINE_LOOP ); 
	double j;
	double y = size;
	double range = 0.05;
	
	glPushMatrix();
	{
		//glTranslatef(0.0, 0.1, 0.0);
		//renderWall(dSize);
		//glTranslatef(0.0, -0.1, 0.0);
		glColor4f(red, green, blue, 1.0); 

		N( 1.0, 0.0, 0.0); 
		//for(j=-y; j<y; j+=range)
		//{
			glBegin(GL_QUADS);
			{
				glVertex3d(y, 0.0, y);
				glVertex3d(y, 0.0, -y);
				glVertex3d(-y, 0.0, -y);
				glVertex3d(-y, 0.0, y);
			}
			glEnd();
			/*
			glBegin(GL_LINE_LOOP);
			{
				glVertex3d(j, 0.0, -y);
				glVertex3d(j, 0.0, y);
			}
			glEnd();

			glBegin(GL_LINE_LOOP);
			{
				glVertex3d(-y, 0.0, j);
				glVertex3d(y, 0.0, j);
			}
			glEnd();*/
					
		//}
		
		/*V(+,-,+); 
		V(+,-,-); 
		V(+,+,-); 
		V(+,+,+); */
//	glEnd();
    /*glBegin( GL_LINE_LOOP ); glColor3f(color, 0.0, 0.0); N( 0.0, 1.0, 0.0); V(+,+,+); V(+,+,-); V(-,+,-); V(-,+,+); glEnd();
    glBegin( GL_LINE_LOOP ); glColor3f(color, 0.0, 0.0); N( 0.0, 0.0, 1.0); V(+,+,+); V(-,+,+); V(-,-,+); V(+,-,+); glEnd();
    glBegin( GL_LINE_LOOP ); glColor3f(color, 0.0, 0.0); N(-1.0, 0.0, 0.0); V(-,-,+); V(-,+,+); V(-,+,-); V(-,-,-); glEnd();
    glBegin( GL_LINE_LOOP ); glColor3f(color, 0.0, 0.0); N( 0.0,-1.0, 0.0); V(-,-,+); V(-,-,-); V(+,-,-); V(+,-,+); glEnd();
    glBegin( GL_LINE_LOOP ); glColor3f(color, 0.0, 0.0); N( 0.0, 0.0,-1.0); V(-,-,-); V(-,+,-); V(+,+,-); V(+,-,-); glEnd();
*/
	}
	glPopMatrix();
#   undef V
#   undef N
}

void renderWall( GLdouble dSize)
{
    double size = dSize * 0.5;

#   define V(a,b,c) glVertex3d( a size, b size, c size );
#   define N(a,b,c) glNormal3d( a, b, c );

    /*
     * PWO: I dared to convert the code to use macros...
     */
 //   glBegin( GL_LINE_LOOP ); 
	double j;
	double y = size;
	double range = 0.05;
	glPushMatrix();
	{
		glColor4f(0.2, 0.2, 0.2, 0.0); 

		N( 1.0, 0.0, 0.0); 
		
			glBegin(GL_QUADS);
			{
				glVertex3d(y, 0.0, y);
				glVertex3d(y, 0.0, -y);
				glVertex3d(-y, 0.0, -y);
				glVertex3d(-y, 0.0, y);
			}
			glEnd();

					
		
		/*V(+,-,+); 
		V(+,-,-); 
		V(+,+,-); 
		V(+,+,+); */
//	glEnd();
    /*glBegin( GL_LINE_LOOP ); glColor3f(color, 0.0, 0.0); N( 0.0, 1.0, 0.0); V(+,+,+); V(+,+,-); V(-,+,-); V(-,+,+); glEnd();
    glBegin( GL_LINE_LOOP ); glColor3f(color, 0.0, 0.0); N( 0.0, 0.0, 1.0); V(+,+,+); V(-,+,+); V(-,-,+); V(+,-,+); glEnd();
    glBegin( GL_LINE_LOOP ); glColor3f(color, 0.0, 0.0); N(-1.0, 0.0, 0.0); V(-,-,+); V(-,+,+); V(-,+,-); V(-,-,-); glEnd();
    glBegin( GL_LINE_LOOP ); glColor3f(color, 0.0, 0.0); N( 0.0,-1.0, 0.0); V(-,-,+); V(-,-,-); V(+,-,-); V(+,-,+); glEnd();
    glBegin( GL_LINE_LOOP ); glColor3f(color, 0.0, 0.0); N( 0.0, 0.0,-1.0); V(-,-,-); V(-,+,-); V(+,+,-); V(+,-,-); glEnd();
*/
	}
	glPopMatrix();
#   undef V
#   undef N
}


/*
 * Draws a solid cube. Code contributed by Andreas Umbach <marvin@dataway.ch>
 */
void renderSolidCube( GLdouble dSize )
{
    double size = dSize * 0.5;

#   define V(a,b,c) glVertex3d( a size, b size, c size );
#   define N(a,b,c) glNormal3d( a, b, c );

    /*
     * PWO: Again, I dared to convert the code to use macros...
     */
    glBegin( GL_QUADS );
        N( 1.0, 0.0, 0.0); V(+,-,+); V(+,-,-); V(+,+,-); V(+,+,+);
        N( 0.0, 1.0, 0.0); V(+,+,+); V(+,+,-); V(-,+,-); V(-,+,+);
        N( 0.0, 0.0, 1.0); V(+,+,+); V(-,+,+); V(-,-,+); V(+,-,+);
        N(-1.0, 0.0, 0.0); V(-,-,+); V(-,+,+); V(-,+,-); V(-,-,-);
        N( 0.0,-1.0, 0.0); V(-,-,+); V(-,-,-); V(+,-,-); V(+,-,+);
        N( 0.0, 0.0,-1.0); V(-,-,-); V(-,+,-); V(+,+,-); V(+,-,-);
    glEnd();

#   undef V
#   undef N
}

void renderQuad( GLdouble dSize )
{
    double size = dSize * 0.5;

#   define V(a,b,c) glVertex3d( a size, b size, c size );
#   define N(a,b,c) glNormal3d( a, b, c );

    /*
     * PWO: Again, I dared to convert the code to use macros...
     */
    glBegin( GL_QUADS );
        N( 1.0, 0.0, 0.0); V(+,-,+); V(+,-,-); V(+,+,-); V(+,+,+);
   
    glEnd();

#   undef V
#   undef N
}

/*
 * Compute lookup table of cos and sin values forming a cirle
 *
 * Notes:
 *    It is the responsibility of the caller to free these tables
 *    The size of the table is (n+1) to form a connected loop
 *    The last entry is exactly the same as the first
 *    The sign of n can be flipped to get the reverse loop
 */

static void circleTable(double **sint,double **cost,const int n)
{
    int i;

    /* Table size, the sign of n flips the circle direction */

    const int size = abs(n);

    /* Determine the angle between samples */

    const double angle = 2*M_PI/(double)n;

    /* Allocate memory for n samples, plus duplicate of first entry at the end */

    *sint = (double *) calloc(sizeof(double), size+1);
    *cost = (double *) calloc(sizeof(double), size+1);

    /* Bail out if memory allocation fails, fgError never returns */

    if (!(*sint) || !(*cost))
    {
        free(*sint);
        free(*cost);
        //fgError("Failed to allocate memory in circleTable");
    }

    /* Compute cos and sin around the circle */

    for (i=0; i<size; i++)
    {
        (*sint)[i] = sin(angle*i);
        (*cost)[i] = cos(angle*i);
    }

    /* Last sample is duplicate of the first */

    (*sint)[size] = (*sint)[0];
    (*cost)[size] = (*cost)[0];
}

/*
 * Draws a solid sphere
 */

/*
 * Draws a solid sphere
 */
void renderWireSphere(GLdouble radius, GLint slices, GLint stacks)
{
    int i,j;

    /* Adjust z and radius as stacks and slices are drawn. */

    double r;
    double x,y,z;

    /* Pre-computed circle */
        
    double *sint1,*cost1;
    double *sint2,*cost2;
    circleTable(&sint1,&cost1,-slices  );
    circleTable(&sint2,&cost2, stacks*2);

    /* Draw a line loop for each stack */

    for (i=1; i<stacks; i++)
    {
        z = cost2[i];
        r = sint2[i];

        glBegin(GL_LINE_LOOP);

            for(j=0; j<=slices; j++)
            {
                x = cost1[j];
                y = sint1[j];

                glNormal3d(x,y,z);
                glVertex3d(x*r*radius,y*r*radius,z*radius);
            }

        glEnd();
    }

    /* Draw a line loop for each slice */

    for (i=0; i<slices; i++)
    {
        glBegin(GL_LINE_STRIP);

            for(j=0; j<=stacks; j++)
            {
                x = cost1[i]*sint2[j];
                y = sint1[i]*sint2[j];
                z = cost2[j];

                glNormal3d(x,y,z);
                glVertex3d(x*radius,y*radius,z*radius);
            }

        glEnd();
    }

    /* Release sin and cos tables */

    free(sint1);
    free(cost1);
    free(sint2);
    free(cost2);
}

/*
 *
 */
double rdod_r[14][3] = { { 0.0, 0.0, 1.0 },
  {  0.707106781187,  0.000000000000,  0.5 }, {  0.000000000000,  0.707106781187,  0.5 }, { -0.707106781187,  0.000000000000,  0.5 }, {  0.000000000000, -0.707106781187,  0.5 },
  {  0.707106781187,  0.707106781187,  0.0 }, { -0.707106781187,  0.707106781187,  0.0 }, { -0.707106781187, -0.707106781187,  0.0 }, {  0.707106781187, -0.707106781187,  0.0 },
  {  0.707106781187,  0.000000000000, -0.5 }, {  0.000000000000,  0.707106781187, -0.5 }, { -0.707106781187,  0.000000000000, -0.5 }, {  0.000000000000, -0.707106781187, -0.5 },
  {  0.0, 0.0, -1.0 } } ;
int rdod_v [12][4] = { { 0,  1,  5,  2 }, { 0,  2,  6,  3 }, { 0,  3,  7,  4 }, { 0,  4,  8, 1 },
                       { 5, 10,  6,  2 }, { 6, 11,  7,  3 }, { 7, 12,  8,  4 }, { 8,  9,  5, 1 },
                       { 5,  9, 13, 10 }, { 6, 10, 13, 11 }, { 7, 11, 13, 12 }, { 8, 12, 13, 9 } } ;
double rdod_n[12][3] = {
  {  0.353553390594,  0.353553390594,  0.5 }, { -0.353553390594,  0.353553390594,  0.5 }, { -0.353553390594, -0.353553390594,  0.5 }, {  0.353553390594, -0.353553390594,  0.5 },
  {  0.000000000000,  1.000000000000,  0.0 }, { -1.000000000000,  0.000000000000,  0.0 }, {  0.000000000000, -1.000000000000,  0.0 }, {  1.000000000000,  0.000000000000,  0.0 },
  {  0.353553390594,  0.353553390594, -0.5 }, { -0.353553390594,  0.353553390594, -0.5 }, { -0.353553390594, -0.353553390594, -0.5 }, {  0.353553390594, -0.353553390594, -0.5 }
  } ;


#define NUM_FACES     4

static GLdouble tetrahedron_v[4][3] =  /* Vertices */
{
  { -0.5, -0.288675134595, -0.144337567297 },
  {  0.5, -0.288675134595, -0.144337567297 },
  {  0.0,  0.577350269189, -0.144337567297 },
  {  0.0,  0.0,             0.672159013631 }
} ;

static GLint tetrahedron_i[4][3] =  /* Vertex indices */
{
  { 0, 1, 2 }, { 0, 2, 3 }, { 0, 3, 1 }, { 1, 3, 2 }
} ;

static GLdouble tetrahedron_n[4][3] =  /* Normals */
{
  {  0.0,             0.0,            -1.0 },
  { -0.816496580928,  0.471404520791,  0.333333333333 },
  {  0.0,            -0.942809041582,  0.333333333333 },
  {  0.816496580928,  0.471404520791,  0.333333333333 }
} ;

#undef NUM_FACES

/*
 * freeglut_teapot.c
 *
 * Teapot(tm) rendering code.
 *
 * Copyright (c) 1999-2000 Pawel W. Olszta. All Rights Reserved.
 * Written by Pawel W. Olszta, <olszta@sourceforge.net>
 * Creation date: Fri Dec 24 1999
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * PAWEL W. OLSZTA BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Original teapot code copyright follows:
 */

/*
 * (c) Copyright 1993, Silicon Graphics, Inc.
 *
 * ALL RIGHTS RESERVED
 *
 * Permission to use, copy, modify, and distribute this software
 * for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appear in all copies and that
 * both the copyright notice and this permission notice appear in
 * supporting documentation, and that the name of Silicon
 * Graphics, Inc. not be used in advertising or publicity
 * pertaining to distribution of the software without specific,
 * written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU
 * "AS-IS" AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR
 * OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  IN NO
 * EVENT SHALL SILICON GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE
 * ELSE FOR ANY DIRECT, SPECIAL, INCIDENTAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OF ANY KIND, OR ANY DAMAGES WHATSOEVER,
 * INCLUDING WITHOUT LIMITATION, LOSS OF PROFIT, LOSS OF USE,
 * SAVINGS OR REVENUE, OR THE CLAIMS OF THIRD PARTIES, WHETHER OR
 * NOT SILICON GRAPHICS, INC.  HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * ARISING OUT OF OR IN CONNECTION WITH THE POSSESSION, USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 * US Government Users Restricted Rights
 *
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer
 * Software clause at DFARS 252.227-7013 and/or in similar or
 * successor clauses in the FAR or the DOD or NASA FAR
 * Supplement.  Unpublished-- rights reserved under the copyright
 * laws of the United States.  Contractor/manufacturer is Silicon
 * Graphics, Inc., 2011 N.  Shoreline Blvd., Mountain View, CA
 * 94039-7311.
 *
 * OpenGL(TM) is a trademark of Silicon Graphics, Inc.
 */

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>

/* -- PRIVATE FUNCTIONS ---------------------------------------------------- */

/*
 * Rim, body, lid, and bottom data must be reflected in x and y;
 * handle and spout data across the y axis only.
 */
static int patchdata[][16] =
{
    { 102, 103, 104, 105,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15 }, /* rim    */
    {  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27 }, /* body   */
    {  24,  25,  26,  27,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40 },
    {  96,  96,  96,  96,  97,  98,  99, 100, 101, 101, 101, 101,   0,   1,   2,   3 }, /* lid    */
    {   0,   1,   2,   3, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117 },
    { 118, 118, 118, 118, 124, 122, 119, 121, 123, 126, 125, 120,  40,  39,  38,  37 }, /* bottom */
    {  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56 }, /* handle */
    {  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  28,  65,  66,  67 },
    {  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,  80,  81,  82,  83 }, /* spout  */
    {  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95 }
};

static double cpdata[][3] =
{
    {0.2, 0, 2.7}, {0.2, -0.112, 2.7}, {0.112, -0.2, 2.7}, {0,
    -0.2, 2.7}, {1.3375, 0, 2.53125}, {1.3375, -0.749, 2.53125},
    {0.749, -1.3375, 2.53125}, {0, -1.3375, 2.53125}, {1.4375,
    0, 2.53125}, {1.4375, -0.805, 2.53125}, {0.805, -1.4375,
    2.53125}, {0, -1.4375, 2.53125}, {1.5, 0, 2.4}, {1.5, -0.84,
    2.4}, {0.84, -1.5, 2.4}, {0, -1.5, 2.4}, {1.75, 0, 1.875},
    {1.75, -0.98, 1.875}, {0.98, -1.75, 1.875}, {0, -1.75,
    1.875}, {2, 0, 1.35}, {2, -1.12, 1.35}, {1.12, -2, 1.35},
    {0, -2, 1.35}, {2, 0, 0.9}, {2, -1.12, 0.9}, {1.12, -2,
    0.9}, {0, -2, 0.9}, {-2, 0, 0.9}, {2, 0, 0.45}, {2, -1.12,
    0.45}, {1.12, -2, 0.45}, {0, -2, 0.45}, {1.5, 0, 0.225},
    {1.5, -0.84, 0.225}, {0.84, -1.5, 0.225}, {0, -1.5, 0.225},
    {1.5, 0, 0.15}, {1.5, -0.84, 0.15}, {0.84, -1.5, 0.15}, {0,
    -1.5, 0.15}, {-1.6, 0, 2.025}, {-1.6, -0.3, 2.025}, {-1.5,
    -0.3, 2.25}, {-1.5, 0, 2.25}, {-2.3, 0, 2.025}, {-2.3, -0.3,
    2.025}, {-2.5, -0.3, 2.25}, {-2.5, 0, 2.25}, {-2.7, 0,
    2.025}, {-2.7, -0.3, 2.025}, {-3, -0.3, 2.25}, {-3, 0,
    2.25}, {-2.7, 0, 1.8}, {-2.7, -0.3, 1.8}, {-3, -0.3, 1.8},
    {-3, 0, 1.8}, {-2.7, 0, 1.575}, {-2.7, -0.3, 1.575}, {-3,
    -0.3, 1.35}, {-3, 0, 1.35}, {-2.5, 0, 1.125}, {-2.5, -0.3,
    1.125}, {-2.65, -0.3, 0.9375}, {-2.65, 0, 0.9375}, {-2,
    -0.3, 0.9}, {-1.9, -0.3, 0.6}, {-1.9, 0, 0.6}, {1.7, 0,
    1.425}, {1.7, -0.66, 1.425}, {1.7, -0.66, 0.6}, {1.7, 0,
    0.6}, {2.6, 0, 1.425}, {2.6, -0.66, 1.425}, {3.1, -0.66,
    0.825}, {3.1, 0, 0.825}, {2.3, 0, 2.1}, {2.3, -0.25, 2.1},
    {2.4, -0.25, 2.025}, {2.4, 0, 2.025}, {2.7, 0, 2.4}, {2.7,
    -0.25, 2.4}, {3.3, -0.25, 2.4}, {3.3, 0, 2.4}, {2.8, 0,
    2.475}, {2.8, -0.25, 2.475}, {3.525, -0.25, 2.49375},
    {3.525, 0, 2.49375}, {2.9, 0, 2.475}, {2.9, -0.15, 2.475},
    {3.45, -0.15, 2.5125}, {3.45, 0, 2.5125}, {2.8, 0, 2.4},
    {2.8, -0.15, 2.4}, {3.2, -0.15, 2.4}, {3.2, 0, 2.4}, {0, 0,
    3.15}, {0.8, 0, 3.15}, {0.8, -0.45, 3.15}, {0.45, -0.8,
    3.15}, {0, -0.8, 3.15}, {0, 0, 2.85}, {1.4, 0, 2.4}, {1.4,
    -0.784, 2.4}, {0.784, -1.4, 2.4}, {0, -1.4, 2.4}, {0.4, 0,
    2.55}, {0.4, -0.224, 2.55}, {0.224, -0.4, 2.55}, {0, -0.4,
    2.55}, {1.3, 0, 2.55}, {1.3, -0.728, 2.55}, {0.728, -1.3,
    2.55}, {0, -1.3, 2.55}, {1.3, 0, 2.4}, {1.3, -0.728, 2.4},
    {0.728, -1.3, 2.4}, {0, -1.3, 2.4}, {0, 0, 0}, {1.425,
    -0.798, 0}, {1.5, 0, 0.075}, {1.425, 0, 0}, {0.798, -1.425,
    0}, {0, -1.5, 0.075}, {0, -1.425, 0}, {1.5, -0.84, 0.075},
    {0.84, -1.5, 0.075}
};

static double tex[2][2][2] =
{
    { {0.0, 0.0}, {1.0, 0.0} },
    { {0.0, 1.0}, {1.0, 1.0} }
};

void renderEllipse(float radius, float cosArg, float sinArg)
{
	double Theta;
	double theta;
	double x,y,z;

	glBegin(GL_LINE_LOOP);
	for(Theta=0.0; Theta!=360.0; Theta+=0.5)
	{
		theta = Theta * M_PI / 180.0;

		//sin(((Bolygok[i].orbit+PlanetData[i].periodDelay)/360) * 2 * M_PI);

		//x = radius * cos(theta) * cosArg;
		//y = radius * sin(theta) * sinArg;
		x = cos(theta) * cosArg;
		y = sin(theta) * sinArg;
		

		//z = x * sinArg / cosArg;
		z = 0.0;
		if(Theta==0.0) glVertex3f(x, z, y); // hack, a feher csik miatt
		glVertex3f(x, z, y);


	}
	glVertex3f(x,z,y);
	glEnd();

}

void renderGridZ(float y, float range, float height)
{
	float i,j;

	glColor3f(0.0, 0.15, 0.0);
	
	
		//for(i=-x; i!=x; i+=range)
		//{
			
				for(j=-y; j!=y; j+=range)
				{
					glBegin(GL_LINE_LOOP);
					{
						glVertex3d(j, height, -y);
						glVertex3d(j, height, y);
					}
					glEnd();

					glBegin(GL_LINE_LOOP);
					{
						glVertex3d(-y, height, j);
						glVertex3d(y, height, j);
					}
					glEnd();
					
				}
		

}


void renderGrid(float y, float range)
{
	float i,j;

	glColor3f(0.0, 0.3, 0.0);
	
	
		//for(i=-x; i!=x; i+=range)
		//{
			
				for(j=-y; j!=y; j+=range)
				{
					glBegin(GL_LINE_LOOP);
					{
						glVertex3d(j, 0.0, -y);
						glVertex3d(j, 0.0, y);
					}
					glEnd();

					glBegin(GL_LINE_LOOP);
					{
						glVertex3d(-y, 0.0, j);
						glVertex3d(y, 0.0, j);
					}
					glEnd();
					
				}
		

}

/* -- INTERFACE FUNCTIONS -------------------------------------------------- */

/*
 * Renders a beautiful wired teapot...
 */

/*
 * Renders a beautiful filled teapot...
 */

#endif // _GEOMETRY_H_
