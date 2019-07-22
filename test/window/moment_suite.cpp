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
#include <trial/online/detail/functional.hpp>
#include <trial/online/window/moment.hpp>

using namespace trial::online;

//-----------------------------------------------------------------------------

namespace mean_double_1_suite
{

void test_ctor()
{
    window::moment<double, 1> filter;
    TRIAL_TEST_EQ(filter.capacity(), 1);
    TRIAL_TEST_EQ(filter.empty(), true);
    TRIAL_TEST_EQ(filter.full(), false);
    TRIAL_TEST_EQ(filter.size(), 0);
    TRIAL_TEST_EQ(filter.mean(), 0.0);
}

void test_many()
{
    window::moment<double, 1> filter;
    TRIAL_TEST_EQ(filter.capacity(), 1);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.empty(), false);
    TRIAL_TEST_EQ(filter.full(), true);
    TRIAL_TEST_EQ(filter.size(), 1);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    filter.push(2.0);
    TRIAL_TEST_EQ(filter.empty(), false);
    TRIAL_TEST_EQ(filter.full(), true);
    TRIAL_TEST_EQ(filter.size(), 1);
    TRIAL_TEST_EQ(filter.mean(), 2.0);
    filter.push(3.0);
    TRIAL_TEST_EQ(filter.empty(), false);
    TRIAL_TEST_EQ(filter.full(), true);
    TRIAL_TEST_EQ(filter.size(), 1);
    TRIAL_TEST_EQ(filter.mean(), 3.0);
}

void run()
{
    test_ctor();
    test_many();
}

} // namespace mean_double_1_suite

//-----------------------------------------------------------------------------

namespace mean_double_2_suite
{

void test_ctor()
{
    window::moment<double, 2> filter;
    TRIAL_TEST_EQ(filter.capacity(), 2);
    TRIAL_TEST_EQ(filter.empty(), true);
    TRIAL_TEST_EQ(filter.full(), false);
    TRIAL_TEST_EQ(filter.size(), 0);
    TRIAL_TEST_EQ(filter.mean(), 0.0);
}

void test_one()
{
    window::moment<double, 2> filter;
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.empty(), false);
    TRIAL_TEST_EQ(filter.full(), false);
    TRIAL_TEST_EQ(filter.size(), 1);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
}

void test_same()
{
    window::moment<double, 2> filter;
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.size(), 1);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.size(), 2);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.empty(), false);
    TRIAL_TEST_EQ(filter.full(), true);
    TRIAL_TEST_EQ(filter.size(), 2);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
}

void test_two()
{
    window::moment<double, 2> filter;
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    filter.push(3.0);
    TRIAL_TEST_EQ(filter.mean(), 2.0);
}

void test_three()
{
    window::moment<double, 2> filter;
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    filter.push(3.0);
    TRIAL_TEST_EQ(filter.mean(), 2.0);
    filter.push(0.0);
    TRIAL_TEST_EQ(filter.mean(), 1.5);
}

void test_linear_increase()
{
    window::moment<double, 2> filter;
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    filter.push(2.0);
    TRIAL_TEST_EQ(filter.mean(), 1.5);
    filter.push(3.0);
    TRIAL_TEST_EQ(filter.mean(), 2.5);
    filter.push(4.0);
    TRIAL_TEST_EQ(filter.mean(), 3.5);
    filter.push(5.0);
    TRIAL_TEST_EQ(filter.mean(), 4.5);
    filter.push(6.0);
    TRIAL_TEST_EQ(filter.mean(), 5.5);
}

void test_clear()
{
    window::moment<double, 2> filter;
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.size(), 1);
    filter.clear();
    TRIAL_TEST_EQ(filter.size(), 0);
    filter.push(2.0);
    TRIAL_TEST_EQ(filter.size(), 1);
    TRIAL_TEST_EQ(filter.mean(), 2.0);
}

void run()
{
    test_ctor();
    test_same();
    test_one();
    test_two();
    test_three();
    test_linear_increase();
    test_clear();
}

} // namespace mean_double_2_suite

