#ifndef GOLD_H
#define GOLD_H

#include "item.h"
#include <string>

class gold: public item {
    int value;

 public:
    gold();
    void set_value(int value);
    int get_value();
};

#endif
