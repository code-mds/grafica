#include <math.h>
#include <stdlib.h>
#include <GLUT/glut.h>     //sunellipsemoon.cpp

void DrawIt(void)
{
float d2r;
// Angle of revolution around Sun
static float theta = 0.0, thetar, phi = 0.0, phir = 0.0;
	d2r = 3.14159265 / 180.0;
	thetar = theta * d2r;
	phir = phi * d2r;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	glTranslatef(0.0, 0.0, -10.0);   
	glColor3ub(255, 255, 0);  	// yellow Sun
	glutSolidSphere(20.0f, 15, 15);

// Planet Orbit
   glPushMatrix();
	glColor3ub(0,0,255);    	   // blue Planet
	glTranslatef(50.0 + 120.0* sin(thetar), 40.0 *cos(thetar), 0.0f);  // Translate from origin to orbit distance
	glutSolidSphere(6.0f, 15, 15);    

//moon orbit
	glColor3ub(0, 255,255);    		  // Green moon (cheese!)
	glTranslatef(-120.0* sin(thetar), -40.0 *cos(thetar), 0.0f);
	glTranslatef(20.0* sin(phir*0.75), 20.0 *cos(phir*0.75), 0.0);  //move moon
	glTranslatef(120.0* sin(thetar), 40.0 *cos(thetar), 0.0);
	glutSolidSphere(3.0f, 15, 15);    
	phi +=20.0;
   glPopMatrix();

//second planet
   glPushMatrix();
	glColor3ub(0,0,255);    	    // Blue Planet
	glTranslatef(40.0* sin(thetar*0.5), 40.0 *cos(thetar*0.5), 0.0);  // Translate from origin to orbit distance
	glutSolidSphere(7.0f, 15, 15);  
   glPopMatrix();

//Third planet
   glPushMatrix();
	glColor3ub(255,0,255);    	    // Pink Planet
	glTranslatef(60.0* sin(thetar*0.25), 60.0 *cos(thetar*0.25), 0.0);  // Translate from origin to orbit distance
	glutSolidSphere(5.0f, 15, 15);    
   glPopMatrix();


	theta += 10.0;    
    glutSwapBuffers();  // motion=swap+redraw
}

void init()
{
	glEnable(GL_DEPTH_TEST);	
	glClearColor(0.0, 0.0, 0.0, 1.0);   
}

void TimerFunc(int value)
{
    glutPostRedisplay();      
    glutTimerFunc(100, TimerFunc, 1);  
}

void ChangeSize(int w, int h)
{
GLfloat nRange = 100.0;
	if(h == 0)	h = 1;     

    glViewport(0, 0, w, h);   
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//clipping volume (left, right, bottom, top, near, far)
    if (w <= h)
		glOrtho (-nRange, nRange, nRange*h/w, -nRange*h/w, -nRange*2.0, nRange*2.0);
    else
		glOrtho (-nRange*w/h, nRange*w/h, nRange, -nRange, -nRange*2.0, nRange*2.0);
}

void main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition( 100, 50);
    glutInitWindowSize( 400, 200);
	glutCreateWindow("Elliptical trajectory");
	init();
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(DrawIt);
    glutTimerFunc(50, TimerFunc, 1);
   	glutMainLoop();
}