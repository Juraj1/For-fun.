//
// Created by jza on 7/2/25.
//

#ifndef MOCKIFACE_H
#define MOCKIFACE_H

#include "iface.h"

class MockIface : public iface {
public:
    MockIface() = default;

    void testA() override;
    void testB() override;
};

#endif //MOCKIFACE_H
