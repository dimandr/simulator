/*
 *  Player - One Hell of a Robot Server
 *  glutgraphics.cc: GLUT-based graphics3d + 2d driver
 *  Copyright (C) 2007  
 *     Brian Gerkey, Richard Vaughan
 *                      
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/*
 * A simple example of how to write a driver that will be built as a
 * shared object.
 */

// ONLY if you need something that was #define'd as a result of configure 
// (e.g., HAVE_CFMAKERAW), then #include <config.h>, like so:
/*
#if HAVE_CONFIG_H
#include <config.h>
#endif
 */

#include <unistd.h>
#include <string.h>

//#include <libplayercore/playercore.h>
#include <QtOpenGL>
#if defined(Q_WS_MAC)
#include <OpenGL/glu.h>
#else
#ifndef QT_LINUXBASE
#include <GL/glu.h>
#endif
#endif
#include <stdio.h>
#include <math.h>


GLfloat light0_ambient[] =
{0.2, 0.2, 0.2, 1.0};
GLfloat light0_diffuse[] =
{0.0, 0.0, 0.0, 1.0};
GLfloat light1_diffuse[] =
{1.0, 0.0, 0.0, 1.0};
GLfloat light1_position[] =
{1.0, 1.0, 1.0, 0.0};
GLfloat light2_diffuse[] =
{0.0, 1.0, 0.0, 1.0};
GLfloat light2_position[] =
{-1.0, -1.0, 1.0, 0.0};
float s = 0.0;
GLfloat angle1 = 0.0, angle2 = 0.0;

	void 
output(GLfloat x, GLfloat y, char *text)
{
	char *p;

	glPushMatrix();
	glTranslatef(x, y, 0);
        //for (p = text; *p; p++)
        //	glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
	glPopMatrix();
}

	void 
display(void)
{
	static GLfloat amb[] =
	{0.4, 0.4, 0.4, 0.0};
	static GLfloat dif[] =
	{1.0, 1.0, 1.0, 0.0};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	amb[3] = dif[3] = cos(s) / 2.0 + 0.5;
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);

	glPushMatrix();
	glTranslatef(-0.3, -0.3, 0.0);
	glRotatef(angle1, 1.0, 5.0, 0.0);
	glCallList(1);        /* render ico display list */
	glPopMatrix();

	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHT2);
	glDisable(GL_LIGHT1);
	amb[3] = dif[3] = 0.5 - cos(s * .95) / 2.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);

	glPushMatrix();
	glTranslatef(0.3, 0.3, 0.0);
	glRotatef(angle2, 1.0, 0.0, 5.0);
	glCallList(1);        /* render ico display list */
	glPopMatrix();

	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 1500, 0, 1500);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	/* Rotate text slightly to help show jaggies. */
	glRotatef(4, 0.0, 0.0, 1.0);
	output(200, 225, "This is antialiased.");
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_BLEND);
	output(160, 100, "This text is not.");
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPopAttrib();
	glMatrixMode(GL_MODELVIEW);

//	glutSwapBuffers();
}

	void 
idle(void)
{
	angle1 = (GLfloat) fmod(angle1 + 0.8, 360.0);
	angle2 = (GLfloat) fmod(angle2 + 1.1, 360.0);
	s += 0.05;

	//usleep( 100000 );

	static int g=1;
	printf( "cycle %d\n", g++ );

//	glutPostRedisplay();
}

	void 
redraw( int val )
{
	angle1 = (GLfloat) fmod(angle1 + 0.8, 360.0);
	angle2 = (GLfloat) fmod(angle2 + 1.1, 360.0);
	s += 0.05;

	//usleep( 100000 );

	static int g=1;
	printf( "cycle %d\n", g++ );

//	glutPostRedisplay();

//	glutTimerFunc( 100, redraw, 0 );
}

	void 
visible(int vis)
{
//	if (vis == GLUT_VISIBLE)
//		//glutTimerFunc( 100, redraw, 0 );
//		glutIdleFunc( idle );
//	else
//		glutIdleFunc(NULL);
}


