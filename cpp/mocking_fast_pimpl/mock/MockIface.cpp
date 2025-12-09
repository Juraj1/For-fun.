#include <iostream>
#include "MockIface.h"

int MockIface::testA() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return 11;
}

int MockIface::testB() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return 99;
}
