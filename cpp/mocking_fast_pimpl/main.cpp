#include <iostream>

#include "MockIface.h"
#include "IImpl.h"
#include "iface.h"

template <typename T>
int function(iface<T> &input) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return input.testA();
}

int main() {
    IImpl foo;
    std::cout << foo.testA() << std::endl;
    std::cout << foo.testB() << std::endl;
    foo.setA(42);
    std::cout << foo.testA() << std::endl;
    foo.setB(69);
    std::cout << foo.testB() << std::endl;

    IImpl bar(foo);
    std::cout << bar.testA() << std::endl;
    std::cout << bar.testB() << std::endl;
    bar.setA(420);
    bar.setB(690);
    std::cout << bar.testA() << std::endl;
    std::cout << bar.testB() << std::endl;
    std::cout << "#################################" << std::endl;
    std::cout << foo.testA() << std::endl;
    std::cout << foo.testB() << std::endl;

    IImpl moved_bar(std::move(bar));
    std::cout << moved_bar.testA() << std::endl;
    std::cout << moved_bar.testB() << std::endl;
    moved_bar.setA(1);
    moved_bar.setB(2);
    std::cout << moved_bar.testA() << std::endl;
    std::cout << moved_bar.testB() << std::endl;
    std::cout << "#################################" << std::endl;
    std::cout << bar.testA() << std::endl;
    std::cout << bar.testB() << std::endl;


    MockIface mocked;
    mocked.testA();
    mocked.testB();

    std::cout << "#################################" << std::endl;
    std::cout << function(mocked) << std::endl;
    std::cout << function(foo) << std::endl;

    return 0;
}