#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include "pos.h"

class character {
    int hp;
    int atk;
    int def;
    std::string race;
    bool is_dead = false;
    pos position;
    char symbol;
 public:
    character(int hp, int atk, int def, std::string race, char symbol);
    int get_hp() const;
    int get_atk() const;
    // int get_def() const;
    // int get_race() const;
    // int get_dead() const;
    // int get_pos() const;
    virtual ~character() = 0;
    
};

#endif
