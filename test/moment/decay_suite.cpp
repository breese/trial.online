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
#include <trial/online/moment/decay.hpp>

using one_eight = std::ratio<1, 8>;

//-----------------------------------------------------------------------------

namespace mean_double_suite
{

void test_empty()
{
    trial::online::moment::decay<double, one_eight> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
}

void test_same()
{
    // Slow convergence towards real mean is due to lack of normalization
    const double tolerance = 1e-6;
    trial::online::moment::decay<double, one_eight> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.125, tolerance);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.234375, tolerance);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.330078, tolerance);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.413818, tolerance);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.487091, tolerance);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.551205, tolerance);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.607304, tolerance);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.656391, tolerance);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.699342, tolerance);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.736924, tolerance);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.769809, tolerance);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.798583, tolerance);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.823760, tolerance);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.845790, tolerance);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.865066, tolerance);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.881933, tolerance);
}

void test_increasing()
{
    const double tolerance = 1e-5;
    trial::online::moment::decay<double, one_eight> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.125, tolerance);
    filter.push(2.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.359375, tolerance);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.689453, tolerance);
    filter.push(4.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1.10327, tolerance);
    filter.push(5.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1.59036, tolerance);
    filter.push(6.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2.14157, tolerance);
    filter.push(7.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2.74887, tolerance);
    filter.push(8.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 3.40526, tolerance);
    filter.push(9.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 4.1046, tolerance);
    filter.push(10.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 4.84153, tolerance);
}

void test_clear()
{
    trial::online::moment::decay<double, one_eight> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.125);
    filter.clear();
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
}

void run()
{
    test_empty();
    test_same();
    test_increasing();
    test_clear();
}

} // namespace mean_double_suite

//-----------------------------------------------------------------------------

namespace variance_double_suite
{

using mean_ratio = std::ratio<1, 8>;
using var_ratio = std::ratio<1, 4>;

void test_empty()
{
    trial::online::moment::decay_variance<double, mean_ratio, var_ratio> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
}

void test_clear()
{
    const double tolerance = 1e-5;
    trial::online::moment::decay_variance<double, mean_ratio, var_ratio> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.125, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.191406, tolerance);
    filter.clear();
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
}

void test_same()
{
    // FIXME: Verify variance results
    const double tolerance = 1e-5;
    trial::online::moment::decay_variance<double, mean_ratio, var_ratio> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.125, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.191406, tolerance);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.234375, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.2901, tolerance);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.330078, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.329774, tolerance);
}

void test_increasing()
{
    // FIXME: Check variance results
    const double tolerance = 1e-5;
    trial::online::moment::decay_variance<double, mean_ratio, var_ratio> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.125, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.191406, tolerance);
    filter.push(2.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.359375, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.816467, tolerance);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.689453, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 1.94701, tolerance);
    filter.push(4.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1.10327, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 3.55801, tolerance);
    filter.push(5.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1.59036, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 5.57492, tolerance);
    filter.push(6.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2.14157, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 7.90306, tolerance);
    filter.push(7.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2.74887, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 10.445322, tolerance);
    filter.push(8.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 3.40526, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 13.1119, tolerance);
    filter.push(9.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 4.1046, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 15.825145, tolerance);
    filter.push(10.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 4.84153, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 18.521314, tolerance);
}

void run()
{
    test_empty();
    test_clear();
    test_same();
    test_increasing();
}

} // namespace variance_double_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    mean_double_suite::run();
    variance_double_suite::run();

    return boost::report_errors();
}
