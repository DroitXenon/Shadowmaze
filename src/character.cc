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

int character::get_def() const
{
    return def;
}

std::string character::get_race() const{
    return race;
}

pos character::get_pos() const
{
    return position;
}

void character::set_pos(pos position) {
    this->position = position;
}

character::~character() {}
