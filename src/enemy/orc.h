#ifndef ORCS_H
#define ORCS_H
#include "enemy_character.h"
#include <iostream>

class orc: public enemy_character {
 public:
    orc();
    int attack(std::shared_ptr<player_character> player) override;
    // void attacked() override;
};


#endif
