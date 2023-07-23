#ifndef TROLL_H
#define TROLL_H
#include "player_character.h"
#include <iostream>

class troll: public player_character {
 public:
    troll();
    int attack(std::shared_ptr<enemy_character> enemy) override;
    // void attacked() override;
};


#endif
