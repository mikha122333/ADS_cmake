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
    EXPECT_ANY_THROW(Stack<int> tmp(0));
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
TEST(test_stack, push_to_full) {
    Stack<int> tmp(1);
    tmp.push(1);
    EXPECT_ANY_THROW(tmp.push(2121));
}
TEST(test_stack, pop_from_empty) {
    Stack<int> tmp(1);
    EXPECT_ANY_THROW(tmp.pop());
}
TEST(test_stack, is_push_pop_front_okay) {
    Stack<int> tmp(5);
    for (int i = 0; i < 15; i++) {
        tmp.push(i);
        if(tmp.is_full())
            for (int i2 = 0; i2 < 5; i2++) {
                EXPECT_EQ(tmp.pop(), i - i2);
            }
    }
    EXPECT_TRUE(tmp.is_empty());
}
#endif
