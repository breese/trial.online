///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/online/detail/lightweight_test.hpp>
#include <trial/online/correlation/covariance.hpp>

//-----------------------------------------------------------------------------

namespace double_suite
{

void test_empty()
{
    trial::online::correlation::covariance<double> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
}

void test_clear()
{
    trial::online::correlation::covariance<double> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    filter.push(0.0, 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    filter.clear();
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
}

void test_same_no_increment()
{
    trial::online::correlation::covariance<double> filter;
    filter.push(2.0, 2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    filter.push(2.0, 2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    filter.push(2.0, 2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
}

void test_same_increment_by_one()
{
    const double tolerance = 1e-6;
    trial::online::correlation::covariance<double> filter;
    filter.push(1.0, 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    filter.push(2.0, 2.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.25, tolerance);
    filter.push(3.0, 3.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.666667, tolerance);
    filter.push(4.0, 4.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1.25, tolerance);
    filter.push(5.0, 5.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2.0, tolerance);
}

void test_same_increment_by_half()
{
    const double tolerance = 1e-6;
    trial::online::correlation::covariance<double> filter;
    filter.push(1.0, 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    filter.push(1.5, 1.5);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.0625, tolerance);
    filter.push(2.0, 2.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.166667, tolerance);
    filter.push(2.5, 2.5);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.3125, tolerance);
    filter.push(3.0, 3.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.5, tolerance);
}

void test_shifted_no_increment()
{
    trial::online::correlation::covariance<double> filter;
    filter.push(1.0, 2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    filter.push(1.0, 2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    filter.push(1.0, 2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
}

void test_shifted_increment_by_one()
{
    const double tolerance = 1e-6;
    trial::online::correlation::covariance<double> filter;
    filter.push(1.0, 2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    filter.push(2.0, 3.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.25, tolerance);
    filter.push(3.0, 4.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.666667, tolerance);
    filter.push(4.0, 5.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1.25, tolerance);
    filter.push(5.0, 6.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2.0, tolerance);
}

void test_up_down_by_one()
{
    const double tolerance = 1e-6;
    trial::online::correlation::covariance<double> filter;
    filter.push(0.0, 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    filter.push(1.0, -1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), -0.25, tolerance);
    filter.push(2.0, -2.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), -0.666667, tolerance);
    filter.push(3.0, -3.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), -1.25, tolerance);
    filter.push(4.0, -4.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), -2.0, tolerance);
}

void test_down_up_by_one()
{
    const double tolerance = 1e-6;
    trial::online::correlation::covariance<double> filter;
    filter.push(0.0, 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    filter.push(-1.0, 1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), -0.25, tolerance);
    filter.push(-2.0, 2.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), -0.666667, tolerance);
    filter.push(-3.0, 3.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), -1.25, tolerance);
    filter.push(-4.0, 4.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), -2.0, tolerance);
}

void test()
{
    test_empty();
    test_clear();
    test_same_no_increment();
    test_same_increment_by_one();
    test_same_increment_by_half();
    test_shifted_no_increment();
    test_shifted_increment_by_one();
    test_up_down_by_one();
    test_down_up_by_one();
}

} // namespace double_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    double_suite::test();

    return boost::report_errors();
}
