//
// Created by massi on 05.03.2020.
//
#include <iostream>
#include "draw_utils.h"

#define WIREFRAME_COLOR 15, 32, 112

void draw_utils::log(std::string msg) {
    std::cout << msg << std::endl;
}

void draw_utils::testMinMaxLineWidth() {
    GLfloat lineWidthRange[2] = {0.0f, 0.0f};
    glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, lineWidthRange);
}

/**
 * Draw a 3D prism using front and back faces
 * Lateral faces are derived
 * @param front
 * @param back
 */
void draw_utils::draw_prism(Triangle &front, Triangle &back) {

    Rect rect[] = {
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
void draw_utils::draw_parallelepiped(Rect &front, Rect &back) {
    draw_rectangle3D(front);
    draw_rectangle3D(back);

    Rect right = {front.v2, back.v1, back.v4, front.v3, front.color  };
    draw_rectangle3D(right);

    Rect left = {back.v2, front.v1, front.v4, back.v3, front.color  };
    draw_rectangle3D(left);

    Rect bottom = {back.v2, back.v1, front.v2, front.v1, front.color  };
    draw_rectangle3D(bottom);

    Rect top = {front.v4, front.v3, back.v4, back.v3, front.color  };
    draw_rectangle3D(top);
}

/**
 * Draw a 3D rectangle using the rect data struct
 * The rectangle is composed by by 2 triangles
 * @param rect
 */
void draw_utils::draw_rectangle3D(Rect &rect ) {
    draw_triangle3D(rect.v1, rect.v2, rect.v3, rect.color);
    draw_triangle3D(rect.v3, rect.v4, rect.v1, rect.color);
}

/**
 * Draw a 3D triangle using the triangle data struct
 * @param triangle
 */
void draw_utils::draw_triangle3D(Triangle &triangle) {
    draw_triangle3D(triangle.v1, triangle.v2, triangle.v3, triangle.color);
}

/**
 * Draw a 3D triangle using 3 vertex structs
 * @param v1
 * @param v2
 * @param v3
 * @param color
 */
void draw_utils::draw_triangle3D(Vertex &v1, Vertex &v2, Vertex &v3, Color &color) {
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

void draw_utils::internal_triangle3D(const Vertex &v1, const Vertex &v2, const Vertex &v3) {
    glBegin(GL_TRIANGLES);
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v3.x, v3.y, v3.z);
    glEnd();
}

/**
 * Draw X, Y and Z axes in 3 different colors
 */
void draw_utils::draw_axes() {
    if(!_showAxis)
        return;

    glPushMatrix();
    glLineWidth(1.0f);

    glPolygonMode(GL_FRONT, GL_LINE);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xf0f0);

    glBegin(GL_LINES);
    // Draw a red x-axis
    glColor3ub(255, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(10, 0, 0);

    // Draw a green y-axis
    glColor3ub(0, 255, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 10, 0);

    // Draw a blue z-axis
    glColor3ub(0, 0, 255);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 10);

    glEnd();
    glDisable(GL_LINE_STIPPLE);
    glPopMatrix();
}

void draw_utils::toggleAxesVisibility() {
    _showAxis = !_showAxis;
    log(std::string("axis ") + (_showAxis ? "visible" : "hidden"));
    glutPostRedisplay();
}

/**
 * volume cube
 */
void draw_utils::draw_volume(const Ortho &vol) const {
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel (GL_FLAT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //draw the front face dimensions
    glBegin(GL_QUADS);
    glColor4f(1.0, 0, 0, .3);
    glVertex3f(vol.left, vol.bottom, vol.zNear);
    glVertex3f(vol.right, vol.bottom, vol.zNear);
    glVertex3f(vol.right, vol.top, vol.zNear);
    glVertex3f(vol.left, vol.top, vol.zNear);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(0, 1.0, 0, .3);
    glVertex3f(vol.left, vol.bottom, vol.zFar);
    glVertex3f(vol.right, vol.bottom, vol.zFar);
    glVertex3f(vol.right, vol.top, vol.zFar);
    glVertex3f(vol.left, vol.top, vol.zFar);
    glEnd();

    glDisable(GL_FILL);
}


/**
 * WIND
 */
void draw_utils::toggleWireframeVisibility() {
    _showWireFrame = !_showWireFrame;
    log(std::string("wireframe ") + (_showWireFrame ? "visible" : "hidden"));
    glutPostRedisplay();
}

void draw_utils::toggleWindVisibility() {
    _showWind = !_showWind;
    log(std::string("wind ") + (_showWind ? "visible" : "hidden"));
    glutPostRedisplay();
}

void draw_utils::draw_wind(GLfloat windAngle) {
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

