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
#include <trial/online/cumulative/trend.hpp>

using namespace trial::online;

//-----------------------------------------------------------------------------

namespace double_suite
{

void test_ctor()
{
    cumulative::trend<double> filter;
    TRIAL_TEST_EQ(filter.size(), 0);
    TRIAL_TEST_EQ(filter.value(), 0.0);
}

void test_same()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    cumulative::trend<double> filter;

    filter.push(1.0);
    TRIAL_TEST_EQ(filter.size(), 1);
    TRIAL_TEST_WITH(filter.value(), 1.0, tolerance);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.size(), 2);
    TRIAL_TEST_WITH(filter.value(), 1.0, tolerance);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.size(), 3);
    TRIAL_TEST_WITH(filter.value(), 1.0, tolerance);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.size(), 4);
    TRIAL_TEST_WITH(filter.value(), 1.0, tolerance);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.size(), 5);
    TRIAL_TEST_WITH(filter.value(), 1.0, tolerance);
}

void test_linear_increase()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    cumulative::trend<double> filter;

    filter.push(1.0);
    TRIAL_TEST_WITH(filter.value(), 1.0, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.value(), 2.0, tolerance);
    filter.push(3.0);
    TRIAL_TEST_WITH(filter.value(), 3.0, tolerance);
    filter.push(4.0);
    TRIAL_TEST_WITH(filter.value(), 4.0, tolerance);
    filter.push(5.0);
    TRIAL_TEST_WITH(filter.value(), 5.0, tolerance);
    filter.push(6.0);
    TRIAL_TEST_WITH(filter.value(), 6.0, tolerance);
    filter.push(7.0);
    TRIAL_TEST_WITH(filter.value(), 7.0, tolerance);
    filter.push(8.0);
    TRIAL_TEST_WITH(filter.value(), 8.0, tolerance);
    filter.push(9.0);
    TRIAL_TEST_WITH(filter.value(), 9.0, tolerance);
    filter.push(10.0);
    TRIAL_TEST_WITH(filter.value(), 10.0, tolerance);
}

void test_linear_increase_offset()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    cumulative::trend<double> filter;

    filter.push(10.0);
    TRIAL_TEST_WITH(filter.value(), 10.0, tolerance);
    filter.push(11.0);
    TRIAL_TEST_WITH(filter.value(), 11.0, tolerance);
    filter.push(12.0);
    TRIAL_TEST_WITH(filter.value(), 12.0, tolerance);
}

void test_linear_decrease()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    cumulative::trend<double> filter;

    filter.push(10.0);
    TRIAL_TEST_WITH(filter.value(), 10.0, tolerance);
    filter.push(9.0);
    TRIAL_TEST_WITH(filter.value(), 9.0, tolerance);
    filter.push(8.0);
    TRIAL_TEST_WITH(filter.value(), 8.0, tolerance);
    filter.push(7.0);
    TRIAL_TEST_WITH(filter.value(), 7.0, tolerance);
    filter.push(6.0);
    TRIAL_TEST_WITH(filter.value(), 6.0, tolerance);
    filter.push(5.0);
    TRIAL_TEST_WITH(filter.value(), 5.0, tolerance);
    filter.push(4.0);
    TRIAL_TEST_WITH(filter.value(), 4.0, tolerance);
    filter.push(3.0);
    TRIAL_TEST_WITH(filter.value(), 3.0, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.value(), 2.0, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.value(), 1.0, tolerance);
}

void test_alternating()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    cumulative::trend<double> filter;

    // Converge towards 1.5

    filter.push(1.0);
    TRIAL_TEST_WITH(filter.value(), 1.0, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.value(), 2.0, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.value(), 1.44444, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.value(), 1.83333, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.value(), 1.50667, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.value(), 1.75556, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.value(), 1.52517, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.value(), 1.70952, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.value(), 1.53192, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.value(), 1.67873, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.value(), 1.53438, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.value(), 1.65652, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.value(), 1.53501, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.value(), 1.63965, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.value(), 1.53479, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.value(), 1.62636, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.value(), 1.53415, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.value(), 1.61559, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.value(), 1.53333, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.value(), 1.60666, tolerance);

    // Outlier

    filter.push(1000.0);
    TRIAL_TEST_WITH(filter.value(), 139.716, tolerance);

    // Slow recovery

    filter.push(2.0);
    TRIAL_TEST_WITH(filter.value(), 129.374, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.value(), 119.974, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.value(), 111.631, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.value(), 103.971, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.value(), 97.1314, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.value(), 90.7946, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.value(), 85.1106, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.value(), 79.8012, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.value(), 75.0212, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.value(), 70.5231, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.value(), 66.4618, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.value(), 62.614, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.value(), 59.1323, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.value(), 55.8126, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.value(), 52.8039, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.value(), 49.9181, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.value(), 47.2997, tolerance);
}

void test_scatter()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    cumulative::trend<double> filter;

    filter.push(1.0);
    TRIAL_TEST_WITH(filter.value(), 1.0, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.value(), 2.0, tolerance);
    filter.push(1.3);
    TRIAL_TEST_WITH(filter.value(), 1.67778, tolerance);
    filter.push(3.75);
    TRIAL_TEST_WITH(filter.value(), 3.06458, tolerance);
    filter.push(2.25);
    TRIAL_TEST_WITH(filter.value(), 2.97767, tolerance);
    filter.push(1.4);
    TRIAL_TEST_WITH(filter.value(), 2.53139, tolerance);
    filter.push(4.1);
    TRIAL_TEST_WITH(filter.value(), 3.28201, tolerance);
}

void test_clear()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    cumulative::trend<double> filter;

    filter.push(1.0);
    TRIAL_TEST_WITH(filter.value(), 1.0, tolerance);

    filter.clear();

    filter.push(2.0);
    TRIAL_TEST_WITH(filter.value(), 2.0, tolerance);
}

void run()
{
    test_ctor();
    test_same();
    test_linear_increase();
    test_linear_increase_offset();
    test_linear_decrease();
    test_alternating();
    test_scatter();
    test_clear();
}

} // namespace double_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    double_suite::run();

    return boost::report_errors();
}
