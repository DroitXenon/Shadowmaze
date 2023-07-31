#include "start.h"
#include "character.h"
#include "player/shade.h"
#include "player/drow.h"
#include "player/vampire.h"
#include "player/troll.h"
#include "player/goblin.h"
#include "pos.h"
#include "map.h"

#define ESC "\033["
#define LIGHT_BLUE_BKG "106"
#define RED_TXT "31"
#define GREEN_TXT "32"
#define YELLOW_TXT "33"
#define BLUE_TXT "34"
#define PURPLE_TXT "35"
#define RESET "\033[m"

// Control the game flow
void start(std::string map_file, bool with_map, unsigned int seed_int, bool with_seed) {
    srand(seed_int);
    std::string cmd;
    map game_map;
    bool restart = true;
    std::cout << "Your seed is " << seed_int << std::endl;
    
    while (restart) {
        game_map.initialize();
        restart = false;
        // Welcome message
        std::cout << "Welcome to cc 3k, please enter your race" << std:: endl;
        // Choose player race
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

        // Read map data
        if (with_map) {
            game_map.read_map_file(map_file, 0);
        } else {
            game_map.read_empty_map(map_file);
            game_map.set_map();
        }
        game_map.find_around();
        game_map.print_map();

        // Deal with command
        while (true) {
            std::cout << "Please enter your command" << std::endl;
            std::cin >> cmd;
            if (cmd == "no" || cmd == "so" || cmd == "ea" || cmd == "we" || cmd == "ne" || cmd == "nw" || cmd == "se" || cmd == "sw") {
                game_map.move_player(cmd);
                if (game_map.get_floor_change()) {
                    if (game_map.get_floor() == MAX_FLOOR) {
                        game_map.game_over();
                        std::cout << "Do you want to restart? (y/n)" << std::endl;
                        std::cin >> cmd;
                        if (cmd == "y") {
                            restart = true;
                            std::cout << "Restarting" << std::endl;
                            break;
                        } else {
                            std::cout << "Quitting" << std::endl;
                            return;
                        }
                        return;
                    } else if (with_map) {
                        game_map.read_map_file(map_file, game_map.get_floor());
                    } else {
                        game_map.read_empty_map(map_file);
                        game_map.set_map();
                    }
                } else {
                    game_map.move_enemy();
                    if (game_map.is_gameover()) {
                        game_map.game_over();
                        std::cout << "Do you want to restart? (y/n)" << std::endl;
                        std::cin >> cmd;
                        if (cmd == "y") {
                            restart = true;
                            std::cout << "Restarting" << std::endl;
                            break;
                        } else {
                            std::cout << "Quitting" << std::endl;
                            return;
                        }
                    }
                }
            } else if (cmd == "u") {
                std::cin >> cmd;
                game_map.use_potion(cmd);
                game_map.move_enemy();
                if (game_map.is_gameover()) {
                    game_map.game_over();
                    std::cout << "Do you want to restart? (y/n)" << std::endl;
                    std::cin >> cmd;
                    if (cmd == "y") {
                        restart = true;
                        std::cout << "Restarting" << std::endl;
                        break;
                    } else {
                        std::cout << "Quitting" << std::endl;
                        return;
                    }
                }
            } else if (cmd == "a") {
                std::cin >> cmd;
                game_map.player_attack(cmd);
                if (game_map.is_gameover()) {
                    game_map.game_over();
                    std::cout << "Do you want to restart? (y/n)" << std::endl;
                    std::cin >> cmd;
                    if (cmd == "y") {
                        restart = true;
                        std::cout << "Restarting" << std::endl;
                        break;
                    } else {
                        std::cout << "Quitting" << std::endl;
                        return;
                    }
                }
            } else if (cmd == "r") {
                restart = true;
                std::cout << "Restarting" << std::endl;
                break;
            } else if (cmd == "q") {
                game_map.game_over();
                return;
            } else {
                std::cerr << "Not Valid Input, please enter your command" << std::endl;
            }
            game_map.enemy_attack();
            game_map.find_around();
            game_map.print_map();
        }
    }
}
