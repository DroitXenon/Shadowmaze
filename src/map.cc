#include "map.h"


void map::set_player(std::shared_ptr<player_character> character){
    player = character;
    add_action("Player character has spawned.");
}

void map::set_map(){
    int chamber_id_player = rand() % 5 + 1;
    int chamber_id_stair = rand() % 5 + 1;
    while (chamber_id_stair == chamber_id_player) {
        chamber_id_player = rand() % 5 + 1;
        chamber_id_stair = rand() % 5 + 1;
    }
    generate_player(chamber_id_player);
    generate_stair(chamber_id_stair);
    generate_posion();
    generate_gold();
    generate_enemy();
}

void map::generate_player(int chamber_id) {
    pos p;
    p.randomize_pos(chamber_id);
    while (true) {
        if (map_cell[p.get_x()][p.get_y()].get_cell_type() == '.') {
            player->set_pos(p);
            map_cell[p.get_x()][p.get_y()].set_cell_type('@');
            break;
        } else {
            p.randomize_pos(chamber_id);
        }
    }
    //std::cout << "player pos generated" << " " << p.get_x() << " " << p.get_y() << std::endl;
}

void map::generate_stair(int chamber_id) {
    pos p;
    p.randomize_pos(chamber_id);
    while (true) {
        if (map_cell[p.get_x()][p.get_y()].get_cell_type() == '.') {
            map_cell[p.get_x()][p.get_y()].set_cell_type('\\');
            break;
        } else {
            p.randomize_pos(chamber_id);
        }
    }
    //std::cout << "stair pos generated" << " " << p.get_x() << " " << p.get_y() << std::endl;
}

void map::generate_posion() {
    while (num_potion < 10) {
        pos p;
        p.randomize_pos();
        while (true) {
            if (map_cell[p.get_x()][p.get_y()].get_cell_type() == '.') {
                map_cell[p.get_x()][p.get_y()].set_cell_type('P');
                map_cell[p.get_x()][p.get_y()].set_step(false);
                auto new_potion = std::make_shared<potion>();
                new_potion->set_pos(p);
                int potion_type = rand() % 6;
                if (potion_type == 0) {
                    new_potion->set_name("RH");
                } else if (potion_type == 1) {
                    new_potion->set_name("BA");
                } else if (potion_type == 2) {
                    new_potion->set_name("BD");
                } else if (potion_type == 3) {
                    new_potion->set_name("PH");
                } else if (potion_type == 4) {
                    new_potion->set_name("WA");
                } else {
                    new_potion->set_name("WD");
                }
                potions.emplace_back(new_potion);
                break;
            } else {
                p.randomize_pos();
            }
        }
        ++num_potion;
    }
    //std::cout << "potion generated" << std::endl;
}

void map::generate_gold() {
    while (num_gold < 10) {
        //std::cout << "num_gold " << num_gold << std::endl;
        pos p;
        p.randomize_pos();
        //std::cout << "pos generated" << p.get_x() << " " << p.get_y() << std::endl;
        while (true) {
            if (map_cell[p.get_x()][p.get_y()].get_cell_type() == '.') {
                map_cell[p.get_x()][p.get_y()].set_cell_type('G');
                map_cell[p.get_x()][p.get_y()].set_step(true);
                auto new_gold = std::make_shared<gold>();
                new_gold->set_pos(p);
                int gold_type = rand() % 8;
                if (gold_type < 5) {
                    new_gold->set_value(2);
                } else if (gold_type < 7) {
                    new_gold->set_value(1);
                } else {
                    new_gold->set_value(6);
                    new_gold->set_pickable(false);
                    int direction_id = rand() % 8;
                    std::string direction = direction_map[direction_id];
                    pos dragon_pos = direction_pos(direction, p);
                    while (true) {
                        if (map_cell[dragon_pos.get_x()][dragon_pos.get_y()].get_cell_type() == '.') {
                            map_cell[dragon_pos.get_x()][dragon_pos.get_y()].set_cell_type('D');
                            map_cell[dragon_pos.get_x()][dragon_pos.get_y()].set_step(false);
                            auto new_dragon = std::make_shared<dragon>();
                            new_dragon->set_dragon_hoard_id(num_gold);
                            new_dragon->set_pos(dragon_pos);
                            enemies.emplace_back(new_dragon);
                            num_enemy++;
                            //std::cout << "dragon hoard id" << num_gold << " " << new_dragon->get_dragon_hoard_id() << std::endl;
                            break;
                        } else {
                            direction_id = rand() % 8;
                            direction = direction_map[direction_id];
                            dragon_pos = direction_pos(direction, p);
                        }
                    }
                }
                golds.emplace_back(new_gold);
                break;
            } else {
                p.randomize_pos();
            } 
        }
        ++num_gold;
    }
    //std::cout << "gold generated" << std::endl;
}



