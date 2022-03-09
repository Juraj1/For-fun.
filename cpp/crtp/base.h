#ifndef BASE_H
#define BASE_H

#include <iostream>

template <typename T>
class base {
  private:
    base() = default;

    friend T;

    T* implementation = static_cast<T*>(this);
  public:
    auto do_stuff() {
        std::cout << "base dispatch" << std::endl;
        return implementation->do_stuff();
    }
};

#endif
