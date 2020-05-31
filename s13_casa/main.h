//
// Created by massi on 13.04.2020.
//

#ifndef S7_CASA_MAIN_H
#define S7_CASA_MAIN_H

// callbacks
void displayCallback();
void menuCallback(int value);
void reshapeCallback(int w, int h);
void animationCallback(int value);
void windCallback(int value);
void specialKeyCallback(int key, int x, int y);
void keyCallback(unsigned char key, int x, int y);

// initialization
void appInit();
void initLight();
void initTexture();

void setOrthographicProjection();
void setProspectiveProjection();
void createMenu();
void updateCamera();
void reshape(int w, int h);
void forceReshape(char type);
void reset();
void toggleClipPlane();
void saveFile();

#endif //S7_CASA_MAIN_H