void map::generate_enemy() {
    while (num_enemy < 20) {
        pos p;
        p.randomize_pos();
        while (true) {
            int enemy_type = rand() % 18;
            if (enemy_type < 4) {
                if (map_cell[p.get_x()][p.get_y()].get_cell_type() == '.') {
                    map_cell[p.get_x()][p.get_y()].set_cell_type('H');
                    map_cell[p.get_x()][p.get_y()].set_step(false);
                    auto enemy = std::make_shared<human>();
                    enemy->set_pos(p);
                    enemies.emplace_back(enemy);
                    break;
                } else {
                    p.randomize_pos();
                }
            } else if (enemy_type < 7) {
                if (map_cell[p.get_x()][p.get_y()].get_cell_type() == '.') {
                    map_cell[p.get_x()][p.get_y()].set_cell_type('W');
                    map_cell[p.get_x()][p.get_y()].set_step(false);
                    auto enemy = std::make_shared<dwarf>();
                    enemy->set_pos(p);
                    enemies.emplace_back(enemy);
                    break;
                } else {
                    p.randomize_pos();
                }
            } else if (enemy_type < 12) {
                if (map_cell[p.get_x()][p.get_y()].get_cell_type() == '.') {
                    map_cell[p.get_x()][p.get_y()].set_cell_type('E');
                    map_cell[p.get_x()][p.get_y()].set_step(false);
                    auto enemy = std::make_shared<elf>();
                    enemy->set_pos(p);
                    enemies.emplace_back(enemy);
                    break;
                } else {
                    p.randomize_pos();
                }
            } else if (enemy_type < 14) {
                if (map_cell[p.get_x()][p.get_y()].get_cell_type() == '.') {
                    map_cell[p.get_x()][p.get_y()].set_cell_type('O');
                    map_cell[p.get_x()][p.get_y()].set_step(false);
                    auto enemy = std::make_shared<orc>();
                    enemy->set_pos(p);
                    enemies.emplace_back(enemy);
                    break;
                } else {
                    p.randomize_pos();
                }
            } else if (enemy_type < 16) {
                if (map_cell[p.get_x()][p.get_y()].get_cell_type() == '.') {
                    map_cell[p.get_x()][p.get_y()].set_cell_type('M');
                    map_cell[p.get_x()][p.get_y()].set_step(false);
                    auto enemy = std::make_shared<merchant>();
                    enemy->set_pos(p);
                    enemies.emplace_back(enemy);
                    break;
                } else {
                    p.randomize_pos();
                }
            } else {
                if (map_cell[p.get_x()][p.get_y()].get_cell_type() == '.') {
                    map_cell[p.get_x()][p.get_y()].set_cell_type('L');
                    map_cell[p.get_x()][p.get_y()].set_step(false);
                    auto enemy = std::make_shared<halfling>();
                    enemy->set_pos(p);
                    enemies.emplace_back(enemy);
                    break;
                } else {
                    p.randomize_pos();
                }
            }
            
        }
        ++num_enemy;
    }
    //std::cout << "enemy generated" << std::endl;
}

void map::read_empty_map(std::string& filename) {
    std::ifstream map_file{filename};
    std::string line;
    int row = 0;
    clear_map();
    while (getline(map_file, line)) {
        for (int i = 0; i < NUM_COL; ++i) {
            map_cell[i][row].set_cell_type(line[i]);
            origin_map_cell[i][row].set_cell_type(line[i]);
            if (line[i] == '-' || line[i] == '|' || line[i] == ' ') {
                map_cell[i][row].set_step(false);
                origin_map_cell[i][row].set_step(false);
            } else {
                map_cell[i][row].set_step(true);
                origin_map_cell[i][row].set_step(true);
            }
        }
        ++row;
    }
}

