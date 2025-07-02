#include <iostream>
#include "iface.h"
#include "MockIface.h"

int main() {
  iface myInterface;
  myInterface.testA();
  myInterface.testB();
  myInterface.setA(42);
  myInterface.setB(69);
  myInterface.testA();
  myInterface.testB();

  iface copy = myInterface;
  copy.testA();

  iface moved(std::move(myInterface));
  moved.testA();
  moved.setA(420);
  moved.testA();
  myInterface.testA(); // undefined behaviour

  MockIface mockedIface;
  mockedIface.testA();
  return 0;
}
