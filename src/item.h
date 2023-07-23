#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include "pos.h"

class item {
    bool pickable = true;
    std::string name;
    char symbol;
    pos position;
 public:
    item(char symbol);
    virtual ~item() = 0;
    std::string get_name();
    char get_symbol() const;
    bool is_pickable();
    void set_pickable(bool val);
    pos get_pos();
    void set_pos(pos position);
    void set_name(std::string name);
};

#endif
