#ifndef ANOTHER_INTERMEDIATE_H
#define ANOTHER_INTERMEDIATE_H

#include "intermediate.h"
#include <iostream>

template <typename T = void>
class another_intermediate : public intermediate<another_intermediate<T>>{
  private:
    T* impl = static_cast<T*>(this);

    auto do_stuff_impl(std::true_type) {
        std::cout << "another intermediate" << std::endl;
    }

    auto do_stuff_impl(std::false_type) {
        if constexpr (std::is_same_v<another_intermediate, T>) {
            return do_stuff_impl(std::true_type{});
        } else {
            std::cout << "another intermediate dispatch" << std::endl;
            return impl->do_stuff();
        }
    }

  public:
    another_intermediate() = default;

    auto do_stuff() {
        return do_stuff_impl(std::is_same<T, void>{});
    }
};

#endif
