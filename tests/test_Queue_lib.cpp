// Copyright 2026 Ryabov M

#include<gtest/gtest.h>
#include"../Queue_lib/Queue.h"
#include<string>

TEST(QueueTest, CtorAndEmpty) {
    Queue<int> q(5);
    EXPECT_EQ(q.size(), size_t(5));
    EXPECT_TRUE(q.is_empty());
    EXPECT_FALSE(q.is_full());
}

TEST(QueueTest, FrontOnEmptyThrows) {
    Queue<int> q(3);
    EXPECT_THROW(q.front(), std::logic_error);
}

TEST(QueueTest, PopOnEmptyThrows) {
    Queue<int> q(3);
    EXPECT_THROW(q.pop(), std::logic_error);
    EXPECT_TRUE(q.is_empty());
}
TEST(QueueTest, PushPopFifo) {
    Queue<int> q(5);
    q.push(1);
    q.push(2);
    q.push(3);

    EXPECT_EQ(q.pop(), 1);
    EXPECT_EQ(q.pop(), 2);
    EXPECT_EQ(q.pop(), 3);
    EXPECT_TRUE(q.is_empty());
}

TEST(QueueTest, FrontIsOldest) {
    Queue<int> q(5);
    q.push(10);
    q.push(20);
    q.push(30);

    EXPECT_EQ(q.front(), 10);
    q.pop();
    EXPECT_EQ(q.front(), 20);
    q.pop();
    EXPECT_EQ(q.front(), 30);
}

TEST(QueueTest, FrontDoesNotPop) {
    Queue<int> q(5);
    q.push(7);
    EXPECT_EQ(q.front(), 7);
    EXPECT_EQ(q.front(), 7);
    EXPECT_FALSE(q.is_empty());
    EXPECT_EQ(q.pop(), 7);
}

TEST(QueueTest, FrontReturnsReference) {
    Queue<int> q(5);
    q.push(1);
    q.push(2);
    q.front() = 100;
    EXPECT_EQ(q.pop(), 100);
    EXPECT_EQ(q.pop(), 2);
}
TEST(QueueTest, PushToFullThrows) {
    Queue<int> q(3);
    q.push(1);
    q.push(2);
    q.push(3);
    EXPECT_TRUE(q.is_full());

    EXPECT_THROW(q.push(4), std::logic_error);
    EXPECT_EQ(q.pop(), 1);
    EXPECT_EQ(q.pop(), 2);
    EXPECT_EQ(q.pop(), 3);
    EXPECT_TRUE(q.is_empty());
}

TEST(QueueTest, PopEmptyAfterDrain) {
    Queue<int> q(2);
    q.push(1);
    q.push(2);
    q.pop();
    q.pop();
    EXPECT_TRUE(q.is_empty());
    EXPECT_THROW(q.pop(), std::logic_error);
}
TEST(QueueTest, WrapAroundKeepsFifo) {
    Queue<int> q(3);
    q.push(1); q.push(2); q.push(3);
    EXPECT_EQ(q.pop(), 1);
    EXPECT_EQ(q.pop(), 2);

    q.push(4);
    q.push(5);

    EXPECT_EQ(q.pop(), 3);
    EXPECT_EQ(q.pop(), 4);
    EXPECT_EQ(q.pop(), 5);
    EXPECT_TRUE(q.is_empty());
}

TEST(QueueTest, RepeatedFillDrain) {
    Queue<int> q(3);
    int pushed = 0;
    int expected = 1;
    for (int round = 0; round < 10; ++round) {
        while (!q.is_full()) q.push(++pushed);
        while (!q.is_empty()) {
            EXPECT_EQ(q.pop(), expected);
            ++expected;
        }
    }
    EXPECT_EQ(pushed, 30);
}

TEST(QueueTest, InterleavedPushPop) {
    Queue<int> q(3);
    q.push(1);
    q.push(2);
    EXPECT_EQ(q.pop(), 1);
    q.push(3);
    q.push(4);
    EXPECT_TRUE(q.is_full());
    EXPECT_EQ(q.pop(), 2);
    EXPECT_EQ(q.pop(), 3);
    q.push(5);
    EXPECT_EQ(q.pop(), 4);
    EXPECT_EQ(q.pop(), 5);
    EXPECT_TRUE(q.is_empty());
}

