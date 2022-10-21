//
// Adapted by jgros on 10/20/2022.
//

#ifndef TRACKBALL_H
#define TRACKBALL_H

#include <GL/gl.h>

/* call when the user first clicks on the screen (with dimensions */
/*   width by height) at location (x, y)                          */
void setTrackballOnClick( int x, int y, int width, int height, GLfloat* lastPos);

/* call when the user moves the mouse when holding down the mouse */
/*   button.  The params are the new (x, y) location and the      */
/*   screen dimensions.                                           */
void updateTrackballOnMotion( int x, int y, int width, int height, GLfloat* matrix, GLfloat* lastPos );

/* call to multiply the trackball's matrix onto the GL stack.     */
/*    make sure this is only called in the MODELVIEW stack mode   */
void trackballMult( GLfloat* matrix );

#endif //TRACKBALL_H
