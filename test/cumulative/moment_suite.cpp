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
#include <trial/online/cumulative/moment.hpp>

using namespace trial::online;

//-----------------------------------------------------------------------------

namespace mean_double_suite
{

void test_empty()
{
    cumulative::moment<double> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_value(), 0.0);
}

void test_same()
{
    cumulative::moment<double> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_value(), 1.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_value(), 2.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 3);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_value(), 1.5);
}

void test_linear_increase()
{
    cumulative::moment<double> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_value(), 1.0);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_value(), 4.0);
    filter.push(5.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 3);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 3.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_value(), 4.5);
}

void test_linear_decrease()
{
    cumulative::moment<double> filter;
    filter.push(5.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 5.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_value(), 5.0);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 4.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_value(), 8.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 3);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 3.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_value(), 4.5);
}

void test_exponential_increase()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    cumulative::moment<double> filter;
    filter.push(1e0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_value(), 1.0);
    filter.push(1e1);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 5.5, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_value(), 11.0, tolerance);
    filter.push(1e2);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 37.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_value(), 55.5, tolerance);
    filter.push(1e3);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 277.75, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_value(), 370.3333, tolerance);
    filter.push(1e4);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 2222.2, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_value(), 2777.75, tolerance);
    filter.push(1e5);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 18518.5, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_value(), 22222.2, tolerance);
    filter.push(1e6);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 158730.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_value(), 185185.0, tolerance);
    filter.push(1e7);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 1.38889e6, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_value(), 1.5873e6, tolerance);
    filter.push(1e8);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 1.23457e7, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_value(), 1.38889e7, tolerance);
    filter.push(1e9);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 1.11111e8, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_value(), 1.23456e8, tolerance);
}

void run()
{
    test_empty();
    test_same();
    test_linear_increase();
    test_linear_decrease();
    test_exponential_increase();
}

} // namespace mean_double_suite

//-----------------------------------------------------------------------------

namespace mean_int_suite
{

void test_empty()
{
    cumulative::moment<int> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0);
}

void test_same()
{
    cumulative::moment<int> filter;
    filter.push(1);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1);
    filter.push(1);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1);
    filter.push(1);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 3);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1);
}

void test_linear_increase()
{
    cumulative::moment<int> filter;
    filter.push(1);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1);
    filter.push(3);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 2);
    filter.push(5);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 3);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 3);
}

void run()
{
    test_empty();
    test_same();
    test_linear_increase();
}

} // namespace mean_int_suite

//-----------------------------------------------------------------------------

namespace variance_double_suite
{

void test_empty()
{
    cumulative::moment_variance<double> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
}

void test_same()
{
    cumulative::moment_variance<double> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
}

void test_linear_increase()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    cumulative::moment_variance<double> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
    filter.push(2.0);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 1.5, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 0.25, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_variance(), 0.5, tolerance);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 2.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 0.666667, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_variance(), 1.0, tolerance);
    filter.push(4.0);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 2.5, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.25, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_variance(), 1.666667, tolerance);
    filter.push(5.0);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 3.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 2.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_variance(), 2.5, tolerance);
    filter.push(6.0);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 3.5, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 2.91667, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_variance(), 3.5, tolerance);
    filter.push(7.0);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 4.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 4.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_variance(), 4.66667, tolerance);
    filter.push(8.0);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 4.5, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 5.25, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_variance(), 6.0, tolerance);
    filter.push(9.0);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 5.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 6.66667, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_variance(), 7.5, tolerance);
    filter.push(10.0);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 5.5, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 8.25, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_variance(), 9.16667, tolerance);
}

