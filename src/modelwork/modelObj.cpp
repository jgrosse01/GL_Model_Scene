//
// Created by jgros on 10/21/2022.
//

#include "modelObj.h"
#include "../../data/materials.txt"

GLfloat normalSmooth = 0.0;

void setMaterial(GLMmodel* m, int matType) {
    //set the current material to the selected value.
    m->materials[0].name = mat[matType].name;
    m->materials[0].shininess = mat[matType].shiny;
    for(int i = 0; i < 4; i++) {
        m->materials[0].ambient[i] = mat[matType].ambient[i];
        m->materials[0].diffuse[i] = mat[matType].diffuse[i];
        m->materials[0].specular[i] = mat[matType].specular[i];
    }
}

GLMmodel* getObject(int newObj) {
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
    GLMmodel* newObject = glmReadOBJ(objectName);

    //if the object is Al Capone, we want to draw him using the materials specified in al.mtl
    //otherwise, draw the object using the current material.
    if(newObj != 200)
    {
        //not al capone
        newObject->materials = (GLMmaterial*)malloc(sizeof(GLMmaterial) * 1);
        setMaterial(newObject, 0);
    }
    else
    {
        //Al capone...make him cool-lookin'
        char alMaterialStr[] = "../data/al.mtl";
        glmReadMTL(newObject, alMaterialStr);
    }
    glmUnitize(newObject);
    glmFacetNormals( newObject );			// Generates per-triangle normals, if not specified
    //     in the OBJ or SMF file
    glmVertexNormals( newObject, normalSmooth );	                // Generates per-vertex normals, if not specified in
    //     the OBJ or SMF file.  The angle specified is the
    //     maximum angle to smooth across.  90 is a good
    //     starting value, 180 will smooth all normals.
    glmSpheremapTexture( newObject );

    return newObject;
}
