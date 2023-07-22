#include "human.h"

human::human():
    enemy_character{140, 20, 20, "Human", 'H', true} {}

void human::attack(std::shared_ptr<player_character> player) {
    std::cout << "Human attacks!" << std::endl;
}
