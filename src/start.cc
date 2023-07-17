#include "start.h"
#include "character.h"
#include "player/shade.h"
#include "pos.h"
#include "map.h"


void start() {
    std::cout << "Welcome to cc 3k, please enter your race" << std:: endl; // welcome
    char cmd;
    map game_map;
    while (true) {
        std::cin >> cmd;
        if (cmd == 's') {
            auto pc = std::make_shared<shade>();
            game_map.change_player(pc);
            break;
        } else {
            std::cerr << "Not Valid Input, please enter your race" << std::endl;
        }
    }
    
}

void start_w_map(std::string& map) {
    std::cout << "2" << map << std::endl;
}

void start_w_seed(std::string& map, std::string& seed) {
    std::cout << "3" << map << seed << std::endl;
}
