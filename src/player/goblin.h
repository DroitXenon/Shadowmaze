#ifndef GOBLIN_H
#define GOBLIN_H
#include "player_character.h"
#include <iostream>

class goblin: public player_character {
 public:
    goblin();
    int attack(std::shared_ptr<enemy_character> enemy) override;
    // void attacked() override;
};


#endif
