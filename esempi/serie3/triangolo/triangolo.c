// Draw a white triangle against a black background
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

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

                
void draw() {
	glClearColor(1.0, 0.0, 0.0, 0.0);  	//definisce con quale colore cancellare la scena
										//con openGL 2.0 il nero e' lo stato di default iniziale
    glClear(GL_COLOR_BUFFER_BIT);		//cancella la scena
    glLoadIdentity();					//Matrice di trasformazione: identita'
	glColor3f(1.0, 1.0, 1.0);			//Definisce il colore degli oggetti da disegnare
    //glColor3i(INT_MAX , 0, 0);
	glOrtho(0.0, 8.0, 0.0, 8.0, -1.0, 1.0);	 //definisce l'area visualizzabile
	
    glBegin(GL_TRIANGLES);				//definisce il poligono e i 3 vertici
    	glVertex2i(1, 1);
    	glVertex2i(3, 1);
    	glVertex2i(3, 3);

    glEnd();
	
    glFlush();							//esegue i comandi 
}

void reshape(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);				// Inizializza libreria glut per la gestione delle finestre
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // Singolo buffer con modello colore RGBA
    glutCreateWindow("triangolo");  // Crea finestra (dimensioni e posizione di default) e definisce titolo
    glutReshapeFunc(reshape);
    glutDisplayFunc(draw);			// Rendering function
    glutMainLoop();					// loop infinito
}

