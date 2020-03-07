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

typedef struct {
    GLubyte r,g,b;
} color_t;

typedef struct {
    GLfloat x, y, z;
} vertex_t;

typedef struct {
    vertex_t v1, v2, v3;
    color_t color;
} triangle_t;

typedef struct {
    vertex_t v1, v2, v3, v4;
    color_t color;
} rectangle_t;

void draw_axis();
void toggleAxesVisibility();
void toggleWireframeVisibility();

void draw_triangle3D(vertex_t *v1, vertex_t *v2, vertex_t *v3, color_t* color);
void draw_rectangle3D(rectangle_t *rect);
void draw_prism(triangle_t *front, triangle_t *backRect);
void draw_parallelepiped(rectangle_t *front, rectangle_t *backRect);

#endif //GRAFICA_DRAW_UTILS_H
