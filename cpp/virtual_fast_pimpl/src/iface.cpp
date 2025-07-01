#include <memory>
#include <new>
#include "iface.h"
#include "impl.h"

iface::impl *iface::GetImpl() {
  return std::launder(reinterpret_cast<iface::impl*>(&storage));
}

iface::iface() {
  static_assert(sizeof(impl) <= sizeof(storage), "Implementation size greater than provided storage.");
  new (&storage) impl();

}

iface::~iface() {
  std::destroy_at(GetImpl());
}

void iface::testA() {
  GetImpl()->beforeTestA();
}

void iface::testB() {
  GetImpl()->beforeTestB();
}
