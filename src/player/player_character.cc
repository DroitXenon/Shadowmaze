#include "player_character.h"

player_character::player_character(int hp, int atk, int def, std::string race, char symbol, int max_hp): 
    character{hp, atk, def, race, symbol},
    max_hp{max_hp} {
        gold = 0;
        original_atk = atk;
        original_def = def;
    }

int player_character::get_max_hp() const {
    return max_hp;
}

int player_character::get_gold() const {
    return gold;
}

void player_character::set_gold(int gold) {
    this->gold = gold;
}

int player_character::get_original_atk() const {
    return original_atk;
}

int player_character::get_original_def() const {
    return original_def;
}
