#ifndef IMPLEMENTATION_H
#define IMPLEMENTATION_H

#include "intermediate.h"
#include <iostream>

class implementation_a : public intermediate<implementation_a> {
  public:
    auto do_stuff() {
        std::cout << 42 << std::endl;
    }
};

class implementation_b : public intermediate<implementation_b> {
  public:
    auto do_stuff() {
        return 420;
    }
};

#endif
