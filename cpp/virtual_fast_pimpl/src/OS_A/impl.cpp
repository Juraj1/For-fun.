#include "impl.h"
#include <iostream>

void iface::impl::beforeTestA() const {
  std::cout << "IMPLEMENTATION A " << __FILE__ << ": " << __FUNCTION__ << "():" << __LINE__ << " - A: " << A << std::endl;
}

void iface::impl::beforeTestB() const {
  std::cout << "IMPLEMENTATION A " << __FILE__ << ": " << __FUNCTION__ << "():" << __LINE__ << " - B: " << B << std::endl;
}

void iface::impl::printA() const {
  std::cout << A << std::endl;
}

void iface::impl::printB() const {
  std::cout << B << std::endl;
}

void iface::impl::setA(int a) {
  A = a;
}

void iface::impl::setB(int b) {
  B = b;
}