//
// Created by massi on 12.03.2020.
//

#ifndef GRAFICA_HOUSE_H
#define GRAFICA_HOUSE_H


class house {
public:
    void draw();
private:
    void draw_prism_walls();
    void draw_lateral_walls();
    void draw_roof();
    void draw_floor();
    void draw_chimney();
};


#endif //GRAFICA_HOUSE_H
