#include "enemy_character.h"

enemy_character::enemy_character(int hp, int atk, int def, std::string race, char symbol, bool hostile):
    character{hp, atk, def, race, symbol},
    hostile{hostile} {}

std::string enemy_character::get_drop_item() const {
    return drop_item;
}

bool enemy_character::is_active() const {
    return active;
}

bool enemy_character::is_hostile() const {
    return hostile;
}

void enemy_character::set_drop_item(std::string drop_item) {
    this->drop_item = drop_item;
}

void enemy_character::set_active(bool active) {
    this->active = active;
}

void enemy_character::set_hostile(bool hostile) {
    this->hostile = hostile;
}

void enemy_character::attack() {
    std::cout << "Enemy attacks!" << std::endl;
}
