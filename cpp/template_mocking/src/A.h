//
// Created by jza on 1/12/26.
//

#ifndef A_H
#define A_H

#include <string>


template<typename Impl>
class UnitA {
public:
    UnitA() : unitB(){}

    std::string getString() {
        return unitB.getString();
    }


private:
    Impl unitB;
};



#endif //A_H
