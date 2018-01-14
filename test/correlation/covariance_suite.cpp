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
#include <trial/online/average/cumulative.hpp>
#include <trial/online/average/arithmetic.hpp>
#include <trial/online/correlation/covariance.hpp>

//-----------------------------------------------------------------------------

namespace default_double_suite
{

void test_empty()
{
    trial::online::correlation::covariance<double> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.normalized_value(), 0.0);
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
    TRIAL_ONLINE_TEST_EQUAL(filter.normalized_value(), 0.0);
    filter.push(2.0, 2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.normalized_value(), 0.0);
    filter.push(2.0, 2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.normalized_value(), 0.0);
}

void test_same_increment_by_one()
{
    const double tolerance = 1e-6;
    trial::online::correlation::covariance<double> filter;
    filter.push(1.0, 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.normalized_value(), 0.0);
    filter.push(2.0, 2.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), 0.25, tolerance);
    filter.push(3.0, 3.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), 0.666667, tolerance);
    filter.push(4.0, 4.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1.666667, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), 1.25, tolerance);
    filter.push(5.0, 5.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), 2.0, tolerance);
}

void test_same_increment_by_half()
{
    const double tolerance = 1e-6;
    trial::online::correlation::covariance<double> filter;
    filter.push(1.0, 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.normalized_value(), 0.0);
    filter.push(1.5, 1.5);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.125, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), 0.0625, tolerance);
    filter.push(2.0, 2.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.25, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), 0.166667, tolerance);
    filter.push(2.5, 2.5);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.416667, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), 0.3125, tolerance);
    filter.push(3.0, 3.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.625, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), 0.5, tolerance);
}

void test_shifted_no_increment()
{
    trial::online::correlation::covariance<double> filter;
    filter.push(1.0, 2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.normalized_value(), 0.0);
    filter.push(1.0, 2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.normalized_value(), 0.0);
    filter.push(1.0, 2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.normalized_value(), 0.0);
}

void test_shifted_increment_by_one()
{
    const double tolerance = 1e-6;
    trial::online::correlation::covariance<double> filter;
    filter.push(1.0, 2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.normalized_value(), 0.0);
    filter.push(2.0, 3.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), 0.25, tolerance);
    filter.push(3.0, 4.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), 0.666667, tolerance);
    filter.push(4.0, 5.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1.666667, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), 1.25, tolerance);
    filter.push(5.0, 6.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), 2.0, tolerance);
}

void test_up_down_by_one()
{
    const double tolerance = 1e-6;
    trial::online::correlation::covariance<double> filter;
    filter.push(0.0, 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.normalized_value(), 0.0);
    filter.push(1.0, -1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), -0.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), -0.25, tolerance);
    filter.push(2.0, -2.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), -1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), -0.666667, tolerance);
    filter.push(3.0, -3.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), -1.666667, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), -1.25, tolerance);
    filter.push(4.0, -4.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), -2.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), -2.0, tolerance);
}

void test_down_up_by_one()
{
    const double tolerance = 1e-6;
    trial::online::correlation::covariance<double> filter;
    filter.push(0.0, 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.normalized_value(), 0.0);
    filter.push(-1.0, 1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), -0.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), -0.25, tolerance);
    filter.push(-2.0, 2.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), -1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), -0.666667, tolerance);
    filter.push(-3.0, 3.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), -1.666667, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), -1.25, tolerance);
    filter.push(-4.0, 4.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), -2.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), -2.0, tolerance);
}

void run()
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

} // namespace default_double_suite

//-----------------------------------------------------------------------------

namespace default_properties_suite
{

void test_constant()
{
    // Cov(X, a) = 0
    const double a = 0.0;
    trial::online::correlation::covariance<double> filter;
    filter.push(0.0, a);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.normalized_value(), 0.0);
    filter.push(1.0, a);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.normalized_value(), 0.0);
    filter.push(10.0, a);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.normalized_value(), 0.0);
    filter.push(100.0, a);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.normalized_value(), 0.0);
}

void test_same()
{
    // Cov(X, X) = Var(X)
    const double tolerance = 1e-6;
    trial::online::correlation::covariance<double> filter;
    trial::online::average::cumulative_variance<double> average;
    {
        double x = 0.0;
        filter.push(x, x);
        TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.0, tolerance);
        TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), 0.0, tolerance);
        average.push(x);
        TRIAL_ONLINE_TEST_CLOSE(filter.value(), average.variance(), tolerance);
    }
    {
        double x = 1.0;
        filter.push(x, x);
        TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.5, tolerance);
        TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), 0.25, tolerance);
        average.push(x);
        TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), average.variance(), tolerance);
    }
    {
        double x = 10.0;
        filter.push(x, x);
        TRIAL_ONLINE_TEST_CLOSE(filter.value(), 30.333333, tolerance);
        TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), 20.222222, tolerance);
        average.push(x);
        TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), average.variance(), tolerance);
    }
    {
        double x = 100.0;
        filter.push(x, x);
        TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2340.25, tolerance);
        TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), 1755.1875, tolerance);
        average.push(x);
        TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), average.variance(), tolerance);
    }
}

