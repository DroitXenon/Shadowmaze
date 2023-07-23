#ifndef POTION_H
#define POTION_H

#include "item.h"
#include <string>


class potion: public item {
    bool revealed = false;
 public:
    potion();
    bool is_revealed();
    void set_revealed(bool val);

};

#endif
