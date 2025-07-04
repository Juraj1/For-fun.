#include <iostream>
#include "iface.h"
#include "MockIface.h"

int main() {
  iface myInterface;
  std::cout << "testA" << std::endl;
  myInterface.testA();
  std::cout << "testB" << std::endl;
  myInterface.testB();
  myInterface.setA(42);
  myInterface.setB(69);
  std::cout << "testA == 42" << std::endl;
  myInterface.testA();
  std::cout << "testB == 69" << std::endl;
  myInterface.testB();

  std::cout << "copying using default copy constructor" << std::endl;
  iface copy = myInterface;
  std::cout << "copy.testA" << std::endl;
  copy.testA();
  std::cout << "original.testA" << std::endl;
  myInterface.testA();
  std::cout << "changing original A to 1337" << std::endl;
  myInterface.setA(1337);
  myInterface.testA();
  std::cout << "verifying copy.testA == 42" << std::endl;
  copy.testA();

  std::cout << "moving original" << std::endl;
  iface moved(std::move(myInterface));
  std::cout << "moved.testA()" << std::endl;
  moved.testA();
  std::cout << "moved.testA() == 420" << std::endl;
  moved.setA(420);
  moved.testA();
  std::cout << "invoking undefined behaviour for moved object" << std::endl;
  myInterface.testA(); // undefined behaviour

  std::cout << "mocked.testA()" << std::endl;
  MockIface mockedIface;
  mockedIface.testA();
  return 0;
}
