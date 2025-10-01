#ifndef BINARY_H
#define BINARY_H

#include <string>

class Binary {
public:
    Binary();
    Binary(size_t size);
    Binary(const std::initializer_list<unsigned char>& initList);
    Binary(const std::string& binaryString);
    Binary(const Binary& other);
    Binary(Binary&& other) noexcept;
    ~Binary() noexcept;

    Binary& operator=(const Binary& other);
    Binary& operator=(Binary&& other) noexcept;

    size_t getSize() const;
    unsigned char getBit(size_t index) const;

    Binary add(const Binary& other) const;
    Binary subtract(const Binary& other) const;

    bool equals(const Binary& other) const;
    bool greaterThan(const Binary& other) const;
    bool lessThan(const Binary& other) const;

    std::string toString() const;
    void print(std::ostream& os) const;

private:
    size_t size;
    unsigned char* data;
};

#endif