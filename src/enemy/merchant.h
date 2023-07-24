#ifndef MERCHANT_H
#define MERCHANT_H
#include "enemy_character.h"
#include <iostream>

class merchant: public enemy_character {
 public:
    merchant();
    int attack(std::shared_ptr<player_character> player) override;
    // void attacked() override;
};


#endif
