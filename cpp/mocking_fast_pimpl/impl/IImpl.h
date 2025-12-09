#ifndef IIMPL_H
#define IIMPL_H

#define STORAGE_SIZE 8

#include <cstddef>
#include "iface.h"

class IImpl: public iface<IImpl> {
public:
    IImpl();
    ~IImpl();

    IImpl(const IImpl &other) = default;
    IImpl(IImpl &&other) = default;

    int testA();
    int testB();
    void setA(int a);
    void setB(int b);

protected:
    class impl;
    alignas(std::max_align_t) std::byte storage[STORAGE_SIZE]{};
    // using a helper call, not a pointer saves few bytes and frees us of problems with deep copying
    // inlining helper function allows optimiser to get rid of the indirection
    inline impl* GetImpl();
};

#endif //IIMPL_H
