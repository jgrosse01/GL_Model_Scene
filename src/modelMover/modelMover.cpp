//
// Created by jgros on 10/21/2022.
//

#include "modelMover.h"


void congaLine(vector<GLMmodel*> m, int forwardDir[3], int upDir[3], vector<vector<float>> &position) {
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < 3; j++) {
            if (position[i][j] <= 1) {
                position[i][j] += forwardDir[j];
            } else {
                position[i][j] -= 100.0;
            }
        }
    }
    glutPostRedisplay();

}