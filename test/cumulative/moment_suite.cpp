///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2016 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>
#include <trial/online/iterator.hpp>
#include <trial/online/detail/lightweight_test.hpp>
#include <trial/online/detail/functional.hpp>
#include <trial/online/cumulative/moment.hpp>

using namespace trial::online;

//-----------------------------------------------------------------------------

namespace mean_double_suite
{

void test_ctor()
{
    cumulative::moment<double> filter;
    TRIAL_TEST_EQ(filter.size(), 0);
}

void test_same()
{
    cumulative::moment<double> filter;
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.size(), 1);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    // TRIAL_TEST_EQ(filter._unbiased_mean(), undefined);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.size(), 2);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.unbiased_mean(), 2.0);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.size(), 3);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.unbiased_mean(), 1.5);
}

void test_linear_increase()
{
    cumulative::moment<double> filter;
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.size(), 1);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    // TRIAL_TEST_EQ(filter._unbiased_mean(), undefined);
    filter.push(3.0);
    TRIAL_TEST_EQ(filter.size(), 2);
    TRIAL_TEST_EQ(filter.mean(), 2.0);
    TRIAL_TEST_EQ(filter.unbiased_mean(), 4.0);
    filter.push(5.0);
    TRIAL_TEST_EQ(filter.size(), 3);
    TRIAL_TEST_EQ(filter.mean(), 3.0);
    TRIAL_TEST_EQ(filter.unbiased_mean(), 4.5);
}

void test_linear_decrease()
{
    cumulative::moment<double> filter;
    filter.push(5.0);
    TRIAL_TEST_EQ(filter.size(), 1);
    TRIAL_TEST_EQ(filter.mean(), 5.0);
    // TRIAL_TEST_EQ(filter._unbiased_mean(), undefined);
    filter.push(3.0);
    TRIAL_TEST_EQ(filter.size(), 2);
    TRIAL_TEST_EQ(filter.mean(), 4.0);
    TRIAL_TEST_EQ(filter.unbiased_mean(), 8.0);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.size(), 3);
    TRIAL_TEST_EQ(filter.mean(), 3.0);
    TRIAL_TEST_EQ(filter.unbiased_mean(), 4.5);
}

void test_exponential_increase()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    cumulative::moment<double> filter;
    filter.push(1e0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    // TRIAL_TEST_EQ(filter._unbiased_mean(), undefined);
    filter.push(1e1);
    TRIAL_TEST_WITH(filter.mean(), 5.5, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_mean(), 11.0, tolerance);
    filter.push(1e2);
    TRIAL_TEST_WITH(filter.mean(), 37.0, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_mean(), 55.5, tolerance);
    filter.push(1e3);
    TRIAL_TEST_WITH(filter.mean(), 277.75, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_mean(), 370.3333, tolerance);
    filter.push(1e4);
    TRIAL_TEST_WITH(filter.mean(), 2222.2, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_mean(), 2777.75, tolerance);
    filter.push(1e5);
    TRIAL_TEST_WITH(filter.mean(), 18518.5, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_mean(), 22222.2, tolerance);
    filter.push(1e6);
    TRIAL_TEST_WITH(filter.mean(), 158730.0, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_mean(), 185185.0, tolerance);
    filter.push(1e7);
    TRIAL_TEST_WITH(filter.mean(), 1.38889e6, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_mean(), 1.5873e6, tolerance);
    filter.push(1e8);
    TRIAL_TEST_WITH(filter.mean(), 1.23457e7, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_mean(), 1.38889e7, tolerance);
    filter.push(1e9);
    TRIAL_TEST_WITH(filter.mean(), 1.11111e8, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_mean(), 1.23456e8, tolerance);
}

void run()
{
    test_ctor();
    test_same();
    test_linear_increase();
    test_linear_decrease();
    test_exponential_increase();
}

} // namespace mean_double_suite

//-----------------------------------------------------------------------------

