//#include <windows.h>	//lightpyramid.cpp
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#include <GLUT/glut.h>
#include <math.h>
#include <stdio.h>

static GLfloat xrot = 0.0, yrot = 0.0;
static GLfloat xpos = 0.0, ypos = 50.0;
static GLboolean lightEnabled = GL_FALSE;


void Normalise(float vector[3])
{
    GLfloat length;
    // length of the vector
    length = (float)sqrt((vector[0]*vector[0]) +
                         (vector[1]*vector[1]) +
                         (vector[2]*vector[2]));

    // avoid divide by zero.
    if(length == 0.0) length = 1.0;

    // Divide by the length = unit normal vector.
    vector[0] /= length;
    vector[1] /= length;
    vector[2] /= length;
}

void Normal(float v[3][3], float out[3])
{
    float v1[3],v2[3];
    static const int x = 0, y = 1, z = 2;

    // two vectors from the three points
    v1[x] = v[0][x] - v[1][x];
    v1[y] = v[0][y] - v[1][y];
    v1[z] = v[0][z] - v[1][z];

    v2[x] = v[1][x] - v[2][x];
    v2[y] = v[1][y] - v[2][y];
    v2[z] = v[1][z] - v[2][z];

    // cross product to get normal vector in out
    out[x] = v1[y]*v2[z] - v1[z]*v2[y];
    out[y] = v1[z]*v2[x] - v1[x]*v2[z];
    out[z] = v1[x]*v2[y] - v1[y]*v2[x];

    Normalise(out);
}

void DrawIt(void)
{
    GLfloat normal[3];
    GLfloat	 lightPos[] = { xpos, ypos, 50.0, 1.0 };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);  // position light
    // Save the matrix state and do the rotations
    glPushMatrix();
    glRotatef(xrot, 1.0, 0.0, 0.0);
    glRotatef(yrot, 0.0, 1.0, 0.0);

    // set material grey
    glColor3ub(128, 128, 128);
    glBegin(GL_TRIANGLES);

    float v[3][3] = {{ -20.0,0.0,30.0 },
                     { 0.0, 25.0, 30.0 },
                     { 0.0, 0.0, -56.0 }};
    Normal(v,normal);
    glNormal3fv(normal);
    glVertex3fv(v[0]);
    glVertex3fv(v[1]);
    glVertex3fv(v[2]);

    {
        float v[3][3] = {{ 0.0, 0.0, -56.0 },
                         { 0.0, 25.0, 30.0 },
                         { 20.0,0.0,30.0 }};
        Normal(v,normal);
        glNormal3fv(normal);
        glVertex3fv(v[0]);
        glVertex3fv(v[1]);
        glVertex3fv(v[2]);
    }
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(20.0,0.0,30.0);
    glVertex3f(-20.0, 0.0, 30.0);
    glVertex3f(0.0, 0.0, -56.0);

    {
        float v[3][3] = {{ -20.0, 0.0, 30.0 },
                         { 20.0,0.0,30.0 },
                         { 0.0, 25.0, 30.0 }};
        Normal(v,normal);
        glNormal3fv(normal);
        glVertex3fv(v[0]);
        glVertex3fv(v[1]);
        glVertex3fv(v[2]);
        glEnd();
    }
    glPopMatrix();      // Restore matrix state
    glutSwapBuffers();  // Display results
}

void Environment()
{
    // Light values and coordinates
    GLfloat  ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat  diffuseLight[] = { 0.9, 0.9, 0.9, 1.0 };

    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);

    //glEnable(GL_LIGHTING);

    // Setup and enable light 0
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
    glEnable(GL_LIGHT0);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);

    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // blue background
    glClearColor(0.0, 0.0, 1.0, 1.0 );
}

void KeyControl(int key, int x, int y)
{
    if(key == GLUT_KEY_F1) xpos-= 5.0f;

    if(key == GLUT_KEY_F2) 	xpos+= 5.0f;

    if(key == GLUT_KEY_UP) 	xrot-= 5.0;
    if(key == GLUT_KEY_DOWN) xrot += 5.0;
    if(key == GLUT_KEY_LEFT) yrot -= 5.0;
    if(key == GLUT_KEY_RIGHT) yrot += 5.0;
    if(xrot > 356.0f) xrot = 0.0;
    if(xrot < -1.0f)  xrot = 355.0;
    if(yrot > 356.0f) yrot = 0.0;
    if(yrot < -1.0f)  yrot = 355.0;

    glutPostRedisplay();
}

void keyfunc( int key, int x, int y) {
    if (key == 'l')  {
        if (lightEnabled) {
            glDisable(GL_LIGHTING);
            lightEnabled = GL_FALSE;
        }
        else {
            glEnable(GL_LIGHTING);
            lightEnabled = GL_TRUE;
        }
    }
        glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
    GLfloat viewvol = 60.0;

    if(h == 0) h = 1;
    // Reset coordinate system for
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // clipping volume (l, r, b, t, n, f)
    if (w <= h)
        glOrtho (-viewvol, viewvol, -viewvol*h/w, viewvol*h/w, -viewvol, viewvol);
    else
        glOrtho (-viewvol*w/h, viewvol*w/h, -viewvol, viewvol, -viewvol, viewvol);
    // and back to
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Illuminated pyramid");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(KeyControl);
    glutKeyboardFunc(keyfunc);
    glutDisplayFunc(DrawIt);
    Environment();
    glutMainLoop();
}