#ifndef VAMPIRE_H
#define VAMPIRE_H

#include "player_character.h"
#include <iostream>

class vampire: public player_character {
 public:
    vampire();
    int attack(std::shared_ptr<enemy_character> enemy) override;
    // void attacked() override;
};


#endif