namespace mean_int_suite
{

void test_ctor()
{
    cumulative::moment<int> filter;
    TRIAL_TEST_EQ(filter.size(), 0);
}

void test_same()
{
    cumulative::moment<int> filter;
    filter.push(1);
    TRIAL_TEST_EQ(filter.size(), 1);
    TRIAL_TEST_EQ(filter.mean(), 1);
    filter.push(1);
    TRIAL_TEST_EQ(filter.size(), 2);
    TRIAL_TEST_EQ(filter.mean(), 1);
    filter.push(1);
    TRIAL_TEST_EQ(filter.size(), 3);
    TRIAL_TEST_EQ(filter.mean(), 1);
}

void test_linear_increase()
{
    cumulative::moment<int> filter;
    filter.push(1);
    TRIAL_TEST_EQ(filter.size(), 1);
    TRIAL_TEST_EQ(filter.mean(), 1);
    filter.push(3);
    TRIAL_TEST_EQ(filter.size(), 2);
    TRIAL_TEST_EQ(filter.mean(), 2);
    filter.push(5);
    TRIAL_TEST_EQ(filter.size(), 3);
    TRIAL_TEST_EQ(filter.mean(), 3);
}

void run()
{
    test_ctor();
    test_same();
    test_linear_increase();
}

} // namespace mean_int_suite

//-----------------------------------------------------------------------------

namespace variance_double_suite
{

void test_ctor()
{
    cumulative::moment_variance<double> filter;
    TRIAL_TEST_EQ(filter.size(), 0);
}

void test_same()
{
    cumulative::moment_variance<double> filter;
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    // TRIAL_TEST_EQ(filter.unbiased_variance(), undefined);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_variance(), 0.0);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_variance(), 0.0);
}

void test_linear_increase()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    cumulative::moment_variance<double> filter;
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    // TRIAL_TEST_EQ(filter.unbiased_variance(), undefined);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 1.5, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.25, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_variance(), 0.5, tolerance);
    filter.push(3.0);
    TRIAL_TEST_WITH(filter.mean(), 2.0, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.666667, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_variance(), 1.0, tolerance);
    filter.push(4.0);
    TRIAL_TEST_WITH(filter.mean(), 2.5, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.25, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_variance(), 1.666667, tolerance);
    filter.push(5.0);
    TRIAL_TEST_WITH(filter.mean(), 3.0, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 2.0, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_variance(), 2.5, tolerance);
    filter.push(6.0);
    TRIAL_TEST_WITH(filter.mean(), 3.5, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 2.91667, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_variance(), 3.5, tolerance);
    filter.push(7.0);
    TRIAL_TEST_WITH(filter.mean(), 4.0, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 4.0, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_variance(), 4.66667, tolerance);
    filter.push(8.0);
    TRIAL_TEST_WITH(filter.mean(), 4.5, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 5.25, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_variance(), 6.0, tolerance);
    filter.push(9.0);
    TRIAL_TEST_WITH(filter.mean(), 5.0, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 6.66667, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_variance(), 7.5, tolerance);
    filter.push(10.0);
    TRIAL_TEST_WITH(filter.mean(), 5.5, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 8.25, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_variance(), 9.16667, tolerance);
}

void test_exponential_increase()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    cumulative::moment_variance<double> filter;
    filter.push(1e0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    // TRIAL_TEST_EQ(filter.unbiased_variance(), undefined);
    filter.push(1e1);
    TRIAL_TEST_WITH(filter.mean(), 5.5, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 20.25, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_variance(), 40.5, tolerance);
    filter.push(1e2);
    TRIAL_TEST_WITH(filter.mean(), 37.0, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1998., tolerance);
    TRIAL_TEST_WITH(filter.unbiased_variance(), 2997., tolerance);
    filter.push(1e3);
    TRIAL_TEST_WITH(filter.mean(), 277.75, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 175380., tolerance);
    TRIAL_TEST_WITH(filter.unbiased_variance(), 2.3384e5, tolerance);
    filter.push(1e4);
    TRIAL_TEST_WITH(filter.mean(), 2222.2, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.52638e7, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_variance(), 1.90798e7, tolerance);
    filter.push(1e5);
    TRIAL_TEST_WITH(filter.mean(), 18518.5, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.34057e9, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_variance(), 1.60868e9, tolerance);
    filter.push(1e6);
    TRIAL_TEST_WITH(filter.mean(), 158730.0, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.19105e11, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_variance(), 1.38956e11, tolerance);
    filter.push(1e7);
    TRIAL_TEST_WITH(filter.mean(), 1.38889e6, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.06973e13, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_variance(), 1.22254e13, tolerance);
    filter.push(1e8);
    TRIAL_TEST_WITH(filter.mean(), 1.23457e7, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 9.69919e14, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_variance(), 1.09116e15, tolerance);
    filter.push(1e9);
    TRIAL_TEST_WITH(filter.mean(), 1.11111e8, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 8.86644e16, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_variance(), 9.8516e16, tolerance);
}

