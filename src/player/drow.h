#ifndef DROW_H
#define DROW_H

#include "player_character.h"
#include <iostream>

class drow: public player_character {
 public:
    drow();
    int attack(std::shared_ptr<enemy_character> enemy) override;
    // void attacked() override;
};


#endif
