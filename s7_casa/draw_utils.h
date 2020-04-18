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
#include <math.h>

extern bool _showWind;
extern bool _showAxis;
extern bool _showWireFrame;

struct camera_t {
    GLdouble eyex, eyey, eyez;
    GLdouble centerx, centery, centerz;
    GLdouble upx, upy, upz;
};

struct ortho_t {
    GLdouble left, right, bottom, top;
    GLdouble znear, zfar;
};

struct color_t {
    GLubyte r,g,b;
};

struct vertex_t {
    GLfloat x, y, z;
    GLfloat dotProduct(vertex_t& o) { return x*o.x + y*o.y + z*o.z; }
    GLfloat length() { return sqrt(x*x + y*y + z*z); }
};

struct triangle_t {
    vertex_t v1, v2, v3;
    color_t color;
};

struct rectangle_t {
    vertex_t v1, v2, v3, v4;
    color_t color;
};

struct volume_t {
    vertex_t vertex[8];
};

class draw_utils {
public:
    void draw_wind(GLfloat windAngle);
    void draw_axis();
    void draw_volume(const ortho_t &vol) const;
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
