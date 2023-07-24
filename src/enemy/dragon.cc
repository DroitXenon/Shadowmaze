#include "dragon.h"

dragon::dragon():
    enemy_character{150, 20, 20, "Dragon", 'D', false} {}

int dragon::attack(std::shared_ptr<player_character> player) {
    int damage = (int) ceil((100.0 / (100 + player->get_def())) * get_atk());
    player->set_hp(player->get_hp() - damage);
    return damage; 
}