void map::read_map_file(std::string& filename, int floor) {
    std::ifstream map_file{filename};
    std::string line;
    int row = 0;
    int line_num = 0;
    int start_line = floor * NUM_ROW + 1;
    int end_line = (floor + 1) * NUM_ROW;
    //std::cout << start_line << " " << end_line << std::endl;

    clear_map();

    while (getline(map_file, line)) {
        line_num++;
        if (line_num >= start_line && line_num <= end_line) {
            for (int i = 0; i < NUM_COL; ++i) {
                map_cell[i][row].set_cell_type(line[i]);
                origin_map_cell[i][row].set_cell_type(line[i]);
                if (line[i] == '@') {
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_step(true);
                    player->set_pos(pos{i, row, floor});
                } else if (line[i] == '-' || line[i] == '|' ||  line[i] == ' ') {
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_step(false);
                } else if (line[i] == '.' || line[i] == '+' || line[i] == '#') {
                    map_cell[i][row].set_step(true);
                    origin_map_cell[i][row].set_step(true);
                } else if (line[i] == '0') {
                    map_cell[i][row].set_cell_type('P');
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_step(true);
                    auto new_potion = std::make_shared<potion>();
                    new_potion->set_pos(pos{i, row, floor});
                    new_potion->set_name("RH");
                    potions.emplace_back(new_potion);
                    num_potion++;          
                } else if (line[i] == '1') {
                    map_cell[i][row].set_cell_type('P');
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_step(true);
                    auto new_potion = std::make_shared<potion>();
                    new_potion->set_pos(pos{i, row, floor});
                    new_potion->set_name("BA");
                    potions.emplace_back(new_potion);
                    num_potion++;
                    
                } else if (line[i] == '2') {
                    map_cell[i][row].set_cell_type('P');
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_step(true);
                    auto new_potion = std::make_shared<potion>();
                    new_potion->set_pos(pos{i, row, floor});
                    new_potion->set_name("BD");
                    potions.emplace_back(new_potion);
                    num_potion++;
                    
                } else if (line[i] == '3') {
                    map_cell[i][row].set_cell_type('P');
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_step(true);
                    auto new_potion = std::make_shared<potion>();
                    new_potion->set_pos(pos{i, row, floor});
                    new_potion->set_name("PH");
                    potions.emplace_back(new_potion);
                    num_potion++;
                    
                } else if (line[i] == '4') {
                    map_cell[i][row].set_cell_type('P');
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_step(true);
                    auto new_potion = std::make_shared<potion>();
                    new_potion->set_pos(pos{i, row, floor});
                    new_potion->set_name("WA");
                    potions.emplace_back(new_potion);
                    num_potion++;
                    
                } else if (line[i] == '5') {
                    map_cell[i][row].set_cell_type('P');
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_step(true);
                    auto new_potion = std::make_shared<potion>();
                    new_potion->set_pos(pos{i, row, floor});
                    new_potion->set_name("WD");
                    potions.emplace_back(new_potion);
                    num_potion++;
                    
                } else if (line[i] == '6') {
                    map_cell[i][row].set_cell_type('G');
                    map_cell[i][row].set_step(true);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_step(true);
                    auto new_gold = std::make_shared<gold>();
                    new_gold->set_pos(pos{i, row, floor});
                    new_gold->set_value(2);
                    golds.emplace_back(new_gold);
                    num_gold++;

                } else if (line[i] == '7') {
                    map_cell[i][row].set_cell_type('G');
                    map_cell[i][row].set_step(true);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_step(true);
                    auto new_gold = std::make_shared<gold>();
                    new_gold->set_pos(pos{i, row, floor});
                    new_gold->set_value(1);
                    golds.emplace_back(new_gold);
                    num_gold++;
                } else if (line[i] == '8') {
                    map_cell[i][row].set_cell_type('G');
                    map_cell[i][row].set_step(true);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_step(true);
                    auto new_gold = std::make_shared<gold>();
                    new_gold->set_pos(pos{i, row, floor});
                    new_gold->set_value(4);
                    golds.emplace_back(new_gold);
                    num_gold++;
                } else if (line[i] == '9') {
                    map_cell[i][row].set_cell_type('G');
                    map_cell[i][row].set_step(true);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_step(true);
                    auto new_gold = std::make_shared<gold>();
                    new_gold->set_pickable(false);
                    new_gold->set_pos(pos{i, row, floor});
                    new_gold->set_value(6);
                    golds.emplace_back(new_gold);
                    num_gold++;
                } else if (line[i] == 'H') {
                    map_cell[i][row].set_cell_type('H');
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_step(true);
                    auto enemy = std::make_shared<human>();
                    enemy->set_pos(pos{i, row, floor});
                    enemies.emplace_back(enemy);
                    num_enemy++;
                } else if (line[i] == 'W') {
                    map_cell[i][row].set_cell_type('W');
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_step(true);
                    auto enemy = std::make_shared<dwarf>();
                    enemy->set_pos(pos{i, row, floor});
                    enemies.emplace_back(enemy);
                    num_enemy++;
                } else if (line[i] == 'E') {
                    map_cell[i][row].set_cell_type('E');
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_step(true);
                    auto enemy = std::make_shared<elf>();
                    enemy->set_pos(pos{i, row, floor});
                    enemies.emplace_back(enemy);
                    num_enemy++;
                } else if (line[i] == 'O') {
                    map_cell[i][row].set_cell_type('O');
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_step(true);
                    auto enemy = std::make_shared<orc>();
                    enemy->set_pos(pos{i, row, floor});
                    enemies.emplace_back(enemy);
                    num_enemy++;
                } else if (line[i] == 'M') {
                    map_cell[i][row].set_cell_type('M');
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_step(true);
                    auto enemy = std::make_shared<merchant>();
                    enemy->set_pos(pos{i, row, floor});
                    enemies.emplace_back(enemy);
                    num_enemy++;
                } else if (line[i] == 'D') {
                    map_cell[i][row].set_cell_type('D');
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_step(true);
                    auto enemy = std::make_shared<dragon>();
                    enemy->set_pos(pos{i, row, floor});
                    enemy->set_dragon_hoard_id(num_gold);
                    for (int i = 0; i < 8; i++) {
                        std::string direction = direction_map[i];
                        pos gold_pos = direction_pos(direction, enemy->get_pos());
                        int gold_id = which_gold(gold_pos.get_x(), gold_pos.get_y());
                        if (gold_id != -1 && golds[gold_id]->get_value() == 6) {
                            enemy->set_dragon_hoard_id(gold_id);
                        }
                    }
                    // we no ne nw 
                    // 1 3 4 5
                    // for (int x = (i == 0) ? 0 : i - 1 ; x <= (i == NUM_ROW - 1)? i : i + 1; ++x) {
                    //     for (int y = (row == 0)? 0:row - 1; y <= (row == NUM_COL - 1)? row: row + 1; ++y) {
                    //         int gold_id = which_gold(x, y);
                    //         if (golds[gold_id]->get_value() == 6) {
                    //             enemy->set_dragon_hoard_id(gold_id);
                    //         }
                    //     }
                    // }

                    enemies.emplace_back(enemy);
                    num_enemy++;
                } else if (line[i] == 'L') {
                    map_cell[i][row].set_cell_type('L');
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_step(true);
                    auto enemy = std::make_shared<halfling>();
                    enemy->set_pos(pos{i, row, floor});
                    enemies.emplace_back(enemy);
                    num_enemy++;
                }
            }
            ++row;
        }
    }
}