void test_commutative()
{
    // Cov(X, Y) = Cov(Y, X)
    const double tolerance = 1e-6;
    trial::online::correlation::covariance<double> lhs;
    trial::online::correlation::covariance<double> rhs;
    {
        const double x = 0.0;
        const double y = 0.0;
        lhs.push(x, y);
        rhs.push(y, x);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), rhs.value(), tolerance);
    }
    {
        const double x = -1.0;
        const double y = 1.0;
        lhs.push(x, y);
        rhs.push(y, x);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), rhs.value(), tolerance);
    }
    {
        const double x = -2.0;
        const double y = 10.0;
        lhs.push(x, y);
        rhs.push(y, x);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), rhs.value(), tolerance);
    }
    {
        const double x = -3.0;
        const double y = 100.0;
        lhs.push(x, y);
        rhs.push(y, x);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), rhs.value(), tolerance);
    }
    {
        const double x = -4.0;
        const double y = 1000.0;
        lhs.push(x, y);
        rhs.push(y, x);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), rhs.value(), tolerance);
    }
}

void test_distributive()
{
    // Cov(aX, bY) = ab Cov(Y, X)
    const double tolerance = 1e-6;
    trial::online::correlation::covariance<double> lhs;
    trial::online::correlation::covariance<double> rhs;
    const double a = 0.5;
    const double b = 2.0;
    {
        const double x = 0.0;
        const double y = 0.0;
        lhs.push(a * x, b * y);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), a * b * rhs.value(), tolerance);
    }
    {
        const double x = -1.0;
        const double y = 1.0;
        lhs.push(a * x, b * y);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), a * b * rhs.value(), tolerance);
    }
    {
        const double x = -2.0;
        const double y = 10.0;
        lhs.push(a * x, b * y);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), a * b * rhs.value(), tolerance);
    }
    {
        const double x = -3.0;
        const double y = 100.0;
        lhs.push(a * x, b * y);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), a * b * rhs.value(), tolerance);
    }
    {
        const double x = -4.0;
        const double y = 1000.0;
        lhs.push(a * x, b * y);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), a * b * rhs.value(), tolerance);
    }
}

void test_shift_invariant()
{
    // Cov(X + a, Y + b) = Cov(X, Y)
    const double tolerance = 1e-6;
    trial::online::correlation::covariance<double> lhs;
    trial::online::correlation::covariance<double> rhs;
    const double a = 0.5;
    const double b = 2.0;
    {
        const double x = 0.0;
        const double y = 0.0;
        lhs.push(x + a, y + b);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), rhs.value(), tolerance);
    }
    {
        const double x = -1.0;
        const double y = 1.0;
        lhs.push(x + a, y + b);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), rhs.value(), tolerance);
    }
    {
        const double x = -2.0;
        const double y = 10.0;
        lhs.push(x + a, y + b);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), rhs.value(), tolerance);
    }
    {
        const double x = -3.0;
        const double y = 100.0;
        lhs.push(x + a, y + b);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), rhs.value(), tolerance);
    }
    {
        const double x = -4.0;
        const double y = 1000.0;
        lhs.push(x + a, y + b);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), rhs.value(), tolerance);
    }
}

void run()
{
    test_constant();
    test_same();
    test_commutative();
    test_distributive();
    test_shift_invariant();
}

} // namespace default_properties_suite

//-----------------------------------------------------------------------------

