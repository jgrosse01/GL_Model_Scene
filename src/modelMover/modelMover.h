//
// Created by jgros on 10/21/2022.
//

#ifndef MODELMOVER_H
#define MODELMOVER_H

#include "../glm/glm.h"

void updateModelPosition(GLMmodel* m, int dx, int dy, int dz);
void walkForward(GLMmodel* m, int distance, int forwardDir[3]);
void hop(GLMmodel* m, int upDir[3]);
void leftHop(GLMmodel* m, int upDir[3]);
void rightHop(GLMmodel* m, int upDir[3]);
void congaLine(GLMmodel* m, int forwardDir[3], int upDir[3]);
void lineDanceForward(GLMmodel* m);

#endif //MODELMOVER_H