void map::print_map() {

    for (int i = 0; i < NUM_ROW; ++i) {
        for (int j = 0; j < NUM_COL; ++j) {
            char cell_type = map_cell[j][i].get_cell_type();
            if (cell_type == '@' || cell_type == '\\') {
                std::cout << ESC << ";" << BLUE_TXT << "m" << cell_type << RESET;
            } else if (cell_type == 'G') {
                std::cout << ESC << ";" << YELLOW_TXT << "m" << cell_type << RESET;
            } else if (cell_type == 'P') {
                std::cout << ESC << ";" << GREEN_TXT << "m" << cell_type << RESET;
            } else if (cell_type == 'H' || cell_type == 'W' || cell_type == 'E' || cell_type == 'O' || cell_type == 'M' || cell_type == 'D' || cell_type == 'L') {
                std::cout << ESC << ";" << RED_TXT << "m" << cell_type << RESET;
            } else {
                std::cout << cell_type;
            } 
        }
        std::cout << std::endl;
    }
    std::cout << "Race: " << player->get_race() << " Gold: " << player->get_gold() 
              << "                                                   " << "Floor " << floor + 1 << std::endl;
    std::cout << "HP: " << player->get_hp() << std::endl;
    std::cout << "Atk: " << player->get_atk() << std::endl;
    std::cout << "Def: " << player->get_def() << std::endl;
    std::cout << "Action: ";
    for (auto action : actions) {
        std::cout << action; //<< " and ";
    }
    std::cout << std::endl;
    std::cout << "Radar: ";
    if (!radar.empty()) {
        for (auto element: radar) {
            std::cout << element << std::endl;
        }
    } else {
        std::cout << "There is nothing in the 1 block radius." << std::endl;
    }
    actions.clear();
    radar.clear();
}