TEST(QueueTest, SizeOne) {
    Queue<int> q(1);
    EXPECT_TRUE(q.is_empty());
    q.push(42);
    EXPECT_TRUE(q.is_full());
    EXPECT_EQ(q.front(), 42);
    EXPECT_EQ(q.pop(), 42);
    EXPECT_TRUE(q.is_empty());
    EXPECT_THROW(q.pop(), std::logic_error);

    q.push(7);
    EXPECT_EQ(q.pop(), 7);
}
TEST(QueueTest, CopyConstructorPreservesOrder) {
    Queue<int> a(5);
    a.push(1);
    a.push(2);
    a.push(3);

    Queue<int> b(a);

    EXPECT_EQ(b.pop(), 1);
    EXPECT_EQ(b.pop(), 2);
    EXPECT_EQ(b.pop(), 3);
    EXPECT_TRUE(b.is_empty());
    EXPECT_FALSE(a.is_empty());
    EXPECT_EQ(a.pop(), 1);
    EXPECT_EQ(a.pop(), 2);
    EXPECT_EQ(a.pop(), 3);
}

TEST(QueueTest, CopyIsIndependent) {
    Queue<int> a(3);
    a.push(1);
    a.push(2);

    Queue<int> b(a);
    a.push(3);

    EXPECT_EQ(b.pop(), 1);
    EXPECT_EQ(b.pop(), 2);
    EXPECT_TRUE(b.is_empty());

    EXPECT_EQ(a.pop(), 1);
    EXPECT_EQ(a.pop(), 2);
    EXPECT_EQ(a.pop(), 3);
}

TEST(QueueTest, CopyEmpty) {
    Queue<int> a(5);
    Queue<int> b(a);
    EXPECT_TRUE(b.is_empty());
    EXPECT_EQ(b.size(), size_t(5));
    b.push(1);
    EXPECT_EQ(b.pop(), 1);
    EXPECT_TRUE(a.is_empty());
}

TEST(QueueTest, CopyFull) {
    Queue<int> a(3);
    a.push(1); a.push(2); a.push(3);

    Queue<int> b(a);
    EXPECT_TRUE(b.is_full());
    EXPECT_EQ(b.pop(), 1);
    EXPECT_EQ(b.pop(), 2);
    EXPECT_EQ(b.pop(), 3);
}

TEST(QueueTest, CopyWithWrapAround) {
    Queue<int> a(3);
    a.push(1); a.push(2); a.push(3);
    a.pop();
    a.push(4);

    Queue<int> b(a);
    EXPECT_EQ(b.pop(), 2);
    EXPECT_EQ(b.pop(), 3);
    EXPECT_EQ(b.pop(), 4);
    EXPECT_TRUE(b.is_empty());

    EXPECT_EQ(a.pop(), 2);
    EXPECT_EQ(a.pop(), 3);
    EXPECT_EQ(a.pop(), 4);
}

TEST(QueueTest, CopyPartialWrap) {
    Queue<int> a(5);
    a.push(1); a.push(2); a.push(3);
    a.pop(); a.pop();
    a.push(4); a.push(5);
    a.push(6);

    Queue<int> b(a);
    EXPECT_EQ(b.pop(), 3);
    EXPECT_EQ(b.pop(), 4);
    EXPECT_EQ(b.pop(), 5);
    EXPECT_EQ(b.pop(), 6);
}
TEST(QueueTest, WorksWithStrings) {
    Queue<std::string> q(3);
    q.push("alpha");
    q.push("beta");
    EXPECT_EQ(q.front(), "alpha");
    EXPECT_EQ(q.pop(), "alpha");
    q.push("gamma");
    EXPECT_EQ(q.pop(), "beta");
    EXPECT_EQ(q.pop(), "gamma");
    EXPECT_TRUE(q.is_empty());
}

TEST(QueueTest, CopyWithStrings) {
    Queue<std::string> a(3);
    a.push("a"); a.push("b"); a.push("c");
    a.pop();
    a.push("d");

    Queue<std::string> b(a);
    EXPECT_EQ(b.pop(), "b");
    EXPECT_EQ(b.pop(), "c");
    EXPECT_EQ(b.pop(), "d");
}
