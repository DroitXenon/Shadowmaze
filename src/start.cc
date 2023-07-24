#include "start.h"
#include "character.h"
#include "player/shade.h"
#include "player/drow.h"
#include "player/vampire.h"
#include "player/troll.h"
#include "player/goblin.h"
#include "pos.h"
#include "map.h"


void start(std::string map_file, bool with_map, unsigned int seed_int, bool with_seed) {
    srand(seed_int);
    std::string cmd;
    map game_map;
    bool restart = true;
    std::cout << "Your seed is " << seed_int << std::endl; // print seed
    
    while (restart) {
        restart = false;
        std::cout << "Welcome to cc 3k, please enter your race" << std:: endl; // welcome
        while (true) {
            std::cin >> cmd;
            if (cmd == "s") {
                auto pc = std::make_shared<shade>();
                game_map.set_player(pc);
                std::cout << "You chose shade" << std::endl;
                break;
            } else if (cmd == "d") {
                auto pc = std::make_shared<drow>();
                game_map.set_player(pc);
                std::cout << "You chose drow" << std::endl;
                break;
            } else if (cmd == "v") {
                auto pc = std::make_shared<vampire>();
                game_map.set_player(pc);
                std::cout << "You chose vampire" << std::endl;
                break;
            } else if (cmd == "t") {
                auto pc = std::make_shared<troll>();
                game_map.set_player(pc);
                std::cout << "You chose troll" << std::endl;
                break;
            } else if (cmd == "g") {
                auto pc = std::make_shared<goblin>();
                game_map.set_player(pc);
                std::cout << "You chose goblin" << std::endl;
                break;
            } else if (cmd == "q") {
                std::cout << "Quitting" << std::endl;
                return;
            } else if (cmd == "r") {
                restart = true;
                std::cout << "Restarting" << std::endl;
                break;
            } else {
                std::cerr << "Not Valid Input, please enter your race" << std::endl;
            }
        }

        if (restart) {
            continue;
        }

        if (with_map) {
            game_map.read_map_file(map_file, 1);
        } else {
            game_map.read_empty_map(map_file);
            game_map.set_map();
        }
        game_map.print_map();

        while (true) {
            std::cout << "Please enter your command" << std::endl;
            std::cin >> cmd;
            if (cmd == "no" || cmd == "so" || cmd == "ea" || cmd == "we" || cmd == "ne" || cmd == "nw" || cmd == "se" || cmd == "sw") {
                game_map.move_player(cmd);
                if (game_map.get_floor_change()) {
                    if (game_map.get_floor() == 6) {
                        std::cout << "You Win" << std::endl;
                        return;
                    } else if (with_map) {
                        game_map.read_map_file(map_file, game_map.get_floor());
                    } else {
                        game_map.read_empty_map(map_file);
                        game_map.set_map();
                    }
                } else {
                    game_map.find_around();
                    game_map.move_enemy();
                    game_map.enemy_attack();
                    game_map.check_state();
                    if (game_map.is_gameover()) {
                        std::cout << "Game Over" << std::endl;
                        return;
                    }
                }
                game_map.print_map();
            } else if (cmd == "u") {
                std::cin >> cmd;
                game_map.use_potion(cmd);
                game_map.move_enemy();
                game_map.enemy_attack();
                game_map.check_state();
                if (game_map.is_gameover()) {
                    game_map.game_over();
                    return;
                }
                else {
                    game_map.find_around();
                    game_map.print_map();
                }
            } else if (cmd == "a") {
                std::cin >> cmd;
                game_map.player_attack(cmd);
                game_map.enemy_attack();
                game_map.check_state();
                if (game_map.is_gameover()) {
                    std::cout << "Game Over" << std::endl;
                    return;
                }
                else {
                    game_map.print_map();
                }
            } else if (cmd == "r") {
                restart = true;
                std::cout << "Restarting" << std::endl;
                break;
            } else if (cmd == "q") {
                std::cout << "Quitting" << std::endl;
                return;
            } else {
                std::cerr << "Not Valid Input, please enter your command" << std::endl;
            }
        }
    }
}


