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
#include <trial/online/interim/moment.hpp>

using namespace trial::online;

//-----------------------------------------------------------------------------

namespace mean_api_suite
{

void test_ctor()
{
    interim::moment<double, 4> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST(!filter.empty());

    // Copy constructor
    interim::moment<double, 4> copy(filter);
    TRIAL_ONLINE_TEST(!copy.empty());

    // Copy assignment
    interim::moment<double, 4> assign;
    assign = filter;
    TRIAL_ONLINE_TEST(!assign.empty());

    // Move constructor
    interim::moment<double, 4> mover(std::move(copy));
    TRIAL_ONLINE_TEST(!mover.empty());

    // Move assignment
    interim::moment<double, 4> massign;
    massign = std::move(assign);
    TRIAL_ONLINE_TEST(!massign.empty());
}

void test_clear()
{
    interim::moment<double, 4> filter;
    filter.push(1.0);
    filter.push(2.0);
    filter.push(3.0);
    filter.push(4.0);
    filter.push(5.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 4);
    filter.clear();
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
}

void test_capacity()
{
    interim::moment<double, 4> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.capacity(), 4);
}

void test_size()
{
    interim::moment<double, 4> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    filter.push(2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 3);
    filter.push(4.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 4);
    filter.push(5.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 4);
}

void test_empty()
{
    interim::moment<double, 4> filter;
    TRIAL_ONLINE_TEST(filter.empty());
    filter.push(1.0);
    TRIAL_ONLINE_TEST(!filter.empty());
}

void test_full()
{
    interim::moment<double, 4> filter;
    TRIAL_ONLINE_TEST(!filter.full());
    filter.push(1.0);
    filter.push(2.0);
    filter.push(3.0);
    TRIAL_ONLINE_TEST(!filter.full());
    filter.push(4.0);
    TRIAL_ONLINE_TEST(filter.full());
    filter.push(5.0);
    TRIAL_ONLINE_TEST(filter.full());
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

} // namespace mean_api_suite

//-----------------------------------------------------------------------------

namespace mean_double_suite
{

void test_same()
{
    interim::moment<double, 4> filter;

    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.0);

    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.0);

    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 3);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.0);

    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.0);

    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.0);
}

void test_linear_increase()
{
    interim::moment<double, 4> filter;

    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.0);

    filter.push(2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.5);

    filter.push(3.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 3);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 2.0);

    filter.push(4.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 2.5);

    // Window is full

    filter.push(5.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 3.5);

    filter.push(6.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 4.5);
}

void test_linear_increase_from_offset()
{
    interim::moment<double, 4> filter;
    filter.push(10.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 10.0);
    filter.push(11.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 10.5);
    filter.push(12.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 11.0);
    filter.push(13.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 11.5);
    filter.push(14.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 12.5);
    filter.push(15.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 13.5);
}

void test_linear_decrease()
{
    interim::moment<double, 4> filter;
    filter.push(10.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 10.0);
    filter.push(9.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 9.5);
    filter.push(8.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 9.0);
    filter.push(7.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 8.5);
    filter.push(6.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 7.5);
    filter.push(5.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 6.5);
}

void run()
{
    test_same();
    test_linear_increase();
    test_linear_increase_from_offset();
    test_linear_decrease();
}

} // namespace mean_double_suite

//-----------------------------------------------------------------------------

namespace variance_api_suite
{

void test_ctor()
{
    interim::moment_variance<double, 4> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST(!filter.empty());

    // Copy constructor
    interim::moment_variance<double, 4> copy(filter);
    TRIAL_ONLINE_TEST(!copy.empty());

    // Copy assignment
    interim::moment_variance<double, 4> assign;
    assign = filter;
    TRIAL_ONLINE_TEST(!assign.empty());

    // Move constructor
    interim::moment_variance<double, 4> mover(std::move(copy));
    TRIAL_ONLINE_TEST(!mover.empty());

    // Move assignment
    interim::moment_variance<double, 4> massign;
    massign = std::move(assign);
    TRIAL_ONLINE_TEST(!massign.empty());
}

void test_clear()
{
    interim::moment_variance<double, 4> filter;
    filter.push(1.0);
    filter.push(2.0);
    filter.push(3.0);
    filter.push(4.0);
    filter.push(5.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 4);
    filter.clear();
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
}

void test_capacity()
{
    interim::moment_variance<double, 4> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.capacity(), 4);
}

void test_size()
{
    interim::moment_variance<double, 4> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    filter.push(2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 3);
    filter.push(4.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 4);
    filter.push(5.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 4);
}

void test_empty()
{
    interim::moment_variance<double, 4> filter;
    TRIAL_ONLINE_TEST(filter.empty());
    filter.push(1.0);
    TRIAL_ONLINE_TEST(!filter.empty());
}

void test_full()
{
    interim::moment_variance<double, 4> filter;
    TRIAL_ONLINE_TEST(!filter.full());
    filter.push(1.0);
    filter.push(2.0);
    filter.push(3.0);
    TRIAL_ONLINE_TEST(!filter.full());
    filter.push(4.0);
    TRIAL_ONLINE_TEST(filter.full());
    filter.push(5.0);
    TRIAL_ONLINE_TEST(filter.full());
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

} // namespace variance_api_suite

//-----------------------------------------------------------------------------

namespace variance_double_suite
{

void test_linear_increase()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    interim::moment_variance<double, 4> filter;

    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.0);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 0.0, tolerance);

    filter.push(2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.5);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 0.25, tolerance);

    filter.push(3.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 2.0);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 0.666667, tolerance);

    filter.push(4.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 2.5);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.25, tolerance);

    // Window is full

    filter.push(5.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 3.5);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.25, tolerance); // 1.25

    filter.push(6.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 4.5);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.06818, tolerance); // 1.25

    filter.push(7.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 5.5);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 0.958333, tolerance); // 1.25

    filter.push(8.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 6.5);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.25, tolerance); // 1.25

    filter.push(9.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 7.5);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.25, tolerance); // 1.25
}

void test_scatter()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    interim::moment_variance<double, 4> filter;

    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);

    filter.push(3.0);
    TRIAL_ONLINE_TEST_WITH(filter.mean(), 2.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.0, tolerance);

    filter.push(0.0);
    TRIAL_ONLINE_TEST_WITH(filter.mean(), 1.33333, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.55556, tolerance);

    filter.push(5.0);
    TRIAL_ONLINE_TEST_WITH(filter.mean(), 2.25, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 3.6875, tolerance);

    // Window is full

    filter.push(2.0);
    TRIAL_ONLINE_TEST_WITH(filter.mean(), 2.15, tolerance); // 2.5
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 3.6875, tolerance); // 3.25

    filter.push(3.0);
    TRIAL_ONLINE_TEST_WITH(filter.mean(), 2.41667, tolerance); // 2.5
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 3.0625, tolerance); // 3.25

    filter.push(4.0);
    TRIAL_ONLINE_TEST_WITH(filter.mean(), 2.89286, tolerance); // 3.5
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 2.17708, tolerance); // 1.25

    filter.push(1.0);
    TRIAL_ONLINE_TEST_WITH(filter.mean(), 2.5, tolerance); // 2.5
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.59821, tolerance); // 1.25
}

void run()
{
    test_linear_increase();
    test_scatter();
}

} // namespace variance_double_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    mean_api_suite::run();
    mean_double_suite::run();
    variance_api_suite::run();
    variance_double_suite::run();

    return boost::report_errors();
}