namespace arithmetic_properties_suite
{

template <typename T, int Moment>
using average_type = trial::online::average::basic_arithmetic<T, 64, Moment>;

template <typename T>
using covariance_type = trial::online::correlation::basic_covariance<T, average_type>;

void test_constant()
{
    // Cov(X, a) = 0
    const double a = 0.0;
    covariance_type<double> filter;
    filter.push(0.0, a);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    filter.push(1.0, a);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    filter.push(10.0, a);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    filter.push(100.0, a);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
}

void test_same()
{
    // Cov(X, X) = Var(X)
    const double tolerance = 1e-6;
    covariance_type<double> filter;
    average_type<double, 2> average;
    {
        double x = 0.0;
        filter.push(x, x);
        TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.0, tolerance);
        TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), 0.0, tolerance);
        average.push(x);
        TRIAL_ONLINE_TEST_CLOSE(filter.value(), average.variance(), tolerance);
    }
    {
        double x = 1.0;
        filter.push(x, x);
        average.push(x);
        TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.5, tolerance);
        TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), 0.25, tolerance);
        TRIAL_ONLINE_TEST_CLOSE(filter.value(), average.variance(), tolerance);
    }
    {
        double x = 10.0;
        filter.push(x, x);
        average.push(x);
        TRIAL_ONLINE_TEST_CLOSE(filter.value(), 30.333333, tolerance);
        TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), 20.222222, tolerance);
        TRIAL_ONLINE_TEST_CLOSE(filter.value(), average.variance(), tolerance);
    }
    {
        double x = 100.0;
        filter.push(x, x);
        average.push(x);
        TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2340.25, tolerance);
        TRIAL_ONLINE_TEST_CLOSE(filter.normalized_value(), 1755.1875, tolerance);
        TRIAL_ONLINE_TEST_CLOSE(filter.value(), average.variance(), tolerance);
    }
}

void test_commutative()
{
    // Cov(X, Y) = Cov(Y, X)
    const double tolerance = 1e-6;
    covariance_type<double> lhs;
    covariance_type<double> rhs;
    {
        const double x = 0.0;
        const double y = 0.0;
        lhs.push(x, y);
        rhs.push(y, x);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), rhs.value(), tolerance);
    }
    {
        const double x = -1.0;
        const double y = 1.0;
        lhs.push(x, y);
        rhs.push(y, x);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), rhs.value(), tolerance);
    }
    {
        const double x = -2.0;
        const double y = 10.0;
        lhs.push(x, y);
        rhs.push(y, x);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), rhs.value(), tolerance);
    }
    {
        const double x = -3.0;
        const double y = 100.0;
        lhs.push(x, y);
        rhs.push(y, x);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), rhs.value(), tolerance);
    }
    {
        const double x = -4.0;
        const double y = 1000.0;
        lhs.push(x, y);
        rhs.push(y, x);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), rhs.value(), tolerance);
    }
}

void test_distributive()
{
    // Cov(aX, bY) = ab Cov(Y, X)
    const double tolerance = 1e-6;
    covariance_type<double> lhs;
    covariance_type<double> rhs;
    const double a = 0.5;
    const double b = 2.0;
    {
        const double x = 0.0;
        const double y = 0.0;
        lhs.push(a * x, b * y);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), a * b * rhs.value(), tolerance);
    }
    {
        const double x = -1.0;
        const double y = 1.0;
        lhs.push(a * x, b * y);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), a * b * rhs.value(), tolerance);
    }
    {
        const double x = -2.0;
        const double y = 10.0;
        lhs.push(a * x, b * y);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), a * b * rhs.value(), tolerance);
    }
    {
        const double x = -3.0;
        const double y = 100.0;
        lhs.push(a * x, b * y);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), a * b * rhs.value(), tolerance);
    }
    {
        const double x = -4.0;
        const double y = 1000.0;
        lhs.push(a * x, b * y);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), a * b * rhs.value(), tolerance);
    }
}

void test_shift_invariant()
{
    // Cov(X + a, Y + b) = Cov(X, Y)
    const double tolerance = 1e-6;
    covariance_type<double> lhs;
    covariance_type<double> rhs;
    const double a = 0.5;
    const double b = 2.0;
    {
        const double x = 0.0;
        const double y = 0.0;
        lhs.push(x + a, y + b);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), rhs.value(), tolerance);
    }
    {
        const double x = -1.0;
        const double y = 1.0;
        lhs.push(x + a, y + b);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), rhs.value(), tolerance);
    }
    {
        const double x = -2.0;
        const double y = 10.0;
        lhs.push(x + a, y + b);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), rhs.value(), tolerance);
    }
    {
        const double x = -3.0;
        const double y = 100.0;
        lhs.push(x + a, y + b);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), rhs.value(), tolerance);
    }
    {
        const double x = -4.0;
        const double y = 1000.0;
        lhs.push(x + a, y + b);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.value(), rhs.value(), tolerance);
    }
}

void run()
{
    test_constant();
    test_same();
    test_commutative();
    test_distributive();
    test_shift_invariant();
}

} // namespace arithmetic_properties_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    default_double_suite::run();
    default_properties_suite::run();
    arithmetic_properties_suite::run();

    return boost::report_errors();
}