void map::move_player(std::string direction) {
    int new_x = direction_pos(direction, player->get_pos()).get_x();
    int new_y = direction_pos(direction, player->get_pos()).get_y();
    if (map_cell[new_x][new_y].get_cell_type() == '\\') {
        actions.emplace_back("PC moves " + direction + ". ");
        actions.emplace_back("PC goes to next floor. ");
        floor++;
        floor_change = true;
        return;
    } else if (map_cell[new_x][new_y].get_step()) {
        if (map_cell[new_x][new_y].get_cell_type() == 'G') {
            int gold_id = which_gold(new_x, new_y);
            if (golds[gold_id]->is_pickable()) {
                 //std::cout << "gold id: " << gold_id << std::endl;
                player->set_gold(player->get_gold() + golds[gold_id]->get_value());
                actions.emplace_back("gold picked up, value:" + std::to_string(golds[gold_id]->get_value()) + ". ");
                //golds.erase(golds.begin() + gold_id);
                num_gold--;
            } else {
                std::cout << "gold id: " << gold_id << std::endl;
                actions.emplace_back("Dragon still alive. Dragon hoard can not be picked up. ");
                return;
            }
        }
        map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_type(origin_map_cell[player->get_pos().get_x()][player->get_pos().get_y()].get_cell_type());
        map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_step(origin_map_cell[player->get_pos().get_x()][player->get_pos().get_y()].get_step());
        pos p{new_x, new_y, player->get_pos().get_floor()};
        player->set_pos(p);
        map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_type('@');
        actions.emplace_back("PC moves " + direction + ".");
    } else {
        actions.emplace_back("PC cannot moves " + direction + ".");
    }
}

void map::player_attack(std::string direction) {
    int enemy_id = which_enemy(direction_pos(direction, player->get_pos()).get_x(), direction_pos(direction, player->get_pos()).get_y());
    if (enemy_id != -1) {
        int damage = player->attack(enemies[enemy_id]);
        actions.emplace_back("PC deals " + std::to_string(damage) + " damage (");
        if (enemies[enemy_id]->get_race() == "Merchant") {
            enemies[enemy_id]->set_hostile(true);
            add_action("Merchant becomes hostile. ");
            //std::cout << "Merchant is hostile" << std::endl;
        } 
        if (enemies[enemy_id]->get_hp() <= 0) {
            actions.emplace_back("Dead).");
            map_cell[enemies[enemy_id]->get_pos().get_x()][enemies[enemy_id]->get_pos().get_y()].set_cell_type('.');
            map_cell[enemies[enemy_id]->get_pos().get_x()][enemies[enemy_id]->get_pos().get_y()].set_step(true);
            drop_gold(enemies[enemy_id]);
            enemies.erase(enemies.begin() + enemy_id);
            enemies.shrink_to_fit();
            num_enemy--;
        } else {
            actions.emplace_back(std::to_string(enemies[enemy_id]->get_hp()) + "HP).");
            enemies[enemy_id]->set_active(false);
            move_enemy();
            enemy_attack();
            enemies[enemy_id]->set_active(true);
        }
    } else {
        actions.emplace_back("No enemy in this direction. You wasted a turn.");
    }
}


void map::move_enemy() {
    for (int i = 0; i < NUM_ROW; ++i) {  
        for (int j = 0; j < NUM_COL; ++j) {
            int enemy_id = which_enemy(j, i);
            if (enemy_id != -1 && !enemies[enemy_id]->is_moved() && enemies[enemy_id]->is_active() && enemies[enemy_id]->get_race() != "Dragon" && !enemies[enemy_id]->is_disable()) { //if found enemy
                //std::cout << "enemy found" << std::endl;
                
                while (!enemies[enemy_id]->is_moved()) {
                    int random_direction = rand() % 8;
                    std::string direction = direction_map[random_direction];
                    int new_x = direction_pos(direction, enemies[enemy_id]->get_pos()).get_x();
                    int new_y = direction_pos(direction, enemies[enemy_id]->get_pos()).get_y();
                    if (map_cell[new_x][new_y].get_cell_type() == '.') {
                        map_cell[j][i].set_cell_type(origin_map_cell[j][i].get_cell_type());
                        map_cell[j][i].set_step(origin_map_cell[j][i].get_step());
                        pos p{new_x, new_y, enemies[enemy_id]->get_pos().get_floor()};
                        enemies[enemy_id]->set_pos(p);
                        enemies[enemy_id]->set_moved(true);
                        map_cell[new_x][new_y].set_cell_type(enemies[enemy_id]->get_symbol());
                        map_cell[new_x][new_y].set_step(false); 
                        
                    }
                }
            }
        }
    }
    for (int i = 0; i < num_enemy; ++i) {
        enemies[i]->set_moved(false);
    }
}

