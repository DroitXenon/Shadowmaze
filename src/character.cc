#include "character.h"

character::character(int hp, int atk, int def, std::string race, char symbol):
    hp{hp},
    atk{atk},
    def{def},
    race{race},
    symbol{symbol} {}

int character::get_hp() const
{
    return hp;
}

int character::get_atk() const{
    return atk;
}

character::~character() {}