//-----------------------------------------------------------------------------

namespace mean_double_3_suite
{

void test_ctor()
{
    window::moment<double, 3> filter;
    TRIAL_TEST_EQ(filter.capacity(), 3);
    TRIAL_TEST_EQ(filter.empty(), true);
    TRIAL_TEST_EQ(filter.full(), false);
    TRIAL_TEST_EQ(filter.size(), 0);
    TRIAL_TEST_EQ(filter.mean(), 0.0);
}

void test_linear_increase()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    window::moment<double, 3> filter;
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.mean(), 1.0, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 1.5, tolerance);
    filter.push(3.0);
    TRIAL_TEST_WITH(filter.mean(), 2.0, tolerance);
    filter.push(4.0);
    TRIAL_TEST_WITH(filter.mean(), 3.0, tolerance);
    filter.push(5.0);
    TRIAL_TEST_WITH(filter.mean(), 4.0, tolerance);
    filter.push(6.0);
    TRIAL_TEST_WITH(filter.mean(), 5.0, tolerance);
}

void run()
{
    test_ctor();
    test_linear_increase();
}

} // namespace mean_double_3_suite

//-----------------------------------------------------------------------------

namespace mean_double_4_suite
{

void test_ctor()
{
    window::moment<double, 4> filter;
    TRIAL_TEST_EQ(filter.capacity(), 4);
    TRIAL_TEST_EQ(filter.empty(), true);
    TRIAL_TEST_EQ(filter.full(), false);
    TRIAL_TEST_EQ(filter.size(), 0);
    TRIAL_TEST_EQ(filter.mean(), 0.0);
}

void test_same()
{
    window::moment<double, 4> filter;
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.size(), 1);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.size(), 2);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.size(), 3);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.size(), 4);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.empty(), false);
    TRIAL_TEST_EQ(filter.full(), true);
    TRIAL_TEST_EQ(filter.size(), 4);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
}

void test_linear_increase()
{
    window::moment<double, 4> filter;
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    filter.push(2.0);
    TRIAL_TEST_EQ(filter.mean(), 1.5);
    filter.push(3.0);
    TRIAL_TEST_EQ(filter.mean(), 2.0);
    filter.push(4.0);
    TRIAL_TEST_EQ(filter.mean(), 2.5);
    filter.push(5.0);
    TRIAL_TEST_EQ(filter.mean(), 3.5);
    filter.push(6.0);
    TRIAL_TEST_EQ(filter.mean(), 4.5);
}

void test_linear_increase_from_offset()
{
    window::moment<double, 4> filter;
    filter.push(10.0);
    TRIAL_TEST_EQ(filter.mean(), 10.0);
    filter.push(11.0);
    TRIAL_TEST_EQ(filter.mean(), 10.5);
    filter.push(12.0);
    TRIAL_TEST_EQ(filter.mean(), 11.0);
    filter.push(13.0);
    TRIAL_TEST_EQ(filter.mean(), 11.5);
    filter.push(14.0);
    TRIAL_TEST_EQ(filter.mean(), 12.5);
    filter.push(15.0);
    TRIAL_TEST_EQ(filter.mean(), 13.5);
}

void test_linear_decrease()
{
    window::moment<double, 4> filter;
    filter.push(10.0);
    TRIAL_TEST_EQ(filter.mean(), 10.0);
    filter.push(9.0);
    TRIAL_TEST_EQ(filter.mean(), 9.5);
    filter.push(8.0);
    TRIAL_TEST_EQ(filter.mean(), 9.0);
    filter.push(7.0);
    TRIAL_TEST_EQ(filter.mean(), 8.5);
    filter.push(6.0);
    TRIAL_TEST_EQ(filter.mean(), 7.5);
    filter.push(5.0);
    TRIAL_TEST_EQ(filter.mean(), 6.5);
}

void run()
{
    test_ctor();
    test_same();
    test_linear_increase();
    test_linear_increase_from_offset();
    test_linear_decrease();
}

} // namespace mean_double_4_suite

//-----------------------------------------------------------------------------

