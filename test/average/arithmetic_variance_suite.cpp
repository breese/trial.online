///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2016 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/online/detail/lightweight_test.hpp>
#include <trial/online/average/arithmetic_variance.hpp>

//-----------------------------------------------------------------------------

namespace arithmetic_variance_1_suite
{

void test_empty()
{
    trial::online::average::arithmetic_variance<double, 1> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.capacity(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), true);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
}

void test_many()
{
    trial::online::average::arithmetic_variance<double, 1> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.capacity(), 1);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), true);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    filter.push(2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), true);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), true);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 3.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
}

void test()
{
    test_empty();
    test_many();
}

} // namespace arithmetic_variance_1_suite

//-----------------------------------------------------------------------------

namespace arithmetic_variance_2_suite
{

void test_empty()
{
    trial::online::average::arithmetic_variance<double, 2> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.capacity(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), true);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
}

void test_one()
{
    trial::online::average::arithmetic_variance<double, 2> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
}

void test_same()
{
    trial::online::average::arithmetic_variance<double, 2> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), true);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
}

void test_two()
{
    trial::online::average::arithmetic_variance<double, 2> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 2.0);
}

void test_three()
{
    trial::online::average::arithmetic_variance<double, 2> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 2.0);
    filter.push(0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.5);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 4.5);
}

void test_clear()
{
    trial::online::average::arithmetic_variance<double, 2> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    filter.clear();
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    filter.push(2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
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

} // namespace arithmetic_variance_2_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    arithmetic_variance_1_suite::test();
    arithmetic_variance_2_suite::test();

    return boost::report_errors();
}
