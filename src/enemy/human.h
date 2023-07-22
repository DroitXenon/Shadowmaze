#ifndef HUMAN_H
#define HUMAN_H
#include "enemy_character.h"
#include <iostream>

class human: public enemy_character {
 public:
    human();
    void attack() override;
    // void attacked() override;
};


#endif