//
// Created by massi on 05.03.2020.
//
#include "draw_utils.h"

bool _showWind = true;
bool _showAxis = true;
bool _showWireFrame = true;
#define WIREFRAME_COLOR 15, 32, 112
void internal_triangle3D(const vertex_t &v1, const vertex_t &v2, const vertex_t &v3);

/**
 * Draw a 3D prism using front and back faces
 * Lateral faces are derived
 * @param front
 * @param back
 */
void draw_prism(triangle_t &front, triangle_t &back) {

    rectangle_t rect[] = {
            {
                front.v2,
                front.v1,
                back.v2,
                back.v1,
                front.color
            },
            {
                front.v3,
                back.v3,
                back.v2,
                front.v1,
                front.color
            },
            {
                back.v3,
                front.v3,
                front.v2,
                back.v1,
                front.color
            },
    };

    draw_rectangle3D(rect[0]);
    draw_rectangle3D(rect[1]);
    draw_rectangle3D(rect[2]);

    draw_triangle3D(front);
    draw_triangle3D(back);
}

/**
 * Draw a 3D parallelepiped using front and back face
 * Lateral faces are derived
 * @param front
 * @param back
 */
void draw_parallelepiped(rectangle_t &front, rectangle_t &back) {
    draw_rectangle3D(front);
    draw_rectangle3D(back);

    rectangle_t right = {front.v2, back.v1, back.v4, front.v3, front.color  };
    draw_rectangle3D(right);

    rectangle_t left = {back.v2, front.v1, front.v4, back.v3, front.color  };
    draw_rectangle3D(left);

    rectangle_t bottom = {back.v2, back.v1, front.v2, front.v1, front.color  };
    draw_rectangle3D(bottom);

    rectangle_t top = {front.v4, front.v3, back.v4, back.v3, front.color  };
    draw_rectangle3D(top);
}

/**
 * Draw a 3D rectangle using the rect data struct
 * The rectangle is composed by by 2 triangles
 * @param rect
 */
void draw_rectangle3D(rectangle_t &rect ) {
    draw_triangle3D(rect.v1, rect.v2, rect.v3, rect.color);
    draw_triangle3D(rect.v3, rect.v4, rect.v1, rect.color);
}

/**
 * Draw a 3D triangle using the triangle data struct
 * @param triangle
 */
void draw_triangle3D(triangle_t &triangle) {
    draw_triangle3D(triangle.v1, triangle.v2, triangle.v3, triangle.color);
}

/**
 * Draw a 3D triangle using 3 vertex structs
 * @param v1
 * @param v2
 * @param v3
 * @param color
 */
void draw_triangle3D(vertex_t &v1, vertex_t &v2, vertex_t &v3, color_t &color) {
    glColor3ub(color.r, color.g, color.b);
    glPolygonMode(GL_FRONT,GL_FILL);
    internal_triangle3D(v1, v2, v3);

    if(_showWireFrame) {
        // wireframe
        glLineWidth(1.0f);
        glColor3ub(WIREFRAME_COLOR);
        glPolygonMode(GL_FRONT, GL_LINE);
        internal_triangle3D(v1, v2, v3);
    }
}

void internal_triangle3D(const vertex_t &v1, const vertex_t &v2, const vertex_t &v3) {
    glBegin(GL_TRIANGLES);
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v3.x, v3.y, v3.z);
    glEnd();
}

/**
 * Draw X, Y and Z axis in 3 different colors
 */
void draw_axis() {
    if(!_showAxis)
        return;

    glPushMatrix();
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
    glPopMatrix();
}

void draw_wind(GLfloat windAngle) {
    if(!_showWind)
        return;

    glPushMatrix();
    glRotatef(windAngle, 0, 1, 0);
    glLineWidth(5.0f);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xf0f0);
    glBegin(GL_LINES);
    glColor3ub(214, 234, 248);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, -10);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    glPopMatrix();
}

void toggleAxesVisibility() {
    _showAxis = !_showAxis;
    glutPostRedisplay();
}

void toggleWireframeVisibility() {
    _showWireFrame = !_showWireFrame;
    glutPostRedisplay();
}

void toggleWindVisibility() {
    _showWind = !_showWind;
    glutPostRedisplay();
}

void testMinMaxLineWidth() {
    GLfloat lineWidthRange[2] = {0.0f, 0.0f};
    glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, lineWidthRange);
}
