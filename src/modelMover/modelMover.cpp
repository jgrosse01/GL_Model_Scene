//
// Created by jgros on 10/21/2022.
//

#include "modelMover.h"

void updateModelPosition(GLMmodel* m, int dx, int dy, int dz) {
    m->position[0] += dx;
    m->position[1] += dy;
    m->position[2] += dz;
    glmDraw(m, GLM_SMOOTH | GLM_MATERIAL);
}

void walkForward(GLMmodel* m, int distance, int forwardDir[3]) {
    for (int i = 0; i < distance; i++) {
        updateModelPosition(m, forwardDir[0], forwardDir[1], forwardDir[2]);
        glutPostRedisplay();
    }
}

void hop(GLMmodel* m, int upDir[3]) {
    for (int i = 0; i < 30; i++) {
        updateModelPosition(m, upDir[0], upDir[1], upDir[2]);
        glutPostRedisplay();
    }
    for (int i = 0; i < 30; i++) {
        updateModelPosition(m, -upDir[0], -upDir[1], -upDir[2]);
        glutPostRedisplay();
    }
}

void leftHop(GLMmodel* m, int upDir[3]) {

}

void rightHop(GLMmodel* m, int upDir[3]) {

}

void congaLine(GLMmodel* m, int forwardDir[3], int upDir[3]) {
    int forwardDist = 500;
    walkForward(m, forwardDist, forwardDir);
    leftHop(m, upDir);
    walkForward(m, forwardDist, forwardDir);
    rightHop(m, upDir);
}

void lineDanceForward(GLMmodel* m) {

}
