#ifndef __IMPLA_H__
#define __IMPLA_H__

#include "iface.h"

class iface::impl {
public:
  void beforeTestA();
  void beforeTestB();
private:
  int A;
  int B;
};

#endif // __IIMPL_H__
