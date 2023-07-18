#ifndef POS_H
#define POS_H
#include <iostream>

class pos {
    int x;
    int y;
    int floor;
 public:
    pos(int x = 0, int y = 0, int floor = 1);
    void randomize_pos(int chamber_id = rand() % 5 + 1);
    int get_x();
    int get_y();
    int get_floor();
};

#endif
