#include "map.h"

void map::set_player(std::shared_ptr<player_character> character){
    player = character;
    actions.emplace_back("Player character has spawned.");
    //std::cout << "player set" << std::endl;
}

void map::set_map(){
    int chamber_id_player = rand() % 5 + 1;
    int chamber_id_stair = rand() % 5 + 1;
    while (chamber_id_stair == chamber_id_player) {
        chamber_id_player = rand() % 5 + 1;
        chamber_id_stair = rand() % 5 + 1;
    }
    std::cout << "player chamber id generated " << chamber_id_player << std::endl;
    std::cout << "stair chamber id generated " << chamber_id_stair << std::endl;
    generate_player(chamber_id_player);
    std::cout << "player generated" << std::endl;
    generate_stair(chamber_id_stair);
    std::cout << "stair generated" << std::endl;
    generate_posion();
    generate_gold();
    generate_enemy();
}

void map::generate_player(int chamber_id) {
    pos p;
    p.randomize_pos(chamber_id);
    //std::cout << map_cell[p.get_x()][p.get_y()].get_cell_type() << std::endl;
    while (true) {
        if (map_cell[p.get_x()][p.get_y()].get_cell_type() == '.') {
            player->set_pos(p);
            map_cell[p.get_x()][p.get_y()].set_cell_type('@');
            map_cell[p.get_x()][p.get_y()].set_cell_name("player");
            break;
        } else {
            p.randomize_pos(chamber_id);
        }
    }
    std::cout << "player pos generated" << " " << p.get_x() << " " << p.get_y() << std::endl;
}

void map::generate_stair(int chamber_id) {
    pos p;
    p.randomize_pos(chamber_id);
    while (true) {
        if (map_cell[p.get_x()][p.get_y()].get_cell_type() == '.') {
            map_cell[p.get_x()][p.get_y()].set_cell_type('\\');
            map_cell[p.get_x()][p.get_y()].set_cell_name("stair");
            break;
        } else {
            p.randomize_pos(chamber_id);
        }
    }
    std::cout << "stair pos generated" << " " << p.get_x() << " " << p.get_y() << std::endl;
}

void map::generate_posion() {
    while (num_posion < 10) {
        pos p;
        p.randomize_pos();
        while (true) {
            if (map_cell[p.get_x()][p.get_y()].get_cell_type() == '.') {
                map_cell[p.get_x()][p.get_y()].set_cell_type('P');
                map_cell[p.get_x()][p.get_y()].set_cell_name("potion");
                map_cell[p.get_x()][p.get_y()].set_step(false);
                break;
            } else {
                p.randomize_pos();
            }
        }
        ++num_posion;
    }
    std::cout << "potion generated" << std::endl;
}

void map::generate_gold() {
    while (num_gold < 10) {
        pos p;
        p.randomize_pos();
        while (true) {
            if (map_cell[p.get_x()][p.get_y()].get_cell_type() == '.') {
                map_cell[p.get_x()][p.get_y()].set_cell_type('G');
                map_cell[p.get_x()][p.get_y()].set_cell_name("gold");
                break;
            } else {
                p.randomize_pos();
            }
        }
        ++num_gold;
    }
    std::cout << "gold generated" << std::endl;
}

void map::generate_enemy() {
    while (num_enemy < 20) {
        pos p;
        p.randomize_pos();
        while (true) {
            if (map_cell[p.get_x()][p.get_y()].get_cell_type() == '.') {
                map_cell[p.get_x()][p.get_y()].set_cell_type('E');
                map_cell[p.get_x()][p.get_y()].set_cell_name("enemy");
                map_cell[p.get_x()][p.get_y()].set_step(false);
                break;
            } else {
                p.randomize_pos();
            }
        }
        ++num_enemy;
    }
    std::cout << "enemy generated" << std::endl;
}

