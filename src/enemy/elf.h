#ifndef ELF_H
#define ELF_H
#include "enemy_character.h"
#include <iostream>

class elf: public enemy_character {
 public:
    elf();
    int attack(std::shared_ptr<player_character> player) override;
    // void attacked() override;
};

#endif
