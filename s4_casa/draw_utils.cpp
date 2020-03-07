//
// Created by massi on 05.03.2020.
//
#include "draw_utils.h"

bool showAxis = true;
bool showWireFrame = true;

void internal_triangle3D(const vertex_t *v1, const vertex_t *v2, const vertex_t *v3);

void draw_prism(triangle_t *front, triangle_t *backRect) {

}

void draw_parallelepiped(rectangle_t *front, rectangle_t *backRect) {
    draw_rectangle3D(front);
    draw_rectangle3D(backRect);

    rectangle_t right = {front->v2, backRect->v1, backRect->v4, front->v3, front->color  };
    draw_rectangle3D(&right);

    rectangle_t left = {backRect->v2, front->v1, front->v4, backRect->v3, front->color  };
    draw_rectangle3D(&left);

    rectangle_t bottom = {backRect->v2, backRect->v1, front->v2, front->v1, front->color  };
    draw_rectangle3D(&bottom);

    rectangle_t top = {front->v4, front->v3, backRect->v4, backRect->v3, front->color  };
    draw_rectangle3D(&top);
}

void draw_rectangle3D(rectangle_t * rect ) {
    draw_triangle3D(&rect->v1, &rect->v2, &rect->v3, &rect->color);
    draw_triangle3D(&rect->v3, &rect->v4, &rect->v1, &rect->color);
}

void draw_triangle3D(vertex_t *v1, vertex_t *v2, vertex_t *v3, color_t* color) {
    glColor3ub(color->r, color->g, color->b);
    glPolygonMode(GL_FRONT,GL_FILL);
    internal_triangle3D(v1, v2, v3);

    if(showWireFrame) {
        // wireframe
        glLineWidth(1.0);
        glColor3ub(15, 32, 112);
        glPolygonMode(GL_FRONT, GL_LINE);
        internal_triangle3D(v1, v2, v3);
    }
}

void internal_triangle3D(const vertex_t *v1, const vertex_t *v2, const vertex_t *v3) {
    glBegin(GL_TRIANGLES);
    glVertex3f(v1->x, v1->y, v1->z);
    glVertex3f(v2->x, v2->y, v2->z);
    glVertex3f(v3->x, v3->y, v3->z);
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

void toggleAxesVisibility() {
    showAxis = !showAxis;
    glutPostRedisplay();
}

void toggleWireframeVisibility() {
    showWireFrame = !showWireFrame;
    glutPostRedisplay();
}
