/* look_at */
/* In OpenVMS compilare con cc/float=ieee */

#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define X .525731112119133606
#define Z .850650808352039932

float phi=90.0,theta=0.0,r=1.0,xe=0.0,ye,ze, k, xu=0.0, yu=1.0, zu=0.0,
      thetau=0.0;
GLdouble left=-1.0 , right=1.0, bottom=-1.0, top=1.0;
int cull_face=GL_FALSE, up_vector=GL_FALSE, piramide=GL_FALSE,
    ViewingVolumeFermo=GL_FALSE, glv[4];
GLdouble near=0.0, far=2.0;               
static GLfloat vico[12][3] = {
 { -X,0.0,Z}, {X,0.0, Z}, {-X,0.0,-Z}, {X  ,0.0,-Z }, 
 {0.0, Z, X}, {0.0,Z ,-X}, {0.0,-Z, X}, {0.0,-Z , -X}, 
 {Z, X, 0.0}, {-Z,X,0.0}, {Z, -X,0.0}, {-Z ,-X ,0.0} 
}; 

static GLfloat vpira[5][3] = {
 {0.0,0.0, -Z}, 
 {-X, -X, Z}, {-X,  X, Z}, {X, X, Z}, {X, -X, Z} 
}; 

static GLint indico[20][3]= {
 {4 ,0 , 1},  {9 ,0 , 4},  {5 ,9 , 4},  {5 ,4 , 8}, {8,4 , 1}, 
 {10,8 , 1},  {3 ,8 ,10},  {3 ,5 , 8},  {2 ,5 , 3}, {7 ,2 , 3}, 
 {10,7 , 3},  {6 ,7 ,10},  {11 ,7, 6},  {0,11 , 6}, { 1 ,0 , 6}, 
 {1 ,6 ,10},  {0 ,9 ,11},  {11 ,9, 2},  {2 ,9 , 5}, {2 ,7 ,11} 
};

static GLint indpira[4][3]= {
 {0,2,3}, {0,3,4}, {4,1,0},{0,1,2} 
};

void disegna_triangolo(GLfloat *v1, GLfloat *v2, GLfloat *v3){
 glBegin(GL_TRIANGLES);
  glVertex3fv(v1);
  glVertex3fv(v2);
  glVertex3fv(v3);
 glEnd();
}

void disegna_icosaedro(){
  int i;
  for (i=0; i < 20; i++) {
    disegna_triangolo(&vico[indico[i][0]][0],
            &vico[indico[i][1]][0],
            &vico[indico[i][2]][0]);
  }
}

void disegna_piramide(){
  int i;
  for (i=0; i < 4; i++) {
    disegna_triangolo(&vpira[indpira[i][0]][0],
                      &vpira[indpira[i][1]][0],
                      &vpira[indpira[i][2]][0]);
  }
}

void disegna_punti(){
 glBegin(GL_POINTS);
 glVertex3fv(&vico[0][0]);
 glVertex3fv(&vico[1][0]);
 glVertex3fv(&vico[4][0]);
 glVertex3fv(&vico[6][0]);
 glEnd();
}

void display(void) {
 glClear(GL_COLOR_BUFFER_BIT);
 glLoadIdentity();
 if(!up_vector) {
   xe=r*sin(k*phi)*sin(k*theta);
   ye=r*cos(k*phi);
   ze=r*sin(k*phi)*cos(k*theta);
   printf("xe,ye,ze, near, far: %f, %f, %f %f %f\n",xe,ye,ze, near, far);
 }
 else {
   xu=sin(k*thetau);
   zu=sin(k*thetau);
   printf("upvector - xu,zu: %f, %f\n",xu, zu);	
 }
 
 gluLookAt(xe,ye,ze,0.0,0.0,0.0,xu,yu,zu);
 if(piramide)
   disegna_piramide();
 else {
   disegna_icosaedro();
   disegna_punti();
 }
 glFlush();
}

void shape(int w, int h) {
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
     if (w <= h)
        glOrtho (left, right, bottom*(GLfloat)h/(GLfloat)w,
                 top*(GLfloat)h/(GLfloat)w, near, far);
     else
        glOrtho (left*(GLfloat)w/(GLfloat)h,
                 right*(GLfloat)w/(GLfloat)h,bottom,top, near, far);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void reshape(int w, int h) {
   glViewport(0, 0, (GLint) w, (GLint) h);
   shape(w,h);
}

void keyboard(unsigned char key, int x, int y) {
   switch (key) {
      case 27:
         exit(0);
         break;
      case 'f':
         if(ViewingVolumeFermo)
           ViewingVolumeFermo=GL_FALSE;
         else
           ViewingVolumeFermo=GL_TRUE;
         break;
      case 't':
         if(piramide)
           piramide=GL_FALSE;
         else
           piramide=GL_TRUE;
         glutPostRedisplay();
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
      case '+':
         r+=0.1;
         if(ViewingVolumeFermo){
           near+=0.1; far+=0.1;
           glGetIntegerv(GL_VIEWPORT,glv);
           shape(glv[2],glv[3]);
         }
         glutPostRedisplay();
         break;
      case '-':
         r-=0.1;
         if(ViewingVolumeFermo){
           near-=0.1; far-=0.1;
           glGetIntegerv(GL_VIEWPORT,glv);
           shape(glv[2],glv[3]);
         }
         glutPostRedisplay();
         break;
      case 'u':
         if(up_vector) 
           up_vector=GL_FALSE;
         else 
           up_vector=GL_TRUE;
         break;
   } 
}
void keyboardS(int key, int x, int y) {
   switch (key) {
      case GLUT_KEY_UP:
        if(!up_vector)
          phi-=1.0;
   	break;
      case GLUT_KEY_DOWN:
        if(!up_vector)
          phi+=1.0;
   	break;
      case GLUT_KEY_RIGHT:
        if(!up_vector)
          theta+=1.0;
        else
          thetau+=2.0;
   	break;
      case GLUT_KEY_LEFT:
        if(!up_vector)
          theta-=1.0;
        else
          thetau-=2.0;
   	break;
   }
   glutPostRedisplay();
}

int main(int argc, char** argv) {

 glutInit(&argc, argv);
 glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);	  
 glutInitWindowSize (500, 500);
 glutCreateWindow (argv[0]);
 glutDisplayFunc(display);	   
 glutReshapeFunc(reshape);	   
 glutSpecialFunc(keyboardS);	   
 glutKeyboardFunc(keyboard);	   

 k=atan(1.0)/45; 
 glClearColor (1.0, 1.0, 1.0, 1.0);
 glColor3f(0.0, 0.0, 0.0);	
 glLineWidth(2.0);	
 glPointSize(10.0);
 glPolygonMode(GL_FRONT,GL_LINE);
 glPolygonMode(GL_BACK,GL_LINE);
 glCullFace(GL_BACK);

 glutMainLoop();
}
