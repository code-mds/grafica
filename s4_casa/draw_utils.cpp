//
// Created by massi on 05.03.2020.
//
#include "draw_utils.h"

bool showAxis = true;
bool showWireFrame = true;

void draw_paralleleliped(GLfloat *bottomLeft1, GLfloat *bottomRight1, GLfloat *topRight1, GLfloat *topLeft1,
                         GLfloat *bottomLeft2, GLfloat *bottomRight2, GLfloat *topRight2, GLfloat *topLeft2,
                         GLubyte* frontColor, GLubyte *backColor) {
    //front
    draw_rectangle3D(bottomLeft1, bottomRight1, topRight1, topLeft1, frontColor);
    //right
    draw_rectangle3D(bottomRight1, bottomLeft2, topLeft2, topRight1, frontColor);
    //back
    draw_rectangle3D(bottomLeft2, bottomRight2, topRight2, topLeft2, backColor);
    //left
    draw_rectangle3D(bottomRight2, bottomLeft1, topLeft1, topRight2, frontColor);
    //bottom
    draw_rectangle3D(bottomRight2, bottomLeft2, bottomRight1, bottomLeft1, frontColor);
    //top
    draw_rectangle3D(topLeft1, topRight1, topLeft2, topRight2, frontColor);
}

void draw_rectangle3D(GLfloat *bottomLeft, GLfloat *bottomRight, GLfloat *topRight, GLfloat *topLeft, GLubyte* color ) {
    draw_triangle3D(bottomLeft, bottomRight, topRight, color);
    draw_triangle3D(topRight, topLeft, bottomLeft, color);
}

void draw_triangle3D(GLfloat v1[], GLfloat v2[], GLfloat v3[], GLubyte* color) {
    glColor3ubv(color);
    glPolygonMode(GL_FRONT,GL_FILL);
    glBegin(GL_TRIANGLES);
    glVertex3fv(v1);
    glVertex3fv(v2);
    glVertex3fv(v3);
    glEnd();

    if(showWireFrame) {
        // wireframe
        glLineWidth(1.0);
        glColor3ub(15, 32, 112);
        glPolygonMode(GL_FRONT, GL_LINE);
        glBegin(GL_TRIANGLES);
        glVertex3fv(v1);
        glVertex3fv(v2);
        glVertex3fv(v3);
        glEnd();
    }
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
