#ifndef SHADE_H
#define SHADE_H
#include "player_character.h"
#include <iostream>

class shade: public player_character {
 public:
    shade();
    ~shade();
    void attack() override;
    // void attacked() override;
};


#endif