void test_exponential_increase()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    cumulative::moment_variance<double> filter;
    filter.push(1e0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
    filter.push(1e1);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 5.5, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 20.25, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_variance(), 40.5, tolerance);
    filter.push(1e2);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 37.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1998., tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_variance(), 2997., tolerance);
    filter.push(1e3);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 277.75, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 175380., tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_variance(), 2.3384e5, tolerance);
    filter.push(1e4);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 2222.2, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.52638e7, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_variance(), 1.90798e7, tolerance);
    filter.push(1e5);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 18518.5, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.34057e9, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_variance(), 1.60868e9, tolerance);
    filter.push(1e6);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 158730.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.19105e11, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_variance(), 1.38956e11, tolerance);
    filter.push(1e7);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 1.38889e6, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.06973e13, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_variance(), 1.22254e13, tolerance);
    filter.push(1e8);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 1.23457e7, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 9.69919e14, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_variance(), 1.09116e15, tolerance);
    filter.push(1e9);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 1.11111e8, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 8.86644e16, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_variance(), 9.8516e16, tolerance);
}

void run()
{
    test_empty();
    test_same();
    test_linear_increase();
    test_exponential_increase();
}

} // namespace variance_double_suite

//-----------------------------------------------------------------------------

namespace skew_double_suite
{

void test_empty()
{
    cumulative::moment_skew<double> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.skew(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_skew(), 0.0);
}

void test_same()
{
    cumulative::moment_skew<double> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.skew(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_skew(), 0.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.skew(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_skew(), 0.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.skew(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_skew(), 0.0);
}

void test_linear_increase()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    cumulative::moment_skew<double> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.skew(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_skew(), 0.0);
    filter.push(2.0);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 1.5, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 0.25, tolerance);
    TRIAL_ONLINE_TEST_EQUAL(filter.skew(), 0.0);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 2.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 0.666667, tolerance);
    TRIAL_ONLINE_TEST_EQUAL(filter.skew(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_skew(), 0.0);
    filter.push(4.0);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 2.5, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.25, tolerance);
    TRIAL_ONLINE_TEST_EQUAL(filter.skew(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_skew(), 0.0);
    filter.push(5.0);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 3.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 2.0, tolerance);
    TRIAL_ONLINE_TEST_EQUAL(filter.skew(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_skew(), 0.0);
}

void test_exponential_increase()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    cumulative::moment_skew<double> filter;
    filter.push(1e0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.skew(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_skew(), 0.0);
    filter.push(1e1);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 5.5, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 20.25, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.skew(), 0.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_skew(), 0.0, tolerance);
    filter.push(1e2);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 37.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1998., tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.skew(), 0.68567, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_skew(), 1.67954, tolerance);
    filter.push(1e3);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 277.75, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 175380., tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.skew(), 1.12582, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_skew(), 1.95, tolerance);
    filter.push(1e4);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 2222.2, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.52638e7, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.skew(), 1.46675, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_skew(), 2.1865, tolerance);
    filter.push(1e5);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 18518.5, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.34057e9, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.skew(), 1.75227, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_skew(), 2.3994, tolerance);
    filter.push(1e6);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 1.5873e5, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.19105e11, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.skew(), 2.00181, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_skew(), 2.59464, tolerance);
    filter.push(1e7);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 1.3889e6, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.06973e13, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.skew(), 2.22579, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_skew(), 2.77605, tolerance);
    filter.push(1e8);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 12345679., tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 9.69919e14, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.skew(), 2.43051, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_skew(), 2.9462, tolerance);
    filter.push(1e9);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 1.1111e8, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 8.86644e16, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.skew(), 2.62009, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_skew(), 3.10704, tolerance);
}

void test_left_skew()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    cumulative::moment_skew<double> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.skew(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_skew(), 0.0);
    filter.push(2.0);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 1.5, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 0.25, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.skew(), 0.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_skew(), 0.0, tolerance);
    filter.push(5.0);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 2.66667, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 2.88889, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.skew(), 0.52800, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_skew(), 1.29334, tolerance);
    filter.push(15.0);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 5.75, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 30.6875, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.skew(), 0.92814, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.unbiased_skew(), 1.60758, tolerance);
}

void run()
{
    test_empty();
    test_same();
    test_linear_increase();
    test_exponential_increase();
    test_left_skew();
}

} // namespace skew_double_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    mean_double_suite::run();
    mean_int_suite::run();
    variance_double_suite::run();
    skew_double_suite::run();

    return boost::report_errors();
}
