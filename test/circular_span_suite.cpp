///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <array>
#include <vector>
#include <algorithm>
#include <numeric>
#include <trial/online/detail/lightweight_test.hpp>
#include <trial/online/circular_span.hpp>

using namespace trial::online;

//-----------------------------------------------------------------------------

namespace plain_array_suite
{

void test_ctor()
{
    int array[4];
    circular_span<int> span(array);
    TRIAL_ONLINE_TEST(span.empty());
    TRIAL_ONLINE_TEST(!span.full());
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(span.capacity(), 4);
}

void test_push_front()
{
    int array[4];
    circular_span<int> span(array);
    span.push_front(1);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 1);
    span.push_front(2);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 2);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 1);
    span.push_front(3);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 3);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 3);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 1);
    span.push_front(4);
    TRIAL_ONLINE_TEST(span.full());
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 1);
    span.push_front(5);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 5);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 2);
    span.push_front(6);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 6);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 3);
    span.push_front(7);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 7);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 4);
    span.push_front(8);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 8);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 5);
    span.push_front(9);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 9);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 6);
}

void test_push_back()
{
    int array[4];
    circular_span<int> span(array);
    span.push_back(1);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 1);
    span.push_back(2);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 2);
    span.push_back(3);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 3);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 3);
    span.push_back(4);
    TRIAL_ONLINE_TEST(span.full());
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 4);
    span.push_back(5);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 2);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 5);
    span.push_back(6);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 3);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 6);
    span.push_back(7);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 7);
    span.push_back(8);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 5);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 8);
    span.push_back(9);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 6);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 9);
}

void test_push_alternating()
{
    int array[4];
    circular_span<int> span(array);
    span.push_back(1);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 1);
    span.push_front(2);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 2);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 1);
    span.push_back(3);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 3);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 2);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 3);
    span.push_front(4);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 3);
    span.push_back(5);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 2); // 4 was pushed out
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 5);
    span.push_front(6);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 6);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 3); // 5 was pushed out
}

void test_pop_front()
{
    int array[4];
    circular_span<int> span(array);
    span.push_back(1);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 1);
    span.pop_front();
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 0);
    span.push_back(1);
    span.push_back(2);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 2);
    span.pop_front();
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 2);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 2);
    span.push_back(3);
    span.push_back(4);
    span.push_back(5);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 2);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 5);
    span.pop_front();
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 3);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 3);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 5);
}

void test_pop_back()
{
    int array[4];
    circular_span<int> span(array);
    span.push_back(1);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 1);
    span.pop_back();
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 0);
    span.push_back(1);
    span.push_back(2);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 2);
    span.pop_back();
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 1);
    span.push_back(3);
    span.push_back(4);
    span.push_back(5);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 5);
    span.pop_back();
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 3);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 4);
}

void test_assign_operator()
{
    int array[4];
    circular_span<int> span(array);
    span = { 11 };
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 11);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 11);
    span = { 21, 22 };
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 21);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 22);
    span = { 31, 32, 33 };
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 3);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 31);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 33);
    span = { 41, 42, 43, 44 };
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 41);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 44);
    span = { 51, 52, 53, 54, 55 };
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 52);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 55);
}

void test_assign_iterator()
{
    int array[4];
    circular_span<int> span(array);
    {
        std::vector<int> input = { 11 };
        span.assign(input.begin(), input.end());
    }
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 11);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 11);
    {
        std::vector<int> input = { 21, 22 };
        span.assign(input.begin(), input.end());
    }
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 21);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 22);
    {
        std::vector<int> input = { 31, 32, 33 };
        span.assign(input.begin(), input.end());
    }
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 3);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 31);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 33);
    {
        std::vector<int> input = { 41, 42, 43, 44 };
        span.assign(input.begin(), input.end());
    }
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 41);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 44);
    {
        std::vector<int> input = { 51, 52, 53, 54, 55 };
        span.assign(input.begin(), input.end());
    }
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 52);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 55);
}

void test_assign_initializer_list()
{
    int array[4];
    circular_span<int> span(array);
    span.assign({ 11 });
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 11);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 11);
    span.assign({ 21, 22 });
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 21);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 22);
    span.assign({ 31, 32, 33 });
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 3);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 31);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 33);
    span.assign({ 41, 42, 43, 44 });
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 41);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 44);
    span.assign({ 51, 52, 53, 54, 55 });
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 52);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 55);
}

void run()
{
    test_ctor();
    test_push_front();
    test_push_back();
    test_push_alternating();
    test_pop_front();
    test_pop_back();
    test_assign_operator();
    test_assign_iterator();
    test_assign_initializer_list();
}

} // namespace plain_array_suite

