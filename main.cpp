#include <GL/freeglut.h>
#include "src/glm/glm.cpp"
#include "src/trackball/trackball.cpp"
#include "data/materials.txt"

using namespace std;

// Globals
int screenWidth = 800, screenHeight = 680;

bool trackCamera = false, trackLight = false;

GLfloat normalSmooth = 0.0;

GLfloat lastTrackballPos[3] = {0,0,0};
GLfloat trackballMatrix[16] = {1,0,0,0,    0,1,0,0,    0,0,1,0,    0,0,0,1};
GLfloat lastLightPos[3] = {0,0,0};
GLfloat lightMatrix[16] = {1,0,0,0,    0,1,0,0,    0,0,1,0,    0,0,0,1};

GLMmodel* currentObject;
int currentMaterial = 0;


// Lighting Global Values
GLfloat global_ambient[4] = {0.2, 0.2, 0.2, 1.0};
GLfloat light0_ambient[4] = {0.2, 0.2, 0.2, 1.0};
GLfloat light0_diffuse[4] = {1.0, 1.0, 1.0, 1.0};
GLfloat light0_specular[4] = {1.0, 1.0, 1.0, 1.0};
GLfloat light0_position[4] = {0, 0, 2, 0.0};


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    // light trackball
    glLoadIdentity();
    trackballMult(lightMatrix);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

    // object trackball
    glLoadIdentity();
    glTranslatef(0,0,-1);
    trackballMult(trackballMatrix);

    glmDraw(currentObject, GLM_SMOOTH | GLM_MATERIAL);

    glFlush();
    glutSwapBuffers();
}

void idle() {

}

void reshape( int w, int h )
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90,4.0/3.0, 1, 100);
    glOrtho(-2, 2, -2, 2, 1, 100);
    gluLookAt(0, 0, 0, 0, 0, 3, 0, 1, 0);
    glutPostRedisplay();
    screenWidth = w;
    screenHeight = h;
}

void processKeys(unsigned char key, int x, int y) {
    switch ( key )
    {
        default:
            break;
        case 't':
            glEnable(GL_NORMALIZE);
            break;
        case 'r':
            glDisable(GL_NORMALIZE);
            break;
        case 'S':
            normalSmooth += 1;
            glmUnitize(currentObject);
            glmFacetNormals( currentObject );
            glmVertexNormals( currentObject, normalSmooth );
            glmSpheremapTexture( currentObject );
            break;
        case 's':
            normalSmooth -= 1;
            glmUnitize(currentObject);
            glmFacetNormals( currentObject );
            glmVertexNormals( currentObject, normalSmooth );
            glmSpheremapTexture( currentObject );
            break;
        case 'Q':
            exit(0);
        case 'q':
            exit(0);
    }
}

// moves modelview objects based on mouse inputs
void motion(int x, int y) {
    if (trackCamera) {
        // update camera view
        updateTrackballOnMotion(x, y, screenWidth, screenHeight, trackballMatrix, lastTrackballPos);
        glutPostRedisplay();
    }
    if (trackLight) {
        // update light location
        updateTrackballOnMotion(x, y, screenWidth, screenHeight, lightMatrix, lastLightPos);
        glutPostRedisplay();
    }
}

void processButtons(int b, int state, int x, int y) {
    switch ( b ) {
        default:
            break;

        case GLUT_LEFT_BUTTON: {
            switch( state ) {
                case GLUT_DOWN:
                    //toggle the 'left-down' switch so that the program updates the object trackball orientation on motion.
                    setTrackballOnClick(x, y, screenWidth, screenHeight, lastTrackballPos);
                    trackCamera = true;
                    break;
                case GLUT_UP:
                    //turn the trackball updates of (the user has released the mouse button)
                    trackCamera = false;
                    break;
            }
            break;
        }

        case GLUT_MIDDLE_BUTTON: {
            switch (state) {
                case GLUT_DOWN:
                    //toggle the 'left-down' switch so that the program updates the light trackball orientation on motion.
                    setTrackballOnClick(x, y, screenWidth, screenHeight, lastLightPos);
                    trackLight = true;
                    break;
                case GLUT_UP:
                    //turn the trackball updates of (the user has released the mouse button)
                    trackLight = false;
                    break;
            }
            break;
        }
    }
}

void setMaterial(int matType) {
    //set the current material to the selected value.
    currentObject->materials[0].name = mat[matType].name;
    currentObject->materials[0].shininess = mat[matType].shiny;
    for(int i = 0; i < 4; i++) {
        currentObject->materials[0].ambient[i] = mat[matType].ambient[i];
        currentObject->materials[0].diffuse[i] = mat[matType].diffuse[i];
        currentObject->materials[0].specular[i] = mat[matType].specular[i];
    }
}

void getObject(int newObj) {
    char* objectName;
    //determine which object the user selected.
    // file names need to go up two directories because they are called from a different file
    switch(newObj)
    {
        case 200:
            objectName = "../data/al.obj";
            break;
        case 201:
            objectName = "../data/bunny.obj";
            break;
        case 202:
            objectName = "../data/cow.obj";
            break;
        case 203:
            objectName = "../data/dragon_10k.obj";
            break;
        case 204:
            objectName = "../data/teapot.obj";
            break;
        default:
            objectName = "../data/bunny.obj";
            break;
    }
    //load the selected object into the object variable
    currentObject = glmReadOBJ(objectName);

    //if the object is Al Capone, we want to draw him using the materials specified in al.mtl
    //otherwise, draw the object using the current material.
    if(newObj != 200)
    {
        //not al capone
        currentObject->materials = (GLMmaterial*)malloc(sizeof(GLMmaterial) * 1);
        setMaterial(currentMaterial);
    }
    else
    {
        //Al capone...make him cool-lookin'
        char alMaterialStr[] = "../data/al.mtl";
        glmReadMTL(currentObject, alMaterialStr);
    }
    glmUnitize(currentObject);
    glmFacetNormals( currentObject );			// Generates per-triangle normals, if not specified
    //     in the OBJ or SMF file
    glmVertexNormals( currentObject, normalSmooth );	                // Generates per-vertex normals, if not specified in
    //     the OBJ or SMF file.  The angle specified is the
    //     maximum angle to smooth across.  90 is a good
    //     starting value, 180 will smooth all normals.
    glmSpheremapTexture( currentObject );
}



void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glViewport(0, 0, screenWidth, screenHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90,screenWidth/(screenHeight*1.0), 1, 100);
    glOrtho(-2, 2, -2, 2, 1, 100);
    gluLookAt(0, 0, 0, 0, 0, 3, 0, 1, 0);
    glClearColor(0, 0, 0, 0);
    getObject(200);	//start with Al Capone

    //set up lighting
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( screenWidth, screenHeight );
    glutInitWindowPosition( 100, 100 );
    glutCreateWindow("What A Scene!!!");

    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutIdleFunc( idle );
    glutMouseFunc( processButtons );
    glutMotionFunc( motion );
    glutKeyboardFunc( processKeys );

    init();

    glutMainLoop();

    return 0;
}
