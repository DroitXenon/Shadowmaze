#ifndef CELL_H
#define CELL_H
#include <string>

class cell {
    char cell_type;
    std::string cell_name;
 public:
    //cell(char cell_type, std::string cell_name);
    char get_cell_type();
    std::string get_cell_name();
    void set_cell_type(char cell_type);
    void set_cell_name(std::string cell_name);
};

#endif