void map::enemy_attack() {
    for (int i = 0; i < num_enemy; ++i) {
        if (!enemies[i]->is_disable() && (is_adjacent(enemies[i]->get_pos(), player->get_pos()) || (enemies[i]->get_dragon_hoard_id() == -1 ? false :is_adjacent(golds[enemies[i]->get_dragon_hoard_id()]->get_pos(), player->get_pos())))) {
            if (enemies[i]->is_hostile()) {
                int attack_chance = rand() % 2;
                if (attack_chance) {
                    int damage = enemies[i]->attack(player);
                    actions.emplace_back(enemies[i]->get_race() + " deals " + std::to_string(damage) + " damage to PC. ");
                    // if (player->get_hp() <= 0) {
                    //     gameover = true;
                    //     return;
                    // }
                } else {
                    actions.emplace_back(enemies[i]->get_race() + " miss! ");
                }
            }
            if (enemies[i]->get_race() == "Dragon") {
                enemies[i]->set_hostile(true);
            }
        }
    }
}

void map::use_potion(std::string &direction) {
    int potion_id = which_potion(direction_pos(direction, player->get_pos()).get_x(), direction_pos(direction, player->get_pos()).get_y());
    if (potion_id != -1) {
        if (potions[potion_id]->get_name() == "RH") {
            if (player->get_race() == "Drow") {
                player->set_hp(player->get_hp() + 15);
            } else {
                player->set_hp(player->get_hp() + 10);
            }
            actions.emplace_back("PC uses RH. ");
            actions.emplace_back("PC gains 10 HP. ");
        } else if (potions[potion_id]->get_name() == "BA") {
            if (player->get_race() == "Drow") {
                player->set_atk(player->get_atk() + 7.5);
            } else {
                player->set_atk(player->get_atk() + 5);
            }
            actions.emplace_back("PC uses BA. ");
            actions.emplace_back("PC gains 5 Atk. ");
        } else if (potions[potion_id]->get_name() == "BD") {
            if (player->get_race() == "Drow") {
                player->set_def(player->get_def() + 7.5);
            } else {
                player->set_def(player->get_def() + 5);
            }
            actions.emplace_back("PC uses BD. ");
            actions.emplace_back("PC gains 5 Def. ");
        } else if (potions[potion_id]->get_name() == "PH") {
            if (player->get_race() == "Drow") {
                player->set_hp(player->get_hp() - 15);
            } else {
                player->set_hp(player->get_hp() - 10);
            }
            actions.emplace_back("PC uses PH. ");
            actions.emplace_back("PC loses 10 HP. ");
        } else if (potions[potion_id]->get_name() == "WA") {
            if (player->get_race() == "Drow") {
                player->set_atk(player->get_atk() - 7.5);
            } else {
                player->set_atk(player->get_atk() - 5);
            }
            actions.emplace_back("PC uses WA. ");
            actions.emplace_back("PC loses 5 Atk. ");
        } else if (potions[potion_id]->get_name() == "WD") {
            if (player->get_race() == "Drow") {
                player->set_def(player->get_def() - 7.5);
            } else {
                player->set_def(player->get_def() - 5);
            }
            actions.emplace_back("PC uses WD. ");
            actions.emplace_back("PC loses 5 Def. ");
        }
        
        int potion_state_id = potion_map[potions[potion_id]->get_name()];
        potion_state[potion_state_id] = true;      
        map_cell[potions[potion_id]->get_pos().get_x()][potions[potion_id]->get_pos().get_y()].set_cell_type('.');
        map_cell[potions[potion_id]->get_pos().get_x()][potions[potion_id]->get_pos().get_y()].set_step(true);
        potions.erase(potions.begin() + potion_id);
        potions.shrink_to_fit();
        num_potion--;
        // if (player->get_hp() <= 0) {
        //     gameover = true;
        // } else if (player->get_hp() > player->get_max_hp()) {
        //     player->set_hp(player->get_max_hp());
        //     actions.emplace_back("PC HP is full. ");
        // }
    } else {
        actions.emplace_back("No potion in this direction. You wasted a turn.");
    }
}

