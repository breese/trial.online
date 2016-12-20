///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2016 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/detail/lightweight_test.hpp>
#include <trial/online/average/arithmetic.hpp>

//-----------------------------------------------------------------------------

namespace double_1_suite
{

void test_empty()
{
    trial::online::average::arithmetic<double, 1> filter;
    BOOST_TEST_EQ(filter.capacity(), 1);
    BOOST_TEST_EQ(filter.empty(), true);
    BOOST_TEST_EQ(filter.full(), false);
    BOOST_TEST_EQ(filter.size(), 0);
    BOOST_TEST_EQ(filter.mean(), 0.0);
}

void test_many()
{
    trial::online::average::arithmetic<double, 1> filter;
    BOOST_TEST_EQ(filter.capacity(), 1);
    filter.push(1.0);
    BOOST_TEST_EQ(filter.empty(), false);
    BOOST_TEST_EQ(filter.full(), true);
    BOOST_TEST_EQ(filter.size(), 1);
    BOOST_TEST_EQ(filter.mean(), 1.0);
    filter.push(2.0);
    BOOST_TEST_EQ(filter.empty(), false);
    BOOST_TEST_EQ(filter.full(), true);
    BOOST_TEST_EQ(filter.size(), 1);
    BOOST_TEST_EQ(filter.mean(), 2.0);
    filter.push(3.0);
    BOOST_TEST_EQ(filter.empty(), false);
    BOOST_TEST_EQ(filter.full(), true);
    BOOST_TEST_EQ(filter.size(), 1);
    BOOST_TEST_EQ(filter.mean(), 3.0);
}

void test()
{
    test_empty();
    test_many();
}

} // namespace double_1_suite

//-----------------------------------------------------------------------------

namespace double_2_suite
{

void test_empty()
{
    trial::online::average::arithmetic<double, 2> filter;
    BOOST_TEST_EQ(filter.capacity(), 2);
    BOOST_TEST_EQ(filter.empty(), true);
    BOOST_TEST_EQ(filter.full(), false);
    BOOST_TEST_EQ(filter.size(), 0);
    BOOST_TEST_EQ(filter.mean(), 0.0);
}

void test_one()
{
    trial::online::average::arithmetic<double, 2> filter;
    filter.push(1.0);
    BOOST_TEST_EQ(filter.empty(), false);
    BOOST_TEST_EQ(filter.full(), false);
    BOOST_TEST_EQ(filter.size(), 1);
    BOOST_TEST_EQ(filter.mean(), 1.0);
}

void test_same()
{
    trial::online::average::arithmetic<double, 2> filter;
    filter.push(1.0);
    BOOST_TEST_EQ(filter.size(), 1);
    BOOST_TEST_EQ(filter.mean(), 1.0);
    filter.push(1.0);
    BOOST_TEST_EQ(filter.size(), 2);
    BOOST_TEST_EQ(filter.mean(), 1.0);
    filter.push(1.0);
    BOOST_TEST_EQ(filter.empty(), false);
    BOOST_TEST_EQ(filter.full(), true);
    BOOST_TEST_EQ(filter.size(), 2);
    BOOST_TEST_EQ(filter.mean(), 1.0);
}

void test_two()
{
    trial::online::average::arithmetic<double, 2> filter;
    filter.push(1.0);
    BOOST_TEST_EQ(filter.mean(), 1.0);
    filter.push(3.0);
    BOOST_TEST_EQ(filter.mean(), 2.0);
}

void test_three()
{
    trial::online::average::arithmetic<double, 2> filter;
    filter.push(1.0);
    BOOST_TEST_EQ(filter.mean(), 1.0);
    filter.push(3.0);
    BOOST_TEST_EQ(filter.mean(), 2.0);
    filter.push(0.0);
    BOOST_TEST_EQ(filter.mean(), 1.5);
}

void test_clear()
{
    trial::online::average::arithmetic<double, 2> filter;
    filter.push(1.0);
    BOOST_TEST_EQ(filter.size(), 1);
    filter.clear();
    BOOST_TEST_EQ(filter.size(), 0);
    filter.push(2.0);
    BOOST_TEST_EQ(filter.size(), 1);
    BOOST_TEST_EQ(filter.mean(), 2.0);
}

void test()
{
    test_empty();
    test_same();
    test_one();
    test_two();
    test_three();
    test_clear();
}

} // namespace double_2_suite

//-----------------------------------------------------------------------------