namespace mean_float_2_suite
{

void test_ctor()
{
    window::moment<float, 2> filter;
    TRIAL_TEST_EQ(filter.capacity(), 2);
    TRIAL_TEST_EQ(filter.empty(), true);
    TRIAL_TEST_EQ(filter.full(), false);
    TRIAL_TEST_EQ(filter.size(), 0);
    TRIAL_TEST_EQ(filter.mean(), 0.0f);
}

void test_one()
{
    window::moment<float, 2> filter;
    filter.push(1.0f);
    TRIAL_TEST_EQ(filter.empty(), false);
    TRIAL_TEST_EQ(filter.full(), false);
    TRIAL_TEST_EQ(filter.size(), 1);
    TRIAL_TEST_EQ(filter.mean(), 1.0f);
}

void test_same()
{
    window::moment<float, 2> filter;
    filter.push(1.0f);
    TRIAL_TEST_EQ(filter.size(), 1);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    filter.push(1.0f);
    TRIAL_TEST_EQ(filter.size(), 2);
    TRIAL_TEST_EQ(filter.mean(), 1.0f);
    filter.push(1.0f);
    TRIAL_TEST_EQ(filter.empty(), false);
    TRIAL_TEST_EQ(filter.full(), true);
    TRIAL_TEST_EQ(filter.size(), 2);
    TRIAL_TEST_EQ(filter.mean(), 1.0f);
}

void test_two()
{
    window::moment<float, 2> filter;
    filter.push(1.0f);
    TRIAL_TEST_EQ(filter.mean(), 1.0f);
    filter.push(3.0f);
    TRIAL_TEST_EQ(filter.mean(), 2.0f);
}

void test_three()
{
    window::moment<float, 2> filter;
    filter.push(1.0f);
    TRIAL_TEST_EQ(filter.mean(), 1.0f);
    filter.push(3.0f);
    TRIAL_TEST_EQ(filter.mean(), 2.0f);
    filter.push(0.0f);
    TRIAL_TEST_EQ(filter.mean(), 1.5f);
}

void test_clear()
{
    window::moment<float, 2> filter;
    filter.push(1.0f);
    TRIAL_TEST_EQ(filter.size(), 1);
    filter.clear();
    TRIAL_TEST_EQ(filter.size(), 0);
    filter.push(2.0f);
    TRIAL_TEST_EQ(filter.size(), 1);
    TRIAL_TEST_EQ(filter.mean(), 2.0f);
}

void run()
{
    test_ctor();
    test_same();
    test_one();
    test_two();
    test_three();
    test_clear();
}

} // namespace mean_float_2_suite

//-----------------------------------------------------------------------------

namespace mean_int_2_suite
{

void test_ctor()
{
    window::moment<int, 2> filter;
    TRIAL_TEST_EQ(filter.capacity(), 2);
    TRIAL_TEST_EQ(filter.empty(), true);
    TRIAL_TEST_EQ(filter.full(), false);
    TRIAL_TEST_EQ(filter.size(), 0);
    TRIAL_TEST_EQ(filter.mean(), 0);
}

void test_one()
{
    window::moment<int, 2> filter;
    filter.push(1);
    TRIAL_TEST_EQ(filter.empty(), false);
    TRIAL_TEST_EQ(filter.full(), false);
    TRIAL_TEST_EQ(filter.size(), 1);
    TRIAL_TEST_EQ(filter.mean(), 1);
}

void test_same()
{
    window::moment<int, 2> filter;
    filter.push(1);
    TRIAL_TEST_EQ(filter.size(), 1);
    TRIAL_TEST_EQ(filter.mean(), 1);
    filter.push(1);
    TRIAL_TEST_EQ(filter.size(), 2);
    TRIAL_TEST_EQ(filter.mean(), 1);
    filter.push(1);
    TRIAL_TEST_EQ(filter.empty(), false);
    TRIAL_TEST_EQ(filter.full(), true);
    TRIAL_TEST_EQ(filter.size(), 2);
    TRIAL_TEST_EQ(filter.mean(), 1);
}

void test_two()
{
    window::moment<int, 2> filter;
    filter.push(1);
    TRIAL_TEST_EQ(filter.mean(), 1);
    filter.push(3);
    TRIAL_TEST_EQ(filter.mean(), 2);
}

void test_three()
{
    window::moment<int, 2> filter;
    filter.push(1);
    TRIAL_TEST_EQ(filter.mean(), 1);
    filter.push(3);
    TRIAL_TEST_EQ(filter.mean(), 2);
    filter.push(0);
    TRIAL_TEST_EQ(filter.mean(), 2); // Rounded up
}

void test_clear()
{
    window::moment<int, 2> filter;
    filter.push(1);
    TRIAL_TEST_EQ(filter.size(), 1);
    filter.clear();
    TRIAL_TEST_EQ(filter.size(), 0);
    filter.push(2);
    TRIAL_TEST_EQ(filter.size(), 1);
    TRIAL_TEST_EQ(filter.mean(), 2);
}

void run()
{
    test_ctor();
    test_same();
    test_one();
    test_two();
    test_three();
    test_clear();
}

} // namespace mean_int_2_suite

