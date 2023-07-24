#ifndef HALFLING_H
#define HALFLING_H
#include "enemy_character.h"
#include <iostream>

class halfling: public enemy_character {
 public:
    halfling();
    int attack(std::shared_ptr<player_character> player) override;
    // void attacked() override;
};


#endif
