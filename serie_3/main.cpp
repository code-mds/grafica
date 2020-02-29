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

float FLAG_WIDTH = 420.0f;
float FLAG_HEIGHT = 250.0f;
float MARGIN = 50.0f;

// reshape function, call with glutReshapeFunc(reshape) in yout main function
//void reshape(int width, int height) {
//    const float ar_origin =  FLAG_WIDTH /  FLAG_HEIGHT;
//    const float ar_new =  width /  height;
//
//    float scale_w =  width /  FLAG_WIDTH;
//    float scale_h =  height /  FLAG_HEIGHT;
//    if (ar_new > ar_origin) {
//        scale_w = scale_h;
//    } else {
//        scale_h = scale_w;
//    }
//
//    float margin_x = (width - FLAG_WIDTH * scale_w) / 2;
//    float margin_y = (height - FLAG_HEIGHT * scale_h) / 2;
//
//    glViewport(margin_x, margin_y, FLAG_WIDTH * scale_w, FLAG_HEIGHT * scale_h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//
//    gluOrtho2D(0, FLAG_WIDTH / ar_origin, 0, FLAG_HEIGHT / ar_origin);
//
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity() ;
//}

void reshape(int w, int h) {
    printf("reshape: w=%d, h=%d\n",w,h);
    glViewport(0, 0, (GLint) w, (GLint) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat ar = FLAG_WIDTH / FLAG_HEIGHT;

    if (w <= h) {
        ar = (GLfloat)h/(GLfloat)w;
        gluOrtho2D (-1.5, 1.5, -1.5*ar, 1.5*ar);
    }
    else{
        ar = (GLfloat)w/(GLfloat)h;
        gluOrtho2D (-1.5*ar, 1.5*ar, -1.5, 1.5);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void draw() {
    glClearColor(180/255.0,180/255.0, 180/255.0, 0.0);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();

    GLfloat lb[] = {-FLAG_WIDTH/2,-FLAG_WIDTH/2};
    GLfloat rb[] = {FLAG_WIDTH/2,-FLAG_WIDTH/2};
    GLfloat rt[] = {FLAG_WIDTH/2,FLAG_HEIGHT/2};
    GLfloat lt[] = {-FLAG_WIDTH/2,FLAG_HEIGHT/2};
    GLfloat middle[] = {0.0, 0.0};
    gluOrtho2D (-1.5*FLAG_WIDTH/2, 1.5*FLAG_WIDTH/2, -1.5*FLAG_HEIGHT/2, 1.5*FLAG_HEIGHT/2);

    // white rectangle
    glColor3ub(255, 255, 255);
    glBegin(GL_TRIANGLES);
    glVertex2fv(lb);
    glVertex2fv(rb);
    glVertex2fv(rt);
    glVertex2fv(rt);
    glVertex2fv(lt);
    glVertex2fv(lb);
    glEnd();

    glColor3ub(15, 32, 112);
//    glPushMatrix();
//    glTranslatef(0, -0.5, 0);
//    glBegin(GL_TRIANGLES);
//    glVertex2fv(middle);
//        glVertex2fv(left_bottom);
//        glVertex2fv(right_bottom);
//    glEnd();
//    glPopMatrix();

//
//    GLfloat flag_left = scene_left;
//    GLfloat flag_right = scene_right;
//    GLfloat flag_top = scene_top;
//    GLfloat flag_bottom = scene_bottom;
////    GLfloat flag_margin = 0.5f;
//    GLfloat middle_x = (flag_left + flag_right) / 2;
//    GLfloat middle_y = (flag_top + flag_bottom) / 2;
//
//    // draw bottom triangle
//
////    glPushMatrix();
////    glTranslatef(0, -0.5, 0);
////    glBegin(GL_TRIANGLES);
////        glVertex2f(flag_left , flag_bottom);
////        glVertex2f(flag_right , flag_bottom);
////        glVertex2f(middle_x, middle_y );
////    glEnd();
////    glPopMatrix();



//    glBegin(GL_TRIANGLE_STRIP);
//        glVertex2f(flag_left + flag_margin, flag_bottom);
//        glVertex2f(flag_right - flag_margin, flag_bottom);
//        glVertex2f(middle_x, middle_y - flag_margin);
//    glEnd();
//
//    // draw top triangle
//    glBegin(GL_TRIANGLE_STRIP);
//        glVertex2f(flag_left + flag_margin, flag_top);
//        glVertex2f(middle_x, middle_y + flag_margin);
//        glVertex2f(flag_right - flag_margin, flag_top);
//    glEnd();
//
//    // draw left triangle
//    glBegin(GL_TRIANGLE_STRIP);
//        glVertex2f(flag_left, flag_top - flag_margin);
//        glVertex2f(flag_left, flag_bottom + flag_margin);
//        glVertex2f(middle_x - flag_margin, middle_y);
//    glEnd();

//    glBegin(GL_TRIANGLE_STRIP);
//        glVertex2fv(flag_right, flag_top - flag_margin);
//        glVertex2f(middle_x + flag_margin, middle_y);
//        glVertex2f(flag_right, flag_bottom + flag_margin);
//    glEnd();

    glLoadIdentity();
    glBegin(GL_LINE_STRIP);
    glVertex2fv(rt);
    glVertex2fv(lt);
    glVertex2fv(lb);
    glVertex2fv(rb);
    glVertex2fv(rt);
    glEnd();


    glutSwapBuffers();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(822, 500);
    glutCreateWindow("bandiera scozzese");
    glutReshapeFunc(reshape);
    glutDisplayFunc(draw);
    glutMainLoop();
}




//void reshape(int w, int h) {
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
//
////    const float aspectRatio = ((float)w) / h;
////    float xSpan = 1; // Feel free to change this to any xSpan you need.
////    float ySpan = 1; // Feel free to change this to any ySpan you need.
////
////    if (aspectRatio > 1){
////        // Width > Height, so scale xSpan accordinly.
////        xSpan *= aspectRatio;
////    }
////    else{
////        // Height >= Width, so scale ySpan accordingly.
////        ySpan = xSpan / aspectRatio;
////    }
////
////    gluOrtho2D(-1*xSpan, xSpan, -1*ySpan, ySpan);
////
////    glViewport(0, 0, (GLint) w, (GLint) h);
//}

