#ifndef IMPL_H
#define IMPL_H

#include "IImpl.h"

class IImpl::impl {
public:
  int beforeTestA();
  int beforeTestB();
  void setA(int a);
  void setB(int b);
private:
  int A = 10;
  int B = 20;
};

#endif //IMPL_H
