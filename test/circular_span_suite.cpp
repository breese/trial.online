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
#include <trial/online/detail/lightweight_test.hpp>
#include <trial/online/circular_span.hpp>

using namespace trial::online;

//-----------------------------------------------------------------------------

namespace plain_array_suite
{

void test_empty()
{
    int array[4];
    circular_span<decltype(array)> span(array);
    TRIAL_ONLINE_TEST(span.empty());
    TRIAL_ONLINE_TEST(!span.full());
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(span.capacity(), 4);
}

void test_push_back()
{
    int array[4];
    circular_span<decltype(array)> span(array);
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
    test_empty();
    test_push_back();
}

} // namespace plain_array_suite

//-----------------------------------------------------------------------------

namespace std_array_suite
{

void test_empty()
{
    std::array<int, 4> array;
    circular_span<int> span(array.begin(), array.end());
    TRIAL_ONLINE_TEST(span.empty());
    TRIAL_ONLINE_TEST(!span.full());
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(span.capacity(), 4);
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
    test_empty();
    test_push_back();
}

} // namespace std_array_suite

//-----------------------------------------------------------------------------

namespace std_vector_suite
{

void test_very_empty()
{
    std::vector<int> array;
    circular_span<int> span(array.begin(), array.end());
    TRIAL_ONLINE_TEST(span.empty());
    TRIAL_ONLINE_TEST(span.full());
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(span.capacity(), 0);
}

void test_empty()
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
    test_very_empty();
    test_empty();
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

void test_const_iterator()
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

void run()
{
    test_empty();
    test_iterator();
    test_const_iterator();
}

} // namespace iterator_suite

//-----------------------------------------------------------------------------

namespace clear_suite
{

void clear_empty()
{
    int array[4];
    circular_span<decltype(array)> span(array);
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 0);
    span.clear();
    TRIAL_ONLINE_TEST_EQUAL(span.size(), 0);
}

void clear_partial()
{
    int array[4];
    circular_span<decltype(array)> span(array);
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
    circular_span<decltype(array)> span(array);
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
    circular_span<decltype(array)> span(array);
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
// main
//-----------------------------------------------------------------------------

int main()
{
    plain_array_suite::run();
    std_array_suite::run();
    std_vector_suite::run();
    iterator_suite::run();
    clear_suite::run();

    return boost::report_errors();
}
