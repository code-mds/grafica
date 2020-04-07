/* pushpop */
/* In OpenVMS compilare con CC/FLOAT=IEEE */

#include <GLUT/glut.h>
#include <stdio.h>

GLUquadricObj *gq;
GLfloat angolo=36.0;

void raggio() {
  glBegin(GL_LINES);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.2,0.0,0.0);
  glEnd();
} 
 
void stella() {
  int i;
  for (i=0;i<360/angolo;i++) {
     glRotatef(angolo,0.0,0.0,1.0);
     raggio();
  }
}

void ruota() {
  stella();
  gluDisk(gq,0.17,0.2,(360/angolo+1)*5,1);
}

void telaio() {
 glBegin(GL_LINE_LOOP);
   glVertex2f( 0.0, 0.0);
   glVertex2f(-0.2, 0.0);
   glVertex2f(-0.4, 0.25);
   glVertex2f(-0.6, 0.25);
   glVertex2f(-0.8, 0.00);
   glVertex2f(-0.8, 0.4);
   glVertex2f( 0.0, 0.4);

   glVertex2f( 0.8, 0.4);
   glVertex2f( 0.8, 0.00);
   glVertex2f( 0.6, 0.25);
   glVertex2f( 0.4, 0.25);
   glVertex2f( 0.2, 0.0);
 glEnd();
}

void assi() {
  glBegin(GL_LINES);
   glVertex2f( 0.0, -0.1);
   glVertex2f( 0.0, +0.1);
   glVertex2f( 0.1,  0.0);
   glVertex2f(-0.1,  0.0);
  glEnd(); 
 }

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  telaio();
  glPushMatrix();
  glTranslatef(-0.5,0.0,0.0);
  ruota();  
  glPopMatrix();
  glLineWidth(4.0);	
  glColor3f(1.0, 0.0, 0.0);	
  assi();
  glColor3f(0.0, 0.0, 0.0);	
  glLineWidth(2.0);	
  glPushMatrix();
  glTranslatef(0.5,0.0,0.0);
  ruota();  
  glPopMatrix();

  glFlush();
}
   
void reshape(int w, int h) {
   glViewport(0, 0, (GLint) w, (GLint) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      gluOrtho2D (-1.0, 1.0, -1.0*(GLfloat)h/(GLfloat)w,
              1.0*(GLfloat)h/(GLfloat)w);
	  
   else
      gluOrtho2D (-1.0*(GLfloat)w/(GLfloat)h,
               1.0*(GLfloat)w/(GLfloat)h, -1.0, 1.0);
		
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

int main(int argc, char** argv) {


 glutInit(&argc, argv);
 glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);	  
 glutInitWindowSize (500, 500);
 glutCreateWindow (argv[0]);
 glutDisplayFunc(display);	   
 glutReshapeFunc(reshape);	   

 glClearColor (1.0, 1.0, 1.0, 1.0);
 glColor3f(0.0, 0.0, 0.0);	
 glLineWidth(2.0);	
 gq=gluNewQuadric();
 glutMainLoop();
}