void test_scatter()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    cumulative::moment_variance<double> filter;

    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);

    filter.push(3.0);
    TRIAL_TEST_WITH(filter.mean(), 2.0, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.0, tolerance);

    filter.push(0.0);
    TRIAL_TEST_WITH(filter.mean(), 1.33333, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.55556, tolerance);

    filter.push(5.0);
    TRIAL_TEST_WITH(filter.mean(), 2.25, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 3.6875, tolerance);

    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 2.2, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 2.96, tolerance);

    filter.push(3.0);
    TRIAL_TEST_WITH(filter.mean(), 2.33333, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 2.55556, tolerance);

    filter.push(4.0);
    TRIAL_TEST_WITH(filter.mean(), 2.57143, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 2.53061, tolerance);

    filter.push(1.0);
    TRIAL_TEST_WITH(filter.mean(), 2.375, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 2.48438, tolerance);
}

void run()
{
    test_ctor();
    test_same();
    test_linear_increase();
    test_exponential_increase();
    test_scatter();
}

} // namespace variance_double_suite

//-----------------------------------------------------------------------------

namespace skewness_double_suite
{

void test_ctor()
{
    cumulative::moment_skewness<double> filter;
    TRIAL_TEST_EQ(filter.size(), 0);
}

void test_same()
{
    cumulative::moment_skewness<double> filter;
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_skewness(), 0.0);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_skewness(), 0.0);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_skewness(), 0.0);
}

void test_linear_increase()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    cumulative::moment_skewness<double> filter;
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_skewness(), 0.0);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 1.5, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.25, tolerance);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    filter.push(3.0);
    TRIAL_TEST_WITH(filter.mean(), 2.0, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.666667, tolerance);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_skewness(), 0.0);
    filter.push(4.0);
    TRIAL_TEST_WITH(filter.mean(), 2.5, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.25, tolerance);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_skewness(), 0.0);
    filter.push(5.0);
    TRIAL_TEST_WITH(filter.mean(), 3.0, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 2.0, tolerance);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_skewness(), 0.0);
}

void test_exponential_increase()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    cumulative::moment_skewness<double> filter;
    filter.push(1e0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_skewness(), 0.0);
    filter.push(1e1);
    TRIAL_TEST_WITH(filter.mean(), 5.5, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 20.25, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_skewness(), 0.0, tolerance);
    filter.push(1e2);
    TRIAL_TEST_WITH(filter.mean(), 37.0, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1998., tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 0.68567, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_skewness(), 1.67954, tolerance);
    filter.push(1e3);
    TRIAL_TEST_WITH(filter.mean(), 277.75, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 175380., tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.12582, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_skewness(), 1.95, tolerance);
    filter.push(1e4);
    TRIAL_TEST_WITH(filter.mean(), 2222.2, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.52638e7, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.46675, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_skewness(), 2.1865, tolerance);
    filter.push(1e5);
    TRIAL_TEST_WITH(filter.mean(), 18518.5, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.34057e9, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.75227, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_skewness(), 2.3994, tolerance);
    filter.push(1e6);
    TRIAL_TEST_WITH(filter.mean(), 1.5873e5, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.19105e11, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 2.00181, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_skewness(), 2.59464, tolerance);
    filter.push(1e7);
    TRIAL_TEST_WITH(filter.mean(), 1.3889e6, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.06973e13, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 2.22579, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_skewness(), 2.77605, tolerance);
    filter.push(1e8);
    TRIAL_TEST_WITH(filter.mean(), 12345679., tolerance);
    TRIAL_TEST_WITH(filter.variance(), 9.69919e14, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 2.43051, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_skewness(), 2.9462, tolerance);
    filter.push(1e9);
    TRIAL_TEST_WITH(filter.mean(), 1.1111e8, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 8.86644e16, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 2.62009, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_skewness(), 3.10704, tolerance);
}

