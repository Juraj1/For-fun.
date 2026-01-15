#include <iostream>
#include "A.h"
#include "impl.h"

int main() {
    UnitA<impl> impl;
    std::cout << impl.getString() << std::endl;
}
