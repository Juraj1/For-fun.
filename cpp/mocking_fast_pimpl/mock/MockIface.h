#ifndef MOCKIFACE_H
#define MOCKIFACE_H

#include "iface.h"

class MockIface: public iface<MockIface> {
public:
    MockIface() = default;

    int testA();
    int testB();
};

#endif //MOCKIFACE_H
