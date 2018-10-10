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
#include <trial/online/moment/decay.hpp>

using namespace trial::online;

//-----------------------------------------------------------------------------

using one_four = std::ratio<1, 4>;
using one_eight = std::ratio<1, 8>;

//-----------------------------------------------------------------------------

namespace mean_double_suite
{

void test_empty()
{
    moment::decay<double, one_eight> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
}

void test_same()
{
    moment::decay<double, one_eight> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
}

void test_linear_increase()
{
    const double tolerance = 1e-5;

    moment::decay<double, one_eight> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    filter.push(2.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1.53333, tolerance);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2.08876, tolerance);
    filter.push(4.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2.66608, tolerance);
    filter.push(5.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 3.26502, tolerance);
    filter.push(6.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 3.88525, tolerance);
    filter.push(7.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 4.52635, tolerance);
    filter.push(8.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 5.18786, tolerance);
    filter.push(9.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 5.86924, tolerance);
    filter.push(10.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 6.56991, tolerance);
}

void test_linear_decrease()
{
    const double tolerance = 1e-5;
    moment::decay<double, one_eight> filter;
    filter.push(10.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 10.0);
    filter.push(9.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 9.46667, tolerance);
    filter.push(8.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 8.91124, tolerance);
    filter.push(7.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 8.33392, tolerance);
    filter.push(6.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 7.73498, tolerance);
    filter.push(5.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 7.11475, tolerance);
    filter.push(4.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 6.47365, tolerance);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 5.81214, tolerance);
    filter.push(2.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 5.13076, tolerance);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 4.43009, tolerance);
}

void test_exponential_increase()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    moment::decay<double, one_eight> filter;
    filter.push(1e0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    filter.push(1e1);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 5.8, tolerance);
    filter.push(1e2);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 41.473, tolerance);
    filter.push(1e3);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 331.01, tolerance);
    filter.push(1e4);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 2812.32, tolerance);
    filter.push(1e5);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 24852.2, tolerance);
    filter.push(1e6);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 225565.0, tolerance);
    filter.push(1e7);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 2.08696e6, tolerance);
    filter.push(1e8);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 1.95879e7, tolerance);
    filter.push(1e9);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 1.85889e8, tolerance);
}

void test_clear()
{
    moment::decay<double, one_eight> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    filter.clear();
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
}

void run()
{
    test_empty();
    test_same();
    test_linear_increase();
    test_linear_decrease();
    test_exponential_increase();
    test_clear();
}

} // namespace mean_double_suite

//-----------------------------------------------------------------------------

namespace mean_float_suite
{

void test_empty()
{
    moment::decay<float, one_eight> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0f);
}

void test_same()
{
    moment::decay<float, one_eight> filter;
    filter.push(1.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0f);
    filter.push(1.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0f);
    filter.push(1.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0f);
}

void test_linear_increase()
{
    const float tolerance = 1e-5;
    moment::decay<float, one_eight> filter;
    filter.push(1.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0f);
    filter.push(2.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1.53333f, tolerance);
    filter.push(3.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2.08876f, tolerance);
    filter.push(4.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2.66608f, tolerance);
    filter.push(6.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 3.52165f, tolerance);
    filter.push(5.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 3.85690f, tolerance);
    filter.push(7.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 4.50384f, tolerance);
    filter.push(8.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 5.16963f, tolerance);
    filter.push(9.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 5.85427f, tolerance);
    filter.push(10.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 6.55748f, tolerance);
}

void test_linear_decrease()
{
    const float tolerance = 1e-5;
    moment::decay<float, one_eight> filter;
    filter.push(10.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 10.0f);
    filter.push(9.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 9.46667f, tolerance);
    filter.push(8.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 8.91124f, tolerance);
    filter.push(7.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 8.33392f, tolerance);
    filter.push(5.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 7.47835f, tolerance);
    filter.push(6.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 7.1431f, tolerance);
    filter.push(4.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 6.49616f, tolerance);
    filter.push(3.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 5.83037f, tolerance);
    filter.push(2.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 5.14573f, tolerance);
    filter.push(1.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 4.44252f, tolerance);
}

