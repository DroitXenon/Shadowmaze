#include "start.h"

// Control the game flow
void start(std::string map_file, bool with_map, unsigned int seed_int, bool with_seed) {
    srand(seed_int);
    std::string cmd;
    map game_map;
    bool restart = true;
    std::cout << "Seed: " << seed_int << std::endl;
    // Welcome message
    std::ifstream f {"welcome.txt"}; 
	while (getline(f, cmd)) {
		std::cout << cmd << std::endl;
	}
    while (restart) {
        // Initialize map after each restart
        game_map.initialize();
        restart = false;
        std::cout << "Please enter your race:" << std::endl;
        std::cout << ESC << ";" << CYAN_TXT << "m" << "s: " << RESET << "Shade" << std::endl;
        std::cout << ESC << ";" << CYAN_TXT << "m" << "d: " << RESET << "Drow" << std::endl;
        std::cout << ESC << ";" << CYAN_TXT << "m" << "v: " << RESET << "Vampire" << std::endl;
        std::cout << ESC << ";" << CYAN_TXT << "m" << "t: " << RESET << "Troll" << std::endl;
        std::cout << ESC << ";" << CYAN_TXT << "m" << "g: " << RESET << "Goblin" << std::endl;
        
        // Choose player race
        std::cin >> cmd;
        if (cmd == "s") {
            auto pc = std::make_shared<shade>();
            game_map.set_player(pc);
            std::cout << "You chose shade" << std::endl;
        } else if (cmd == "d") {
            auto pc = std::make_shared<drow>();
            game_map.set_player(pc);
            std::cout << "You chose drow" << std::endl;
        } else if (cmd == "v") {
            auto pc = std::make_shared<vampire>();
            game_map.set_player(pc);
            std::cout << "You chose vampire" << std::endl;
        } else if (cmd == "t") {
            auto pc = std::make_shared<troll>();
            game_map.set_player(pc);
            std::cout << "You chose troll" << std::endl;
        } else if (cmd == "g") {
            auto pc = std::make_shared<goblin>();
            game_map.set_player(pc);
            std::cout << "You chose goblin" << std::endl;              
        } else if (cmd == "q") {
            std::cout << "Quitting..." << std::endl;
            return;
        } else if (cmd == "r") {
            std::cout << "Restarting..." << std::endl;
            continue;
        } else {
            std::cerr << "Not Valid Input" << std::endl;
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
            // Player Move
            if (cmd == "no" || cmd == "so" || cmd == "ea" || cmd == "we" || cmd == "ne" || cmd == "nw" || cmd == "se" || cmd == "sw") {
                game_map.move_player(cmd);
                // If player move to a stair, change floor
                if (game_map.get_floor_change()) {
                    if (game_map.get_floor() == MAX_FLOOR) {
                        game_map.game_over();
                        std::cout << "Do you want to restart? ";
                        std::cout << ESC << ";" << CYAN_TXT << "m" << "(y/n)" << RESET << std::endl;
                        std::cin >> cmd;
                        if (cmd == "y") {
                            restart = true;
                            std::cout << "Restarting..." << std::endl;
                            break;
                        } else {
                            std::cout << "Quitting..." << std::endl;
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
                }
            // Use Potion
            } else if (cmd == "u") {
                std::cin >> cmd;
                game_map.use_potion(cmd);
                game_map.move_enemy();
            // Attack Enemy
            } else if (cmd == "a") {
                std::cin >> cmd;
                game_map.player_attack(cmd);
            // Restart
            } else if (cmd == "r") {
                restart = true;
                std::cout << "Restarting..." << std::endl;
                break;
            // Quit 
            } else if (cmd == "q") {
                game_map.game_over();
                return;
            } else {
                std::cerr << "Not Valid Input, please enter your command" << std::endl;
            }
            game_map.enemy_attack();
            game_map.check_state();
            if (game_map.is_gameover()) {
                game_map.game_over();
                std::cout << "Do you want to restart? ";
                std::cout << ESC << ";" << CYAN_TXT << "m" << "(y/n)" << RESET << std::endl;
                std::cin >> cmd;
                if (cmd == "y") {
                    restart = true;
                    std::cout << "Restarting..." << std::endl;
                    break;
                } else {
                    std::cout << "Quitting..." << std::endl;
                    return;
                }
            }
            game_map.find_around();
            game_map.print_map();
        }
    }
}
