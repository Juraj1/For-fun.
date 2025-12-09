#include <iostream>
#include "impl.h"
int IImpl::impl::beforeTestA() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return A;
}

int IImpl::impl::beforeTestB() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return B;
}

void IImpl::impl::setA(const int a) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    A = a;
}

void IImpl::impl::setB(const int b) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    B = b;
}
