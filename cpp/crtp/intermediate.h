#ifndef INTERMEDIATE_H
#define INTERMEDIATE_H

#include "base.h"

template <typename T = void>
class intermediate : public base<intermediate<T>> {
  private:
    T* impl = static_cast<T*>(this);

    auto do_stuff_impl(std::true_type) {
        std::cout << "intermediate" << std::endl;
    }

    auto do_stuff_impl(std::false_type) {
        if constexpr (std::is_same_v<intermediate, T>) {
            return do_stuff_impl(std::true_type{});
        } else {
            std::cout << "intermediate dispatch" << std::endl;
            return impl->do_stuff();
        }
    }

  public:
    intermediate() = default;

    auto do_stuff() {
        return do_stuff_impl(std::is_same<T, void>{});
    }
};

#endif
