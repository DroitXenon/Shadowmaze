#include "orc.h"

orc::orc():
    enemy_character{140, 20, 20, "Orc", 'O', true} {}

int orc::attack(std::shared_ptr<player_character> player) {
    int damage = (int) ceil((100.0 / (100 + player->get_def())) * get_atk());
    if (player->get_race() == "Goblin") {
        damage *= 1.5;
    }
    player->set_hp(player->get_hp() - damage);
    return damage; 
}
