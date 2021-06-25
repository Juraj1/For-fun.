#ifndef IMPLEMENTATION_H
#define IMPLEMENTATION_H

#include "base.h"
#include <iostream>

class implementation_a : public base<implementation_a> {
public:
  auto do_stuff() {
    std::cout << 42 << std::endl;
  }
};

class implementation_b : public base<implementation_b> {
public:
  auto do_stuff() {
    return 420;
  }
};

#endif
