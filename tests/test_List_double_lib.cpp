// TList_double_tests.cpp
#include <gtest/gtest.h>
#include "../List_double_lib/TList_double.h"

#define LIST_DOUBLE_TESTS
#ifdef LIST_DOUBLE_TESTS

TEST(ListDoubleTest, CtorAndSize) {
    List_double<int> l;
    EXPECT_TRUE(l.is_empty());
    EXPECT_EQ(l.size(), 0);

    Node<int>* n = l.push_back(10);
    ASSERT_NE(n, nullptr);
    EXPECT_EQ(n->_data, 10);
    EXPECT_FALSE(l.is_empty());
    EXPECT_EQ(l.size(), 1);
}

TEST(ListDoubleTest, PushFrontPushBackPop) {
    List_double<int> l;

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

TEST(ListDoubleTest, PushBackMaintainsPrev) {
    List_double<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    EXPECT_EQ(l.size(), 3);

    EXPECT_EQ(l.pop_back(), 3);
    EXPECT_EQ(l.pop_back(), 2);
    EXPECT_EQ(l.pop_back(), 1);

    EXPECT_TRUE(l.is_empty());
}

TEST(ListDoubleTest, InsertByIndex) {
    List_double<int> l;
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

TEST(ListDoubleTest, InsertBeginAndEnd) {
    List_double<int> l;
    l.push_back(2);

    l.insert(1, static_cast<size_t>(0));
    l.insert(3, l.size());

    EXPECT_EQ(l.size(), 3);
    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 3);
}

TEST(ListDoubleTest, InsertIntoEmpty) {
    List_double<int> l;
    l.insert(5, static_cast<size_t>(0));
    EXPECT_EQ(l.size(), 1);
    EXPECT_EQ(l.pop_front(), 5);
    EXPECT_TRUE(l.is_empty());
}

TEST(ListDoubleTest, InsertAfterNode) {
    List_double<int> l;

    Node<int>* a = l.push_back(1);
    Node<int>* c = l.push_back(3);

    l.insert(2, a);

    EXPECT_EQ(l.size(), 3);
    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 3);
}

TEST(ListDoubleTest, InsertAfterLastNodeUpdatesLast) {
    List_double<int> l;
    Node<int>* a = l.push_back(1);

    l.insert(2, a);

    EXPECT_EQ(l.size(), 2);
    EXPECT_EQ(l.pop_back(), 2);
    EXPECT_EQ(l.pop_back(), 1);
    EXPECT_TRUE(l.is_empty());
}

TEST(ListDoubleTest, InsertAfterMiddleMaintainsPrev) {
    List_double<int> l;

    Node<int>* a = l.push_back(1);
    Node<int>* c = l.push_back(3);

    l.insert(2, a);

    EXPECT_EQ(l.size(), 3);
    EXPECT_EQ(l.pop_back(), 3);
    EXPECT_EQ(l.pop_back(), 2);
    EXPECT_EQ(l.pop_back(), 1);
}

TEST(ListDoubleTest, EraseByIndex) {
    List_double<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    EXPECT_EQ(l.erase(1), 2);
    EXPECT_EQ(l.size(), 2);
    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 3);
}

TEST(ListDoubleTest, EraseFirstAndLastByIndex) {
    List_double<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    EXPECT_EQ(l.erase(static_cast<size_t>(0)), 1);
    EXPECT_EQ(l.size(), 2);

    EXPECT_EQ(l.erase(l.size() - 1), 3);
    EXPECT_EQ(l.size(), 1);

    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_TRUE(l.is_empty());
}

TEST(ListDoubleTest, EraseOnlyElementByIndex) {
    List_double<int> l;
    l.push_back(42);

    EXPECT_EQ(l.erase(static_cast<size_t>(0)), 42);
    EXPECT_TRUE(l.is_empty());
}

TEST(ListDoubleTest, EraseMiddleNodeDecrementsSize) {
    List_double<int> l;
    Node<int>* a = l.push_back(1);
    Node<int>* b = l.push_back(2);
    Node<int>* c = l.push_back(3);

    EXPECT_EQ(l.erase(b), 2);
    EXPECT_EQ(l.size(), 2);

    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_back(), 3);
    EXPECT_TRUE(l.is_empty());
}

