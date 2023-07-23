#include "orc.h"

orc::orc():
    enemy_character{140, 20, 20, "Orcs", 'O', true} {}

int orc::attack(std::shared_ptr<player_character> player) {
    int damage = (int) ceil((100.0 / (100 + player->get_def())) * get_atk());
    player->set_hp(player->get_hp() - damage);
    return damage; 
}
