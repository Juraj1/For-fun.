#ifndef __IFACE_H__
#define __IFACE_H__

#ifdef OS_A
#define STORAGE_SIZE 8
#else
#define STORAGE_SIZE 12
#endif

#include <cstddef>

class iface {
public:
  iface();
  virtual ~iface();

  iface(const iface &other) = default;
  iface(iface &&other) noexcept = default;

  virtual void testA();
  virtual void testB();
  virtual void setA(int a);
  virtual void setB(int b);

protected:
  class impl;
  alignas(std::max_align_t) std::byte storage[STORAGE_SIZE]{};
  // using a helper call, not a pointer saves few bytes and frees us of problems with deep copying
  // inlining helper function allows optimiser to get rid of the indirection
  inline impl *GetImpl();
};

#endif // __IFACE_H__
