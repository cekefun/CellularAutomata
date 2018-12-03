#include "cellular-automata/storage-basic.hpp"

#include <functional>

#include <gtest/gtest.h>

using namespace CellularAutomata;

namespace {
template<typename T>
void doInitTest(std::int32_t minX, std::int32_t minY, std::int32_t maxX, std::int32_t maxY, const T & def) {
    Fixed2DStorage<T> storageA(std::make_pair(minX, minY), std::make_pair(maxX, maxY), def);
    Fixed2DStorage<T> storageB(minX, minY, maxX, maxY, def);

    std::int32_t sizeX = maxX - minX;
    std::int32_t sizeY = maxY - minY;

    ASSERT_EQ(sizeX * sizeY, storageA.size());
    ASSERT_EQ(sizeX * sizeY, storageB.size());

    for (std::int32_t i = minX; i < maxX; ++i) {
        for (std::int32_t j = minY; j < maxY; ++j) {
            EXPECT_EQ(def, storageA(i, j));
            EXPECT_EQ(def, storageB(i, j));
        }
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
void doWriteTest(std::int32_t minX, std::int32_t minY, std::int32_t maxX, std::int32_t maxY, std::function<T(std::int32_t, std::int32_t)> valueFunc) {
    T defaultValue {};

    Fixed2DStorage<T> storageA(std::make_pair(minX, minY), std::make_pair(maxX, maxY), defaultValue);
    Fixed2DStorage<T> storageB(minX, minY, maxX, maxY, defaultValue);

    std::int32_t sizeX = maxX - minX;
    std::int32_t sizeY = maxY - minY;

    ASSERT_EQ(sizeX * sizeY, storageA.size());
    ASSERT_EQ(sizeX * sizeY, storageB.size());

    for (std::int32_t i = minX; i < maxX; ++i) {
        for (std::int32_t j = minY; j < maxY; ++j) {
            storageA(i, j) = valueFunc(i, j);
            storageB(i, j) = valueFunc(i, j);
        }
    }

    for (std::int32_t i = minX; i < maxX; ++i) {
        for (std::int32_t j = minY; j < maxY; ++j) {
            EXPECT_EQ(valueFunc(i, j), storageA(i, j));
            EXPECT_EQ(valueFunc(i, j), storageB(i, j));
        }
    }
}

struct TestWritesShowThroughStructType {
    std::int32_t x;
    std::int32_t y;
};

bool operator==(const TestWritesShowThroughStructType & lhs, const TestWritesShowThroughStructType & rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
}

TEST(Fixed2DStorage, PairConstructor) {
    Fixed2DStorage<bool> storageA(std::make_pair(0, 0), std::make_pair(4, 4), false);

    EXPECT_EQ(4 * 4, storageA.size());

    Fixed2DStorage<bool> storageB(std::make_pair(-4, -4), std::make_pair(0, 0), false);

    EXPECT_EQ(4 * 4, storageB.size());

    Fixed2DStorage<bool> storageC(std::make_pair(-2, -2), std::make_pair(2, 2), false);

    EXPECT_EQ(4 * 4, storageC.size());
}

TEST(Fixed2DStorage, PiecewiseConstructor) {
    Fixed2DStorage<bool> storageA(0, 0, 4, 4, false);

    EXPECT_EQ(4 * 4, storageA.size());

    Fixed2DStorage<bool> storageB(-4, -4, 0, 0, false);

    EXPECT_EQ(4 * 4, storageB.size());

    Fixed2DStorage<bool> storageC(-2, -2, 2, 2, false);

    EXPECT_EQ(4 * 4, storageC.size());
}

TEST(Fixed2DStorage, ConstructorZeroSize) {
    EXPECT_ANY_THROW(Fixed2DStorage<bool>(std::make_pair(4, 0), std::make_pair(4, 4), false));
    EXPECT_ANY_THROW(Fixed2DStorage<bool>(std::make_pair(0, 4), std::make_pair(4, 4), false));

    EXPECT_ANY_THROW(Fixed2DStorage<bool>(std::make_pair(-4, -4), std::make_pair(-4, 0), false));
    EXPECT_ANY_THROW(Fixed2DStorage<bool>(std::make_pair(-4, -4), std::make_pair(0, -4), false));

    EXPECT_ANY_THROW(Fixed2DStorage<bool>(std::make_pair(0, -2), std::make_pair(0, 2), false));
    EXPECT_ANY_THROW(Fixed2DStorage<bool>(std::make_pair(-2, 0), std::make_pair(2, 0), false));
}

TEST(Fixed2DStorage, ConstructorNegativeSize) {
    EXPECT_ANY_THROW(Fixed2DStorage<bool>(std::make_pair(4, 0), std::make_pair(0, 4), false));
    EXPECT_ANY_THROW(Fixed2DStorage<bool>(std::make_pair(0, 4), std::make_pair(4, 0), false));

    EXPECT_ANY_THROW(Fixed2DStorage<bool>(std::make_pair(0, -4), std::make_pair(-4, 0), false));
    EXPECT_ANY_THROW(Fixed2DStorage<bool>(std::make_pair(-4, 0), std::make_pair(0, -4), false));

    EXPECT_ANY_THROW(Fixed2DStorage<bool>(std::make_pair(2, -2), std::make_pair(-2, 2), false));
    EXPECT_ANY_THROW(Fixed2DStorage<bool>(std::make_pair(-2, 2), std::make_pair(2, -2), false));
}

TEST(Fixed2DStorage, InitNativeType) {
    using ValueType = double;
    ValueType defaultValue(3.14159265358979323846);

    doInitTest(+0, +0, +4, +4, defaultValue);
    doInitTest(-4, -4, +0, +0, defaultValue);
    doInitTest(-2, -2, +2, +2, defaultValue);

    doInitTest(-128, 0, 128, 256, defaultValue);
}

TEST(Fixed2DStorage, InitValueTypePair) {
    using ValueType = std::pair<int, double>;
    ValueType defaultValue(42, 3.14159265358979323846);

    doInitTest(+0, +0, +4, +4, defaultValue);
    doInitTest(-4, -4, +0, +0, defaultValue);
    doInitTest(-2, -2, +2, +2, defaultValue);

    doInitTest(-128, 0, 128, 256, defaultValue);
}

TEST(Fixed2DStorage, InitStruct) {
    using ValueType = TestInitStructValueType;
    ValueType defaultValue { true, 42, 3.14159265358979323846 };

    doInitTest(+0, +0, +4, +4, defaultValue);
    doInitTest(-4, -4, +0, +0, defaultValue);
    doInitTest(-2, -2, +2, +2, defaultValue);

    doInitTest(-128, 0, 128, 256, defaultValue);
}

TEST(Fixed2DStorage, WritesShowThrough) {
    using ValueType = std::uint64_t;

    std::function<ValueType(std::int32_t, std::int32_t)> valueFunc = [](std::int32_t x, std::int32_t y) -> ValueType {
        return ((static_cast<std::uint64_t>(x) << 32) & 0xFFFFFFFF00000000) | (static_cast<std::uint64_t>(y) & 0xFFFFFFFF);
    };

    doWriteTest(+0, +0, +4, +4, valueFunc);
    doWriteTest(-4, -4, +0, +0, valueFunc);
    doWriteTest(-2, -2, +2, +2, valueFunc);

    doWriteTest(-128, 0, 128, 256, valueFunc);
}

TEST(Fixed2DStorage, WritesShowThroughStruct) {
    using ValueType = TestWritesShowThroughStructType;

    std::function<ValueType(std::int32_t, std::int32_t)> valueFunc = [](std::int32_t x, std::int32_t y) -> ValueType {
        return { x, y };
    };

    doWriteTest(+0, +0, +4, +4, valueFunc);
    doWriteTest(-4, -4, +0, +0, valueFunc);
    doWriteTest(-2, -2, +2, +2, valueFunc);

    doWriteTest(-128, 0, 128, 256, valueFunc);
}
