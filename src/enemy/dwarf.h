#ifndef DWARF_H
#define DWARF_H
#include "enemy_character.h"
#include <iostream>

class dwarf: public enemy_character {
 public:
    dwarf();
    int attack(std::shared_ptr<player_character> player) override;
    // void attacked() override;
};

#endif
