/* cubo */
/* In OpenVMS compilare con cc/float=ieee */

#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define X .5
#define Y .5
#define Z .5

float phi=90.0,theta=0.0,r=1.0,xe=0.0,ye,ze, k, xu=0.0, yu=1.0, zu=0.0,
      thetau=0.0;
GLdouble left=-1.0 , right=1.0, bottom=-1.0, top=1.0;
int cull_face=GL_FALSE, up_vector=GL_FALSE, prospettiva=GL_FALSE, glv[4];
GLdouble clip_plane_0[4]={1.0,-1.0,0.0,0.5};
int clip_plane;

static GLfloat vdata[8][3] = {
 { X, Y , Z}, {-X, Y, Z}, {-X, Y,-Z}, { X, Y,-Z}, 
 { X,-Y , Z}, {-X,-Y, Z}, {-X,-Y,-Z}, { X,-Y,-Z} 
}; 

static GLint tindices[6][4]= {
 {0,3,2,1},  {4,7,3,0},  {4,5,6,7},  {0,1,5,4},  {6,5,1,2}, {6,2,3,7}};

void disegna_quadrato(GLfloat *v1, GLfloat *v2, GLfloat *v3, GLfloat *v4){
 glBegin(GL_QUADS);
  glVertex3fv(v1);
  glVertex3fv(v2);
  glVertex3fv(v3);
  glVertex3fv(v4);
 glEnd();
}

void disegna_punti() {
 glBegin(GL_POINTS);
   glVertex3fv(&vdata[0][0]);
   glVertex3fv(&vdata[4][0]);
   glVertex3fv(&vdata[5][0]);
   glVertex3fv(&vdata[1][0]);
 glEnd();
}

void display(void) {
 int i;
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  if(!up_vector) {
    xe=r*sin(k*phi)*sin(k*theta);
    ye=r*cos(k*phi);
    ze=r*sin(k*phi)*cos(k*theta);
    printf("xe,ye,ze: %f, %f, %f\n",xe,ye,ze);
  }
  else {
    xu=sin(k*thetau);
    zu=sin(k*thetau);
  }
  
  gluLookAt(xe,ye,ze,0.0,0.0,0.0,xu,yu,zu);
  for (i=0; i < 6; i++) {
    disegna_quadrato(&vdata[tindices[i][0]][0],
                     &vdata[tindices[i][1]][0],
                     &vdata[tindices[i][2]][0],
                     &vdata[tindices[i][3]][0]);
  }
  disegna_punti();
  glFlush();
}

void shape(int w, int h) {
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if(!prospettiva) {
     if (w <= h)
        glOrtho (left, right, bottom*(GLfloat)h/(GLfloat)w,
                 top*(GLfloat)h/(GLfloat)w, 0.0, 10.0);
     else
        glOrtho (left*(GLfloat)w/(GLfloat)h,
                 right*(GLfloat)w/(GLfloat)h,bottom,top, 0.0, 10.0);
   } else 
   gluPerspective(95.0,1.0,0.0,10.0);
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
      case 'l': /* clipping plane */
         if(clip_plane) {
           glDisable(GL_CLIP_PLANE0);
           clip_plane=GL_FALSE;
           printf("Clip OFF\n");
         } 
         else {
           glEnable(GL_CLIP_PLANE0);
           clip_plane=GL_TRUE;
           printf("Clip ON\n");
         }
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
          glutPostRedisplay();
         break;
      case '-':
         r-=0.1;
          glutPostRedisplay();
         break;
      case 'u':
         if(up_vector) 
           up_vector=GL_FALSE;
         else 
           up_vector=GL_TRUE;
         break;
      case 'p':
         if(prospettiva) 
           prospettiva=GL_FALSE;
         else
           prospettiva=GL_TRUE;
         glGetIntegerv(GL_VIEWPORT,glv);
         shape(glv[2],glv[3]);
         glutPostRedisplay();
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
 glColor3f(1.0, 0.0, 0.0);	
 glLineWidth(2.0);	
 glPointSize(10.0);
 glPolygonMode(GL_FRONT,GL_LINE);
 glPolygonMode(GL_BACK,GL_LINE);
 glCullFace(GL_BACK);
 glClipPlane (GL_CLIP_PLANE0,clip_plane_0);

 glutMainLoop();
}
