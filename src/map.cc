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
                } else if (line[i] == '0') {
                    map_cell[i][row].set_cell_type('P');
                    map_cell[i][row].set_cell_name("potion");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    //
                } else if (line[i] == '1') {
                    map_cell[i][row].set_cell_type('P');
                    map_cell[i][row].set_cell_name("potion");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    //
                } else if (line[i] == '2') {
                    map_cell[i][row].set_cell_type('P');
                    map_cell[i][row].set_cell_name("potion");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    //
                } else if (line[i] == '3') {
                    map_cell[i][row].set_cell_type('P');
                    map_cell[i][row].set_cell_name("potion");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    //
                } else if (line[i] == '4') {
                    map_cell[i][row].set_cell_type('P');
                    map_cell[i][row].set_cell_name("potion");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    //
                } else if (line[i] == '5') {
                    map_cell[i][row].set_cell_type('P');
                    map_cell[i][row].set_cell_name("potion");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    //
                } else if (line[i] == '6') {
                    map_cell[i][row].set_cell_type('G');
                    map_cell[i][row].set_cell_name("gold");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    //
                } else if (line[i] == '7') {
                    map_cell[i][row].set_cell_type('G');
                    map_cell[i][row].set_cell_name("gold");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    //
                } else if (line[i] == '8') {
                    map_cell[i][row].set_cell_type('G');
                    map_cell[i][row].set_cell_name("gold");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    //
                } else if (line[i] == '9') {
                    map_cell[i][row].set_cell_type('G');
                    map_cell[i][row].set_cell_name("gold");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                    //
                } else if (line[i] == '@') {
                    map_cell[i][row].set_cell_type('@');
                    map_cell[i][row].set_cell_name("player");
                    map_cell[i][row].set_step(true);
                    origin_map_cell[i][row].set_cell_name("tile");
                    origin_map_cell[i][row].set_step(true);
                } else if (line[i] == 'H') {
                    map_cell[i][row].set_cell_type('H');
                    map_cell[i][row].set_cell_name("enemy");
                    map_cell[i][row].set_step(false);
                    origin_map_cell[i][row].set_cell_name("enemy");
                    origin_map_cell[i][row].set_step(false);
                    auto enemy = std::make_shared<human>();
                    enemy->set_pos(pos{i, row, floor});
                    enemies.emplace_back(enemy);
                    num_enemy++;
                } else if (line[i] == 'W') {
                    
                } else if (line[i] == 'E') {

                } else if (line[i] == 'O') {

                } else if (line[i] == 'M') {

                } else if (line[i] == 'D') {

                } else if (line[i] == 'L') {

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
    if (direction == "no") {
        if (map_cell[player->get_pos().get_x()][player->get_pos().get_y() - 1].get_step()) {
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_type(origin_map_cell[player->get_pos().get_x()][player->get_pos().get_y()].get_cell_type());
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_name(origin_map_cell[player->get_pos().get_x()][player->get_pos().get_y()].get_cell_name());
            pos p{player->get_pos().get_x(), player->get_pos().get_y() - 1, player->get_pos().get_floor()};
            player->set_pos(p);
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_type('@');
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_name("player");
            actions.emplace_back("PC moves North.");
        } else {
            actions.emplace_back("PC cannot move North.");
        }
    } else if (direction == "so") {
        if (map_cell[player->get_pos().get_x()][player->get_pos().get_y() + 1].get_step()) {
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_type(origin_map_cell[player->get_pos().get_x()][player->get_pos().get_y()].get_cell_type());
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_name(origin_map_cell[player->get_pos().get_x()][player->get_pos().get_y()].get_cell_name());
            pos p{player->get_pos().get_x(), player->get_pos().get_y() + 1, player->get_pos().get_floor()};
            player->set_pos(p);
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_type('@');
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_name("player");
            actions.emplace_back("PC moves South.");
        } else {
            actions.emplace_back("PC cannot move South.");
        }
    } else if (direction == "ea") {
        if (map_cell[player->get_pos().get_x() + 1][player->get_pos().get_y()].get_step()) {
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_type(origin_map_cell[player->get_pos().get_x()][player->get_pos().get_y()].get_cell_type());
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_name(origin_map_cell[player->get_pos().get_x()][player->get_pos().get_y()].get_cell_name());
            pos p{player->get_pos().get_x() + 1, player->get_pos().get_y(), player->get_pos().get_floor()};
            player->set_pos(p);
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_type('@');
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_name("player");
            actions.emplace_back("PC moves East.");
        } else {
            actions.emplace_back("PC cannot move East.");
        }
    } else if (direction == "we") {
        if (map_cell[player->get_pos().get_x() - 1][player->get_pos().get_y()].get_step()) {
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_type(origin_map_cell[player->get_pos().get_x()][player->get_pos().get_y()].get_cell_type());
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_name(origin_map_cell[player->get_pos().get_x()][player->get_pos().get_y()].get_cell_name());
            pos p{player->get_pos().get_x() - 1, player->get_pos().get_y(), player->get_pos().get_floor()};
            player->set_pos(p);
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_type('@');
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_name("player");
            actions.emplace_back("PC moves West.");
        } else {
            actions.emplace_back("PC cannot move West.");
        }
    } else if (direction == "ne") {
        if (map_cell[player->get_pos().get_x() + 1][player->get_pos().get_y() - 1].get_step()) {
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_type(origin_map_cell[player->get_pos().get_x()][player->get_pos().get_y()].get_cell_type());
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_name(origin_map_cell[player->get_pos().get_x()][player->get_pos().get_y()].get_cell_name());
            pos p{player->get_pos().get_x() + 1, player->get_pos().get_y() - 1, player->get_pos().get_floor()};
            player->set_pos(p);
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_type('@');
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_name("player");
            actions.emplace_back("PC moves Northeast.");
        } else {
            actions.emplace_back("PC cannot move Northeast.");
        }
    } else if (direction == "nw") {
        if (map_cell[player->get_pos().get_x() - 1][player->get_pos().get_y() - 1].get_step()) {
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_type(origin_map_cell[player->get_pos().get_x()][player->get_pos().get_y()].get_cell_type());
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_name(origin_map_cell[player->get_pos().get_x()][player->get_pos().get_y()].get_cell_name());
            pos p{player->get_pos().get_x() - 1, player->get_pos().get_y() - 1, player->get_pos().get_floor()};
            player->set_pos(p);
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_type('@');
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_name("player");
            actions.emplace_back("PC moves Northwest.");
        } else {
            actions.emplace_back("PC cannot move Northwest.");
        }
    } else if (direction == "se") {
        if (map_cell[player->get_pos().get_x() + 1][player->get_pos().get_y() + 1].get_step()) {
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_type(origin_map_cell[player->get_pos().get_x()][player->get_pos().get_y()].get_cell_type());
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_name(origin_map_cell[player->get_pos().get_x()][player->get_pos().get_y()].get_cell_name());
            pos p{player->get_pos().get_x() + 1, player->get_pos().get_y() + 1, player->get_pos().get_floor()};
            player->set_pos(p);
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_type('@');
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_name("player");
            actions.emplace_back("PC moves Southeast.");
        } else {
            actions.emplace_back("PC cannot move Southeast.");
        }
    } else {
        if (map_cell[player->get_pos().get_x() - 1][player->get_pos().get_y() + 1].get_step()) {
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_type(origin_map_cell[player->get_pos().get_x()][player->get_pos().get_y()].get_cell_type());
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_name(origin_map_cell[player->get_pos().get_x()][player->get_pos().get_y()].get_cell_name());
            pos p{player->get_pos().get_x() - 1, player->get_pos().get_y() + 1, player->get_pos().get_floor()};
            player->set_pos(p);
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_type('@');
            map_cell[player->get_pos().get_x()][player->get_pos().get_y()].set_cell_name("player");
            actions.emplace_back("PC moves Southwest.");
        } else {
            actions.emplace_back("PC cannot move Southwest.");
        }
    }

}

