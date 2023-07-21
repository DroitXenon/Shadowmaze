#include "pos.h"

pos::pos(int x, int y, int floor):
    x{x},
    y{y},
    floor{floor} {}

void pos::randomize_pos(int chamber_id) {
    if (chamber_id == 1) {
        x = rand() % 26 + 3;
        y = rand() % 4 + 3;
    } else if (chamber_id == 2) {
        x = rand() % 37 + 39;
        y = rand() % 10 + 3;
        while (x < 61 && y > 8) {
            x = rand() % 37 + 39;
            y = rand() % 10 + 3;
        }
    } else if (chamber_id == 3) {
        x = rand() % 12 + 38;
        y = rand() % 3 + 10;
    } else if (chamber_id == 4) {
        x = rand() % 21 + 4;
        y = rand() % 7 + 15;
    } else {
        x = rand() % 39 + 37;
        y = rand() % 6 + 16;
    }   
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
