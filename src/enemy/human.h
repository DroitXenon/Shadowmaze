#ifndef HUMAN_H
#define HUMAN_H
#include "enemy_character.h"
#include <iostream>

class human: public enemy_character {
 public:
    human();
    int attack(std::shared_ptr<player_character> player) override;
    // void attacked() override;
};


#endif