TEST(ListDoubleTest, EraseFirstByNode) {
    List_double<int> l;
    Node<int>* a = l.push_back(1);
    Node<int>* b = l.push_back(2);

    EXPECT_EQ(l.erase(a), 1);
    EXPECT_EQ(l.size(), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_TRUE(l.is_empty());
}

TEST(ListDoubleTest, EraseLastByNode) {
    List_double<int> l;
    Node<int>* a = l.push_back(1);
    Node<int>* b = l.push_back(2);

    EXPECT_EQ(l.erase(b), 2);
    EXPECT_EQ(l.size(), 1);
    EXPECT_EQ(l.pop_back(), 1);
    EXPECT_TRUE(l.is_empty());
}

TEST(ListDoubleTest, EraseOnlyByNode) {
    List_double<int> l;
    Node<int>* a = l.push_back(7);

    EXPECT_EQ(l.erase(a), 7);
    EXPECT_TRUE(l.is_empty());
}

TEST(ListDoubleTest, Find) {
    List_double<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    Node<int>* n = l.find(2);
    ASSERT_NE(n, nullptr);
    EXPECT_EQ(n->_data, 2);

    EXPECT_EQ(l.find(42), nullptr);

    List_double<int> empty;
    EXPECT_EQ(empty.find(1), nullptr);
}

TEST(ListDoubleTest, FindFirstAndLast) {
    List_double<int> l;
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

TEST(ListDoubleTest, Exceptions) {
    List_double<int> empty;

    EXPECT_THROW(empty.pop_front(), std::logic_error);
    EXPECT_THROW(empty.pop_back(), std::logic_error);

    List_double<int> l;
    l.push_back(1);

    EXPECT_THROW(l.insert(2, l.size() + 1), std::out_of_range);
    EXPECT_THROW(l.erase(l.size()), std::out_of_range);
    EXPECT_THROW(l.erase(static_cast<Node<int>*>(nullptr)), std::logic_error);
}

TEST(ListDoubleTest, iterator_test_standart) {
    List_double<int> l;
    for (int i = 0; i < 20; i++) {
        l.push_back(i);
    }
    auto r = l.begin();
    for (int i = 0; i < 20; i++) {
        EXPECT_EQ(*r++, i);
    }
}

TEST(ListDoubleTest, iterator_test_except) {
    List_double<int> l;
    auto r = l.begin();
    EXPECT_ANY_THROW(r++);
    EXPECT_ANY_THROW(r += 3);
    EXPECT_ANY_THROW(r + 3);
}

TEST(ListDoubleTest, iterator_test_eq) {
    List_double<int> li;
    li.push_back(3);
    li.push_back(2);
    auto f = li.begin();
    auto l = li.end();
    EXPECT_FALSE(f == l);
    EXPECT_TRUE(f != l);
    f += 2;
    EXPECT_FALSE(f != l);
    EXPECT_TRUE(f == l);
}

TEST(ListDoubleTest, IteratorBackward) {
    List_double<int> l;
    for (int i = 0; i < 5; ++i) {
        l.push_back(i);
    }

    auto it = l.begin();
    it += 4;
    EXPECT_EQ(*it, 4);

    --it;
    EXPECT_EQ(*it, 3);

    it -= 2;
    EXPECT_EQ(*it, 1);

    auto post = it--;
    EXPECT_EQ(*post, 1);
    EXPECT_EQ(*it, 0);
}

TEST(ListDoubleTest, IteratorBackwardBeginThrows) {
    List_double<int> l;
    l.push_back(1);
    l.push_back(2);

    auto it = l.begin();
    EXPECT_THROW(--it, std::out_of_range);
    EXPECT_THROW(it--, std::out_of_range);
}

TEST(ListDoubleTest, IteratorBackwardEndThrows) {
    List_double<int> l;
    l.push_back(1);
    l.push_back(2);

    auto it = l.end();
    EXPECT_THROW(--it, std::out_of_range);
    EXPECT_THROW(it--, std::out_of_range);

    // -=
    auto it2 = l.end();
    EXPECT_THROW(it2 -= 1, std::out_of_range);
}

TEST(ListDoubleTest, IteratorBackwardFromSecond) {
    List_double<int> l;
    l.push_back(10);
    l.push_back(20);

    auto it = l.begin();
    ++it;
    EXPECT_EQ(*it, 20);

    --it;
    EXPECT_EQ(*it, 10);
}

#endif