//-----------------------------------------------------------------------------

namespace variance_double_1_suite
{

void test_ctor()
{
    window::moment_variance<double, 1> filter;
    TRIAL_TEST_EQ(filter.capacity(), 1);
    TRIAL_TEST_EQ(filter.empty(), true);
    TRIAL_TEST_EQ(filter.full(), false);
    TRIAL_TEST_EQ(filter.size(), 0);
    TRIAL_TEST_EQ(filter.mean(), 0.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_variance(), 0.0);
}

void test_many()
{
    window::moment_variance<double, 1> filter;
    TRIAL_TEST_EQ(filter.capacity(), 1);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.empty(), false);
    TRIAL_TEST_EQ(filter.full(), true);
    TRIAL_TEST_EQ(filter.size(), 1);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_variance(), 0.0);
    filter.push(2.0);
    TRIAL_TEST_EQ(filter.empty(), false);
    TRIAL_TEST_EQ(filter.full(), true);
    TRIAL_TEST_EQ(filter.size(), 1);
    TRIAL_TEST_EQ(filter.mean(), 2.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_variance(), 0.0);
    filter.push(3.0);
    TRIAL_TEST_EQ(filter.empty(), false);
    TRIAL_TEST_EQ(filter.full(), true);
    TRIAL_TEST_EQ(filter.size(), 1);
    TRIAL_TEST_EQ(filter.mean(), 3.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_variance(), 0.0);
}

void run()
{
    test_ctor();
    test_many();
}

} // namespace variance_double_1_suite

//-----------------------------------------------------------------------------

namespace variance_double_2_suite
{

void test_ctor()
{
    window::moment_variance<double, 2> filter;
    TRIAL_TEST_EQ(filter.capacity(), 2);
    TRIAL_TEST_EQ(filter.empty(), true);
    TRIAL_TEST_EQ(filter.full(), false);
    TRIAL_TEST_EQ(filter.size(), 0);
    TRIAL_TEST_EQ(filter.mean(), 0.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_variance(), 0.0);
}

void test_one()
{
    window::moment_variance<double, 2> filter;
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.empty(), false);
    TRIAL_TEST_EQ(filter.full(), false);
    TRIAL_TEST_EQ(filter.size(), 1);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_variance(), 0.0);
}

void test_same()
{
    window::moment_variance<double, 2> filter;
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.size(), 1);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_variance(), 0.0);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.size(), 2);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_variance(), 0.0);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.empty(), false);
    TRIAL_TEST_EQ(filter.full(), true);
    TRIAL_TEST_EQ(filter.size(), 2);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_variance(), 0.0);
}

void test_two()
{
    window::moment_variance<double, 2> filter;
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_variance(), 0.0);
    filter.push(3.0);
    TRIAL_TEST_EQ(filter.mean(), 2.0);
    TRIAL_TEST_EQ(filter.variance(), 1.0);
    TRIAL_TEST_EQ(filter.unbiased_variance(), 2.0);
}

