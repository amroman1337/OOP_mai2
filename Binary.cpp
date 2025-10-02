#include "Binary.h"
#include <iostream>
#include <string>
#include <stdexcept>


Binary::Binary() : size(0), data(nullptr) {}

Binary::Binary(size_t size) : size(size), data(new unsigned char[size]) {
    for (size_t i = 0; i < size; ++i) {
        data[i] = 0;
    }
}

Binary::Binary(const std::initializer_list<unsigned char>& initList) 
    : size(initList.size()), data(new unsigned char[initList.size()]) {
    size_t i = 0;
    for (auto value : initList) {
        if (value != 0 && value != 1) {
            delete[] data;
            throw std::invalid_argument("разрешены значения только 0 и 1");
        }
        data[i++] = value;
    }
}

Binary::Binary(const std::string& binaryString) 
    : size(binaryString.length()), data(new unsigned char[binaryString.length()]) {
    for (size_t i = 0; i < size; ++i) {
        char c = binaryString[i];
        if (c == '0') {
            data[i] = 0;
        } else if (c == '1') {
            data[i] = 1;
        } else {
            delete[] data;
            throw std::invalid_argument("строка должна содержать только '0' и '1'");
        }
    }
}

Binary::Binary(const Binary& other) 
    : size(other.size), data(new unsigned char[other.size]) {
    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

Binary::Binary(Binary&& other) noexcept: size(other.size), data(other.data) {
    size = other.size;
    data = other.data;
    other.size = 0;
    other.data = nullptr;
}

Binary::~Binary() noexcept {
    if (data != nullptr) {
        delete[] data;
    }
    size = 0;
}

Binary& Binary::operator=(const Binary& other) {
    if (this != &other) {
        if (data != nullptr) {
            delete[] data;
        }
        size = other.size;
        data = new unsigned char[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

Binary& Binary::operator=(Binary&& other) noexcept {
    if (this != &other) {
        if (data != nullptr) {
            delete[] data;
        }
        size = other.size;
        data = other.data;
        other.size = 0;
        other.data = nullptr;
    }
    return *this;
}

size_t Binary::getSize() const {
    return size;
}

unsigned char Binary::getBit(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("");
    }
    return data[index];
}

Binary Binary::add(const Binary& other) const {
    if (size != other.size) {
        throw std::invalid_argument("числа должны быть одинаковы по размеру");
    }
    Binary result(size);
    unsigned char help = 0;
    for (size_t i = 0; i < size; ++i) {
        unsigned char a = data[i];
        unsigned char b = other.data[i];
        unsigned char sum = a + b + help;
        
        result.data[i] = sum % 2;
        help = sum / 2;
    }
    if (help > 0) {
        throw std::overflow_error("переполнение при сложении");
    }
    return result;
}

Binary Binary::subtract(const Binary& other) const {
    if (size != other.size) {
        throw std::invalid_argument("числа должны быть одинаковы по размеру");
    }
    Binary result(size);
    unsigned char help = 0;
    for (size_t i = 0; i < size; ++i) {
        int diff = data[i] - other.data[i] - help;
        
        if (diff < 0) {
            diff += 2;
            help = 1;
        } else {
            help = 0;
        }
        result.data[i] = static_cast<unsigned char>(diff);
    }
    
    if (help > 0) {
        throw std::underflow_error("отрицательный результат при вычитании");
    }
    
    return result;
}

bool Binary::greaterThan(const Binary& other) const {
    if (size != other.size) {
        throw std::invalid_argument("числа должны быть одинаковы по размеру");
    }
    for (int i = static_cast<int>(size) - 1; i >= 0; --i) {
        if (data[i] > other.data[i]) {
            return true;
        } else if (data[i] < other.data[i]) {
            return false;
        }
    }
    return false;
}

bool Binary::lessThan(const Binary& other) const {
    if (size != other.size) {
        throw std::invalid_argument("числа должны быть одинаковы по размеру");
    }
    
    for (int i = static_cast<int>(size) - 1; i >= 0; --i) {
        if (data[i] < other.data[i]) {
            return true;
        } else if (data[i] > other.data[i]) {
            return false;
        }
    }
    return false;
}

bool Binary::equals(const Binary& other) const {
    if (size != other.size) {
        return false;
    }
    for (size_t i = 0; i < size; ++i) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

std::string Binary::toString() const {
    std::string result;
    for (int i = size - 1; i >= 0; --i) {
        result += (data[i] == 0) ? '0' : '1';
    }
    return result;
}

void Binary::print(std::ostream& os) const {
    os << toString();
}