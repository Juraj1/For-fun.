#ifndef IMPLEMENTATION_H
#define IMPLEMENTATION_H

#include "another_intermediate.h"
#include <iostream>

class implementation_a : public another_intermediate<implementation_a> {
  public:
    auto do_stuff() {
        std::cout << 42 << std::endl;
    }
};

class implementation_b : public another_intermediate<implementation_b> {
  public:
    auto do_stuff() {
        return 420;
    }
};

#endif
