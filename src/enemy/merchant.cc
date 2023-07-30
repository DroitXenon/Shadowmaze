#include "merchant.h"

merchant::merchant():
    enemy_character{30, 70, 5, "Merchant", 'M', false, -1} {}

int merchant::attack(std::shared_ptr<player_character> player) {
    int damage = (int) ceil((100.0 / (100 + player->get_def())) * get_atk());
    player->set_hp(player->get_hp() - damage);
    return damage; 
}
