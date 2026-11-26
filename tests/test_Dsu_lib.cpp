// Copyright 2026 Ryabov M

#include<gtest/gtest.h>

#include"../Dsu_lib/Dsu_lib.h"

TEST(dsu_tests, test_find_1) {
    Dsu d1(10);
    for (size_t i = 1; i < 11; i++) {
        EXPECT_EQ(d1.find(i), i);
    }
}

TEST(dsu_tests, test_find_2) {
    Dsu d1(10);
    d1.t_union(9, 10);
    for (size_t i = 1; i < 9; i++) {
        EXPECT_EQ(d1.find(i), i);
    }
    EXPECT_EQ(d1.find(9), 9);
    EXPECT_EQ(d1.find(10), 9);
}

TEST(dsu_tests, test_find_3) {
    Dsu d1(10);
    d1.t_union(9, 10);
    d1.t_union(10, 8);
    for (size_t i = 1; i < 8; i++) {
        EXPECT_EQ(d1.find(i), i);
    }
    EXPECT_EQ(d1.find(9), 9);
    EXPECT_EQ(d1.find(10), 9);
    EXPECT_EQ(d1.find(8), 9);
}

TEST(dsu_tests, test_find_4) {
    Dsu d1(10);
    d1.t_union(9, 10);
    d1.t_union(7, 8);
    d1.t_union(7, 10);
    for (size_t i = 1; i < 7; i++) {
        EXPECT_EQ(d1.find(i), i);
    }
    EXPECT_EQ(d1.find(9), 7);
    EXPECT_EQ(d1.find(10), 7);
    EXPECT_EQ(d1.find(8), 7);
    EXPECT_EQ(d1.find(7), 7);
}

TEST(dsu_tests, test_find_5) {
    Dsu d1(10);
    d1.t_union(7, 8);
    d1.t_union(10, 7);
    for (size_t i = 1; i < 7; i++) {
        EXPECT_EQ(d1.find(i), i);
    };
    EXPECT_EQ(d1.find(10), 7);
    EXPECT_EQ(d1.find(8), 7);
    EXPECT_EQ(d1.find(7), 7);
}