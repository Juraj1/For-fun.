#include <memory>
#include <new>

#include "IImpl.h"
#include "impl.h"


inline IImpl::impl* IImpl::GetImpl() {
    return std::launder(reinterpret_cast<impl*>(&storage));
}

IImpl::IImpl() {
    static_assert(sizeof(impl) <= sizeof(storage), "Implementation size greater than provided storage.");
    new (&storage) impl();
}

IImpl::~IImpl() {
    std::destroy_at(GetImpl());
}

int IImpl::testA() {
    return GetImpl()->beforeTestA();
}

int IImpl::testB() {
    return GetImpl()->beforeTestB();
}

void IImpl::setA(const int a) {
    GetImpl()->setA(a);
}

void IImpl::setB(const int b) {
    GetImpl()->setB(b);
}
