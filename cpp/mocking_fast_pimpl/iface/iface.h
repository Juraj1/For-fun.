#ifndef __IFACE_H__
#define __IFACE_H__

template <typename T>
class iface {
public:
  iface() = default;
  ~iface() = default;

  iface(const iface &other) = default;
  iface(iface &&other) noexcept = default;

  int testA() {
    return static_cast<T*>(this)->testA();
  }

  int testB() {
    return static_cast<T*>(this)->testB();
  }

  void setA(int a) {
    static_cast<T*>(this)->setA(a);
  }

  void setB(int b) {
    static_cast<T*>(this)->setB(b);
  }
};

#endif // __IFACE_H__
