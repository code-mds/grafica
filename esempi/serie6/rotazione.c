#include <stdlib.h>
#include <GLUT/glut.h>


float angle=0.0;

void Display ( void ) {
	glClear(GL_COLOR_BUFFER_BIT );
	glColor3f(0.0, 1.0, 0.0);
	glMatrixMode( GL_MODELVIEW ) ;
	glLoadIdentity ( ) ;
	for(angle=0; angle <18; angle=angle + 3) {
	
		
		// ruota intorno all'asse z
		glRotatef( angle, 0.0, 0.0, 1.0);
		if (angle > 8) {
			//ruota intorno all'asse x
			glRotatef( angle*2, 1.0, 0.0, 0.0);
			glColor3f(1.0, 0.0, 0.0);
		}
    	glBegin(GL_LINE_LOOP);
    	glVertex2f(0.25, 0.25);
        glVertex2f(0.75, 0.25);
        glVertex2f(0.75, 0.75);
        glVertex2f(0.25, 0.75);
		glEnd();
	}
	glFlush();
}

void MyInit ( void ) {
  glClearColor   ( 0.0, 0.0, 0.0, 1.0 );
}

void Reshape( int w, int h){
	glMatrixMode  ( GL_PROJECTION );
	glLoadIdentity( ) ;
	if(w<h)
 		gluOrtho2D( 0.0, (double)1.0*w/h, 0.0, (double)1.0 );
	else
		gluOrtho2D( 0.0, (double)1.0, 0.0, (double)1.0*h/w);
	//glMatrixMode  ( GL_MODELVIEW );
	//glLoadIdentity( );
}

void main(int argc, char **argv) {
    glutInit               ( &argc, argv ) ;
    glutInitDisplayMode    ( GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize     ( 250, 250 );
    glutInitWindowPosition ( 50, 50 );      
    glutCreateWindow       ( "Display z & x rotation" );
    MyInit ( );
    glutDisplayFunc ( Display );
    glutReshapeFunc( Reshape);
    glutMainLoop ( ) ;
}

