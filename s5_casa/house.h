//
// Created by massi on 12.03.2020.
//

#ifndef GRAFICA_HOUSE_H
#define GRAFICA_HOUSE_H

#include <GL/glew.h>

class house {
public:
    void draw();
    void toggle_door();
    void update_model();

private:
    GLfloat doorAngle = 0.0;
    GLboolean openDoor = false;

    void draw_prism_walls();
    void draw_lateral_walls();
    void draw_roof();
    void draw_floor();
    void draw_chimney();
    void draw_door();
};


#endif //GRAFICA_HOUSE_H
