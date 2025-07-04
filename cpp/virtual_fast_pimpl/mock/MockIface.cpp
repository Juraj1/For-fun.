//
// Created by jza on 7/2/25.
//

#include <iostream>
#include "iface.h"
#include "MockIface.h"

void MockIface::testA() {
  std::cout << "testA" << std::endl;
}

void MockIface::testB() {
  std::cout << "testB" << std::endl;
}