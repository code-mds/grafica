/* normali_random */ 

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#define NUM 10
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

const GLfloat PI = 3.1415926535f;

const GLfloat ALT = 5.0;
const GLfloat DIST = 5.0;		
const GLfloat LATO = 6.0;		

int window_width = 600;
int window_height = 600;
int alpha, dev = 0 ;
float beta = 90.0, esponente=0.0 , shininess=0.0;
int luce_parallela = GL_FALSE , luce_diffusa = GL_TRUE, 
    luce_riflessa = GL_FALSE;

int mostra_normali = GL_TRUE;

const GLfloat bianco[] = { 1.0, 1.0, 1.0, 1.0 };
const GLfloat nero[] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat suolo_diffuso[] = { 0.7f, 0.7f, 0.2f, 1.0 };
const GLfloat suolo_riflesso[] = { 0.4f, 0.4f, 0.1f, 1.0 };
const GLfloat luce_rifl[] = { 2.0f, 2.0f, 2.0f, 1.0 };
const GLfloat luce_dif[] = { 0.95f, 0.95f, 0.95f, 1.0 };
const GLfloat luce_pos[] = { 0.0, 1.0, 0.0, 1.0 };
const GLfloat luce_par[] = { 0.0, 1.0, 0.0, 0.0 };
const GLfloat luce_spenta[] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat direzione_spot[] = { 0.0, -1.0, 0.0, 1.0 };

GLfloat vert[NUM][NUM][3];	
GLfloat norm[NUM][NUM][3];

void vertici() {
   int x,z;
   for (x = 0; x < NUM; x++)
      for (z = 0; z < NUM; z++) {
         vert[x][z][0] = LATO * (((float)x)/((float)NUM) -0.5);
         vert[x][z][1] = 0.0;
         vert[x][z][2] = LATO * (((float)z)/((float)NUM) -0.5);
   }
}

void normali() {
   int x,z;
   GLfloat u,v,w;
   for (x = 0; x < NUM; x++)
      for (z = 0; z < NUM; z++) {
         u = ((float)dev/20) * rand() / RAND_MAX;
         w = ((float)dev/20) * rand() / RAND_MAX;
         if((u*u+w*w)>0.9999999)
            v=0.000001;
         else
            v = sqrt(1.0 - u * u - w * w);
         norm[x][z][0] = u;
         norm[x][z][1] = v; 
         norm[x][z][2] = w;
      }
}

void display () {
   int x,z;
   glClearColor(0.5, 0.5, 1.0, 1.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();
   glPushMatrix();
   glTranslatef(0.25, 0, 0);
   for (x = 0; x < NUM - 1; x++)
     for (z = 0; z < NUM - 1; z++) {
         glBegin(GL_QUADS);
           glNormal3fv(norm[x][z]);
           glVertex3fv(vert[x][z]);
           glVertex3fv(vert[x+1][z]);
           glVertex3fv(vert[x+1][z+1]);
           glVertex3fv(vert[x][z+1]);
         glEnd();
   }
	
   if (mostra_normali) {
     glDisable(GL_LIGHTING);
     glColor3f(1.0, 0.0, 0.0);
     glLineWidth(2.0);
     glBegin(GL_LINES);
        for (x = 1; x < NUM; x++)
           for (z = 1; z < NUM; z++) {
              glVertex3fv(vert[x][z]);
              glVertex3f(
              vert[x][z][0] + norm[x][z][0],
              vert[x][z][1] + norm[x][z][1],
              vert[x][z][2] + norm[x][z][2]);
           }
     glEnd();
     glEnable(GL_LIGHTING);
   }
   glutSwapBuffers();
}

void reshape (int w, int h) {
   window_width = w;
   window_height = h;
   glViewport(0, 0, window_width, window_height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(30.0, 
     (GLfloat)window_width/(GLfloat)window_height, 0.5, 3 * LATO);
   glutPostRedisplay();
}

void keys (unsigned char key, int x, int y) {
   switch (key) {
     case 27:			
       exit(0);
     case 'n':			
       mostra_normali = ! mostra_normali;
       glutPostRedisplay();
       break;
     case 'r':
       luce_riflessa = ! luce_riflessa;
       if (luce_riflessa) 
         glLightfv(GL_LIGHT0, GL_SPECULAR, luce_rifl);
       else
         glLightfv(GL_LIGHT0, GL_SPECULAR, luce_spenta);
       glutPostRedisplay();
       break;
     case 'd':
       luce_diffusa = ! luce_diffusa;
       if (luce_diffusa) 
         glLightfv(GL_LIGHT0, GL_DIFFUSE, luce_dif);
       else
         glLightfv(GL_LIGHT0, GL_DIFFUSE, luce_spenta);
       glutPostRedisplay();
       break;
     case 'x':
       dev=(dev+1)%20;
       normali();
      glutPostRedisplay();
       break;
     case 'C':
       if( beta <180.0) beta=beta+1.0;
       glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,beta);
       glutPostRedisplay();
       printf("beta=%f\n",beta);
       break;
     case 'c':
       if(beta >0.0)beta=beta-1.0;
       glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,beta);
       glutPostRedisplay();
       printf("beta=%f\n",beta);
       break;
     case 'E':
       if( esponente <128.0) esponente=esponente+1.0;
       glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,esponente);
       glutPostRedisplay();
       printf("esponente=%f\n",esponente);
       break;
     case 'e':
       if(esponente >0.0)esponente=esponente-1.0;
       glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,esponente);
       glutPostRedisplay();
       printf("esponente=%f\n",esponente);
       break;
     case 'S':
       if( shininess <128.0) shininess=shininess+1.0;
       glMaterialf(GL_FRONT,GL_SHININESS,shininess);
       glutPostRedisplay();
       printf("shininess=%f\n",shininess);
       break;
     case 's':
       if(shininess >0.0)shininess=shininess-1.0;
       glMaterialf(GL_FRONT,GL_SHININESS,shininess);
       glutPostRedisplay();
       printf("shininess=%f\n",shininess);
       break;
     case 'p':
       luce_parallela = ! luce_parallela;
       if (luce_parallela) 
         glLightfv(GL_LIGHT0, GL_POSITION, luce_par);
       else
         glLightfv(GL_LIGHT0, GL_POSITION, luce_pos);
       glutPostRedisplay();
       break;
   }
}

void init () {
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glShadeModel(GL_SMOOTH);
   gluLookAt (0.0, ALT, DIST,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0 );
   glPushMatrix();
   vertici();
   normali();
   glShadeModel(GL_FLAT);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, luce_dif);
   glLightfv(GL_LIGHT0, GL_SPECULAR, luce_spenta);
   glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direzione_spot);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, suolo_diffuso);
   glMaterialfv(GL_FRONT, GL_SPECULAR, suolo_riflesso);
   glEnable(GL_LIGHT0);
   glLightfv(GL_LIGHT0, GL_POSITION, luce_pos);
   glEnable(GL_DEPTH_TEST);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keys);
}

int main (int argc, char *argv[]) {
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(window_width, window_height);
   glutCreateWindow("Normali random.");
   glutReshapeWindow (1201,501);
   init();
   printf("'x': modifica normale\n'n': normali on/off\n"); 
   printf("'d': luce diffusa on/off\n'r': luce riflessa on/off\n");
   printf("'p': toggle luce posizionata/parallela\n");
   printf("'C': > spot cutoff\n'c': < spot cutoff\n");
   printf("'E': > spot exponent\n'e': < spot exponent\n");
   printf("'S': > lucentezza\n's': < lucentezza\n");
   glutMainLoop();
}
