// Copyright 2026 Ryabov M

#include <gtest/gtest.h>
#include "../WIP_on_mass/TStack.h"

#define TSTACK_TESTS
#ifdef TSTACK_TESTS
TEST(test_stack, con_1) {
    Stack<int> tmp(5);
    EXPECT_TRUE(tmp.is_empty());
    EXPECT_FALSE(tmp.is_full());
}
TEST(test_stack, con_wrong) {
    EXPECT_ANY_THROW( Stack<int> tmp(0));
}
TEST(test_stack, con_copy) {
    Stack<int> tmp1(5);
    Stack<int> tmp(tmp1);
    EXPECT_TRUE(tmp.is_empty());
    EXPECT_FALSE(tmp.is_full());
}
TEST(test_stack, con_copy_dont_change) {
    Stack<int> tmp1(5);
    for (int i = 0; i < 2; i++) {
        tmp1.push(i);
    }
    Stack<int> tmp(tmp1);
    tmp.push(3);
    EXPECT_EQ(tmp1.pop(), 1);
    EXPECT_EQ(tmp1.pop(), 0);
    EXPECT_EQ(tmp.pop(), 3);
    EXPECT_EQ(tmp.pop(), 1);
    EXPECT_EQ(tmp.pop(), 0);
}
TEST(test_stack, con_copy_dont_change) {
    Stack<int> tmp1(5);
    for (int i = 0; i < 2; i++) {
        tmp1.push(i);
    }
    Stack<int> tmp(tmp1);
    tmp.push(3);
    EXPECT_EQ(tmp1.pop(), 1);
    EXPECT_EQ(tmp1.pop(), 0);
    EXPECT_EQ(tmp.pop(), 3);
    EXPECT_EQ(tmp.pop(), 1);
    EXPECT_EQ(tmp.pop(), 0);
}
#endif