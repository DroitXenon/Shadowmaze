#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "../character.h"
#include "../pos.h"

class player_character: public character {
    int max_hp;
    int gold = 0;
 public:
    player_character(int hp, int atk, int def, std::string race, char symbol, int max_hp);
    //int get_max_hp() const;
    //int get_gold() const;
    // void use();
    virtual void attack() = 0;
    // virtual void attacked() = 0;
    
};

#endif
