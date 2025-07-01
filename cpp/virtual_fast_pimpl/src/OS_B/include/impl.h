#ifndef __IMPLB_H__
#define __IMPLB_H__

#include "iface.h"

class iface::impl {
public:
  void beforeTestA();
  void beforeTestB();
private:
  int A;
  int B;
  int C;
};

#endif // __IMPLB_H__
