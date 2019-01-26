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
#include <trial/online/detail/functional.hpp>
#include <trial/online/window/moment.hpp>
#include <trial/online/window/comoment.hpp>

using namespace trial::online;

//-----------------------------------------------------------------------------

namespace properties_suite
{

void test_constant()
{
    // Cov(X, a) = 0
    const double a = 0.0;
    window::covariance<double, 32> filter;
    filter.push(0.0, a);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    filter.push(1.0, a);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    filter.push(10.0, a);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    filter.push(100.0, a);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
}

void test_same()
{
    // Cov(X, X) = Var(X)
    const double tolerance = 1e-6;
    window::covariance<double, 32> filter;
    window::moment_variance<double, 32> average;
    {
        double x = 0.0;
        filter.push(x, x);
        TRIAL_ONLINE_TEST_CLOSE(filter.unbiased_variance(), 0.0, tolerance);
        TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.0, tolerance);
        average.push(x);
        TRIAL_ONLINE_TEST_CLOSE(filter.variance(), average.variance(), tolerance);
    }
    {
        double x = 1.0;
        filter.push(x, x);
        average.push(x);
        TRIAL_ONLINE_TEST_CLOSE(filter.unbiased_variance(), 0.5, tolerance);
        TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.25, tolerance);
        TRIAL_ONLINE_TEST_CLOSE(filter.variance(), average.variance(), tolerance);
    }
    {
        double x = 10.0;
        filter.push(x, x);
        average.push(x);
        TRIAL_ONLINE_TEST_CLOSE(filter.unbiased_variance(), 30.333333, tolerance);
        TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 20.222222, tolerance);
        TRIAL_ONLINE_TEST_CLOSE(filter.variance(), average.variance(), tolerance);
    }
    {
        double x = 100.0;
        filter.push(x, x);
        average.push(x);
        TRIAL_ONLINE_TEST_CLOSE(filter.unbiased_variance(), 2340.25, tolerance);
        TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 1755.1875, tolerance);
        TRIAL_ONLINE_TEST_CLOSE(filter.variance(), average.variance(), tolerance);
    }
}

void test_commutative()
{
    // Cov(X, Y) = Cov(Y, X)
    const double tolerance = 1e-6;
    window::covariance<double, 32> lhs;
    window::covariance<double, 32> rhs;
    {
        const double x = 0.0;
        const double y = 0.0;
        lhs.push(x, y);
        rhs.push(y, x);
        TRIAL_ONLINE_TEST_CLOSE(lhs.unbiased_variance(), rhs.unbiased_variance(), tolerance);
        TRIAL_ONLINE_TEST_CLOSE(lhs.variance(), rhs.variance(), tolerance);
    }
    {
        const double x = -1.0;
        const double y = 1.0;
        lhs.push(x, y);
        rhs.push(y, x);
        TRIAL_ONLINE_TEST_CLOSE(lhs.unbiased_variance(), rhs.unbiased_variance(), tolerance);
        TRIAL_ONLINE_TEST_CLOSE(lhs.variance(), rhs.variance(), tolerance);
    }
    {
        const double x = -2.0;
        const double y = 10.0;
        lhs.push(x, y);
        rhs.push(y, x);
        TRIAL_ONLINE_TEST_CLOSE(lhs.unbiased_variance(), rhs.unbiased_variance(), tolerance);
        TRIAL_ONLINE_TEST_CLOSE(lhs.variance(), rhs.variance(), tolerance);
    }
    {
        const double x = -3.0;
        const double y = 100.0;
        lhs.push(x, y);
        rhs.push(y, x);
        TRIAL_ONLINE_TEST_CLOSE(lhs.unbiased_variance(), rhs.unbiased_variance(), tolerance);
        TRIAL_ONLINE_TEST_CLOSE(lhs.variance(), rhs.variance(), tolerance);
    }
    {
        const double x = -4.0;
        const double y = 1000.0;
        lhs.push(x, y);
        rhs.push(y, x);
        TRIAL_ONLINE_TEST_CLOSE(lhs.unbiased_variance(), rhs.unbiased_variance(), tolerance);
        TRIAL_ONLINE_TEST_CLOSE(lhs.variance(), rhs.variance(), tolerance);
    }
}

void test_distributive()
{
    // Cov(aX, bY) = ab Cov(Y, X)
    const double tolerance = 1e-6;
    window::covariance<double, 32> lhs;
    window::covariance<double, 32> rhs;
    const double a = 0.5;
    const double b = 2.0;
    {
        const double x = 0.0;
        const double y = 0.0;
        lhs.push(a * x, b * y);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.unbiased_variance(), a * b * rhs.unbiased_variance(), tolerance);
        TRIAL_ONLINE_TEST_CLOSE(lhs.variance(), a * b * rhs.variance(), tolerance);
    }
    {
        const double x = -1.0;
        const double y = 1.0;
        lhs.push(a * x, b * y);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.unbiased_variance(), a * b * rhs.unbiased_variance(), tolerance);
        TRIAL_ONLINE_TEST_CLOSE(lhs.variance(), a * b * rhs.variance(), tolerance);
    }
    {
        const double x = -2.0;
        const double y = 10.0;
        lhs.push(a * x, b * y);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.unbiased_variance(), a * b * rhs.unbiased_variance(), tolerance);
        TRIAL_ONLINE_TEST_CLOSE(lhs.variance(), a * b * rhs.variance(), tolerance);
    }
    {
        const double x = -3.0;
        const double y = 100.0;
        lhs.push(a * x, b * y);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.unbiased_variance(), a * b * rhs.unbiased_variance(), tolerance);
        TRIAL_ONLINE_TEST_CLOSE(lhs.variance(), a * b * rhs.variance(), tolerance);
    }
    {
        const double x = -4.0;
        const double y = 1000.0;
        lhs.push(a * x, b * y);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.unbiased_variance(), a * b * rhs.unbiased_variance(), tolerance);
        TRIAL_ONLINE_TEST_CLOSE(lhs.variance(), a * b * rhs.variance(), tolerance);
    }
}

