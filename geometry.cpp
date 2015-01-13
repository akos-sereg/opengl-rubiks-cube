#include "RubikCube.h"

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
	
	glTranslatef((-1.0)*getArany(), -1.0*getArany(), -0.25*getArany());
	//renderWireCubeColor(0.95, 0.5);
	double dst = 0.5;

	
	for(i=0; i!=3; i++)
	{
		
		//glRotatef(90.0, 0.0, 0.0, 1.0);
		glPushMatrix();
		{
			glTranslatef(1.0*i*getArany(), (-dst)*getArany(), 0.0*getArany());
			renderGridColor(0.8*getArany(), colors[n].red, colors[n].green, colors[n].blue);
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
			glTranslatef(1.0*i*getArany(), (2.0 + dst+0.006)*getArany(), 0.0);
			renderGridColor(0.8*getArany(), colors[n].red, colors[n].green, colors[n].blue);
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
		glTranslatef(0.0, (dst+0.006)*getArany(), 0.0);
		renderGridColor(0.8*getArany(), colors[n].red, colors[n].green, colors[n].blue);
		glTranslatef(0.0, (-dst-0.006)*getArany(), 0.0);
		glRotatef(-90.0, 0.0, 0.0, 1.0);
		
		n++;
		

		for(i=0; i!=3; i++)
		{
			glTranslatef(0.0, 0.0, 0.0);
			renderCubeColor(1.0*getArany(), 0.5*getArany());
			glRotatef(90.0, 1.0, 0.0, 0.0);
			glTranslatef(0.0, (dst+0.006)*getArany(), 0.0);
			renderGridColor(0.8*getArany(), colors[n].red, colors[n].green, colors[n].blue);
			glTranslatef(0.0, (-dst-0.006)*getArany(), 0.0);
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			
			
			n++;

			glTranslatef(getArany()*1.0, 0.0, 0.0);
		}
		
		glRotatef(90.0, 0.0, 0.0, 1.0);
		glTranslatef(0.0, (dst-0.006)*getArany(), 0.0);
		renderGridColor(0.8*getArany(), colors[n].red, colors[n].green, colors[n].blue);
		glTranslatef(0.0, (-dst+0.006)*getArany(), 0.0);
		glRotatef(-90.0, 0.0, 0.0, 1.0);
		
		n++;

		glTranslatef(-3.0*getArany(), getArany()*1.0, 0.0);
		
		}
		glPopMatrix();
		glTranslatef(0.0, 1.0*getArany(), 0.0);
		
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
				renderCubeColor(0.95*getArany(), 0.5*getArany());
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