void map::read_empty_map(std::string& filename) {
    std::ifstream map_file{filename};
    std::string line;
    int row = 0;
    while (getline(map_file, line)) {
        for (int i = 0; i < NUM_COL; ++i) {
            map_cell[i][row].set_cell_type(line[i]);
            origin_map_cell[i][row].set_cell_type(line[i]);
            if (line[i] == '-') {
                map_cell[i][row].set_cell_name("wall");
                map_cell[i][row].set_step(false);
                origin_map_cell[i][row].set_cell_name("wall");
                origin_map_cell[i][row].set_step(false);
            } else if (line[i] == '|') {
                map_cell[i][row].set_cell_name("wall");
                map_cell[i][row].set_step(false);
                origin_map_cell[i][row].set_cell_name("wall");
                origin_map_cell[i][row].set_step(false);
            } else if (line[i] == '.') {
                map_cell[i][row].set_cell_name("tile");
                map_cell[i][row].set_step(true);
                origin_map_cell[i][row].set_cell_name("tile");
                origin_map_cell[i][row].set_step(true);
            } else if (line[i] == '+') {
                map_cell[i][row].set_cell_name("door");
                map_cell[i][row].set_step(true);
                origin_map_cell[i][row].set_cell_name("door");
                origin_map_cell[i][row].set_step(true);
            } else if (line[i] == '#') {
                map_cell[i][row].set_cell_name("passage");
                map_cell[i][row].set_step(true);
                origin_map_cell[i][row].set_cell_name("passage");
                origin_map_cell[i][row].set_step(true);
            } else if (line[i] == ' ') {
                map_cell[i][row].set_cell_name("empty");
                map_cell[i][row].set_step(false);
                origin_map_cell[i][row].set_cell_name("empty");
                origin_map_cell[i][row].set_step(false);
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
    int start_line = 0;
    int end_line = 0;

    if (floor == 1) {
        start_line = 0;
        end_line = 25;
    } else if (floor == 2) {
        start_line = 26;
        end_line = 50;
    } else if (floor == 3) {
        start_line = 51;
        end_line = 75;
    } else if (floor == 4) {
        start_line = 76;
        end_line = 100;
    } else {
        start_line = 101;
        end_line = 125;
    }

    while (getline(map_file, line)) {
        line_num++;
        if (line_num >= start_line && line_num <= end_line) {
            for (int i = 0; i < NUM_COL; ++i) {
                map_cell[i][row].set_cell_type(line[i]);
                origin_map_cell[i][row].set_cell_type(line[i]);
                if (line[i] == '@') {
                    map_cell[i][row].set_cell_name("player");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    player->set_pos(pos{i, row, floor});

                } else if (line[i] == '-') {
                    map_cell[i][row].set_cell_name("wall");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_name("wall");
                    origin_map_cell[i][row].set_step(false);
                } else if (line[i] == '|') {
                    map_cell[i][row].set_cell_name("wall");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_name("wall");
                    origin_map_cell[i][row].set_step(false);
                } else if (line[i] == '.') {
                    map_cell[i][row].set_cell_name("tile");
                    map_cell[i][row].set_step(true);
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                } else if (line[i] == '+') {
                    map_cell[i][row].set_cell_name("door");
                    map_cell[i][row].set_step(true);
                    origin_map_cell[i][row].set_cell_name("door");
                    origin_map_cell[i][row].set_step(true);
                } else if (line[i] == '#') {
                    map_cell[i][row].set_cell_name("passage");
                    map_cell[i][row].set_step(true);
                    origin_map_cell[i][row].set_cell_name("passage");
                    origin_map_cell[i][row].set_step(true);
                } else if (line[i] == ' ') {
                    map_cell[i][row].set_cell_name("empty");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_name("empty");
                    origin_map_cell[i][row].set_step(false);
                } else if (line[i] == '0') {
                    map_cell[i][row].set_cell_type('P');
                    map_cell[i][row].set_cell_name("potion");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    //
                } else if (line[i] == '1') {
                    map_cell[i][row].set_cell_type('P');
                    map_cell[i][row].set_cell_name("potion");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    //
                } else if (line[i] == '2') {
                    map_cell[i][row].set_cell_type('P');
                    map_cell[i][row].set_cell_name("potion");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    //
                } else if (line[i] == '3') {
                    map_cell[i][row].set_cell_type('P');
                    map_cell[i][row].set_cell_name("potion");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    //
                } else if (line[i] == '4') {
                    map_cell[i][row].set_cell_type('P');
                    map_cell[i][row].set_cell_name("potion");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    //
                } else if (line[i] == '5') {
                    map_cell[i][row].set_cell_type('P');
                    map_cell[i][row].set_cell_name("potion");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    //
                } else if (line[i] == '6') {
                    map_cell[i][row].set_cell_type('G');
                    map_cell[i][row].set_cell_name("gold");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    //
                } else if (line[i] == '7') {
                    map_cell[i][row].set_cell_type('G');
                    map_cell[i][row].set_cell_name("gold");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    //
                } else if (line[i] == '8') {
                    map_cell[i][row].set_cell_type('G');
                    map_cell[i][row].set_cell_name("gold");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    //
                } else if (line[i] == '9') {
                    map_cell[i][row].set_cell_type('G');
                    map_cell[i][row].set_cell_name("gold");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    //
                } else if (line[i] == 'H') {
                    map_cell[i][row].set_cell_type('H');
                    map_cell[i][row].set_cell_name("enemy");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    auto enemy = std::make_shared<human>();
                    enemy->set_pos(pos{i, row, floor});
                    enemies.emplace_back(enemy);
                    num_enemy++;
                } else if (line[i] == 'W') {
                    map_cell[i][row].set_cell_type('H');
                    map_cell[i][row].set_cell_name("enemy");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    auto enemy = std::make_shared<dwarf>();
                    enemy->set_pos(pos{i, row, floor});
                    enemies.emplace_back(enemy);
                    num_enemy++;
                } else if (line[i] == 'E') {
                    map_cell[i][row].set_cell_type('H');
                    map_cell[i][row].set_cell_name("enemy");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    auto enemy = std::make_shared<elf>();
                    enemy->set_pos(pos{i, row, floor});
                    enemies.emplace_back(enemy);
                    num_enemy++;
                } else if (line[i] == 'O') {
                    map_cell[i][row].set_cell_type('H');
                    map_cell[i][row].set_cell_name("enemy");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    auto enemy = std::make_shared<orc>();
                    enemy->set_pos(pos{i, row, floor});
                    enemies.emplace_back(enemy);
                    num_enemy++;
                } else if (line[i] == 'M') {
                    map_cell[i][row].set_cell_type('H');
                    map_cell[i][row].set_cell_name("enemy");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    auto enemy = std::make_shared<merchant>();
                    enemy->set_pos(pos{i, row, floor});
                    enemies.emplace_back(enemy);
                    num_enemy++;
                } else if (line[i] == 'D') {
                    map_cell[i][row].set_cell_type('H');
                    map_cell[i][row].set_cell_name("enemy");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    auto enemy = std::make_shared<dragon>();
                    enemy->set_pos(pos{i, row, floor});
                    enemies.emplace_back(enemy);
                    num_enemy++;
                } else if (line[i] == 'L') {
                    map_cell[i][row].set_cell_type('H');
                    map_cell[i][row].set_cell_name("enemy");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_type('.');
                    origin_map_cell[i][row].set_cell_name("tile");
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
            std::cout << map_cell[j][i].get_cell_type();
        }
        std::cout << std::endl;
    }
    std::cout << "Race: " << player->get_race() << " Gold: " << player->get_gold() << std::endl;
    std::cout << "HP: " << player->get_hp() << std::endl;
    std::cout << "Atk: " << player->get_atk() << std::endl;
    std::cout << "Def: " << player->get_def() << std::endl;
    std::cout << "Action: ";
    for (auto action : actions) {
        std::cout << action;
    }
    std::cout << std::endl;
    actions.clear();
}

void map::move_player(std::string direction) {
    int new_x = direction_pos(direction, player->get_pos()).get_x();
    int new_y = direction_pos(direction, player->get_pos()).get_y();
    if (map_cell[new_x][new_y].get_step()) {
        map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_type(origin_map_cell[player->get_pos().get_x()][player->get_pos().get_y()].get_cell_type());
        map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_name(origin_map_cell[player->get_pos().get_x()][player->get_pos().get_y()].get_cell_name());
        map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_step(origin_map_cell[player->get_pos().get_x()][player->get_pos().get_y()].get_step());
        pos p{new_x, new_y, player->get_pos().get_floor()};
        player->set_pos(p);
        map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_type('@');
        map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_name("player");
        actions.emplace_back("PC moves " + direction + ".");
    } else {
        actions.emplace_back("PC cannot moves " + direction + ".");
    }
}

void map::player_attack(std::string direction) {
    int enemy_id = which_enemy(direction_pos(direction, player->get_pos()).get_x(), direction_pos(direction, player->get_pos()).get_y());
    if (enemy_id != -1 && !enemies[enemy_id]->get_dead()) {
        int damage = player->attack(enemies[enemy_id]);
        actions.emplace_back("PC deals " + std::to_string(damage) + " damage to H (");
        if (enemies[enemy_id]->get_hp() <= 0) {
            actions.emplace_back("Dead).");
            //std::cout << "enemy dead" << std::endl;
            map_cell[enemies[enemy_id]->get_pos().get_x()][enemies[enemy_id]->get_pos().get_y()].set_cell_type('.');
            map_cell[enemies[enemy_id]->get_pos().get_x()][enemies[enemy_id]->get_pos().get_y()].set_cell_name("tile");
            map_cell[enemies[enemy_id]->get_pos().get_x()][enemies[enemy_id]->get_pos().get_y()].set_step(true);
            enemies.erase(enemies.begin() + enemy_id);
            enemies.shrink_to_fit();
            num_enemy--;
        } else {
            actions.emplace_back(std::to_string(enemies[enemy_id]->get_hp()) + "HP).");
        }
    } else {
        actions.emplace_back("No enemy in this direction. You wasted a turn.");
    }
}

// void map::move_enemy_from_to(int enemy_id, int x1, int y1, int x2, int y2) {
//     map_cell[x1][y1].set_cell_type(origin_map_cell[x1][y1].get_cell_type());
//     map_cell[x1][y1].set_cell_name(origin_map_cell[x1][y1].get_cell_name());
//     map_cell[x1][y1].set_step(origin_map_cell[x1][y1].get_step());
//     pos p{x2, y2, enemies[enemy_id]->get_pos().get_floor()};
//     enemies[enemy_id]->set_pos(p);
//     enemies[enemy_id]->set_moved(true);
//     map_cell[x2][y2].set_cell_type(enemies[enemy_id]->get_symbol());
//     map_cell[x2][y2].set_cell_name(enemies[enemy_id]->get_race());
//     map_cell[x2][y2].set_step(false);
// }

void map::move_enemy() {
    for (int i = 0; i < NUM_ROW; ++i) {  
        for (int j = 0; j < NUM_COL; ++j) {
            int enemy_id = which_enemy(j, i);
            if (enemy_id != -1 && !enemies[enemy_id]->is_moved() && !enemies[enemy_id]->get_dead()) { //if found enemy
                //std::cout << "enemy found" << std::endl;
                while (!enemies[enemy_id]->is_moved()) {
                    int random_direction = rand() % 8;
                    //std::cout << random_direction << std::endl;
                    std::string direction = direction_map[random_direction];
                    //std::cout << direction << std::endl;
                    int new_x = direction_pos(direction, enemies[enemy_id]->get_pos()).get_x();
                    int new_y = direction_pos(direction, enemies[enemy_id]->get_pos()).get_y();
                    if (map_cell[new_x][new_y].get_cell_type() == '.') {
                        map_cell[j][i].set_cell_type(origin_map_cell[j][i].get_cell_type());
                        map_cell[j][i].set_cell_name(origin_map_cell[j][i].get_cell_name());
                        map_cell[j][i].set_step(origin_map_cell[j][i].get_step());
                        pos p{new_x, new_y, enemies[enemy_id]->get_pos().get_floor()};
                        enemies[enemy_id]->set_pos(p);
                        enemies[enemy_id]->set_moved(true);
                        map_cell[new_x][new_y].set_cell_type(enemies[enemy_id]->get_symbol());
                        map_cell[new_x][new_y].set_cell_name(enemies[enemy_id]->get_race());
                        map_cell[new_x][new_y].set_step(false); 
                    } else {
                        random_direction = rand() % 8;
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
        if (!enemies[i]->get_dead() && is_adjacent(enemies[i]->get_pos(), player->get_pos())) {
            if (enemies[i]->is_hostile()) {
                int damage = enemies[i]->attack(player);
                actions.emplace_back(enemies[i]->get_race() + " deals " + std::to_string(damage) + " damage to PC. ");
                if (player->get_hp() <= 0) {
                    set_gameover();
                    return;
                }
            }
        }
    }
}

void map::use_potion(std::string &direction) {
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

int map::which_potion() {
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

void map::set_gameover() {
    gameover = true;
}

void map::check_state() {
}
