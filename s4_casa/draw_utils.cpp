//
// Created by massi on 05.03.2020.
//
#include "draw_utils.h"

bool showAxis = true;

void draw_rectangle3D(GLfloat *bottomLeft, GLfloat *bottomRight, GLfloat *topRight, GLfloat *topLeft, float border) {

    draw_triangle3D(bottomLeft, bottomRight, topRight, border);
    draw_triangle3D(bottomLeft, topRight, topLeft, border);
}

void draw_triangle3D(GLfloat *v1, GLfloat *v2, GLfloat *v3, float border) {
    if(border > 0) {
        // wireframe
        glLineWidth(border);
        glColor3ub(15, 32, 112);
        glPolygonMode(GL_FRONT, GL_LINE);
    }

    glBegin(GL_TRIANGLES);
    glVertex3fv(v1);
    glVertex3fv(v2);
    glVertex3fv(v3);
    glEnd();
}

void draw_axis() {
    if(!showAxis)
        return;

    glLineWidth(1.0f);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xf0f0);
    // axes are ten units long.
    glBegin(GL_LINES);
    // Draw a red x-axis
    glColor3ub(255, 0, 0);
    glVertex3f(-2, 0, 0);
    glVertex3f(2, 0, 0);
    // Draw a green y-axis
    glColor3ub(0, 255, 0);
    glVertex3f(0, -2, 0);
    glVertex3f(0, 2, 0);
    // Draw a blue z-axis
    glColor3ub(0, 0, 255);
    glVertex3f(0, 0, -2);
    glVertex3f(0, 0, 2);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
}
