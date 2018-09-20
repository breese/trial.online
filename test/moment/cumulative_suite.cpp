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
#include <trial/online/moment/cumulative.hpp>

//-----------------------------------------------------------------------------

namespace average_double_suite
{

void test_empty()
{
    trial::online::moment::cumulative<double> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_value(), 0.0);
}

void test_same()
{
    trial::online::moment::cumulative<double> filter;
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

void test_increasing()
{
    trial::online::moment::cumulative<double> filter;
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

void test_decreasing()
{
    trial::online::moment::cumulative<double> filter;
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

void run()
{
    test_empty();
    test_same();
    test_increasing();
    test_decreasing();
}

} // namespace average_double_suite

//-----------------------------------------------------------------------------

namespace average_int_suite
{

void test_empty()
{
    trial::online::moment::cumulative<int> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0);
}

void test_same()
{
    trial::online::moment::cumulative<int> filter;
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

void test_increasing()
{
    trial::online::moment::cumulative<int> filter;
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
    test_increasing();
}

} // namespace average_int_suite

//-----------------------------------------------------------------------------

namespace variance_double_suite
{

void test_empty()
{
    trial::online::moment::cumulative_variance<double> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
}

void test_same()
{
    trial::online::moment::cumulative_variance<double> filter;
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

void test_increasing()
{
    const double tolerance = 1e-5;
    trial::online::moment::cumulative_variance<double> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
    filter.push(2.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.25, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.unbiased_variance(), 0.5, tolerance);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.666667, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.unbiased_variance(), 1.0, tolerance);
    filter.push(4.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 1.25, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.unbiased_variance(), 1.666667, tolerance);
    filter.push(5.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 3.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 2.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.unbiased_variance(), 2.5, tolerance);
    filter.push(6.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 3.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 2.91667, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.unbiased_variance(), 3.5, tolerance);
    filter.push(7.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 4.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 4.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.unbiased_variance(), 4.66667, tolerance);
    filter.push(8.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 4.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 5.25, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.unbiased_variance(), 6.0, tolerance);
    filter.push(9.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 5.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 6.66667, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.unbiased_variance(), 7.5, tolerance);
    filter.push(10.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 5.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 8.25, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.unbiased_variance(), 9.16667, tolerance);
}

void run()
{
    test_empty();
    test_same();
    test_increasing();
}

} // namespace variance_double_suite

//-----------------------------------------------------------------------------

namespace skew_double_suite
{

void test_empty()
{
    trial::online::moment::cumulative_skew<double> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.skew(), 0.0);
}

void test_same()
{
    trial::online::moment::cumulative_skew<double> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.skew(), 0.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.skew(), 0.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.skew(), 0.0);
}

void test_increasing()
{
    const double tolerance = 1e-6;
    trial::online::moment::cumulative_skew<double> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.skew(), 0.0);
    filter.push(2.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.25, tolerance);
    TRIAL_ONLINE_TEST_EQUAL(filter.skew(), 0.0);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.666667, tolerance);
    TRIAL_ONLINE_TEST_EQUAL(filter.skew(), 0.0);
    filter.push(4.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 1.25, tolerance);
    TRIAL_ONLINE_TEST_EQUAL(filter.skew(), 0.0);
    filter.push(5.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 3.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 2.0, tolerance);
    TRIAL_ONLINE_TEST_EQUAL(filter.skew(), 0.0);
}

void test_left_skew()
{
    const double tolerance = 1e-5;
    trial::online::moment::cumulative_skew<double> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.skew(), 0.0);
    filter.push(2.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.25, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.skew(), 0.0, tolerance);
    filter.push(5.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2.66667, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 2.88889, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.skew(), 0.52800, tolerance);
    filter.push(15.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 5.75, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 30.6875, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.skew(), 0.92814, tolerance);
}

void run()
{
    test_empty();
    test_same();
    test_increasing();
    test_left_skew();
}

} // namespace skew_double_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    average_double_suite::run();
    average_int_suite::run();
    variance_double_suite::run();
    skew_double_suite::run();

    return boost::report_errors();
}
