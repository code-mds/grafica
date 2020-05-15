/* bitmap */

#include <GLUT/glut.h>
#include <stdio.h>

GLfloat vet[]={0.0,0.0,0.0,0.0} ;

GLubyte rasters[24] = {
    0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
    0xff, 0x00, 0xff, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
    0xff, 0xc0, 0xff, 0xc0};

void init(void){
    glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
    glClearColor (1.0, 1.0, 1.0, 1.0);
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 0.0, 0.0);
    glRasterPos2i (10, 10);
    glGetFloatv(GL_CURRENT_RASTER_POSITION,(GLfloat *)vet);
    printf("Posizione corrente del raster%f %f \n",vet[0],vet[1]);
    glBitmap (10, 12, 0, 0, 12, 15, rasters);
    glGetFloatv(GL_CURRENT_RASTER_POSITION,(GLfloat *)vet);
    printf("Posizione corrente del raster:%f %f \n",vet[0],vet[1]);

    glColor3f (0.0, 1.0, 0.0);
    glRasterPos2i (vet[0], vet[1]);
    glBitmap (10, 12, 0, 0, 12, 15, rasters);
    glGetFloatv(GL_CURRENT_RASTER_POSITION,(GLfloat *)vet);
    printf("Posizione corrente del raste:%f %f \n",vet[0],vet[1]);

    glColor3f (0.0, 0.0, 1.0);
    glRasterPos2i (vet[0], vet[1]);
    glBitmap (10, 12, 0, 0, 12,15, rasters);
    glGetFloatv(GL_CURRENT_RASTER_POSITION,(GLfloat *)vet);
    printf("Posizione corrente del raste:%f %f \n",vet[0],vet[1]);
    glColor3f (1.0, 0.0, 0.0);
    glBitmap (10, 12, 0, 0, 12, 0, rasters);
    glGetFloatv(GL_CURRENT_RASTER_POSITION,(GLfloat *)vet);
    printf("Posizione corrente del raste:%f %f \n",vet[0],vet[1]);
    glFlush();
}

int main(int argc, char** argv)	{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);	  
   glutInitWindowSize (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display);	   
   glClearColor (1.0, 1.0, 1.0, 1.0);
   gluOrtho2D(0.0,100.0,0.0,100.0);
   glutMainLoop();
}
