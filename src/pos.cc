#include "pos.h"

pos::pos(int x, int y, int floor):
    x{x},
    y{y},
    floor{floor} {}

void pos::randomize_pos(int chamber_id) {
    x = 13;
    y = 4;
    // if (chamber_id == 1) {
    //     x = rand() % 26 + 4;
    //     y = rand() % 4 + 4;
    // } else if (chamber_id == 2) {
    //     x = rand() % 37 + 40;
    //     y = rand() % 10 + 4;
    // } else if (chamber_id == 3) {
    // } else if (chamber_id == 4) {
    // } else {
    // } 
    
}

int pos::get_x() {
    return x;
}

int pos::get_y() {
    return y;
}

int pos::get_floor() {
    return floor;
}