void test_shift_invariant()
{
    // Cov(X + a, Y + b) = Cov(X, Y)
    const double tolerance = 1e-6;
    window::covariance<double, 32> lhs;
    window::covariance<double, 32> rhs;
    const double a = 0.5;
    const double b = 2.0;
    {
        const double x = 0.0;
        const double y = 0.0;
        lhs.push(x + a, y + b);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.unbiased_variance(), rhs.unbiased_variance(), tolerance);
        TRIAL_ONLINE_TEST_CLOSE(lhs.variance(), rhs.variance(), tolerance);
    }
    {
        const double x = -1.0;
        const double y = 1.0;
        lhs.push(x + a, y + b);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.unbiased_variance(), rhs.unbiased_variance(), tolerance);
        TRIAL_ONLINE_TEST_CLOSE(lhs.variance(), rhs.variance(), tolerance);
    }
    {
        const double x = -2.0;
        const double y = 10.0;
        lhs.push(x + a, y + b);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.unbiased_variance(), rhs.unbiased_variance(), tolerance);
        TRIAL_ONLINE_TEST_CLOSE(lhs.variance(), rhs.variance(), tolerance);
    }
    {
        const double x = -3.0;
        const double y = 100.0;
        lhs.push(x + a, y + b);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.unbiased_variance(), rhs.unbiased_variance(), tolerance);
        TRIAL_ONLINE_TEST_CLOSE(lhs.variance(), rhs.variance(), tolerance);
    }
    {
        const double x = -4.0;
        const double y = 1000.0;
        lhs.push(x + a, y + b);
        rhs.push(x, y);
        TRIAL_ONLINE_TEST_CLOSE(lhs.unbiased_variance(), rhs.unbiased_variance(), tolerance);
        TRIAL_ONLINE_TEST_CLOSE(lhs.variance(), rhs.variance(), tolerance);
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

} // namespace properties_suite

//-----------------------------------------------------------------------------

namespace double_suite
{

void test_empty()
{
    window::covariance<double, 4> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
}

void test_same_no_increment()
{
    window::covariance<double, 4> filter;
    filter.push(2.0, 2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
    filter.push(2.0, 2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
    filter.push(2.0, 2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
    filter.push(2.0, 2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
    filter.push(2.0, 2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
}

void test_same_increment_by_one()
{
    const double tolerance = 1e-6;
    window::covariance<double, 4> filter;
    filter.push(1.0, 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
    filter.push(2.0, 2.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.25, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.unbiased_variance(), 0.5, tolerance);
    filter.push(3.0, 3.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.666667, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.unbiased_variance(), 1.0, tolerance);
    filter.push(4.0, 4.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 1.25, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.unbiased_variance(), 1.666667, tolerance);
    // Window full
    filter.push(5.0, 5.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 1.25, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.unbiased_variance(), 1.666667, tolerance);
}

void test_same_increment_by_half()
{
    const double tolerance = 1e-6;
    window::covariance<double, 4> filter;
    filter.push(1.0, 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
    filter.push(1.5, 1.5);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.0625, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.unbiased_variance(), 0.125, tolerance);
    filter.push(2.0, 2.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.166667, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.unbiased_variance(), 0.25, tolerance);
    filter.push(2.5, 2.5);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.3125, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.unbiased_variance(), 0.416667, tolerance);
    // Window full
    filter.push(3.0, 3.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.3125, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.unbiased_variance(), 0.416667, tolerance);
}

void test_exponential_increase()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    window::covariance<double, 4> filter;
    filter.push(1e0, 1e0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
    filter.push(1e1, 1e1);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 20.25, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_variance(), 40.5, tolerance);
    filter.push(1e2, 1e2);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1998.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_variance(), 2997.0, tolerance);
    filter.push(1e3, 1e3);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.7538e5, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_variance(), 2.3384e5, tolerance);
    filter.push(1e4, 1e4);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.7538e7, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_variance(), 2.3384e7, tolerance);
    filter.push(1e5, 1e5);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.7538e9, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_variance(), 2.3384e9, tolerance);
    filter.push(1e6, 1e6);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.7538e11, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_variance(), 2.3384e11, tolerance);
}

void test_clear()
{
    window::covariance<double, 4> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    filter.push(0.0, 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    filter.clear();
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
}

void run()
{
    test_empty();
    test_clear();
    test_same_no_increment();
    test_same_increment_by_one();
    test_same_increment_by_half();
    test_exponential_increase();
}

} // namespace double_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    properties_suite::run();
    double_suite::run();

    return boost::report_errors();
}
