#include <math.h>	//pist_lit.cpp
#include <stdlib.h>
#include <GLUT/glut.h>

static GLfloat xRot = 0.0;
static GLfloat yRot = 0.0;
char thetachar[3];
float theta = 0.0, degtorads = 0.0174532925;

void DisplayPiston ( void );
void MyInit     ( ) ;
void Bang();
void Int2Char(int );

void Bang( void)
{
glColor3f(1.0, 0.0, 0.0);
glBegin(GL_POINTS);
 glVertex2f(0.0,12.0);
glEnd();
glFlush();
glPointSize(10.0);
}

void Int2Char(int number)
{     //integer -> char for graphics o/p
char charnum[10] = {'0','1','2','3','4','5','6','7','8','9'};
int n1, n2, n3;
n1 = number % 10;
n2 = number - n1;
n2 = n2 % 100;
n3 = number - n2 - n1;
n2 = n2 / 10;
n3 = n3 / 100;
thetachar[0] = charnum[n1];
thetachar[1] = charnum[n2];
thetachar[2] = charnum[n3];
}

void DisplayPiston( void ) {
char xang[9] = {'T','h','e','t','a','='};
int i;
GLfloat x, y, xtop, ytop, crank_rad, crank_rad2, con_lenth;
GLUquadricObj *cylobj;
glClear( GL_COLOR_BUFFER_BIT);
Int2Char( (int) theta);
xang[6] = thetachar[2];
if( xang[6] == '0') xang[6] = ' ';
xang[7] = thetachar[1];
xang[8] = thetachar[0];
glColor3f(1.0, 0.0, 0.0);
for(i=0; i<9; i++) {
 glRasterPos3f(3.1+i*0.8, 0.0, 0.0);
 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, xang[i]);
}
//  rotation of whole systen
glPushMatrix();
	glRotatef(xRot, 1.0, 0.0, 0.0);
	glRotatef(yRot, 0.0, 1.0, 0.0);
	glPushMatrix();      //ignition
		if(theta >75.0 && theta <95.0) Bang();
    glPopMatrix();

    glPushMatrix();   //Rectf axes centred on origin
       glColor3f(0.0, 1.0, 0.0);             
       glTranslatef( 0.0, -2.0, 0.0);
       glRectf(5.0, 0.2, -5.0, -0.2);
       glRotatef(90.0, 0.0, 0.0, 1.0);
       glRectf(5.0, 0.2, -5.0, -0.2);
    glPopMatrix();

  glPushMatrix();      //con rod
    crank_rad = 2.0;
    con_lenth = 6.0;
    xtop = 0.0;
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
      x = crank_rad *  cos(theta*degtorads);
      y = crank_rad *  sin(theta*degtorads);
      ytop = y + sqrt(con_lenth*con_lenth - x*x);
      glVertex2f(x, y-2.0);
      glVertex2f(xtop, ytop+1.0);
    glEnd();
  glPopMatrix();

    cylobj = gluNewQuadric();
    gluQuadricDrawStyle(cylobj, GLU_FILL);
    gluQuadricNormals(cylobj, GLU_FLAT);
    glColor3f(0.6, 0.6, 0.6);
  glPushMatrix();      // piston
      glRotatef(-90.0, 1.0, 0.0, 0.0);
      glTranslatef( xtop, 0.0, ytop);  //z now in y direction
      gluCylinder(cylobj, 1.0, 1.5, 3.0, 10, 8);
  glPopMatrix();

  glPushMatrix();      //line crank
      crank_rad2 = crank_rad * 0.5;
      glColor3f(0.0, 0.0, 1.0);
      glTranslatef( 0.0, -2.0, 0.0);
      glRotatef(theta , 0.0, 0.0, 1.0);
      glTranslatef( crank_rad2, 0.0, 0.0);
      glRectf(-crank_rad2, 0.1, crank_rad2, -0.1);
   		glColor3f(1.0, 1.0, 0.0);
   	  glPushMatrix();  //solid crank
   		glScalef (1.5, 0.6, 0.5);
   		glutSolidCube (1.0);
   	  glPopMatrix();
  glPopMatrix();
//glFlush();
  glutSwapBuffers();
glPopMatrix();
}

void MyInit ( void ) {
    glClearColor   ( 1.0, 1.0, 1.0, 0.0 ) ;
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(5.0);
    glShadeModel(GL_FLAT);
}

void ArrowKeys(int key, int x, int y)
{
	if(key == GLUT_KEY_UP) 	xRot-= 5.0;
	if(key == GLUT_KEY_DOWN) xRot += 5.0;
	if(key == GLUT_KEY_LEFT) yRot -= 5.0;
	if(key == GLUT_KEY_RIGHT) yRot += 5.0;
	if(key > 356.0) xRot = 0.0;
	if(key < -1.0)  xRot = 355.0;
	if(key > 356.0) yRot = 0.0;
	if(key < -1.0)  yRot = 355.0;
    glutPostRedisplay();
}

void wo_wo_wo()
{
int i, j;
for(i=0; i<900000; i++) j=0; //slow dowm!
   theta = theta + 0.5;
   if(theta>=720.0) theta-=720;
   glutPostRedisplay();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho(-11.0, 11.0, -11.0, 13.0, 11.0, -11.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void main(int argc, char **argv) {
    glutInit               ( &argc, argv );
    glutInitDisplayMode    ( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize     ( 240, 180 );
    glutInitWindowPosition ( 50, 50 ) ;
    glutCreateWindow       ( "Piston engine" );
    MyInit ( );
	glutSpecialFunc(ArrowKeys);
    glutDisplayFunc( DisplayPiston);
    glutReshapeFunc( reshape);
    glutIdleFunc(wo_wo_wo);
    glutMainLoop ( );
}


