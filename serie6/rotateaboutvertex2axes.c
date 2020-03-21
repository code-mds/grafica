#include <stdlib.h>
#include <GLUT/glut.h>

float angle=0.0;

void Display();
void MyInit( );
void Reshape(int w, int h);

void Display ( void ) {
	GLfloat red;	
	glClear ( GL_COLOR_BUFFER_BIT );
	glColor3f(0.0, 1.0, 0.0);
	red = 0.3;
	for(angle=0; angle < 25; angle=angle + 3) {
		if( angle < 10 ) {
			glTranslatef(.75f, 0.75f, 0.0f);
			glRotatef( angle, 0.0, 0.0, 1.0);
			glTranslatef(-0.75f, -0.75f, 0.0f);
		}
		if( angle > 9 ) {
			red = red + 0.1;
			glColor3f(red, 0.0, 0.0);
			glTranslatef(.75f, 0.75f, 0.0f);
			glRotatef( angle, 1.0, 0.0, 0.0);
			glRotatef( angle/2.0, 0.0, 0.0, 1.0);
			glTranslatef(-0.75f, -0.75f, 0.0f);
		}
    	glBegin(GL_LINE_LOOP);
    		glVertex3f(0.25, 0.25, 0.0);
        	glVertex3f(0.75, 0.25, 0.0);
        	glVertex3f(0.75, 0.75, 0.0);
        	glVertex3f(0.25, 0.75, 0.0);
			glEnd();
	}
	glFlush();
}

void MyInit ( void ) {
 	glClearColor   ( 0.0, 0.0, 0.0, 1.0 );
 	glMatrixMode  ( GL_MODELVIEW );
  	glLoadIdentity( );
}

void Reshape( int w, int h) {
	glMatrixMode  ( GL_PROJECTION );
	glLoadIdentity( );
	if(w<h)
 		gluOrtho2D( 0.0, (double)1.0*w/h, 0.0, (double)1.0 );
	else
		gluOrtho2D( 0.0, (double)1.0, 0.0, (double)1.0*h/w);
	glMatrixMode  ( GL_MODELVIEW );
	glLoadIdentity( );
}

void main(int argc, char **argv) {
    glutInit              ( &argc, argv ) ;
    glutInitDisplayMode   ( GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize    ( 250, 250 );
    glutInitWindowPosition( 50, 50 );      
    glutCreateWindow      ( "x & z rotation about TRHC" );
    MyInit ( );
    glutDisplayFunc ( Display );
    glutReshapeFunc( Reshape);
    glutMainLoop ( );
}