bool map::is_adjacent(pos p1, pos p2) {
    if (abs(p1.get_x() - p2.get_x()) <= 1 && abs(p1.get_y() - p2.get_y()) <= 1) {
        return true;
    } else {
        return false;
    }
}

int map::which_enemy(int x, int y) {
    for (int i = 0; i < num_enemy; ++i) {
        if (enemies[i]->get_pos().get_x() == x && enemies[i]->get_pos().get_y() == y) {
            return i;
        }
    }
    return -1;
}

int map::which_potion(int x, int y) {
    for (int i = 0; i < num_potion; ++i) {
        if (potions[i]->get_pos().get_x() == x && potions[i]->get_pos().get_y() == y) {
            return i;
        }
    }
    return -1;
}

int map::which_gold(int x, int y) {
    for (int i = 0; i < num_gold; ++i) {
        if (golds[i]->get_pos().get_x() == x && golds[i]->get_pos().get_y() == y) {
            return i;
        }
    }
    return -1;
}

pos map::direction_pos(std::string direction, pos current_pos) {
    if (direction == "so") {
        pos p{current_pos.get_x(), current_pos.get_y() + 1, current_pos.get_floor()};
        return p;
    } else if (direction == "no") {
        pos p{current_pos.get_x(), current_pos.get_y() - 1, current_pos.get_floor()};
        return p;
    } else if (direction == "ea") {
        pos p{current_pos.get_x() + 1, current_pos.get_y(), current_pos.get_floor()};
        return p;
    } else if (direction == "we") {
        pos p{current_pos.get_x() - 1, current_pos.get_y(), current_pos.get_floor()};
        return p;
    } else if (direction == "ne") {
        pos p{current_pos.get_x() + 1, current_pos.get_y() - 1, current_pos.get_floor()};
        return p;
    } else if (direction == "nw") {
        pos p{current_pos.get_x() - 1, current_pos.get_y() - 1, current_pos.get_floor()};
        return p;
    } else if (direction == "se") {
        pos p{current_pos.get_x() + 1, current_pos.get_y() + 1, current_pos.get_floor()};
        return p;
    } else {
        pos p{current_pos.get_x() - 1, current_pos.get_y() + 1, current_pos.get_floor()};
        return p;
    }
}

bool map::is_gameover() {
    return gameover;
}

bool map::get_floor_change() {
    return floor_change;
}

int map::get_floor() {
    floor_change = false;
    return floor;
}

void map::drop_gold(std::shared_ptr<enemy_character> enemy) {
    //std::cout << "drop gold entered" << std::endl;
    if (enemy->get_race() == "Human") {
        map_cell[enemy->get_pos().get_x()][enemy->get_pos().get_y()].set_cell_type('G');
        map_cell[enemy->get_pos().get_x()][enemy->get_pos().get_y()].set_step(true);
        auto new_gold = std::make_shared<gold>();
        new_gold->set_pos(pos{enemy->get_pos().get_x(), enemy->get_pos().get_y(), floor});
        new_gold->set_value(4);
        golds.emplace_back(new_gold);
        num_gold++;
        actions.emplace_back(enemy->get_race() + " drops 2 normal pile of gold. ");
    } else if (enemy->get_race() == "Merchant") {
        map_cell[enemy->get_pos().get_x()][enemy->get_pos().get_y()].set_cell_type('G');
        map_cell[enemy->get_pos().get_x()][enemy->get_pos().get_y()].set_step(true);
        auto new_gold = std::make_shared<gold>();
        new_gold->set_pos(pos{enemy->get_pos().get_x(), enemy->get_pos().get_y(), floor});
        new_gold->set_value(4);
        golds.emplace_back(new_gold);
        num_gold++;
        actions.emplace_back(enemy->get_race() + " drops 1 merchant hoard. ");
    } else if (enemy->get_race() == "Dragon") {
        //std:: cout << "dragon hoard id" << enemy->get_dragon_hoard_id() << std::endl;
        golds[enemy->get_dragon_hoard_id()]->set_pickable(true);
        actions.emplace_back(enemy->get_race() + " dead, you can get dragon hoard now. ");
        //std::cout << "dragon hoard id" << enemy->get_dragon_hoard_id() << std::endl;
    } else {
        int possibility = rand() % 2;
        if (possibility) {
            player->set_gold(player->get_gold() + 1);
            actions.emplace_back(enemy->get_race() + " drops 1 small pile of gold. (added to wallet) ");
        } else {
            player->set_gold(player->get_gold() + 2);
            actions.emplace_back(enemy->get_race() + " drops 1 normal pile of gold. (added to wallet) ");
        }
    }
}

