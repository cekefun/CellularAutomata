#include "cellular-automata/storage-basic.hpp"

#include <functional>

#include <gtest/gtest.h>

using namespace CellularAutomata;

namespace {
template<typename T>
void doInitTest(std::int32_t min, std::int32_t max, const T & def) {
    Fixed1DStorage<T> storageA(min, max, def);

    std::int32_t size = max - min;

    ASSERT_EQ(size, storageA.size());

    for (std::int32_t i = min; i < max; ++i) {
        EXPECT_EQ(def, storageA(i));
    }
}

struct TestInitStructValueType {
    bool b;
    int i;
    double d;
};

bool operator==(const TestInitStructValueType & lhs, const TestInitStructValueType & rhs) {
    return lhs.b == rhs.b && lhs.i == rhs.i && lhs.d == rhs.d;
}

template<typename T>
void doWriteTest(std::int32_t min, std::int32_t max, std::function<T(std::int32_t)> valueFunc) {
    T defaultValue {};

    Fixed1DStorage<T> storageA(min, max, defaultValue);

    std::int32_t size = max - min;

    ASSERT_EQ(size, storageA.size());

    for (std::int32_t i = min; i < max; ++i) {
        storageA(i) = valueFunc(i);
    }

    for (std::int32_t i = min; i < max; ++i) {
        EXPECT_EQ(valueFunc(i), storageA(i));
    }
}

struct TestWritesShowThroughStructType {
    std::uint32_t a;
    std::uint32_t b;
};

bool operator==(const TestWritesShowThroughStructType & lhs, const TestWritesShowThroughStructType & rhs) {
    return lhs.a == rhs.a && lhs.b == rhs.b;
}
}

TEST(Fixed1DStorage, Constructor) {
    Fixed1DStorage<bool> storageA(0, 4, false);

    EXPECT_EQ(4, storageA.size());

    Fixed1DStorage<bool> storageB(-4, 0, false);

    EXPECT_EQ(4, storageB.size());

    Fixed1DStorage<bool> storageC(-2, 2, false);

    EXPECT_EQ(4, storageC.size());
}

TEST(Fixed1DStorage, ConstructorZeroSize) {
    EXPECT_ANY_THROW(Fixed1DStorage<bool>(4, 4, false));
    EXPECT_ANY_THROW(Fixed1DStorage<bool>(-4, -4, false));
    EXPECT_ANY_THROW(Fixed1DStorage<bool>(0, 0, false));
}

TEST(Fixed1DStorage, ConstructorNegativeSize) {
    EXPECT_ANY_THROW(Fixed1DStorage<bool>(4, 0, false));
    EXPECT_ANY_THROW(Fixed1DStorage<bool>(0, -4, false));
    EXPECT_ANY_THROW(Fixed1DStorage<bool>(2, -2, false));
}

TEST(Fixed1DStorage, InitNativeType) {
    using ValueType = double;
    ValueType defaultValue(3.14159265358979323846);

    doInitTest(+0, +4, defaultValue);
    doInitTest(-4, +0, defaultValue);
    doInitTest(-2, +2, defaultValue);

    doInitTest(-128, 256, defaultValue);
}

TEST(Fixed1DStorage, InitValueTypePair) {
    using ValueType = std::pair<int, double>;
    ValueType defaultValue(42, 3.14159265358979323846);

    doInitTest(+0, +4, defaultValue);
    doInitTest(-4, +0, defaultValue);
    doInitTest(-2, +2, defaultValue);

    doInitTest(-128, 256, defaultValue);
}

TEST(Fixed1DStorage, InitStruct) {
    using ValueType = TestInitStructValueType;
    ValueType defaultValue { true, 42, 3.14159265358979323846 };

    doInitTest(+0, +4, defaultValue);
    doInitTest(-4, +0, defaultValue);
    doInitTest(-2, +2, defaultValue);

    doInitTest(-128, 256, defaultValue);
}

TEST(Fixed1DStorage, WritesShowThrough) {
    using ValueType = std::uint32_t;

    std::function<ValueType(std::int32_t)> valueFunc = [](std::int32_t i) -> ValueType {
        return ~static_cast<std::uint32_t>(i);
    };

    doWriteTest(+0, +4, valueFunc);
    doWriteTest(-4, +0, valueFunc);
    doWriteTest(-2, +2, valueFunc);

    doWriteTest(-128, 256, valueFunc);
}

TEST(Fixed1DStorage, WritesShowThroughStruct) {
    using ValueType = TestWritesShowThroughStructType;

    std::function<ValueType(std::int32_t)> valueFunc = [](std::int32_t i) -> ValueType {
        return { ~static_cast<std::uint32_t>(i), static_cast<std::uint32_t>(i) };
    };

    doWriteTest(+0, +4, valueFunc);
    doWriteTest(-4, +0, valueFunc);
    doWriteTest(-2, +2, valueFunc);

    doWriteTest(-128, 256, valueFunc);
}
