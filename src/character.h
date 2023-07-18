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
    // std::string get_race() const;
    // bool get_dead() const;
    // pos get_pos() const;
    // void set_hp(int hp);
    // void set_atk(int atk);
    // void set_def(int def);
    // void set_dead(bool is_dead);
    void set_pos(pos position);
    virtual ~character() = 0;
    
};

#endif
