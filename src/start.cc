#include "start.h"
#include "character.h"
#include "player/shade.h"
#include "pos.h"
#include "map.h"


void start(std::string map_file, unsigned int seed_int) {
    srand(seed_int);
    std::string cmd;
    map game_map;
    game_map.read_map(map_file);
    //game_map.print_map();

    std::cout << "Your seed is " << seed_int << std::endl; // print seed
    std::cout << "Welcome to cc 3k, please enter your race" << std:: endl; // welcome
    
    while (true) {
        std::cin >> cmd;
        if (cmd == "s") {
            auto pc = std::make_shared<shade>();
            game_map.set_player(pc);
            game_map.set_map();
            std::cout << "You chose shade" << std::endl;
            break;
        } else {
            std::cerr << "Not Valid Input, please enter your race" << std::endl;
        }
    }
    game_map.print_map();

    while (true) {
        std::cout << "Please enter your command" << std::endl;
        std::cin >> cmd;
        if (cmd == "no" || cmd == "so" || cmd == "ea" || cmd == "we" || cmd == "ne" || cmd == "nw" || cmd == "se" || cmd == "sw") {
            game_map.move_player(cmd);
            game_map.move_enemy();
            game_map.print_map();
        } else if (cmd == "u") {
            std::cin >> cmd;
            game_map.use_potion(cmd);
            game_map.move_enemy();
            game_map.print_map();
        } else if (cmd == "a") {
            std::cin >> cmd;
            game_map.attack_enemy(cmd);
            game_map.move_enemy();
            game_map.print_map();
        } else if (cmd == "r") {
            std::cout << "Restarting" << std::endl;
            break;
        } else if (cmd == "q") {
            std::cout << "Quitting" << std::endl;
            break;
        } else {
            std::cerr << "Not Valid Input, please enter your command" << std::endl;
        }
    }
}


