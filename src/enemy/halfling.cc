#include "halfling.h"

halfling::halfling():
    enemy_character{100, 15, 20, "Halfling", 'L', true} {}

int halfling::attack(std::shared_ptr<player_character> player) {
    int damage = (int) ceil((100.0 / (100 + player->get_def())) * get_atk());
    player->set_hp(player->get_hp() - damage);
    return damage; 
}
