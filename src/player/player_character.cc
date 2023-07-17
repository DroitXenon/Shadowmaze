#include "player_character.h"

player_character::player_character(int hp, int atk, int def, std::string race, char symbol, int max_hp): 
    character{hp, atk, def, race, symbol},
    max_hp{max_hp} {}
