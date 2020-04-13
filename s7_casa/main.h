//
// Created by massi on 13.04.2020.
//

#ifndef S7_CASA_MAIN_H
#define S7_CASA_MAIN_H

void displayCallback();
void menuCallback(int value);
void reshapeCallaback(int w, int h);
void animationCallaback(int value);
void windCallaback(int value);
void specialKeyCallback(int key, int x, int y);
void keyCallback(unsigned char key, int x, int y);
void rotateHouse();

#endif //S7_CASA_MAIN_H
