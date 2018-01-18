#include <string>
#include <iostream>
#include <type_traits>
#include <gtest/gtest.h>
#include "persistent_set.h"

using namespace std;
using namespace bezborodov;
using namespace bezborodov::pointers;

TEST(SHARED_PTR_TESTS, nothrow_check)
{
    EXPECT_TRUE(is_nothrow_default_constructible_v<shared_ptr<int>>);
    EXPECT_TRUE(is_nothrow_copy_constructible_v<shared_ptr<int>>);
    EXPECT_TRUE(is_nothrow_move_constructible_v<shared_ptr<int>>);
    EXPECT_TRUE(is_nothrow_copy_assignable_v<shared_ptr<int>>);
    EXPECT_TRUE(is_nothrow_move_assignable_v<shared_ptr<int>>);
    EXPECT_TRUE(is_nothrow_destructible_v<shared_ptr<int>>);
}
TEST(SHARED_PTR_TESTS, default_ctor_check)
{
    shared_ptr<int> x;
    EXPECT_TRUE(x.get() == nullptr);
}
TEST(SHARED_PTR_TESTS, copy_ctor_check)
{
    shared_ptr<int> x(new int(5));
    shared_ptr<int> y(x);
    EXPECT_TRUE(x.get() && *x.get() == 5);
    EXPECT_TRUE(y.get() && *y.get() == 5);
    EXPECT_TRUE(x.count() == 2);
}
TEST(SHARED_PTR_TESTS, move_ctor_check)
{
    shared_ptr<int> x(new int(5));
    shared_ptr<int> y(std::move(x));
    EXPECT_TRUE(x.get() == nullptr);
    EXPECT_TRUE(y.get() && *y == 5);
    EXPECT_TRUE(y.count() == 1);
}
TEST(SHARED_PTR_TESTS, copy_assign_test)
{
    shared_ptr<int> x(new int(5));
    shared_ptr<int> y;
    y = x;
    EXPECT_TRUE(x.get() && *x == 5);
    EXPECT_TRUE(y.get() && *y == 5);
    EXPECT_TRUE(x.count() == 2);
}
TEST(SHARED_PTR_TESTS, move_assign_test)
{
    shared_ptr<int> x(new int(5));
    shared_ptr<int> y;
    y = std::move(x);
    EXPECT_TRUE(x.get() == nullptr);
    EXPECT_TRUE(y.get() && *y == 5);
    EXPECT_TRUE(y.count() == 1);
}
TEST(SHARED_PTR_TESTS, dtor_test)
{
    shared_ptr<int> x(new int(5));
    EXPECT_TRUE(x.get() && *x== 5 && x.count() == 1);
    shared_ptr<int> y[20];
    y[0] = x;
    EXPECT_TRUE(x.get() && *x == 5 && x.count() == 2);
    for (size_t i = 1; i < 20; ++i) {
        y[i] = y[i - 1];
        *y[i] = i;
        EXPECT_TRUE(x.get() && *x == static_cast<int>(i) && x.count() == i + 2);
    }
}
TEST(SHARED_PTR_TESTS, reference_test)
{
    shared_ptr<string> ptr(new string("test"));
    EXPECT_TRUE(ptr->size() == 4);
}
TEST(SHARED_PTR_TESTS, dereference_test)
{
    shared_ptr<string> ptr(new string("test"));
    EXPECT_TRUE(*ptr == "test");
}
TEST(SHARED_PTR_TESTS, get_test)
{
    int* p = new int(5);
    shared_ptr<int> ptr(p);
    EXPECT_TRUE(ptr.get() && ptr.get() == p);
}
TEST(SHARED_PTR_TESTS, count_test) {
    int* p = new int(5);
    shared_ptr<int> p1(p);
    EXPECT_TRUE(p1.get() && *p1 == 5 && p1.count() == 1);
    shared_ptr<int> p2(p1);
    EXPECT_TRUE(p2.get() && *p2 == 5 && p2.count() == 2);
    shared_ptr<int> p3(p2);
    EXPECT_TRUE(p3.get() && *p3 == 5 && p3.count() == 3);
}
TEST(SHARED_PTR_TESTS, reset_test)
{
    int* p = new int(30);
    int* q = new int(239);

    shared_ptr<int> p1(p);
    shared_ptr<int> p2(p1);
    shared_ptr<int> p3;
    p3 = p2;
    EXPECT_TRUE(p1.get() && *p1 == 30 && p1.count() == 3);
    p1.reset(q);
    shared_ptr<int> q1 = p1;
    EXPECT_TRUE(p1.get() && *p1 == 239 && p1.count() == 2);
    EXPECT_TRUE(p2.get() && *p2 ==  30 && p2.count() == 2);
}
TEST(SHARED_PTR_TESTS, swap_test)
{
    shared_ptr<int> p(new int(11193)); // bitcoin price on 18.01.2018 3:58
    shared_ptr<int> q(new int(11261)); // bitcoin price on 18.01.2018 4:05
    EXPECT_TRUE(p.get() && *p == 11193);
    EXPECT_TRUE(q.get() && *q == 11261);
    swap(p, q);
    EXPECT_TRUE(p.get() && *p == 11261);
    EXPECT_TRUE(q.get() && *q == 11193);
}
//-------------------------------------------------------------------------
TEST(LINKED_PTR_TESTS, nothrow_check)
{
    EXPECT_TRUE(is_nothrow_default_constructible_v<linked_ptr<int>>);
    EXPECT_TRUE(is_nothrow_copy_constructible_v<linked_ptr<int>>);
    EXPECT_TRUE(is_nothrow_move_constructible_v<linked_ptr<int>>);
    EXPECT_TRUE(is_nothrow_copy_assignable_v<linked_ptr<int>>);
    EXPECT_TRUE(is_nothrow_move_assignable_v<linked_ptr<int>>);
    EXPECT_TRUE(is_nothrow_destructible_v<linked_ptr<int>>);
}
TEST(LINKED_PTR_TESTS, default_ctor_check)
{
    linked_ptr<int> x;
    EXPECT_TRUE(x.get() == nullptr);
}
TEST(LINKED_PTR_TESTS, copy_ctor_check)
{
    linked_ptr<int> x(new int(5));
    linked_ptr<int> y(x);
    EXPECT_TRUE(x.get() && *x.get() == 5);
    EXPECT_TRUE(y.get() && *y.get() == 5);
}
TEST(LINKED_PTR_TESTS, move_ctor_check)
{
    linked_ptr<int> x(new int(5));
    linked_ptr<int> y(std::move(x));
    EXPECT_TRUE(x.get() == nullptr);
    EXPECT_TRUE(y.get() && *y == 5);
}
TEST(LINKED_PTR_TESTS, copy_assign_test)
{
    linked_ptr<int> x(new int(5));
    linked_ptr<int> y;
    y = x;
    EXPECT_TRUE(x.get() && *x == 5);
    EXPECT_TRUE(y.get() && *y == 5);
}
TEST(LINKED_PTR_TESTS, move_assign_test)
{
    linked_ptr<int> x(new int(5));
    linked_ptr<int> y;
    y = std::move(x);
    EXPECT_TRUE(x.get() == nullptr);
    EXPECT_TRUE(y.get() && *y == 5);
}
TEST(LINKED_PTR_TESTS, dtor_test)
{
    linked_ptr<int> x(new int(5));
    EXPECT_TRUE(x.get() && *x== 5);
    linked_ptr<int> y[20];
    y[0] = x;
    EXPECT_TRUE(x.get() && *x == 5);
    for (size_t i = 1; i < 20; ++i) {
        y[i] = y[i - 1];
        *y[i] = i;
        EXPECT_TRUE(x.get() && *x == static_cast<int>(i));
    }
}
TEST(LINKED_PTR_TESTS, reference_test)
{
    linked_ptr<string> ptr(new string("test"));
    EXPECT_TRUE(ptr->size() == 4);
}
TEST(LINKED_PTR_TESTS, dereference_test)
{
    linked_ptr<string> ptr(new string("test"));
    EXPECT_TRUE(*ptr == "test");
}
TEST(LINKED_PTR_TESTS, get_test)
{
    int* p = new int(5);
    linked_ptr<int> ptr(p);
    EXPECT_TRUE(ptr.get() && ptr.get() == p);
}
TEST(LINKED_PTR_TESTS, count_test) {
    int* p = new int(5);
    linked_ptr<int> p1(p);
    EXPECT_TRUE(p1.get() && *p1 == 5);
    linked_ptr<int> p2(p1);
    EXPECT_TRUE(p2.get() && *p2 == 5);
    linked_ptr<int> p3(p2);
    EXPECT_TRUE(p3.get() && *p3 == 5);
}
TEST(LINKED_PTR_TESTS, reset_test)
{
    int* p = new int(30);
    int* q = new int(239);

    linked_ptr<int> p1(p);
    linked_ptr<int> p2(p1);
    linked_ptr<int> p3;
    p3 = p2;
    EXPECT_TRUE(p1.get() && *p1 == 30);
    p1.reset(q);
    linked_ptr<int> q1 = p1;
    EXPECT_TRUE(p1.get() && *p1 == 239);
    EXPECT_TRUE(p2.get() && *p2 ==  30);
}
TEST(LINKED_PTR_TESTS, swap_test)
{
    linked_ptr<int> p(new int(11193)); // bitcoin price on 18.01.2018 3:58
    linked_ptr<int> q(new int(11261)); // bitcoin price on 18.01.2018 3:58
    EXPECT_TRUE(p.get() && *p == 11193);
    EXPECT_TRUE(q.get() && *q == 11261);
    swap(p, q);
    EXPECT_TRUE(p.get() && *p == 11261);
    EXPECT_TRUE(q.get() && *q == 11193);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
