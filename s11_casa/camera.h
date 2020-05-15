//
// Created by massi on 25.04.2020.
//

#ifndef S7_CASA_CAMERA_H
#define S7_CASA_CAMERA_H
#include <string>
#include "vertex.h"

struct Camera {
    Vertex eye{0, 0, 5.0};
    Vertex center{0, 0, 0};
    Vertex up{0 , 1, 0};

    void reset();

    void moveLeft();
    void moveRight();

    void moveBottom();
    void moveTop();

    void moveForward();
    void moveBackward();

    void lookAt();

    std::string toString();
};


#endif //S7_CASA_CAMERA_H
