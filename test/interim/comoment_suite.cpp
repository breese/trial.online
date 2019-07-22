///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/online/detail/lightweight_test.hpp>
#include <trial/online/detail/functional.hpp>
#include <trial/online/interim/comoment.hpp>

using namespace trial::online;

//-----------------------------------------------------------------------------

namespace api_suite
{

void test_ctor()
{
    interim::covariance<double, 4> filter;
    filter.push(1.0, 1.0);
    TRIAL_TEST(!filter.empty());

    // Copy constructor
    interim::covariance<double, 4> copy(filter);
    TRIAL_TEST(!copy.empty());

    // Copy assignment
    interim::covariance<double, 4> assign;
    assign = filter;
    TRIAL_TEST(!assign.empty());

    // Move constructor
    interim::covariance<double, 4> mover(std::move(copy));
    TRIAL_TEST(!mover.empty());

    // Move assignment
    interim::covariance<double, 4> massign;
    massign = std::move(assign);
    TRIAL_TEST(!massign.empty());
}

void test_clear()
{
    interim::covariance<double, 4> filter;
    filter.push(1.0, 1.0);
    TRIAL_TEST_EQ(filter.size(), 1);

    filter.clear();
    TRIAL_TEST_EQ(filter.size(), 0);
}

void test_capacity()
{
    interim::covariance<double, 4> filter;
    TRIAL_TEST_EQ(filter.capacity(), 4);
}

void test_size()
{
    interim::covariance<double, 4> filter;
    TRIAL_TEST_EQ(filter.size(), 0);
    filter.push(1.0, 1.0);
    TRIAL_TEST_EQ(filter.size(), 1);
    filter.push(2.0, 2.0);
    TRIAL_TEST_EQ(filter.size(), 2);
    filter.push(3.0, 3.0);
    TRIAL_TEST_EQ(filter.size(), 3);
    filter.push(4.0, 4.0);
    TRIAL_TEST_EQ(filter.size(), 4);
    filter.push(5.0, 5.0);
    TRIAL_TEST_EQ(filter.size(), 4);
}

void test_empty()
{
    interim::covariance<double, 4> filter;
    TRIAL_TEST(filter.empty());
    filter.push(1.0, 1.0);
    TRIAL_TEST(!filter.empty());
}

void test_full()
{
    interim::covariance<double, 4> filter;
    TRIAL_TEST(!filter.full());
    filter.push(1.0, 1.0);
    filter.push(2.0, 2.0);
    filter.push(3.0, 3.0);
    TRIAL_TEST(!filter.full());
    filter.push(4.0, 4.0);
    TRIAL_TEST(filter.full());
    filter.push(5.0, 5.0);
    TRIAL_TEST(filter.full());
}

void run()
{
    test_ctor();
    test_clear();
    test_capacity();
    test_size();
    test_empty();
    test_full();
}

} // namespace api_suite

//-----------------------------------------------------------------------------

namespace double_4_suite
{

void test_same_no_increment()
{
    interim::covariance<double, 4> filter;

    filter.push(2.0, 2.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);

    filter.push(2.0, 2.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);

    filter.push(2.0, 2.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);

    filter.push(2.0, 2.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);

    // Window full
    filter.push(2.0, 2.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);

    filter.push(2.0, 2.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);

    filter.push(2.0, 2.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);

    filter.push(2.0, 2.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
}

void test_same_increment_by_one()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    interim::covariance<double, 4> filter;

    filter.push(1.0, 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);

    filter.push(2.0, 2.0);
    TRIAL_TEST_WITH(filter.variance(), 0.25, tolerance);

    filter.push(3.0, 3.0);
    TRIAL_TEST_WITH(filter.variance(), 0.666667, tolerance);

    filter.push(4.0, 4.0);
    TRIAL_TEST_WITH(filter.variance(), 1.25, tolerance);

    // Window full
    filter.push(5.0, 5.0);
    TRIAL_TEST_WITH(filter.variance(), 1.25, tolerance);

    filter.push(6.0, 6.0);
    TRIAL_TEST_WITH(filter.variance(), 1.06818, tolerance); // 1.25

    filter.push(7.0, 7.0);
    TRIAL_TEST_WITH(filter.variance(), 0.95833, tolerance); // 1.25

    filter.push(8.0, 8.0);
    TRIAL_TEST_WITH(filter.variance(), 1.25, tolerance);
}

void test_same_increment_by_half()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    interim::covariance<double, 4> filter;

    filter.push(1.0, 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);

    filter.push(1.5, 1.5);
    TRIAL_TEST_WITH(filter.variance(), 0.0625, tolerance);

    filter.push(2.0, 2.0);
    TRIAL_TEST_WITH(filter.variance(), 0.166667, tolerance);

    filter.push(2.5, 2.5);
    TRIAL_TEST_WITH(filter.variance(), 0.3125, tolerance);

    // Window full
    filter.push(3.0, 3.0);
    TRIAL_TEST_WITH(filter.variance(), 0.3125, tolerance);

    filter.push(3.5, 3.5);
    TRIAL_TEST_WITH(filter.variance(), 0.267045, tolerance); // 0.3125

    filter.push(4.0, 4.0);
    TRIAL_TEST_WITH(filter.variance(), 0.239583, tolerance); // 0.3125

    filter.push(4.5, 4.5);
    TRIAL_TEST_WITH(filter.variance(), 0.3125, tolerance);
}

void test_exponential_increase()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    interim::covariance<double, 4> filter;

    std::cout << sizeof(filter) << std::endl;
    filter.push(1e0, 1e0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);

    filter.push(1e1, 1e1);
    TRIAL_TEST_WITH(filter.variance(), 20.25, tolerance);

    filter.push(1e2, 1e2);
    TRIAL_TEST_WITH(filter.variance(), 1998.0, tolerance);

    filter.push(1e3, 1e3);
    TRIAL_TEST_WITH(filter.variance(), 1.7538e5, tolerance);

    // Window full
    filter.push(1e4, 1e4);
    TRIAL_TEST_WITH(filter.variance(), 1.7538e5, tolerance); // 1.7538e7

    filter.push(1e5, 1e5);
    TRIAL_TEST_WITH(filter.variance(), 3.68325e8, tolerance); // 1.7538e9

    filter.push(1e6, 1e6);
    TRIAL_TEST_WITH(filter.variance(), 9.99001e10, tolerance); // 1.7538e11
}

void run()
{
    test_same_no_increment();
    test_same_increment_by_one();
    test_same_increment_by_half();
    test_exponential_increase();
}

} // namespace double_4_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    api_suite::run();
    double_4_suite::run();

    return boost::report_errors();
}
