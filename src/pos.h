#ifndef POS_H
#define POS_H

class pos {
    int x;
    int y;
    int floor;
 public:
    pos(int x = 0, int y = 0, int floor = 1);
    void randomize_pos(int chamber_id);
    int get_x();
    int get_y();
    int get_floor();
};

#endif