//-----------------------------------------------------------------------------

namespace std_array_suite
{

void test_ctor()
{
    std::array<int, 4> array;
    circular_span<int> span(array.begin(), array.end());
    TRIAL_ONLINE_TEST(span.empty());
    TRIAL_ONLINE_TEST(!span.full());
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(span.capacity(), 4);
}

void test_ctor_init()
{
    std::array<int, 4> array = { 1, 2, 3, 4 };
    circular_span<int> span(array.begin(), array.end(), array.begin(), array.size());
    TRIAL_ONLINE_TEST(!span.empty());
    TRIAL_ONLINE_TEST(span.full());
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.capacity(), 4);
}

void test_push_front()
{
    std::array<int, 4> array;
    circular_span<int> span(array.begin(), array.end());
    span.push_front(1);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 1);
    span.push_front(2);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 2);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 1);
    span.push_front(3);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 3);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 3);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 1);
    span.push_front(4);
    TRIAL_ONLINE_TEST(span.full());
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 1);
    span.push_front(5);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 5);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 2);
    span.push_front(6);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 6);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 3);
}

void test_push_back()
{
    std::array<int, 4> array;
    circular_span<int> span(array.begin(), array.end());
    span.push_back(1);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 1);
    span.push_back(2);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 2);
    span.push_back(3);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 3);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 3);
    span.push_back(4);
    TRIAL_ONLINE_TEST(span.full());
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 4);
    span.push_back(5);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 2);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 5);
    span.push_back(6);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 3);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 6);
}

void run()
{
    test_ctor();
    test_ctor_init();
    test_push_front();
    test_push_back();
}

} // namespace std_array_suite

//-----------------------------------------------------------------------------

namespace std_vector_suite
{

void test_ctor_empty()
{
    std::vector<int> array;
    circular_span<int> span(array.begin(), array.end());
    TRIAL_ONLINE_TEST(span.empty());
    TRIAL_ONLINE_TEST(span.full());
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(span.capacity(), 0);
}

void test_ctor()
{
    std::vector<int> array(4);
    circular_span<int> span(array.begin(), array.end());
    TRIAL_ONLINE_TEST(span.empty());
    TRIAL_ONLINE_TEST(!span.full());
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(span.capacity(), 4);
}

void test_push_back()
{
    std::vector<int> array(4);
    circular_span<int> span(array.begin(), array.end());
    span.push_back(1);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 1);
    span.push_back(2);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 2);
    span.push_back(3);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 3);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 3);
    span.push_back(4);
    TRIAL_ONLINE_TEST(span.full());
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 4);
    span.push_back(5);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 2);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 5);
    span.push_back(6);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(span.front(), 3);
    TRIAL_ONLINE_TEST_EQUAL(span.back(), 6);
}

void run()
{
    test_ctor_empty();
    test_ctor();
    test_push_back();
}

} // namespace std_vector_suite

//-----------------------------------------------------------------------------

