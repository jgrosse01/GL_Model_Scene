/* trackball.cpp                             */
/* -----------                               */
/*                                           */
/* Code to implement a simple trackball-like */
/*     motion control.                       */
/*                                           */
/* This expands on the expansion             */
/*     of Ed Angel's trackball.c             */
/*     demo program.  Though I think I've    */
/*     seen this code (trackball_ptov)       */
/*     before elsewhere.                     */
/*********************************************/

#include <GL/gl.h>
#include <cmath>
#include "trackball.h"

// method by instructor's instructor
void trackball_ptov(int x, int y, int width, int height, float v[3]) {
    float d, a;

    /* project x,y onto a hemi-sphere centered within width, height */
    v[0] = (width - 2.0F*x) / width;
    v[1] = (height - 2.0F*y) / height;
    d = (float) sqrt(v[0]*v[0] + v[1]*v[1]);
    v[2] = (float) cos((M_PI/2.0F) * ((d < 1.0F) ? d : 1.0F));
    a = 1.0F / (float) sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    v[0] *= a;
    v[1] *= a;
    v[2] *= a;
}

void setTrackballOnClick( int x, int y, int width, int height, GLfloat lastPos[3]) {
    trackball_ptov( x, y, width, height, lastPos );
}

// IF THE TRACKBALL DOES NOT MOVE THIS METHOD IS THE PROBLEM, NEED TO FIGURE OUT POINTER STUFF
void updateTrackballOnMotion( int x, int y, int width, int height, GLfloat* matrix, GLfloat* lastPos) {
    float curPos[3], dx, dy, dz, angle, axis[3];
    float oldPos[3];
    oldPos[0] = lastPos[0];
    oldPos[1] = lastPos[1];
    oldPos[2] = lastPos[2];

    trackball_ptov( x, y, width, height, curPos );
    dx = curPos[0] - oldPos[0];
    dy = curPos[1] - oldPos[1];
    dz = curPos[2] - oldPos[2];
    if ( fabs(dx) > 0 || fabs(dy) > 0 || fabs(dz) > 0 )
    {
        angle = 90 * sqrt( dx*dx + dy*dy + dz*dz );
        axis[0] = oldPos[1]*curPos[2] - oldPos[2]*curPos[1];
        axis[1] = oldPos[2]*curPos[0] - oldPos[0]*curPos[2];
        axis[2] = oldPos[0]*curPos[1] - oldPos[1]*curPos[0];

        glPushMatrix();
        glLoadIdentity();
        glRotatef( angle, axis[0], axis[1], axis[2] );

        lastPos[0] = curPos[0];
        lastPos[1] = curPos[1];
        lastPos[2] = curPos[2];
        glMultMatrixf( matrix );
        glGetFloatv( GL_MODELVIEW_MATRIX, matrix );

        glPopMatrix();
    }
}

void trackballMult(GLfloat* matrix) {
    glMultMatrixf( matrix );
}

