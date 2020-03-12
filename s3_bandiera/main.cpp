//glut_test.cpp
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// Headers richiesti da OSX
#ifdef __APPLE__
//#include <OpenGL/gl3.h>
#include <GL/glew.h>
#include <GLUT/glut.h>
#include <iostream>

// headers richiesti da Windows e linux
#else
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

#endif

using namespace std;

const float SCENE_WIDTH = 300.0f;
const float SCENE_HEIGHT = 300.0f;
const float FLAG_WIDTH = 420.0f / SCENE_WIDTH;
const float FLAG_HEIGHT = 250.0f / SCENE_HEIGHT;
const float X_MARGIN = 60.0f/ SCENE_WIDTH;
const float Y_MARGIN = 36.0f/ SCENE_HEIGHT;
const float HALF_FLAG_WIDTH = FLAG_WIDTH / 2;
const float HALF_FLAG_HEIGHT = FLAG_HEIGHT / 2;

const GLfloat left_bottom[] = {-HALF_FLAG_WIDTH, -HALF_FLAG_HEIGHT};
const GLfloat right_bottom[] = {HALF_FLAG_WIDTH, -HALF_FLAG_HEIGHT};
const GLfloat right_top[] = {HALF_FLAG_WIDTH, HALF_FLAG_HEIGHT};
const GLfloat left_top[] = {-HALF_FLAG_WIDTH, HALF_FLAG_HEIGHT};

void triangolo(GLfloat* v1, GLfloat* v2, GLfloat* v3) {
    glColor3ub(15, 32, 112);
    glBegin(GL_TRIANGLES);
    glVertex2fv(v1);
    glVertex2fv(v2);
    glVertex2fv(v3);
    glEnd();
}

void triangolo_basso() {
    GLfloat v1[] = {-HALF_FLAG_WIDTH+X_MARGIN, -HALF_FLAG_HEIGHT};
    GLfloat v2[] = {HALF_FLAG_WIDTH-X_MARGIN, -HALF_FLAG_HEIGHT};
    GLfloat v3[] = {0, -Y_MARGIN};
    triangolo(v1, v2, v3);
}

void triangolo_alto() {
    GLfloat v1[] = {-HALF_FLAG_WIDTH+X_MARGIN, HALF_FLAG_HEIGHT};
    GLfloat v2[] = {HALF_FLAG_WIDTH-X_MARGIN, HALF_FLAG_HEIGHT};
    GLfloat v3[] = {0, Y_MARGIN};
    triangolo(v1, v2, v3);
}

void triangolo_dx() {
    GLfloat v1[] = {HALF_FLAG_WIDTH, HALF_FLAG_HEIGHT-Y_MARGIN};
    GLfloat v2[] = {HALF_FLAG_WIDTH, -HALF_FLAG_HEIGHT+Y_MARGIN};
    GLfloat v3[] = {X_MARGIN, 0};
    triangolo(v1, v2, v3);
}

void triangolo_sx() {
    GLfloat v1[] = {-HALF_FLAG_WIDTH, HALF_FLAG_HEIGHT-Y_MARGIN};
    GLfloat v2[] = {-HALF_FLAG_WIDTH, -HALF_FLAG_HEIGHT+Y_MARGIN};
    GLfloat v3[] = {-X_MARGIN, 0};
    triangolo(v1, v2, v3);
}

void flag_border() {
//    glLoadIdentity();
    glColor3ub(15, 32, 112);
    glPolygonMode(GL_FRONT,GL_LINE);
    glBegin(GL_LINE_STRIP);
    glVertex2fv(right_top);
    glVertex2fv(left_top);
    glVertex2fv(left_bottom);
    glVertex2fv(right_bottom);
    glVertex2fv(right_top);
    glEnd();
}

void flag_background() {
    glPolygonMode(GL_FRONT,GL_FILL);
    glColor3ub(255, 255, 255); // WHITE
    glBegin(GL_TRIANGLES);
    glVertex2fv(left_bottom);
    glVertex2fv(right_bottom);
    glVertex2fv(right_top);
    glVertex2fv(right_top);
    glVertex2fv(left_top);
    glVertex2fv(left_bottom);
    glEnd();
}

void init(void) {
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D (-1.0, 1.0, -1.0, 1.0);
    glClearColor(180/255.0,180/255.0, 180/255.0, 0.0); // GREY
}

void reshape(int w, int h) {
    printf("reshape: w=%d, h=%d\n",w,h);
    glViewport(0, 0, (GLint) w, (GLint) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h) {
        double aspect_ratio = (GLfloat)h/(GLfloat)w;
        glOrtho (-1.0, 1.0, -1.0*aspect_ratio, 1.0*aspect_ratio, -10.0, 10.0);
    }
    else {
        double aspect_ratio = (GLfloat) w / (GLfloat) h;
        glOrtho(-1.0 * aspect_ratio, 1.0 * aspect_ratio, -1.0, 1.0, -10.0, 10.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawCB() {
    glClear( GL_COLOR_BUFFER_BIT );
    flag_background();
    triangolo_basso();
    triangolo_alto();
    triangolo_sx();
    triangolo_dx();
    flag_border();
    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(SCENE_WIDTH, SCENE_HEIGHT);
    glutCreateWindow("bandiera scozzese");
    init();
    glutDisplayFunc(drawCB);
    glutReshapeFunc(reshape);
    glutMainLoop();
}