/* primitive */
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
// Headers richiesti da OSX
#ifdef __APPLE__
//#include <OpenGL/gl3.h>
#include <GL/glew.h>
#include <GLUT/glut.h>
// headers richiesti da Windows e linux
#else

#include <stdio.h>
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#endif



int tastiera=0;

GLenum modo;

void figura(GLenum modo) {
  glBegin(modo);
    glVertex2f(-0.4, +0.6); 
    glVertex2f(-0.8, -0.4); 
    glVertex2f(-0.3, -0.8); 
    glVertex2f( 0.4, -0.6); 
    glVertex2f( 0.2, -0.4); 
    glVertex2f( 0.9,  0.0); 
    glVertex2f( 0.2,  0.4); 
    glVertex2f( 0.1,  0.2); 
  glEnd();
} 

void primitive(void) {
   switch(tastiera) {
      case 0: printf("GL_LINES\n"); 
              figura(GL_LINES);
              break;
      case 1: printf("GL_LINES, spessore 2\n"); 
              glLineWidth(2.0); 
              figura(GL_LINES);
              glLineWidth(0.0);   /* con 1.0 non ripristina la situazione iniziale */
              break;
      case 2: printf("GL_LINES, tratteggio\n"); 
              glLineStipple(1,0xF07); 
              glEnable(GL_LINE_STIPPLE); 
              figura(GL_LINES);
              glDisable(GL_LINE_STIPPLE);
              break;
      case 3: printf("GL_LINE_STRIP\n"); 
              figura(GL_LINE_STRIP);
              break;
      case 4: printf("GL_LINE_LOOP\n"); 
              figura(GL_LINE_LOOP);
	      break;
      case 5: printf("GL_POLYGON\n"); 
              figura(GL_POLYGON);
              break;
      case 6: printf("GL_TRIANGLES,GL_LINE\n"); 
              glPolygonMode(GL_FRONT,GL_LINE); 
              figura(GL_TRIANGLES);
              break;
      case 7: printf("GL_TRIANGLES,GL_FILL\n"); 
              glPolygonMode(GL_FRONT,GL_FILL); 
              figura(GL_TRIANGLES);
              break;
      case 8: printf("GL_QUADS\n"); 
              glPolygonMode(GL_FRONT,GL_LINE); 
              figura(GL_QUADS);
	      break;
      case 9: printf("GL_QUADS,GL_FILL\n"); 
              glPolygonMode(GL_FRONT,GL_FILL); 
              figura(GL_QUADS);
              break;
      case 10:printf("GL_QUAD_STRIP,GL_LINE\n"); 
              glPolygonMode(GL_FRONT,GL_LINE); 
              figura(GL_QUAD_STRIP);
              break;
      case 11:printf("GL_QUAD_STRIP,GL_FILL\n"); 
              glPolygonMode(GL_FRONT,GL_FILL); 
              figura(GL_QUAD_STRIP);
              break;
      case 12:printf("GL_TRIANGLE_STRIP,GL_FILL\n"); 
              glPolygonMode(GL_FRONT,GL_FILL); 
              figura(GL_TRIANGLE_STRIP);
              break;
      case 13:printf("GL_TRIANGLES_FAN,GL_LINE\n"); 
              glPolygonMode(GL_FRONT,GL_LINE); 
              figura(GL_TRIANGLE_FAN);
              break;
      case 14:printf("GL_TRIANGLES_FAN,GL_FILL\n"); 
              glPolygonMode(GL_FRONT,GL_FILL); 
              figura(GL_TRIANGLE_FAN);
              break;
    }
}

void init(void) {
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluOrtho2D (-1.0, 1.0, -1.0, 1.0);
   glClearColor (1.0, 1.0, 1.0, 0.0);
   glColor3f(0.0, 0.0, 1.0);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    primitive();
    glFlush();
}

void reshape(int w, int h) {
   printf("reshape: w=%d, h=%d\n",w,h);
   glViewport(0, 0, (GLint) w, (GLint) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
               1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
   else
      glOrtho (-1.5*(GLfloat)w/(GLfloat)h,
               1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void mouse(int bottone, int stato, int x, int y) {
       tastiera+=1;
       glutPostRedisplay();
       if (tastiera>14)
          tastiera=0;
}

void keyboard(unsigned char key, int x, int y) {
   switch (key) {
      case 27:
         exit(0);
         break;
	
      case 32:
   	tastiera+=1;
	glutPostRedisplay();
	if (tastiera>14)
		tastiera=0;
   	break;
   }
}
int main(int argc, char** argv)	{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);	  
   glutInitWindowSize (350, 350);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display);	   
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouse);
   glutMainLoop();
}