void test_clear()
{
    moment::decay<float, one_eight> filter;
    filter.push(1.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0f);
    filter.clear();
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0f);
}

void run()
{
    test_empty();
    test_same();
    test_linear_increase();
    test_linear_decrease();
    test_clear();
}

} // namespace mean_float_suite

//-----------------------------------------------------------------------------

namespace variance_double_suite
{

void test_empty()
{
    moment::decay_variance<double, one_eight, one_four> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
}

void test_same()
{
    const double tolerance = 1e-5;
    moment::decay_variance<double, one_eight, one_four> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.0, tolerance);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.0, tolerance);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.0, tolerance);
}

void test_linear_increase()
{
    const double tolerance = 1e-5;
    moment::decay_variance<double, one_eight, one_four> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.0, tolerance);
    filter.push(2.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1.53333, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.124444, tolerance);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2.08876, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.429707, tolerance);
    filter.push(4.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2.66608, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.923291, tolerance);
    filter.push(5.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 3.26502, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 1.60733, tolerance);
    filter.push(6.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 3.88525, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 2.47861, tolerance);
    filter.push(7.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 4.52635, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 3.52889, tolerance);
    filter.push(8.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 5.18786, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 4.7455, tolerance);
    filter.push(9.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 5.86924, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 6.11216, tolerance);
    filter.push(10.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 6.56991, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 7.60984, tolerance);
}

void test_linear_decrease()
{
    const double tolerance = 1e-5;
    moment::decay_variance<double, one_eight, one_four> filter;
    filter.push(10.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 10.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.0, tolerance);
    filter.push(9.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 9.46667, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.124444, tolerance);
    filter.push(8.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 8.91124, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.429707, tolerance);
    filter.push(7.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 8.33392, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.923291, tolerance);
    filter.push(6.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 7.73498, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 1.60733, tolerance);
    filter.push(5.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 7.11475, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 2.47861, tolerance);
    filter.push(4.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 6.47365, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 3.52889, tolerance);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 5.81214, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 4.7455, tolerance);
    filter.push(2.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 5.13076, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 6.11216, tolerance);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 4.43009, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 7.60984, tolerance);
}

void test_exponential_increase()
{
    const auto tolerance = detail::close_to<double>(1e-4);
    moment::decay_variance<double, one_eight, one_four> filter;
    filter.push(1e0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 0.0, tolerance);
    filter.push(1e1);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 5.8, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 10.08, tolerance);
    filter.push(1e2);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 41.4734, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1486.96, tolerance);
    filter.push(1e3);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 331.01, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 164617., tolerance);
    filter.push(1e4);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 2812.32, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.70449e7, tolerance);
    filter.push(1e5);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 24852.2, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.72933e9, tolerance);
    filter.push(1e6);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 225565.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.74265e11, tolerance);
    filter.push(1e7);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 2.08696e6, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.75214e13, tolerance);
    filter.push(1e8);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 1.95879e7, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.76054e15, tolerance);
    filter.push(1e9);
    TRIAL_ONLINE_TEST_WITH(filter.value(), 1.85889e8, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.variance(), 1.76876e17, tolerance);
}

void test_clear()
{
    const double tolerance = 1e-5;
    moment::decay_variance<double, one_eight, one_four> filter;
    filter.push(0.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.0, tolerance);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.533333, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.variance(), 0.124444, tolerance);
    filter.clear();
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
}

void run()
{
    test_empty();
    test_same();
    test_linear_increase();
    test_linear_decrease();
    test_exponential_increase();
    test_clear();
}

} // namespace variance_double_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    mean_double_suite::run();
    mean_float_suite::run();
    variance_double_suite::run();

    return boost::report_errors();
}