namespace float_2_suite
{

void test_empty()
{
    trial::online::average::arithmetic<float, 2> filter;
    BOOST_TEST_EQ(filter.capacity(), 2);
    BOOST_TEST_EQ(filter.empty(), true);
    BOOST_TEST_EQ(filter.full(), false);
    BOOST_TEST_EQ(filter.size(), 0);
    BOOST_TEST_EQ(filter.mean(), 0.0f);
}

void test_one()
{
    trial::online::average::arithmetic<float, 2> filter;
    filter.push(1.0f);
    BOOST_TEST_EQ(filter.empty(), false);
    BOOST_TEST_EQ(filter.full(), false);
    BOOST_TEST_EQ(filter.size(), 1);
    BOOST_TEST_EQ(filter.mean(), 1.0f);
}

void test_same()
{
    trial::online::average::arithmetic<float, 2> filter;
    filter.push(1.0f);
    BOOST_TEST_EQ(filter.size(), 1);
    BOOST_TEST_EQ(filter.mean(), 1.0);
    filter.push(1.0f);
    BOOST_TEST_EQ(filter.size(), 2);
    BOOST_TEST_EQ(filter.mean(), 1.0f);
    filter.push(1.0f);
    BOOST_TEST_EQ(filter.empty(), false);
    BOOST_TEST_EQ(filter.full(), true);
    BOOST_TEST_EQ(filter.size(), 2);
    BOOST_TEST_EQ(filter.mean(), 1.0f);
}

void test_two()
{
    trial::online::average::arithmetic<float, 2> filter;
    filter.push(1.0f);
    BOOST_TEST_EQ(filter.mean(), 1.0f);
    filter.push(3.0f);
    BOOST_TEST_EQ(filter.mean(), 2.0f);
}

void test_three()
{
    trial::online::average::arithmetic<float, 2> filter;
    filter.push(1.0f);
    BOOST_TEST_EQ(filter.mean(), 1.0f);
    filter.push(3.0f);
    BOOST_TEST_EQ(filter.mean(), 2.0f);
    filter.push(0.0f);
    BOOST_TEST_EQ(filter.mean(), 1.5f);
}

void test_clear()
{
    trial::online::average::arithmetic<float, 2> filter;
    filter.push(1.0f);
    BOOST_TEST_EQ(filter.size(), 1);
    filter.clear();
    BOOST_TEST_EQ(filter.size(), 0);
    filter.push(2.0f);
    BOOST_TEST_EQ(filter.size(), 1);
    BOOST_TEST_EQ(filter.mean(), 2.0f);
}

void test()
{
    test_empty();
    test_same();
    test_one();
    test_two();
    test_three();
    test_clear();
}

} // namespace float_2_suite

//-----------------------------------------------------------------------------

namespace int_2_suite
{

void test_empty()
{
    trial::online::average::arithmetic<int, 2> filter;
    BOOST_TEST_EQ(filter.capacity(), 2);
    BOOST_TEST_EQ(filter.empty(), true);
    BOOST_TEST_EQ(filter.full(), false);
    BOOST_TEST_EQ(filter.size(), 0);
    BOOST_TEST_EQ(filter.mean(), 0);
}

void test_one()
{
    trial::online::average::arithmetic<int, 2> filter;
    filter.push(1);
    BOOST_TEST_EQ(filter.empty(), false);
    BOOST_TEST_EQ(filter.full(), false);
    BOOST_TEST_EQ(filter.size(), 1);
    BOOST_TEST_EQ(filter.mean(), 1);
}

void test_same()
{
    trial::online::average::arithmetic<int, 2> filter;
    filter.push(1);
    BOOST_TEST_EQ(filter.size(), 1);
    BOOST_TEST_EQ(filter.mean(), 1);
    filter.push(1);
    BOOST_TEST_EQ(filter.size(), 2);
    BOOST_TEST_EQ(filter.mean(), 1);
    filter.push(1);
    BOOST_TEST_EQ(filter.empty(), false);
    BOOST_TEST_EQ(filter.full(), true);
    BOOST_TEST_EQ(filter.size(), 2);
    BOOST_TEST_EQ(filter.mean(), 1);
}

void test_two()
{
    trial::online::average::arithmetic<int, 2> filter;
    filter.push(1);
    BOOST_TEST_EQ(filter.mean(), 1);
    filter.push(3);
    BOOST_TEST_EQ(filter.mean(), 2);
}

void test_three()
{
    trial::online::average::arithmetic<int, 2> filter;
    filter.push(1);
    BOOST_TEST_EQ(filter.mean(), 1);
    filter.push(3);
    BOOST_TEST_EQ(filter.mean(), 2);
    filter.push(0);
    BOOST_TEST_EQ(filter.mean(), 1); // Rounded down
}

void test_clear()
{
    trial::online::average::arithmetic<int, 2> filter;
    filter.push(1);
    BOOST_TEST_EQ(filter.size(), 1);
    filter.clear();
    BOOST_TEST_EQ(filter.size(), 0);
    filter.push(2);
    BOOST_TEST_EQ(filter.size(), 1);
    BOOST_TEST_EQ(filter.mean(), 2);
}

void test()
{
    test_empty();
    test_same();
    test_one();
    test_two();
    test_three();
    test_clear();
}

} // namespace int_2_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    double_1_suite::test();
    double_2_suite::test();
    float_2_suite::test();
    int_2_suite::test();

    return boost::report_errors();
}
