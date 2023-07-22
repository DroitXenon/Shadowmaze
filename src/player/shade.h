#ifndef SHADE_H
#define SHADE_H
#include "player_character.h"
#include <iostream>

class shade: public player_character {
 public:
    shade();
    void attack(std::shared_ptr<enemy_character> enemy) override;
    // void attacked() override;
};


#endif