#include "Binary.h"
#include <iostream>
#include <string>
#include <windows.h>

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    try {
        Binary num1{1, 0, 1, 1};
        Binary num2("1100");
        
        std::cout << "num1: ";
        num1.print(std::cout);
        std::cout << std::endl;
        
        std::cout << "num2: ";
        num2.print(std::cout);
        std::cout << std::endl;
        

        Binary num3 = num1;
        std::cout << &num1 << std::endl;
        std::cout << &num3 << std::endl;

        Binary num4 = num1.add(num2);
        Binary diff = num1.subtract(num2);
        
        std::cout << "cумма: ";
        num4.print(std::cout);
        std::cout << std::endl;
        
        std::cout << "pазность: ";
        diff.print(std::cout);
        std::cout << std::endl;
    } 
    catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << std::endl;
    }
    
    return 0;
}