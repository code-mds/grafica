//
// Created by massi on 05.03.2020.
//

#ifndef GRAFICA_DRAW_UTILS_H
#define GRAFICA_DRAW_UTILS_H

#ifdef __APPLE__
#include <GL/glew.h>
#include <GLUT/glut.h>
#else
// headers richiesti da Windows e linux
#include <GL\glew.h>
#include <GL\freeglut.h>
#include "draw_utils.h"
#endif

extern bool showAxis;
extern bool showWireFrame;

void draw_axis();
void draw_triangle3D(GLfloat *v1, GLfloat *v2, GLfloat *v3, float border);
void draw_rectangle3D(GLfloat *bottomLeft, GLfloat *bottomRight, GLfloat *topRight, GLfloat *topLeft, float border);
void draw_paralleliped(GLfloat *bottomLeft1, GLfloat *bottomRight1, GLfloat *topRight1, GLfloat *topLeft1,
                       GLfloat *bottomLeft2, GLfloat *bottomRight2, GLfloat *topRight2, GLfloat *topLeft2, float border);
#endif //GRAFICA_DRAW_UTILS_H
