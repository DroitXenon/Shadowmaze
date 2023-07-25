#ifndef CELL_H
#define CELL_H
#include <string>

class cell {
    char cell_type;
    bool can_step = true;
 public:
    //cell(char cell_type, std::string cell_name);
    char get_cell_type() const;
    bool get_step() const;
    void set_cell_type(char cell_type);
    void set_step(bool stepable);
};

#endif
