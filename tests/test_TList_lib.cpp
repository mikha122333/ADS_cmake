// Copyright 2026 Ryabov M

#include <gtest/gtest.h>
#include "../List_lib/TList.h"

TEST(ListTest, CtorAndSize) {
    List<int> l;
    EXPECT_TRUE(l.is_empty());
    EXPECT_EQ(l.size(), 0);

    Node<int>* n = l.push_back(10);
    ASSERT_NE(n, nullptr);
    EXPECT_EQ(n->_data, 10);
    EXPECT_FALSE(l.is_empty());
    EXPECT_EQ(l.size(), 1);
}

TEST(ListTest, PushFrontPushBackPop) {
    List<int> l;

    l.push_front(2);
    l.push_front(1);
    l.push_back(3);

    EXPECT_EQ(l.size(), 3);

    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_back(), 3);
    EXPECT_EQ(l.pop_front(), 2);

    EXPECT_TRUE(l.is_empty());
    EXPECT_EQ(l.size(), 0);
}

TEST(ListTest, InsertByIndex) {
    List<int> l;
    l.push_back(1);
    l.push_back(3);

    Node<int>* n = l.insert(2, 1);
    ASSERT_NE(n, nullptr);
    EXPECT_EQ(n->_data, 2);
    EXPECT_EQ(l.size(), 3);

    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 3);
}

TEST(ListTest, InsertBeginAndEnd) {
    List<int> l;
    l.push_back(2);

    l.insert(1, static_cast<size_t>(0));
    l.insert(3, l.size());

    EXPECT_EQ(l.size(), 3);
    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 3);
}

TEST(ListTest, InsertIntoEmpty) {
    List<int> l;
    Node<int>* n = l.insert(5, static_cast<size_t>(0));
    ASSERT_NE(n, nullptr);
    EXPECT_EQ(l.size(), 1);
    EXPECT_EQ(l.pop_front(), 5);
    EXPECT_TRUE(l.is_empty());
}

TEST(ListTest, InsertAfterNode) {
    List<int> l;

    Node<int>* a = l.push_back(1);
    Node<int>* c = l.push_back(3);

    l.insert(2, a);

    EXPECT_EQ(l.size(), 3);
    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 3);
}

TEST(ListTest, InsertAfterLastNodeUpdatesLast) {
    List<int> l;
    Node<int>* a = l.push_back(1);

    l.insert(2, a);

    EXPECT_EQ(l.size(), 2);
    EXPECT_EQ(l.pop_back(), 2);
    EXPECT_EQ(l.pop_back(), 1);
    EXPECT_TRUE(l.is_empty());
}

TEST(ListTest, EraseByIndex) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    EXPECT_EQ(l.erase(1), 2);
    EXPECT_EQ(l.size(), 2);
    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 3);
}

TEST(ListTest, EraseFirstAndLastByIndex) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    EXPECT_EQ(l.erase(static_cast<size_t>(0)), static_cast<size_t>(1));
    EXPECT_EQ(l.size(), 2);

    EXPECT_EQ(l.erase(l.size() - 1), 3);
    EXPECT_EQ(l.size(), 1);

    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_TRUE(l.is_empty());
}

TEST(ListTest, EraseOnlyElementByIndex) {
    List<int> l;
    l.push_back(42);

    EXPECT_EQ(l.erase(static_cast<size_t>(0)), 42);
    EXPECT_TRUE(l.is_empty());
}

TEST(ListTest, EraseMiddleNodeDecrementsSize) {
    List<int> l;
    Node<int>* a = l.push_back(1);
    Node<int>* b = l.push_back(2);
    Node<int>* c = l.push_back(3);

    EXPECT_EQ(l.erase(b), 2);
    EXPECT_EQ(l.size(), 2);

    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_back(), 3);
    EXPECT_TRUE(l.is_empty());
}

TEST(ListTest, EraseFirstByNode) {
    List<int> l;
    Node<int>* a = l.push_back(1);
    Node<int>* b = l.push_back(2);

    EXPECT_EQ(l.erase(a), 1);
    EXPECT_EQ(l.size(), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_TRUE(l.is_empty());
}

TEST(ListTest, EraseLastByNode) {
    List<int> l;
    Node<int>* a = l.push_back(1);
    Node<int>* b = l.push_back(2);

    EXPECT_EQ(l.erase(b), 2);
    EXPECT_EQ(l.size(), 1);
    EXPECT_EQ(l.pop_back(), 1);
    EXPECT_TRUE(l.is_empty());
}

TEST(ListTest, EraseOnlyByNode) {
    List<int> l;
    Node<int>* a = l.push_back(7);

    EXPECT_EQ(l.erase(a), 7);
    EXPECT_TRUE(l.is_empty());
}

TEST(ListTest, Find) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    Node<int>* n = l.find(2);
    ASSERT_NE(n, nullptr);
    EXPECT_EQ(n->_data, 2);

    EXPECT_EQ(l.find(42), nullptr);

    List<int> empty;
    EXPECT_EQ(empty.find(1), nullptr);
}

TEST(ListTest, FindFirstAndLast) {
    List<int> l;
    l.push_back(10);
    l.push_back(20);
    l.push_back(10);

    Node<int>* first10 = l.find(10);
    ASSERT_NE(first10, nullptr);
    EXPECT_EQ(first10->_data, 10);

    Node<int>* last10 = l.find(20);
    ASSERT_NE(last10, nullptr);
    EXPECT_EQ(last10->_data, 20);
}

TEST(ListTest, Exceptions) {
    List<int> empty;

    EXPECT_THROW(empty.pop_front(), std::logic_error);
    EXPECT_THROW(empty.pop_back(), std::logic_error);

    List<int> l;
    l.push_back(1);

    EXPECT_THROW(l.insert(2, l.size() + 1), std::out_of_range);
    EXPECT_THROW(l.erase(l.size()), std::out_of_range);
    EXPECT_THROW(l.erase(static_cast<Node<int>*>(nullptr)), std::logic_error);
}
