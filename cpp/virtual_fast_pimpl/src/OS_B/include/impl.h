#ifndef __IMPLB_H__
#define __IMPLB_H__

#include "iface.h"

class iface::impl {
public:
  void beforeTestA() const;
  void beforeTestB() const;
  void printA() const;
  void printB() const;
  void printC() const;
  void setA(int a);
  void setB(int b);
private:
  int A = 10;
  int B = 20;
  int C = 30;
};

#endif // __IMPLB_H__
