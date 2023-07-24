#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "../character.h"
#include "../pos.h"
#include "../enemy/enemy_character.h"

class enemy_character;
class player_character: public character {
    int max_hp;
    int gold;
 public:
    player_character(int hp, int atk, int def, std::string race, char symbol, int max_hp);
    int get_max_hp() const;
    int get_gold() const;
    void set_gold(int gold);
    // virtual void use() = 0;
    virtual int attack(std::shared_ptr<enemy_character> enemy) = 0;
    // virtual void attacked() = 0;
    
};

#endif
