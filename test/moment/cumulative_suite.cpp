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
}

void test_same()
{
    trial::online::moment::cumulative<double> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 3);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
}

void test_increasing()
{
    trial::online::moment::cumulative<double> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 2.0);
    filter.push(5.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 3);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 3.0);
}

void test_decreasing()
{
    trial::online::moment::cumulative<double> filter;
    filter.push(5.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 5.0);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 4.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 3);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 3.0);
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
}

void test_same()
{
    trial::online::moment::cumulative_variance<double> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
}

void test_increasing()
{
    const double tolerance = 1e-6;
    trial::online::moment::cumulative_variance<double> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    filter.push(2.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.25, tolerance);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.666667, tolerance);
}

void run()
{
    test_empty();
    test_same();
    test_increasing();
}

} // namespace variance_double_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    average_double_suite::run();
    average_int_suite::run();
    variance_double_suite::run();

    return boost::report_errors();
}
