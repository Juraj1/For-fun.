#ifndef __IFACE_H__
#define __IFACE_H__

#include <cstddef>

class iface {
public:
  iface();
  ~iface();
  iface(const iface &other) = delete;
  iface &operator=(const iface &other) = delete;

  void testA();
  void testB();

protected:
  class impl;
#ifdef OS_A
  alignas(std::max_align_t) std::byte storage[8];
#else
  alignas(std::max_align_t) std::byte storage[12];
#endif

  impl *GetImpl();
};

#endif // __IFACE_H__