void test_left_skew()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    cumulative::moment_skewness<double> filter;
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_skewness(), 0.0);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 1.5, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.25, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_skewness(), 0.0, tolerance);
    filter.push(5.0);
    TRIAL_TEST_WITH(filter.mean(), 2.66667, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 2.88889, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 0.52800, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_skewness(), 1.29334, tolerance);
    filter.push(15.0);
    TRIAL_TEST_WITH(filter.mean(), 5.75, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 30.6875, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 0.92814, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_skewness(), 1.60758, tolerance);
}

void run()
{
    test_ctor();
    test_same();
    test_linear_increase();
    test_exponential_increase();
    test_left_skew();
}

} // namespace skewness_double_suite

//-----------------------------------------------------------------------------

namespace kurtosis_double_suite
{

void test_ctor()
{
    cumulative::moment_kurtosis<double> filter;
    TRIAL_TEST_EQ(filter.size(), 0);
}

void test_same()
{
    cumulative::moment_kurtosis<double> filter;
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    TRIAL_TEST_EQ(filter.kurtosis(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_kurtosis(), 0.0);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    TRIAL_TEST_EQ(filter.kurtosis(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_kurtosis(), 0.0);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    TRIAL_TEST_EQ(filter.kurtosis(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_kurtosis(), 0.0);
}

void test_linear_increase()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    cumulative::moment_kurtosis<double> filter;
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    TRIAL_TEST_EQ(filter.kurtosis(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_kurtosis(), 0.0);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 1.5, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.25, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_kurtosis(), 0.0, tolerance);
    filter.push(3.0);
    TRIAL_TEST_WITH(filter.mean(), 2.0, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.666667, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 1.5, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_kurtosis(), 0.0, tolerance);
    filter.push(4.0);
    TRIAL_TEST_WITH(filter.mean(), 2.5, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.25, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 1.64, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_kurtosis(), 1.8, tolerance);
    filter.push(5.0);
    TRIAL_TEST_WITH(filter.mean(), 3.0, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 2.0, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 1.7, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_kurtosis(), 1.8, tolerance);
}

void test_exponential_increase()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    cumulative::moment_kurtosis<double> filter;
    filter.push(1e0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    TRIAL_TEST_EQ(filter.kurtosis(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_kurtosis(), 0.0);
    filter.push(1e1);
    TRIAL_TEST_WITH(filter.mean(), 5.5, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 20.25, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_kurtosis(), 0.0, tolerance);
    filter.push(1e2);
    TRIAL_TEST_WITH(filter.mean(), 37.0, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1998., tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 0.68567, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 1.5, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_kurtosis(), 0.0, tolerance);
    filter.push(1e3);
    TRIAL_TEST_WITH(filter.mean(), 277.75, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 175380., tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.12582, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 2.30928, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_kurtosis(), 6.81961, tolerance);
    filter.push(1e4);
    TRIAL_TEST_WITH(filter.mean(), 2222.2, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.52638e7, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.46675, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 3.20222, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_kurtosis(), 7.8089, tolerance);
    filter.push(1e5);
    TRIAL_TEST_WITH(filter.mean(), 18518.5, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.34057e9, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.75227, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 4.12966, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_kurtosis(), 8.79483, tolerance);
    filter.push(1e6);
    TRIAL_TEST_WITH(filter.mean(), 1.5873e5, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.19105e11, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 2.00181, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 5.07455, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_kurtosis(), 9.77891, tolerance);
    filter.push(1e7);
    TRIAL_TEST_WITH(filter.mean(), 1.3889e6, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.06973e13, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 2.22579, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 6.02947, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_kurtosis(), 10.7619, tolerance);
    filter.push(1e8);
    TRIAL_TEST_WITH(filter.mean(), 12345679., tolerance);
    TRIAL_TEST_WITH(filter.variance(), 9.69919e14, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 2.43051, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 6.99069, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_kurtosis(), 11.7442, tolerance);
    filter.push(1e9);
    TRIAL_TEST_WITH(filter.mean(), 1.1111e8, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 8.86644e16, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 2.62009, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 7.95612, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_kurtosis(), 12.726, tolerance);
}

void test_left_skew()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    cumulative::moment_kurtosis<double> filter;
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    TRIAL_TEST_EQ(filter.kurtosis(), 0.0);
    TRIAL_TEST_EQ(filter.unbiased_kurtosis(), 0.0);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 1.5, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.25, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_kurtosis(), 0.0, tolerance);
    filter.push(5.0);
    TRIAL_TEST_WITH(filter.mean(), 2.66667, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 2.88889, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 0.52800, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 1.5, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_kurtosis(), 0.0, tolerance);
    filter.push(15.0);
    TRIAL_TEST_WITH(filter.mean(), 5.75, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 30.6875, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 0.92814, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 2.13122, tolerance);
    TRIAL_TEST_WITH(filter.unbiased_kurtosis(), 5.48416, tolerance);
}

void run()
{
    test_ctor();
    test_same();
    test_linear_increase();
    test_exponential_increase();
    test_left_skew();
}

} // namespace kurtosis_double_suite

//-----------------------------------------------------------------------------

namespace algorithm_suite
{

template <typename T>
struct less_than
{
    less_than(T value) : threshold(value) {}
    bool operator()(T input)
    {
        return input < threshold;
    }
    const T threshold;
};

template <typename T>
struct squared
{
    T operator()(T value)
    {
        return value * value;
    }
};

void copy_empty()
{
    std::vector<double> input = {};
    cumulative::moment<double> filter;
    std::copy(input.begin(), input.end(), push_inserter(filter));
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
}

void copy_sequence()
{
    std::vector<double> input = { 1.0, 2.0, 3.0, 4.0, 5.0 };
    cumulative::moment<double> filter;
    std::copy(input.begin(), input.end(), push_inserter(filter));
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 5);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 3.0);
}