void map::move_enemy() {
    for (int i = 0; i < NUM_ROW; ++i) {  
        for (int j = 0; j < NUM_COL; ++j) {
            int enemy_id = which_enemy(j, i);
            if (enemy_id != -1) { //if found enemy
                std::cout << "enemy found" << std::endl;
                int random_direction = 0;
                if (random_direction == 0) {
                    if (map_cell[j][i - 1].get_cell_type() == '.') {
                        map_cell[j][i].set_cell_type(origin_map_cell[i][j].get_cell_type());
                        map_cell[j][i].set_cell_name(origin_map_cell[i][j].get_cell_name());
                        pos p{j, i - 1, enemies[enemy_id]->get_pos().get_floor()};
                        enemies[enemy_id]->set_pos(p);
                        map_cell[j][i].set_cell_type('E');
                        map_cell[j][i].set_cell_name("enemy");
                    }
                } else if (random_direction == 1) {
                    if (map_cell[i][j + 1].get_step()) {
                        map_cell[i][j].set_cell_type(origin_map_cell[i][j].get_cell_type());
                        map_cell[i][j].set_cell_name(origin_map_cell[i][j].get_cell_name());
                        pos p{i, j + 1, enemies[enemy_id]->get_pos().get_floor()};
                        enemies[enemy_id]->set_pos(p);
                        map_cell[i][j].set_cell_type('E');
                        map_cell[i][j].set_cell_name("enemy");
                    }
                } else if (random_direction == 2) {
                    if (map_cell[i + 1][j].get_step()) {
                        map_cell[i][j].set_cell_type(origin_map_cell[i][j].get_cell_type());
                        map_cell[i][j].set_cell_name(origin_map_cell[i][j].get_cell_name());
                        pos p{i + 1, j, enemies[enemy_id]->get_pos().get_floor()};
                        enemies[enemy_id]->set_pos(p);
                        map_cell[i][j].set_cell_type('E');
                        map_cell[i][j].set_cell_name("enemy");
                    }
                } else if (random_direction == 3) {
                    if (map_cell[i - 1][j].get_step()) {
                        map_cell[i][j].set_cell_type(origin_map_cell[i][j].get_cell_type());
                        map_cell[i][j].set_cell_name(origin_map_cell[i][j].get_cell_name());
                        pos p{i - 1, j, enemies[enemy_id]->get_pos().get_floor()};
                        enemies[enemy_id]->set_pos(p);
                        map_cell[i][j].set_cell_type('E');
                        map_cell[i][j].set_cell_name("enemy"); 
                    }
                } else if (random_direction == 4) {
                    if (map_cell[i - 1][j - 1].get_step()) {
                        map_cell[i][j].set_cell_type(origin_map_cell[i][j].get_cell_type());
                        map_cell[i][j].set_cell_name(origin_map_cell[i][j].get_cell_name());
                        pos p{i + 1, j, enemies[enemy_id]->get_pos().get_floor()};
                        enemies[enemy_id]->set_pos(p);
                        map_cell[i][j].set_cell_type('E');
                        map_cell[i][j].set_cell_name("enemy"); 
                    }
                } else if (random_direction == 5) {
                    if (map_cell[i - 1][j + 1].get_step()) {
                        map_cell[i][j].set_cell_type(origin_map_cell[i][j].get_cell_type());
                        map_cell[i][j].set_cell_name(origin_map_cell[i][j].get_cell_name());
                        pos p{i - 1, j + 1, enemies[enemy_id]->get_pos().get_floor()};
                        enemies[enemy_id]->set_pos(p);
                        map_cell[i][j].set_cell_type('E');
                        map_cell[i][j].set_cell_name("enemy"); 
                    }
                } else if (random_direction == 6) {
                    if (map_cell[i + 1][j - 1].get_step()) {
                        map_cell[i][j].set_cell_type(origin_map_cell[i][j].get_cell_type());
                        map_cell[i][j].set_cell_name(origin_map_cell[i][j].get_cell_name());
                        pos p{i + 1, j - 1, enemies[enemy_id]->get_pos().get_floor()};
                        enemies[enemy_id]->set_pos(p);
                        map_cell[i][j].set_cell_type('E');
                        map_cell[i][j].set_cell_name("enemy"); 
                    }
                } else {
                    if (map_cell[i + 1][j + 1].get_step()) {
                        map_cell[i][j].set_cell_type(origin_map_cell[i][j].get_cell_type());
                        map_cell[i][j].set_cell_name(origin_map_cell[i][j].get_cell_name());
                        pos p{i + 1, j + 1, enemies[enemy_id]->get_pos().get_floor()};
                        enemies[enemy_id]->set_pos(p);
                        map_cell[i][j].set_cell_type('E');
                        map_cell[i][j].set_cell_name("enemy"); 
                    }
                }
            }
        }
    }
}

void map::use_potion(std::string &direction) {
}

bool map::is_adjacent() {
    
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
}
