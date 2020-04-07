/* icosaedro_suddiviso */

// Headers richiesti da OSX
#ifdef __APPLE__
//#include <OpenGL/gl3.h>
#include <GL/glew.h>
#include <GLUT/glut.h>
// headers richiesti da Windows e linux
#else
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#endif


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#define X .525731112119133606
#define Z .850650808352039932

static GLfloat vdata[12][3] = {
 { -X,0.0,Z}, {X,0.0, Z}, {-X,0.0,-Z}, {X  ,0.0,-Z }, 
 {0.0, Z, X}, {0.0,Z ,-X}, {0.0,-Z, X}, {0.0,-Z , -X}, 
 {Z, X, 0.0}, {-Z,X,0.0}, {Z, -X,0.0}, {-Z ,-X ,0.0} 
}; 

static GLint tindices[20][3]= {
 {4 ,0 , 1},  {9 ,0 , 4},  {5 ,9 , 4},  {5 ,4 , 8},  {8,4 , 1}, 
 {10 ,8, 1},  {3 ,8 ,10},  {3 ,5 , 8},  {2 ,5 , 3},  {7 ,2 , 3}, 
 {10,7,3},  {6 ,7 ,10},  {11 ,7, 6},  {0,11 , 6}, { 1 ,0 , 6}, 
 {1 ,6 ,10},  {0 ,9 ,11},  {11 ,9, 2},  {2 ,9 , 5},  {2 ,7 ,11} };

int livello,  cull_face=GL_FALSE;

void disegna_triangolo(GLfloat *v1, GLfloat *v2, GLfloat *v3){
 glBegin(GL_TRIANGLES);
  glVertex3fv(v1);
  glVertex3fv(v2);
  glVertex3fv(v3);
 glEnd();
}

void normalizza(GLfloat v[3]) {
 GLfloat d = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
 if ( d == 0.0) {
     perror("vettore di lunghezza nulla");
     v[0] = d = 1.0;
 }
 d = 1/d;
 v[0] *= d; v[1] *= d; v[2] *= d;
}

void dividi_o_disegna(GLfloat *v1, GLfloat *v2, GLfloat *v3,int livello){
  GLfloat v12[3], v23[3], v31[3];
  GLint i;

  if(livello == 0)
     disegna_triangolo(v1,v2,v3);
  else {     
   for (i = 0; i < 3; i++) {
     v12[i] = v1[i] + v2[i] ;	/* vettore passante per il punto medio */
     v23[i] = v2[i] + v3[i] ;  
     v31[i] = v3[i] + v1[i] ;
   }  
   normalizza(v12);		/* definisce un punto sulla sfera */
   normalizza(v23);
   normalizza(v31);

   dividi_o_disegna(v1 , v12 , v31 , livello - 1);
   dividi_o_disegna(v2 , v23 , v12 , livello - 1);
   dividi_o_disegna(v3 , v31 , v23 , livello - 1);
   dividi_o_disegna(v12, v23 , v31 , livello - 1);
  }
}

void display(void) {
 int i;
  glClear(GL_COLOR_BUFFER_BIT);
  for (i=0; i < 20; i++) {
    dividi_o_disegna(&vdata[tindices[i][0]][0],
                     &vdata[tindices[i][1]][0],
                     &vdata[tindices[i][2]][0],livello);
  }
  glFlush();
}

void keyboard(unsigned char key, int x, int y) {
   switch (key) {
      case 27:
         exit(0);
         break;
      case 'c':
         if(cull_face) {
           glDisable(GL_CULL_FACE);
           cull_face=GL_FALSE;
         }
         else {
           glEnable(GL_CULL_FACE);
           cull_face=GL_TRUE;
         }
         glutPostRedisplay();
         break;
   }
}
void keyboardS(int key, int x, int y) {
   switch (key) {
      case GLUT_KEY_UP:
   	livello+=1;
	glutPostRedisplay();
   	break;
      case GLUT_KEY_DOWN:
   	if(livello > 0) livello-=1;
	glutPostRedisplay();
   	break;
      case GLUT_KEY_RIGHT:
        glRotatef(1.0,0.0,1.0,0.0);
	glutPostRedisplay();
   	break;
      case GLUT_KEY_LEFT:
        glRotatef(-1.0,0.0,1.0,0.0);
	glutPostRedisplay();
   	break;
   }
}

int main(int argc, char** argv) {

 glutInit(&argc, argv);
 glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);	  
 glutInitWindowSize (500, 500);
 glutCreateWindow (argv[0]);
 glutDisplayFunc(display);	   
 glutSpecialFunc(keyboardS);	   
 glutKeyboardFunc(keyboard);	   
 
 glClearColor (1.0, 1.0, 1.0, 1.0);
 glColor3f(0.0, 0.0, 1.0);	
 glPolygonMode(GL_FRONT,GL_LINE);
 glPolygonMode(GL_BACK,GL_LINE);
 glLoadIdentity();
 glMatrixMode(GL_PROJECTION);
 glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); 
 glCullFace(GL_BACK);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 glutMainLoop();
}