void test_three()
{
    window::moment_variance<double, 2> filter;
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_variance(), 0.0);
    filter.push(3.0);
    TRIAL_TEST_EQ(filter.mean(), 2.0);
    TRIAL_TEST_EQ(filter.variance(), 1.0);
    TRIAL_TEST_EQ(filter.unbiased_variance(), 2.0);
    filter.push(0.0);
    TRIAL_TEST_EQ(filter.mean(), 1.5);
    TRIAL_TEST_EQ(filter.variance(), 2.25);
    TRIAL_TEST_EQ(filter.unbiased_variance(), 4.5);
}

void test_clear()
{
    window::moment_variance<double, 2> filter;
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.size(), 1);
    filter.clear();
    TRIAL_TEST_EQ(filter.size(), 0);
    filter.push(2.0);
    TRIAL_TEST_EQ(filter.size(), 1);
}

void run()
{
    test_ctor();
    test_same();
    test_one();
    test_two();
    test_three();
    test_clear();
}

} // namespace variance_double_2_suite

//-----------------------------------------------------------------------------

namespace variance_double_4_suite
{

void test_linear_increase()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    window::moment_variance<double, 4> filter;

    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_WITH(filter.variance(), 0.0, tolerance);

    filter.push(2.0);
    TRIAL_TEST_EQ(filter.mean(), 1.5);
    TRIAL_TEST_WITH(filter.variance(), 0.25, tolerance);

    filter.push(3.0);
    TRIAL_TEST_EQ(filter.mean(), 2.0);
    TRIAL_TEST_WITH(filter.variance(), 0.666667, tolerance);

    filter.push(4.0);
    TRIAL_TEST_EQ(filter.mean(), 2.5);
    TRIAL_TEST_WITH(filter.variance(), 1.25, tolerance);

    // Window is full

    filter.push(5.0);
    TRIAL_TEST_EQ(filter.mean(), 3.5);
    TRIAL_TEST_WITH(filter.variance(), 1.25, tolerance);

    filter.push(6.0);
    TRIAL_TEST_EQ(filter.mean(), 4.5);
    TRIAL_TEST_WITH(filter.variance(), 1.25, tolerance);

    filter.push(7.0);
    TRIAL_TEST_EQ(filter.mean(), 5.5);
    TRIAL_TEST_WITH(filter.variance(), 1.25, tolerance);

    filter.push(8.0);
    TRIAL_TEST_EQ(filter.mean(), 6.5);
    TRIAL_TEST_WITH(filter.variance(), 1.25, tolerance);

    filter.push(9.0);
    TRIAL_TEST_EQ(filter.mean(), 7.5);
    TRIAL_TEST_WITH(filter.variance(), 1.25, tolerance);
}

void test_scatter()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    window::moment_variance<double, 4> filter;

    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);

    filter.push(3.0);
    TRIAL_TEST_EQ(filter.mean(), 2.0);
    TRIAL_TEST_EQ(filter.variance(), 1.0);

    filter.push(0.0);
    TRIAL_TEST_WITH(filter.mean(), 1.33333, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.55556, tolerance);

    filter.push(5.0);
    TRIAL_TEST_WITH(filter.mean(), 2.25, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 3.6875, tolerance);

    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 2.5, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 3.25, tolerance);

    filter.push(3.0);
    TRIAL_TEST_WITH(filter.mean(), 2.5, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 3.25, tolerance);

    filter.push(4.0);
    TRIAL_TEST_WITH(filter.mean(), 3.5, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.25, tolerance);

    filter.push(1.0);
    TRIAL_TEST_WITH(filter.mean(), 2.5, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.25, tolerance);
}

void run()
{
    test_linear_increase();
    test_scatter();
}

} // namespace variance_double_4_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    mean_double_1_suite::run();
    mean_double_2_suite::run();
    mean_double_3_suite::run();
    mean_double_4_suite::run();
    mean_float_2_suite::run();
    mean_int_2_suite::run();

    variance_double_1_suite::run();
    variance_double_2_suite::run();
    variance_double_4_suite::run();

    return boost::report_errors();
}
