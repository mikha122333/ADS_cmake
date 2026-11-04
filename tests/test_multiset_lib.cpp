// Copyright 2026 Ryabov M

#include <gtest/gtest.h>
#include <set>
#include "../multiset_lib/multiset.h"

TEST(MultistackTest, CtorAndEmpty) {
    multiset<int> ms(10, 3);
    EXPECT_TRUE(ms.is_empty());
    EXPECT_TRUE(ms.is_empty(0));
    EXPECT_TRUE(ms.is_empty(1));
    EXPECT_TRUE(ms.is_empty(2));
    EXPECT_FALSE(ms.is_full());
    EXPECT_FALSE(ms.is_full(0));
}

TEST(MultistackTest, CtorDefaultAmount) {
    multiset<int> ms(5);
    EXPECT_TRUE(ms.is_empty());
    EXPECT_FALSE(ms.is_full());
    ms.push(0, 42);
    EXPECT_FALSE(ms.is_empty());
    EXPECT_EQ(ms.top(0), 42);
}

TEST(MultistackTest, PushPopTopLifo) {
    multiset<int> ms(10, 2);
    ms.push(0, 1);
    ms.push(0, 2);
    ms.push(0, 3);

    EXPECT_EQ(ms.top(0), 3);
    EXPECT_EQ(ms.pop(0), 3);
    EXPECT_EQ(ms.top(0), 2);
    EXPECT_EQ(ms.pop(0), 2);
    EXPECT_EQ(ms.top(0), 1);
    EXPECT_EQ(ms.pop(0), 1);
    EXPECT_TRUE(ms.is_empty(0));
    EXPECT_TRUE(ms.is_empty(1));
}

TEST(MultistackTest, SetsAreIndependent) {
    multiset<int> ms(10, 3);
    ms.push(0, 10);
    ms.push(1, 20);
    ms.push(2, 30);

    EXPECT_EQ(ms.top(0), 10);
    EXPECT_EQ(ms.top(1), 20);
    EXPECT_EQ(ms.top(2), 30);

    ms.pop(1);
    EXPECT_TRUE(ms.is_empty(1));
    EXPECT_FALSE(ms.is_empty(0));
    EXPECT_FALSE(ms.is_empty(2));
}

TEST(MultistackTest, TopReturnsReference) {
    multiset<int> ms(5, 1);
    ms.push(0, 1);
    ms.top(0) = 99;
    EXPECT_EQ(ms.top(0), 99);
    EXPECT_EQ(ms.pop(0), 99);
}

TEST(MultistackTest, TopDoesNotPop) {
    multiset<int> ms(5, 1);
    ms.push(0, 1);
    ms.push(0, 2);
    EXPECT_EQ(ms.top(0), 2);
    EXPECT_EQ(ms.top(0), 2);
    EXPECT_EQ(ms.pop(0), 2);
    EXPECT_EQ(ms.pop(0), 1);
}
TEST(MultistackTest, TopPopOnEmptyThrows) {
    multiset<int> ms(5, 2);
    EXPECT_THROW(ms.top(0), std::out_of_range);
    EXPECT_THROW(ms.pop(0), std::out_of_range);
    EXPECT_THROW(ms.top(1), std::out_of_range);
    EXPECT_THROW(ms.pop(1), std::out_of_range);
}

TEST(MultistackTest, InvalidSetIndexThrows) {
    multiset<int> ms(10, 3);
    EXPECT_THROW(ms.push(3, 1), std::out_of_range);
    EXPECT_THROW(ms.top(3), std::out_of_range);
    EXPECT_THROW(ms.pop(3), std::out_of_range);
    EXPECT_THROW(ms.is_empty(3), std::out_of_range);
    EXPECT_THROW(ms.is_full(3), std::out_of_range);
    EXPECT_THROW(ms.push(100, 1), std::out_of_range);
}

TEST(MultistackTest, EmptyAndFullAggregates) {
    multiset<int> ms(6, 2);

    ms.push(0, 1);
    EXPECT_FALSE(ms.is_empty());
    EXPECT_FALSE(ms.is_full());

    ms.push(0, 2);
    ms.push(0, 3);
    EXPECT_TRUE(ms.is_full(0));
    EXPECT_FALSE(ms.is_full());

    ms.push(1, 10);
    ms.push(1, 20);
    ms.push(1, 30);
    EXPECT_TRUE(ms.is_full(1));
    EXPECT_TRUE(ms.is_full());

    ms.pop(0);
    EXPECT_FALSE(ms.is_full());
}

