#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <iostream>	//monaclassinc.cpp
#include <fstream>
#include <stdlib.h>
#include <math.h>
//#include <windows.h>
#include <GLUT/glut.h>

#define Width 256
#define Height 256

int ww, wh;
static GLubyte Image[Height][Width][4];
static GLuint texName;

#include "Read_bmp.cpp"

void init(void)
{
    ip_bmp_file Read_BMP_file;
    Read_BMP_file.header_data();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures (1, &texName) ;
    glBindTexture(GL_TEXTURE_2D, texName);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ww, wh,  0, GL_RGBA,
                 GL_UNSIGNED_BYTE, Image);
    glBindTexture(GL_TEXTURE_2D, texName);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,   0.0);  glVertex3f(-2.0, -1.0, 0.0);
    glTexCoord2f(0.0,   2.0);  glVertex3f(-2.0, 1.0, 0.0);
    glTexCoord2f(2.0,   2.0);  glVertex3f(0.0, 1.0, 0.0);
    glTexCoord2f(2.0,   0.0);  glVertex3f(0.0, -1.0, 0.0);

    glTexCoord2f(0.0,   0.0);  glVertex3f(0.25, -0.25, -0.25);
    glTexCoord2f(0.0,   1.0);  glVertex3f(0.0, 1.0, 0.0);
    glTexCoord2f(1.0,   1.0);  glVertex3f(1.0, 1.0, -1.0);
    glTexCoord2f(1.0,   0.0);  glVertex3f(1.0, -1.0, -1.0);

    glTexCoord2f(0.0,   0.0);  glVertex3f(1.41421, -1.0, -1.41421);
    glTexCoord2f(0.0,   1.0);  glVertex3f(1.41421, 1.0, -1.41421);
    glTexCoord2f(1.0,   1.0);  glVertex3f(2.82842, 1.0, 0.0);
    glTexCoord2f(1.0,   0.0);  glVertex3f(2.82841, -1.0, 0.0);
    glEnd();

    glFlush();
    glDisable(GL_TEXTURE_2D);
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 5.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -4.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(350, 250);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutReshapeWindow (351,251);
    glutMainLoop();
    return 0;
}