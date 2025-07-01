#include "impl.h"
#include <iostream>

void iface::impl::beforeTestA() {
  std::cout << "IMPLEMENTATION A " << __FILE__ << ": " << __FUNCTION__ << "():" << __LINE__ << " - A: " << A << std::endl;
}

void iface::impl::beforeTestB() {
  std::cout << "IMPLEMENTATION A " << __FILE__ << ": " << __FUNCTION__ << "():" << __LINE__ << " - B: " << B << std::endl;
}
