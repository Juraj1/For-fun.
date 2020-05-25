#include <iostream>
#include "signal.h"


class Printer {
public:
    void print(std::string s) {
        std::cout << __FUNCTION__ << ": " << s << std::endl;
    }

    void asd(std::string s) {
        std::cout << __FUNCTION__ << ": " << s << std::endl;
    }
};

class Manager {
    public:
    Signal<std::string> print;
};


int main(int argc, char *argv[]){
    Printer p;
    Manager m;
    
    std::string a = argv[1];

    std::cout << m.print.connect([](std::string s) {std::cout << __FUNCTION__ << ": " << s << std::endl;}) << std::endl;
    std::cout << m.print.connect_member(&p, &Printer::print) << std::endl;
    std::cout << m.print.connect_member(&p, &Printer::asd) << std::endl;
    m.print.emit(a);

    return 0;
}