void map::find_around() {
    for (int i = 0; i < 8; i++) {
        int direction_x = direction_pos(direction_map[i], player->get_pos()).get_x();
        int direction_y = direction_pos(direction_map[i], player->get_pos()).get_y();
        if (map_cell[direction_x][direction_y].get_cell_type() == 'G') {
            int gold_id = which_gold(direction_x, direction_y);
            //std::cout << "gold id" << gold_id << std::endl;
            if (golds[gold_id]->get_value() == 6) {
                radar.emplace_back("There is a dragon hoard in " + direction_map[i] + ". ");
                for (int i = 0; i < num_enemy; i++) {
                    //std::cout << "dragon become hostile" << std::endl;
                    //std::cout << "dragon hoard id" << enemies[i]->get_dragon_hoard_id() << std::endl;
                    //std::cout << "gold id" << gold_id << std::endl;
                    //std::cout << enemies[i]->get_pos().get_x() << std::endl;
                    if (enemies[i]->get_dragon_hoard_id() == gold_id && enemies[i]->get_race() == "Dragon") {
                        //std::cout << "dragon hoard id" << enemies[i]->get_dragon_hoard_id() << std::endl;
                        //std::cout << "gold id" << gold_id << std::endl;
                        enemies[i]->set_hostile(true);
                        actions.emplace_back("Dragon become hostile. ");
                    }
                }
            } else {
                radar.emplace_back("There is a gold in " + direction_name_map[direction_map[i]] + ". ");
            }
        } else if (map_cell[direction_x][direction_y].get_cell_type() == 'P') {
            int potion_id = which_potion(direction_x, direction_y);
            int potion_state_id = potion_map[potions[potion_id]->get_name()];
            if (!potion_state[potion_state_id]) {
                radar.emplace_back("There is an unknown potion in " + direction_name_map[direction_map[i]] + ". ");
            } else {
                radar.emplace_back("There is a " + potions[potion_id]->get_name() + " potion in " + direction_name_map[direction_map[i]] + ". ");
            }
        } else if (map_cell[direction_x][direction_y].get_cell_type() == 'E' || map_cell[direction_x][direction_y].get_cell_type() == 'H' || map_cell[direction_x][direction_y].get_cell_type() == 'W' || map_cell[direction_x][direction_y].get_cell_type() == 'O' || map_cell[direction_x][direction_y].get_cell_type() == 'M' || map_cell[direction_x][direction_y].get_cell_type() == 'D' || map_cell[direction_x][direction_y].get_cell_type() == 'L') {
            radar.emplace_back("There is an enemy in " + direction_name_map[direction_map[i]] + ". ");
        }
    }
}

void map::game_over() {
    if (player->get_hp() <= 0) {
        std::cout << "Game Over" << std::endl;
    } else if (floor == MAX_FLOOR) {
        std::cout << "You win!" << std::endl;
    } else {
        std::cout << "You quit Shadowmaze!" << std::endl;
    }
    if (player->get_race() == "Shade") {
        std::cout << "Your final score is: " << player->get_gold() * 1.5 << std::endl;
    } else {
        std::cout << "Your final score is: " << player->get_gold() << std::endl;
    }
}



void map::initialize() {
    gameover = false;
    floor_change = false;
    floor = 0;
    actions.clear();
    clear_map();
    
}

void map::clear_map() { 
    memset(map_cell, 0, sizeof(map_cell));
    memset(origin_map_cell, 0, sizeof(origin_map_cell));
    if (floor != 0) {
        player->set_atk(player->get_original_atk());
        player->set_def(player->get_original_def());
        actions.emplace_back("PC loses all buffs. ");
    }
    num_enemy = 0;
    num_potion = 0;
    num_gold = 0;
    enemies.clear();
    golds.clear();
    potions.clear();
}

void map::check_state() {
    if (player->get_hp() <= 0) {
        gameover = true;
    } else if (player->get_race() != "Vampire" &&  player->get_hp() > player->get_max_hp()) {
        player->set_hp(player->get_max_hp());
    }
}

void map::add_action(std::string action) {
    actions.emplace_back(action);
}

void map::disable_enemy() {
    for (int i = 0; i < num_enemy; i++) {
        enemies[i]->set_disable(!enemies[i]->is_disable());
    }
    std::string msg = enemies[0]->is_disable() ? "disable" : "activate";
    add_action("All the enemies are " + msg + ".");
}

