// Copyright 2026 Ryabov M

#include <gtest/gtest.h>
#include "../lib_easy_example/easy_example.h"

#define CHECK_BRECKETS_TESTS

#ifdef CHECK_BRECKETS_TESTS

TEST(test_check_br, test_easy_good) {
    std::string tmp1 = "()";
    std::string tmp2 = "[]";
    std::string tmp3 = "{}";
    EXPECT_TRUE(check_breckets(tmp1));
    EXPECT_TRUE(check_breckets(tmp2));
    EXPECT_TRUE(check_breckets(tmp3));
}

TEST(test_check_br, test_easy_bad) {
    std::string tmp1 = "())";
    std::string tmp2 = "[]]";
    std::string tmp3 = "{}}";
    EXPECT_FALSE(check_breckets(tmp1));
    EXPECT_FALSE(check_breckets(tmp2));
    EXPECT_FALSE(check_breckets(tmp3));
}
#endif