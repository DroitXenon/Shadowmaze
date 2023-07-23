#ifndef DRAGON_H
#define DRAGON_H
#include "enemy_character.h"
#include <iostream>

class dragon: public enemy_character {
 public:
    dragon();
    int attack(std::shared_ptr<player_character> player) override;
    // void attacked() override;
};


#endif
