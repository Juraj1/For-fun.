#ifndef __IMPLA_H__
#define __IMPLA_H__

#include "iface.h"

class iface::impl {
public:
  void beforeTestA() const;
  void beforeTestB() const;
  void printA() const;
  void printB() const;
  void setA(int a);
  void setB(int b);
private:
  int A = 10;
  int B = 20;
};

#endif // __IIMPL_H__