TEST(MultistackTest, RepackagePreservesLifoOrder) {
    multiset<int> ms(6, 2);
    ms.push(1, 10);
    ms.push(1, 20);
    ms.push(1, 30);
    EXPECT_TRUE(ms.is_full(1));

    ms.push(1, 40);

    EXPECT_EQ(ms.pop(1), 40);
    EXPECT_EQ(ms.pop(1), 30);
    EXPECT_EQ(ms.pop(1), 20);
    EXPECT_EQ(ms.pop(1), 10);
    EXPECT_TRUE(ms.is_empty(1));

    EXPECT_TRUE(ms.is_empty(0));
}

TEST(MultistackTest, RepackageKeepsAllSetsNonEmpty) {
    multiset<int> ms(10, 3);
    for (int i = 0; i < 3; ++i) ms.push(0, i);

    EXPECT_TRUE(ms.is_full(0));
    ms.push(0, 100);
    ms.push(0, 101);
    ms.push(0, 102);
    ms.push(0, 103);

    EXPECT_EQ(ms.pop(0), 103);
    EXPECT_EQ(ms.pop(0), 102);
    EXPECT_EQ(ms.pop(0), 101);
    EXPECT_EQ(ms.pop(0), 100);
    EXPECT_EQ(ms.pop(0), 2);
    EXPECT_EQ(ms.pop(0), 1);
    EXPECT_EQ(ms.pop(0), 0);

    EXPECT_NO_THROW(ms.push(1, 7));
    EXPECT_EQ(ms.pop(1), 7);
    EXPECT_NO_THROW(ms.push(2, 8));
    EXPECT_EQ(ms.pop(2), 8);
}

TEST(MultistackTest, RepackageFailsWhenNoFreeSlot) {
    multiset<int> ms(3, 3);
    ms.push(0, 1);
    ms.push(1, 2);
    EXPECT_TRUE(ms.is_full(0));
    EXPECT_TRUE(ms.is_full(1));

    EXPECT_THROW(ms.push(0, 3), std::logic_error);

    EXPECT_EQ(ms.pop(0), 1);
    EXPECT_EQ(ms.pop(1), 2);
}

TEST(MultistackTest, PushWhenTotallyFullThrows) {
    multiset<int> ms(3, 3);
    ms.push(0, 1);
    ms.push(1, 2);
    ms.push(2, 3);
    EXPECT_TRUE(ms.is_full());

    EXPECT_THROW(ms.push(0, 4), std::logic_error);

    EXPECT_EQ(ms.pop(0), 1);
    EXPECT_EQ(ms.pop(1), 2);
    EXPECT_EQ(ms.pop(2), 3);
}

TEST(MultistackTest, RepackageFromEmptyWithExtraSlot) {
    multiset<int> ms(4, 3);
    ms.push(0, 1);
    EXPECT_TRUE(ms.is_full(0));
    EXPECT_NO_THROW(ms.push(0, 2));
    EXPECT_EQ(ms.pop(0), 2);
    EXPECT_EQ(ms.pop(0), 1);
}

TEST(MultistackTest, CopyConstructorPreservesContent) {
    multiset<int> a(10, 2);
    a.push(0, 1);
    a.push(0, 2);
    a.push(1, 10);

    multiset<int> b(a);

    EXPECT_EQ(b.pop(0), 2);
    EXPECT_EQ(b.pop(0), 1);
    EXPECT_TRUE(b.is_empty(0));
    EXPECT_EQ(b.pop(1), 10);
    EXPECT_TRUE(b.is_empty(1));
    EXPECT_EQ(a.top(0), 2);
    EXPECT_FALSE(a.is_empty(0));
    EXPECT_EQ(a.top(1), 10);
}

TEST(MultistackTest, CopyConstructorDeepCopy) {
    multiset<int> a(5, 1);
    a.push(0, 1);
    a.push(0, 2);

    multiset<int> b(a);
    a.push(0, 3);

    EXPECT_EQ(b.pop(0), 2);
    EXPECT_EQ(b.pop(0), 1);
    EXPECT_TRUE(b.is_empty(0));

    EXPECT_EQ(a.pop(0), 3);
    EXPECT_EQ(a.pop(0), 2);
    EXPECT_EQ(a.pop(0), 1);
}
TEST(MultistackTest, StressInterleavedSets) {
    multiset<int> ms(10, 3);
    for (int i = 0; i < 10; ++i) {
        ms.push(i % 3, i);
    }
    EXPECT_TRUE(ms.is_full());

    for (int i = 9; i >= 0; --i) {
        EXPECT_EQ(ms.pop(i % 3), i);
    }
    EXPECT_TRUE(ms.is_empty());
}
