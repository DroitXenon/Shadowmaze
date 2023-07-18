#include "start.h"
#include "character.h"
#include "player/shade.h"
#include "pos.h"
#include "map.h"


void start(std::string map_file, std::string seed) {
    std::cout << "Welcome to cc 3k, please enter your race" << std:: endl; // welcome
    char cmd;
    map game_map;
    game_map.read_map(map_file);
    game_map.print_map();

    while (true) {
        std::cin >> cmd;
        if (cmd == 's') {
            auto pc = std::make_shared<shade>();
            game_map.set_player(pc);
            game_map.set_map();
            game_map.print_map();
            break;
        } else {
            std::cerr << "Not Valid Input, please enter your race" << std::endl;
        }
    }
}