namespace iterator_suite
{

void test_empty()
{
    std::array<int, 4> array;
    circular_span<int> span(array.begin(), array.end());
    TRIAL_ONLINE_TEST(span.begin() == span.end());
}

void test_iterator()
{
    std::array<int, 4> array;
    circular_span<int> span(array.begin(), array.end());
    span.push_back(1);
    TRIAL_ONLINE_TEST(span.begin() != span.end());
    {
        std::vector<int> expect = { 1 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    *span.begin() = 11;
    TRIAL_ONLINE_TEST(span.begin() != span.end());
    {
        std::vector<int> expect = { 11 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
}

void test_iterator_constructible()
{
    std::array<int, 4> array;
    circular_span<int> span(array.begin(), array.end());
    span.push_back(1);
    decltype(span)::iterator alpha; // DefaultConstructible
    alpha = span.begin();
    TRIAL_ONLINE_TEST(alpha == span.begin());
    decltype(span)::iterator bravo(alpha); // CopyConstructible
    TRIAL_ONLINE_TEST(bravo == span.begin());
}

void test_const_iterator()
{
    std::array<int, 4> array;
    circular_span<int> span(array.begin(), array.end());
    span.push_back(1);
    TRIAL_ONLINE_TEST(span.cbegin() != span.cend());
    {
        std::vector<int> expect = { 1 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.cbegin(), span.cend(),
                                    expect.begin(), expect.end());
    }
}

void test_push_back()
{
    std::array<int, 4> array;
    circular_span<int> span(array.begin(), array.end());
    span.push_back(1);
    TRIAL_ONLINE_TEST(span.begin() != span.end());
    {
        std::vector<int> expect = { 1 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(2);
    {
        std::vector<int> expect = { 1, 2 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(3);
    {
        std::vector<int> expect = { 1, 2, 3 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(4);
    {
        std::vector<int> expect = { 1, 2, 3, 4 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(5);
    {
        std::vector<int> expect = { 2, 3, 4, 5 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(6);
    {
        std::vector<int> expect = { 3, 4, 5, 6 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
}

void test_push_front()
{
    std::array<int, 4> array;
    circular_span<int> span(array.begin(), array.end());
    span.push_front(1);
    {
        std::vector<int> expect = { 1 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_front(2);
    {
        std::vector<int> expect = { 2, 1 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_front(3);
    {
        std::vector<int> expect = { 3, 2, 1 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_front(4);
    {
        std::vector<int> expect = { 4, 3, 2, 1 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_front(5);
    {
        std::vector<int> expect = { 5, 4, 3, 2 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_front(6);
    {
        std::vector<int> expect = { 6, 5, 4, 3 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
}

void test_push_alternating()
{
    std::array<int, 4> array;
    circular_span<int> span(array.begin(), array.end());
    span.push_back(1);
    {
        std::vector<int> expect = { 1 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_front(2);
    {
        std::vector<int> expect = { 2, 1 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(3);
    {
        std::vector<int> expect = { 2, 1, 3 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_front(4);
    {
        std::vector<int> expect = { 4, 2, 1, 3 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(5);
    {
        std::vector<int> expect = { 2, 1, 3, 5 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_front(6);
    {
        std::vector<int> expect = { 6, 2, 1, 3 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
}

void run()
{
    test_empty();
    test_iterator();
    test_iterator_constructible();
    test_const_iterator();
    test_push_front();
    test_push_back();
    test_push_alternating();
}

} // namespace iterator_suite

//-----------------------------------------------------------------------------

namespace clear_suite
{

void clear_empty()
{
    int array[4];
    circular_span<int> span(array);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 0);
    span.clear();
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 0);
}

void clear_partial()
{
    int array[4];
    circular_span<int> span(array);
    span.push_back(1);
    span.push_back(2);
    span.push_back(3);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 3);
    span.clear();
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 0);
}

void clear_full()
{
    int array[4];
    circular_span<int> span(array);
    span.push_back(1);
    span.push_back(2);
    span.push_back(3);
    span.push_back(4);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    span.clear();
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 0);
}

void clear_overfull()
{
    int array[4];
    circular_span<int> span(array);
    span.push_back(1);
    span.push_back(2);
    span.push_back(3);
    span.push_back(4);
    span.push_back(5);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    span.clear();
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 0);
}

void run()
{
    clear_empty();
    clear_partial();
    clear_full();
    clear_overfull();
}

} // namespace clear_suite

//-----------------------------------------------------------------------------

namespace window_size_suite
{

void test_1()
{
    std::array<int, 1> array;
    circular_span<int> span(array.begin(), array.end());
    span.push_back(1);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 1);
        std::vector<int> expect = { 1 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(2);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 2);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 2);
        std::vector<int> expect = { 2 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(3);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 3);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 3);
        std::vector<int> expect = { 3 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(4);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 4);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 4);
        std::vector<int> expect = { 4 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(5);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 5);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 5);
        std::vector<int> expect = { 5 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(6);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 6);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 6);
        std::vector<int> expect = { 6 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
}

void test_2()
{
    std::array<int, 2> array;
    circular_span<int> span(array.begin(), array.end());
    span.push_back(1);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 1);
        std::vector<int> expect = { 1 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(2);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 2);
        std::vector<int> expect = { 1, 2 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(3);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 2);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 3);
        std::vector<int> expect = { 2, 3 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(4);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 3);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 4);
        std::vector<int> expect = { 3, 4 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(5);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 4);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 5);
        std::vector<int> expect = { 4, 5 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(6);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 5);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 6);
        std::vector<int> expect = { 5, 6 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
}

void test_3()
{
    std::array<int, 3> array;
    circular_span<int> span(array.begin(), array.end());
    span.push_back(1);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 1);
        std::vector<int> expect = { 1 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(2);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 2);
        std::vector<int> expect = { 1, 2 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(3);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 3);
        std::vector<int> expect = { 1, 2, 3 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(4);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 2);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 4);
        std::vector<int> expect = { 2, 3, 4 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(5);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 3);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 5);
        std::vector<int> expect = { 3, 4, 5 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(6);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 4);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 6);
        std::vector<int> expect = { 4, 5, 6 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(7);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 5);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 7);
        std::vector<int> expect = { 5, 6, 7 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
}

void test_4()
{
    std::array<int, 4> array;
    circular_span<int> span(array.begin(), array.end());
    span.push_back(1);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 1);
        std::vector<int> expect = { 1 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(2);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 2);
        std::vector<int> expect = { 1, 2 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(3);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 3);
        std::vector<int> expect = { 1, 2, 3 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(4);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 1);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 4);
        std::vector<int> expect = { 1, 2, 3, 4 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(5);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 2);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 5);
        std::vector<int> expect = { 2, 3, 4, 5 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(6);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 3);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 6);
        std::vector<int> expect = { 3, 4, 5, 6 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(7);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 4);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 7);
        std::vector<int> expect = { 4, 5, 6, 7 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(8);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 5);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 8);
        std::vector<int> expect = { 5, 6, 7, 8 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
    span.push_back(9);
    {
        TRIAL_ONLINE_TEST_EQUAL(span.front(), 6);
        TRIAL_ONLINE_TEST_EQUAL(span.back(), 9);
        std::vector<int> expect = { 6, 7, 8, 9 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
}

void run()
{
    test_1();
    test_2();
    test_3();
    test_4();
}

} // namespace window_size_suite

//-----------------------------------------------------------------------------

namespace std_algorithm_suite
{

void test_any_of()
{
    int array[4];
    circular_span<int> span(array);
    span = { 1, 2, 3, 4 };
    TRIAL_ONLINE_TEST(std::any_of(span.begin(), span.end(), [] (int current) { return current == 1; }));
    span.push_back(5);
    TRIAL_ONLINE_TEST(!std::any_of(span.begin(), span.end(), [] (int current) { return current == 1; }));
}

void test_fill_n()
{
    int array[4];
    circular_span<int> span(array);
    std::fill_n(std::back_inserter(span), 2 * span.capacity(), 42);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), span.capacity());
    {
        std::vector<int> expect = { 42, 42, 42, 42 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), span.end(),
                                    expect.begin(), expect.end());
    }
}

void test_lower_bound()
{
    int array[4];
    circular_span<int> span(array);
    span = { 1, 2, 3, 4 };
    auto lower = std::lower_bound(span.begin(), span.end(), 3);
    {
        std::vector<int> expect = { 3, 4 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(lower, span.end(),
                                    expect.begin(), expect.end());
    }
}

void test_minmax_element()
{
    int array[4];
    circular_span<int> span(array);
    span = { 1, 2, 3, 4 };
    auto where = std::minmax_element(span.begin(), span.end());
    TRIAL_ONLINE_TEST_EQUAL(*where.first, 1);
    TRIAL_ONLINE_TEST_EQUAL(*where.second, 4);
}

void test_unique()
{
    int array[4];
    circular_span<int> span(array);
    span = { 1, 1, 1, 4 };
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    auto where = std::unique(span.begin(), span.end());
    {
        std::vector<int> expect = { 1, 4 };
        TRIAL_ONLINE_TEST_ALL_EQUAL(span.begin(), where,
                                    expect.begin(), expect.end());
    }
    // span.end() still points to the last undeterminate entry
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 4);
    while (where != span.end())
    {
        span.pop_back();
    }
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 2);
}

void run()
{
    test_any_of();
    test_fill_n();
    test_lower_bound();
    test_minmax_element();
    test_unique();
}

} // namespace std_algorithm_suite

//-----------------------------------------------------------------------------

namespace std_numeric_suite
{

void test_accumulate()
{
    int array[4];
    circular_span<int> span(array);
    span = { 1, 2, 3, 4 };
    TRIAL_ONLINE_TEST_EQUAL(std::accumulate(span.begin(), span.end(), 0), 1 + 2 + 3 + 4);
    span.push_back(5);
    TRIAL_ONLINE_TEST_EQUAL(std::accumulate(span.begin(), span.end(), 0), 2 + 3 + 4 + 5);
}

void test_inner_product()
{
    std::array<int, 4> array;
    circular_span<int> span(array.begin(), array.end());
    span = { 1, 2, 3, 4 };
    TRIAL_ONLINE_TEST_EQUAL(std::inner_product(span.begin(), span.end(), array.begin(), 0),
                            1 * 1 + 2 * 2 + 3 * 3 + 4 * 4);
    span = { 1, 2, 3, 4, 5 };
    TRIAL_ONLINE_TEST_EQUAL(std::inner_product(span.begin(), span.end(), array.begin(), 0),
                            2 * 5 + 3 * 2 + 4 * 3 + 5 * 4);
}

void run()
{
    test_accumulate();
    test_inner_product();
}

} // namespace std_numeric_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    plain_array_suite::run();
    std_array_suite::run();
    std_vector_suite::run();
    iterator_suite::run();
    clear_suite::run();
    window_size_suite::run();
    std_algorithm_suite::run();
    std_numeric_suite::run();

    return boost::report_errors();
}
