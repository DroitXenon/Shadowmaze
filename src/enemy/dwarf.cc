#include "dwarf.h"

dwarf::dwarf():
    enemy_character{100, 20, 30, "Dwarf", 'W', true, -1} {}

int dwarf::attack(std::shared_ptr<player_character> player) {
    int damage = (int) ceil((100.0 / (100 + player->get_def())) * get_atk());
    player->set_hp(player->get_hp() - damage);
    return damage; 
}
