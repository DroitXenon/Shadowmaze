#include "shade.h"
#include <iostream>

shade::shade(): 
    player_character{125, 25, 25, "shade", 's', 125} {}

shade::~shade(){}

void shade::attack() {
    std::cout << "pass" <<std::endl;    
}