#include "Binary.h"
#include <iostream>
#include <string>
#include <windows.h>

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    try {
        Binary num1{1, 0, 1, 1};  // 1011
        Binary num2("1100");       // 1100
        
        std::cout << "num1: ";
        num1.print(std::cout);
        std::cout << std::endl;
        
        std::cout << "num2: ";
        num2.print(std::cout);
        std::cout << std::endl;
        
        Binary sum = num1.add(num2);
        Binary diff = num1.subtract(num2);
        
        std::cout << "Сумма: ";
        sum.print(std::cout);
        std::cout << std::endl;
        
        std::cout << "Разность: ";
        diff.print(std::cout);
        std::cout << std::endl;
        
        std::cout << "num1 equals num2: " << (num1.equals(num2) ? "true" : "false") << std::endl;
        std::cout << "num1 greater than num2: " << (num1.greaterThan(num2) ? "true" : "false") << std::endl;
        std::cout << "num1 less than num2: " << (num1.lessThan(num2) ? "true" : "false") << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    
    return 0;
}