void copy_if_empty()
{
    std::vector<double> input = {};
    cumulative::moment<double> filter;
    std::copy_if(input.begin(), input.end(), push_inserter(filter), less_than<double>(3.0));
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
}

void copy_if_sequence()
{
    std::vector<double> input = { 1.0, 2.0, 3.0, 4.0, 5.0 };
    cumulative::moment<double> filter;
    std::copy_if(input.begin(), input.end(), push_inserter(filter), less_than<double>(3.0));
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.5);
}

void move_empty()
{
    std::vector<double> input = {};
    cumulative::moment<double> filter;
    std::move(input.begin(), input.end(), push_inserter(filter));
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
}

void move_sequence()
{
    std::vector<double> input = { 1.0, 2.0, 3.0, 4.0, 5.0 };
    cumulative::moment<double> filter;
    std::move(input.begin(), input.end(), push_inserter(filter));
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 5);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 3.0);
}

void transform_empty()
{
    std::vector<double> input = {};
    cumulative::moment<double> filter;
    std::transform(input.begin(), input.end(), push_inserter(filter), squared<double>());
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
}

void transform_sequence()
{
    std::vector<double> input = { 1.0, 2.0, 3.0, 4.0, 5.0 };
    cumulative::moment<double> filter;
    std::transform(input.begin(), input.end(), push_inserter(filter), squared<double>());
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 5);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 11.0);
}

void run()
{
    copy_empty();
    copy_sequence();
    copy_if_empty();
    copy_if_sequence();
    move_empty();
    move_sequence();
    transform_empty();
    transform_sequence();
}

} // namespace algorithm_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    mean_double_suite::run();
    mean_int_suite::run();
    variance_double_suite::run();
    skewness_double_suite::run();
    kurtosis_double_suite::run();
    algorithm_suite::run();

    return boost::report_errors();
}
