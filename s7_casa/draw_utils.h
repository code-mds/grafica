//
// Created by massi on 05.03.2020.
//

#ifndef GRAFICA_DRAW_UTILS_H
#define GRAFICA_DRAW_UTILS_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
// headers richiesti da Windows e linux
#include <GL\glew.h>
#include <GL\freeglut.h>
#include "draw_utils.h"
#endif

#include <string>

extern bool _showWind;
extern bool _showAxis;
extern bool _showWireFrame;

typedef struct {
    GLdouble eyex, eyey, eyez;
    GLdouble centerx, centery, centerz;
    GLdouble upx, upy, upz;
} camera_t;

typedef struct {
    GLdouble left, right, bottom, top;
    GLdouble n, f;
} volume_t;

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

class draw_utils {
public:
    void draw_wind(GLfloat windAngle);
    void draw_axis(volume_t param);
    void toggleAxesVisibility();
    void toggleWireframeVisibility();
    void toggleWindVisibility();
    void testMinMaxLineWidth();
    void draw_triangle3D(triangle_t &triangle);
    void draw_triangle3D(vertex_t &v1, vertex_t &v2, vertex_t &v3, color_t &color);
    void draw_rectangle3D(rectangle_t &rect);
    void draw_prism(triangle_t &front, triangle_t &back);
    void draw_parallelepiped(rectangle_t &front, rectangle_t &back);
    void log(std::string msg);

private:
    void internal_triangle3D(const vertex_t &v1, const vertex_t &v2, const vertex_t &v3);

    bool _showWind = true;
    bool _showAxis = true;
    bool _showWireFrame = true;

};
#endif //GRAFICA_DRAW_UTILS_H
