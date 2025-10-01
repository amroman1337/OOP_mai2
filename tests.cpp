#include <gtest/gtest.h>
#include "Binary.h"
#include <sstream>

TEST(BinaryTest, Constructors) {
    Binary defaultBinary;
    EXPECT_EQ(defaultBinary.getSize(), 0);
    
    Binary sizeBinary(4);
    EXPECT_EQ(sizeBinary.getSize(), 4);
    for (size_t i = 0; i < 4; ++i) {
        EXPECT_EQ(sizeBinary.getBit(i), 0);
    }
    
    Binary listBinary{1, 0, 1, 1};
    EXPECT_EQ(listBinary.getSize(), 4);
    EXPECT_EQ(listBinary.getBit(0), 1);
    EXPECT_EQ(listBinary.getBit(1), 0);
    EXPECT_EQ(listBinary.getBit(2), 1);
    EXPECT_EQ(listBinary.getBit(3), 1);
    
    Binary stringBinary("1100");
    EXPECT_EQ(stringBinary.getSize(), 4);
    EXPECT_EQ(stringBinary.getBit(0), 1);
    EXPECT_EQ(stringBinary.getBit(1), 1);
    EXPECT_EQ(stringBinary.getBit(2), 0);
    EXPECT_EQ(stringBinary.getBit(3), 0);
}

// ошибки
TEST(BinaryTest, InvalidInput) {
    EXPECT_THROW(Binary({1, 2, 3}), std::invalid_argument);
    EXPECT_THROW(Binary("1021"), std::invalid_argument);
    EXPECT_THROW(Binary("abc"), std::invalid_argument);
}

// арифметика
TEST(BinaryTest, Addition) {
    Binary a{0, 0, 1, 1}; // 1100 (12)
    Binary b{0, 1, 0, 1}; // 1010 (10)
    Binary result = a.add(b);
    
    // 12 + 10 = 22 (10110), должно быть переполнением
    EXPECT_THROW(a.add(b), std::overflow_error);
    
    Binary c{0, 0, 0, 1}; // 1000 (8)
    Binary d{0, 0, 0, 1}; // 1000 (8)
    EXPECT_THROW(c.add(d), std::overflow_error);
}

TEST(BinaryTest, Subtraction) {
    Binary a{0, 0, 1, 1}; // 1100 (12)
    Binary b{0, 0, 0, 1}; // 1000 (8)
    Binary result = a.subtract(b);
    
    // 12 - 8 = 4 (0100)
    EXPECT_EQ(result.getBit(0), 0);
    EXPECT_EQ(result.getBit(1), 0);
    EXPECT_EQ(result.getBit(2), 1);
    EXPECT_EQ(result.getBit(3), 0);
    
    Binary small{0, 0, 0, 1}; // 1000 (8)
    Binary large{0, 0, 1, 1}; // 1100 (12)
    EXPECT_THROW(small.subtract(large), std::underflow_error);
}

// сравнения
TEST(BinaryTest, Comparison) {
    Binary a{1, 0, 0, 1}; // 1001 (9)
    Binary b{1, 0, 1, 0}; // 0101 (5)
    Binary c{1, 0, 0, 1}; // 1001 (9)
    
    EXPECT_TRUE(a.equals(c));
    EXPECT_FALSE(a.equals(b));
    
    EXPECT_TRUE(a.greaterThan(b));
    EXPECT_FALSE(b.greaterThan(a));
    
    EXPECT_TRUE(b.lessThan(a));
    EXPECT_FALSE(a.lessThan(b));
}

// вывод
TEST(BinaryTest, Output) {
    Binary binary{1, 0, 1, 1};
    
    EXPECT_EQ(binary.toString(), "1011");
    
    std::ostringstream oss;
    binary.print(oss);
    EXPECT_EQ(oss.str(), "1011");
}

// дополнительные тесты
TEST(BinaryTest, EdgeCases) {
    Binary empty;
    EXPECT_EQ(empty.getSize(), 0);
    EXPECT_THROW(empty.getBit(0), std::out_of_range);
    
    Binary single{1};
    EXPECT_EQ(single.getSize(), 1);
    EXPECT_EQ(single.getBit(0), 1);
    
    Binary zeros{0, 0, 0, 0};
    for (size_t i = 0; i < 4; ++i) {
        EXPECT_EQ(zeros.getBit(i), 0);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}