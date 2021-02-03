#include <iostream>

#include "DynamicLibrary/DynamicLibrary.hpp"

int main() {
    std::cout << "Hello, World! \n";

    DL::DynaLib_0 dlObj;
    std::cout << "dlObj.get_int() = " << dlObj.get_int() << '\n';
    dlObj.increase_int();
    std::cout << "dlObj.get_int() = " << dlObj.get_int() << '\n';

    return 0;
}
