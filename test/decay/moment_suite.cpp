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
#include <trial/online/decay/moment.hpp>

using namespace trial::online;

//-----------------------------------------------------------------------------

const auto one_over_eight = 1.0 / 8.0;
const auto one_over_four = 1.0 / 4.0;

//-----------------------------------------------------------------------------

namespace mean_double_suite
{

void test_ctor()
{
    decay::moment<double> filter(one_over_eight);
    TRIAL_TEST_EQ(filter.mean(), 0.0);

    // Copy constructor
    decay::moment<double> copy(filter);
    TRIAL_TEST_EQ(copy.mean(), 0.0);

    // Move constructor
    decay::moment<double> mover(std::move(copy));
    TRIAL_TEST_EQ(mover.mean(), 0.0);
}

void test_same()
{
    decay::moment<double> filter(one_over_eight);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
}

void test_alternating()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    decay::moment<double> filter(one_over_eight);

    // Convergence towards 1.5

    filter.push(1.0);
    TRIAL_TEST_WITH(filter.mean(), 1.0, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 1.53333, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.mean(), 1.33136, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 1.53333, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.mean(), 1.39647, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 1.53333, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.mean(), 1.42356, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 1.53333, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.mean(), 1.43801, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 1.53333, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.mean(), 1.44673, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 1.53333, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.mean(), 1.4524, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 1.53333, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.mean(), 1.45627, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 1.53333, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.mean(), 1.45899, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 1.53333, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.mean(), 1.46094, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 1.53333, tolerance);

    // Outlier

    filter.push(1000.0);
    TRIAL_TEST_WITH(filter.mean(), 134.387, tolerance);

    // Slow recovery

    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 116.913, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.mean(), 101.719, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 88.7272, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.mean(), 77.3577, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 67.636, tolerance);
}

void test_linear_increase()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    decay::moment<double> filter(one_over_eight);

    filter.push(1.0);
    TRIAL_TEST_WITH(filter.mean(), 1.0, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 1.53333, tolerance);
    filter.push(3.0);
    TRIAL_TEST_WITH(filter.mean(), 2.08876, tolerance);
    filter.push(4.0);
    TRIAL_TEST_WITH(filter.mean(), 2.66608, tolerance);
    filter.push(5.0);
    TRIAL_TEST_WITH(filter.mean(), 3.26502, tolerance);
    filter.push(6.0);
    TRIAL_TEST_WITH(filter.mean(), 3.88525, tolerance);
    filter.push(7.0);
    TRIAL_TEST_WITH(filter.mean(), 4.52635, tolerance);
    filter.push(8.0);
    TRIAL_TEST_WITH(filter.mean(), 5.18786, tolerance);
    filter.push(9.0);
    TRIAL_TEST_WITH(filter.mean(), 5.86924, tolerance);
    filter.push(10.0);
    TRIAL_TEST_WITH(filter.mean(), 6.56991, tolerance);
}

void test_linear_decrease()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    decay::moment<double> filter(one_over_eight);

    filter.push(10.0);
    TRIAL_TEST_WITH(filter.mean(), 10.0, tolerance);
    filter.push(9.0);
    TRIAL_TEST_WITH(filter.mean(), 9.46667, tolerance);
    filter.push(8.0);
    TRIAL_TEST_WITH(filter.mean(), 8.91124, tolerance);
    filter.push(7.0);
    TRIAL_TEST_WITH(filter.mean(), 8.33392, tolerance);
    filter.push(6.0);
    TRIAL_TEST_WITH(filter.mean(), 7.73498, tolerance);
    filter.push(5.0);
    TRIAL_TEST_WITH(filter.mean(), 7.11475, tolerance);
    filter.push(4.0);
    TRIAL_TEST_WITH(filter.mean(), 6.47365, tolerance);
    filter.push(3.0);
    TRIAL_TEST_WITH(filter.mean(), 5.81214, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 5.13076, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.mean(), 4.43009, tolerance);
}

void test_exponential_increase()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    decay::moment<double> filter(one_over_eight);

    filter.push(1e0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    filter.push(1e1);
    TRIAL_TEST_WITH(filter.mean(), 5.8, tolerance);
    filter.push(1e2);
    TRIAL_TEST_WITH(filter.mean(), 41.473, tolerance);
    filter.push(1e3);
    TRIAL_TEST_WITH(filter.mean(), 331.01, tolerance);
    filter.push(1e4);
    TRIAL_TEST_WITH(filter.mean(), 2812.32, tolerance);
    filter.push(1e5);
    TRIAL_TEST_WITH(filter.mean(), 24852.2, tolerance);
    filter.push(1e6);
    TRIAL_TEST_WITH(filter.mean(), 225565.0, tolerance);
    filter.push(1e7);
    TRIAL_TEST_WITH(filter.mean(), 2.08696e6, tolerance);
    filter.push(1e8);
    TRIAL_TEST_WITH(filter.mean(), 1.95879e7, tolerance);
    filter.push(1e9);
    TRIAL_TEST_WITH(filter.mean(), 1.85889e8, tolerance);
}

void test_clear()
{
    decay::moment<double> filter(one_over_eight);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    filter.clear();
    TRIAL_TEST_EQ(filter.mean(), 0.0);
}

void run()
{
    test_ctor();
    test_same();
    test_alternating();
    test_linear_increase();
    test_linear_decrease();
    test_exponential_increase();
    test_clear();
}

} // namespace mean_double_suite

//-----------------------------------------------------------------------------

namespace mean_float_suite
{

void test_ctor()
{
    decay::moment<float> filter(one_over_eight);
    TRIAL_TEST_EQ(filter.mean(), 0.0f);
}

void test_same()
{
    decay::moment<float> filter(one_over_eight);
    filter.push(1.0f);
    TRIAL_TEST_EQ(filter.mean(), 1.0f);
    filter.push(1.0f);
    TRIAL_TEST_EQ(filter.mean(), 1.0f);
    filter.push(1.0f);
    TRIAL_TEST_EQ(filter.mean(), 1.0f);
}

void test_linear_increase()
{
    const auto tolerance = detail::close_to<float>(1e-5f);
    decay::moment<float> filter(one_over_eight);
    filter.push(1.0f);
    TRIAL_TEST_EQ(filter.mean(), 1.0f);
    filter.push(2.0f);
    TRIAL_TEST_WITH(filter.mean(), 1.53333f, tolerance);
    filter.push(3.0f);
    TRIAL_TEST_WITH(filter.mean(), 2.08876f, tolerance);
    filter.push(4.0f);
    TRIAL_TEST_WITH(filter.mean(), 2.66608f, tolerance);
    filter.push(6.0f);
    TRIAL_TEST_WITH(filter.mean(), 3.52165f, tolerance);
    filter.push(5.0f);
    TRIAL_TEST_WITH(filter.mean(), 3.85690f, tolerance);
    filter.push(7.0f);
    TRIAL_TEST_WITH(filter.mean(), 4.50384f, tolerance);
    filter.push(8.0f);
    TRIAL_TEST_WITH(filter.mean(), 5.16963f, tolerance);
    filter.push(9.0f);
    TRIAL_TEST_WITH(filter.mean(), 5.85427f, tolerance);
    filter.push(10.0f);
    TRIAL_TEST_WITH(filter.mean(), 6.55748f, tolerance);
}

void test_linear_decrease()
{
    const auto tolerance = detail::close_to<float>(1e-5f);
    decay::moment<float> filter(one_over_eight);
    filter.push(10.0f);
    TRIAL_TEST_EQ(filter.mean(), 10.0f);
    filter.push(9.0f);
    TRIAL_TEST_WITH(filter.mean(), 9.46667f, tolerance);
    filter.push(8.0f);
    TRIAL_TEST_WITH(filter.mean(), 8.91124f, tolerance);
    filter.push(7.0f);
    TRIAL_TEST_WITH(filter.mean(), 8.33392f, tolerance);
    filter.push(5.0f);
    TRIAL_TEST_WITH(filter.mean(), 7.47835f, tolerance);
    filter.push(6.0f);
    TRIAL_TEST_WITH(filter.mean(), 7.1431f, tolerance);
    filter.push(4.0f);
    TRIAL_TEST_WITH(filter.mean(), 6.49616f, tolerance);
    filter.push(3.0f);
    TRIAL_TEST_WITH(filter.mean(), 5.83037f, tolerance);
    filter.push(2.0f);
    TRIAL_TEST_WITH(filter.mean(), 5.14573f, tolerance);
    filter.push(1.0f);
    TRIAL_TEST_WITH(filter.mean(), 4.44252f, tolerance);
}

void test_clear()
{
    decay::moment<float> filter(one_over_eight);
    filter.push(1.0f);
    TRIAL_TEST_EQ(filter.mean(), 1.0f);
    filter.clear();
    TRIAL_TEST_EQ(filter.mean(), 0.0f);
}

void run()
{
    test_ctor();
    test_same();
    test_linear_increase();
    test_linear_decrease();
    test_clear();
}

} // namespace mean_float_suite

//-----------------------------------------------------------------------------

namespace variance_double_suite
{

void test_ctor()
{
    decay::moment_variance<double> filter(one_over_eight, one_over_four);
    TRIAL_TEST_EQ(filter.mean(), 0.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
}

void test_same()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    decay::moment_variance<double> filter(one_over_eight, one_over_four);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.mean(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.0, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.mean(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.0, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.mean(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.0, tolerance);
}

void test_linear_increase()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    decay::moment_variance<double> filter(one_over_eight, one_over_four);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_WITH(filter.variance(), 0.0, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 1.53333, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.124444, tolerance);
    filter.push(3.0);
    TRIAL_TEST_WITH(filter.mean(), 2.08876, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.429707, tolerance);
    filter.push(4.0);
    TRIAL_TEST_WITH(filter.mean(), 2.66608, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.923291, tolerance);
    filter.push(5.0);
    TRIAL_TEST_WITH(filter.mean(), 3.26502, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.60733, tolerance);
    filter.push(6.0);
    TRIAL_TEST_WITH(filter.mean(), 3.88525, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 2.47861, tolerance);
    filter.push(7.0);
    TRIAL_TEST_WITH(filter.mean(), 4.52635, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 3.52889, tolerance);
    filter.push(8.0);
    TRIAL_TEST_WITH(filter.mean(), 5.18786, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 4.7455, tolerance);
    filter.push(9.0);
    TRIAL_TEST_WITH(filter.mean(), 5.86924, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 6.11216, tolerance);
    filter.push(10.0);
    TRIAL_TEST_WITH(filter.mean(), 6.56991, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 7.60984, tolerance);
}

void test_linear_decrease()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    decay::moment_variance<double> filter(one_over_eight, one_over_four);
    filter.push(10.0);
    TRIAL_TEST_EQ(filter.mean(), 10.0);
    TRIAL_TEST_WITH(filter.variance(), 0.0, tolerance);
    filter.push(9.0);
    TRIAL_TEST_WITH(filter.mean(), 9.46667, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.124444, tolerance);
    filter.push(8.0);
    TRIAL_TEST_WITH(filter.mean(), 8.91124, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.429707, tolerance);
    filter.push(7.0);
    TRIAL_TEST_WITH(filter.mean(), 8.33392, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.923291, tolerance);
    filter.push(6.0);
    TRIAL_TEST_WITH(filter.mean(), 7.73498, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.60733, tolerance);
    filter.push(5.0);
    TRIAL_TEST_WITH(filter.mean(), 7.11475, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 2.47861, tolerance);
    filter.push(4.0);
    TRIAL_TEST_WITH(filter.mean(), 6.47365, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 3.52889, tolerance);
    filter.push(3.0);
    TRIAL_TEST_WITH(filter.mean(), 5.81214, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 4.7455, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 5.13076, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 6.11216, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.mean(), 4.43009, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 7.60984, tolerance);
}

void test_exponential_increase()
{
    const auto tolerance = detail::close_to<double>(1e-4);
    decay::moment_variance<double> filter(one_over_eight, one_over_four);
    filter.push(1e0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_WITH(filter.variance(), 0.0, tolerance);
    filter.push(1e1);
    TRIAL_TEST_WITH(filter.mean(), 5.8, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 10.08, tolerance);
    filter.push(1e2);
    TRIAL_TEST_WITH(filter.mean(), 41.4734, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1486.96, tolerance);
    filter.push(1e3);
    TRIAL_TEST_WITH(filter.mean(), 331.01, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 164617., tolerance);
    filter.push(1e4);
    TRIAL_TEST_WITH(filter.mean(), 2812.32, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.70449e7, tolerance);
    filter.push(1e5);
    TRIAL_TEST_WITH(filter.mean(), 24852.2, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.72933e9, tolerance);
    filter.push(1e6);
    TRIAL_TEST_WITH(filter.mean(), 225565.0, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.74265e11, tolerance);
    filter.push(1e7);
    TRIAL_TEST_WITH(filter.mean(), 2.08696e6, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.75214e13, tolerance);
    filter.push(1e8);
    TRIAL_TEST_WITH(filter.mean(), 1.95879e7, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.76054e15, tolerance);
    filter.push(1e9);
    TRIAL_TEST_WITH(filter.mean(), 1.85889e8, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.76876e17, tolerance);
}

void test_clear()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    decay::moment_variance<double> filter(one_over_eight, one_over_four);
    filter.push(0.0);
    TRIAL_TEST_WITH(filter.mean(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.0, tolerance);
    filter.push(1.0);
    TRIAL_TEST_WITH(filter.mean(), 0.533333, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.124444, tolerance);
    filter.clear();
    TRIAL_TEST_EQ(filter.mean(), 0.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
}

void run()
{
    test_ctor();
    test_same();
    test_linear_increase();
    test_linear_decrease();
    test_exponential_increase();
    test_clear();
}

} // namespace variance_double_suite

//-----------------------------------------------------------------------------

namespace skewness_double_suite
{

void test_ctor()
{
    decay::moment_skewness<double> filter(one_over_eight, one_over_four, one_over_four);
    TRIAL_TEST_EQ(filter.mean(), 0.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
}

void test_same()
{
    decay::moment_skewness<double> filter(one_over_eight, one_over_four, one_over_four);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
}

void test_linear_increase()
{
    // Results are inherently skewed because of the weights of exponential smoothing

    const auto tolerance = detail::close_to<double>(1e-5);
    decay::moment_skewness<double> filter(one_over_eight, one_over_four, one_over_four);

    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_WITH(filter.skewness(), 0.0, tolerance);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 1.53333, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.124444, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.32288, tolerance);
    filter.push(3.0);
    TRIAL_TEST_WITH(filter.mean(), 2.08876, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.429707, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.27863, tolerance);
    filter.push(4.0);
    TRIAL_TEST_WITH(filter.mean(), 2.66608, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.923291, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.23592, tolerance);
    filter.push(5.0);
    TRIAL_TEST_WITH(filter.mean(), 3.26502, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.60733, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.20177, tolerance);
    filter.push(6.0);
    TRIAL_TEST_WITH(filter.mean(), 3.88525, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 2.47861, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.1738, tolerance);
    filter.push(7.0);
    TRIAL_TEST_WITH(filter.mean(), 4.52635, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 3.52889, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.15036, tolerance);
    filter.push(8.0);
    TRIAL_TEST_WITH(filter.mean(), 5.18786, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 4.7455, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.13038, tolerance);
    filter.push(9.0);
    TRIAL_TEST_WITH(filter.mean(), 5.86924, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 6.11216, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.1132, tolerance);
    filter.push(10.0);
    TRIAL_TEST_WITH(filter.mean(), 6.56991, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 7.60984, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.09832, tolerance);
}

void test_exponential_increase()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    decay::moment_skewness<double> filter(one_over_eight, one_over_four, one_over_four);

    filter.push(1e0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_WITH(filter.variance(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 0.0, tolerance);
    filter.push(1e1);
    TRIAL_TEST_WITH(filter.mean(), 5.8, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 10.08, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.32288, tolerance);
    filter.push(1e2);
    TRIAL_TEST_WITH(filter.mean(), 41.4734, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1486.96, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.51234, tolerance);
    filter.push(1e3);
    TRIAL_TEST_WITH(filter.mean(), 331.01, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 164617., tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.64023, tolerance);
    filter.push(1e4);
    TRIAL_TEST_WITH(filter.mean(), 2812.32, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.70449e7, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.73071, tolerance);
    filter.push(1e5);
    TRIAL_TEST_WITH(filter.mean(), 24852.2, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.72933e9, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.79586, tolerance);
    filter.push(1e6);
    TRIAL_TEST_WITH(filter.mean(), 225565.0, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.74265e11, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.84332, tolerance);
    filter.push(1e7);
    TRIAL_TEST_WITH(filter.mean(), 2.08696e6, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.75214e13, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.87816, tolerance);
    filter.push(1e8);
    TRIAL_TEST_WITH(filter.mean(), 1.95879e7, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.76054e15, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.9039, tolerance);
    filter.push(1e9);
    TRIAL_TEST_WITH(filter.mean(), 1.85889e8, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.76876e17, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.92298, tolerance);
}

void test_left_skew()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    decay::moment_skewness<double> filter(one_over_eight, one_over_four, one_over_four);

    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 1.53333, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.124444, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.32288, tolerance);
    filter.push(5.0);
    TRIAL_TEST_WITH(filter.mean(), 2.84615, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 2.07671, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.45479, tolerance);
    filter.push(15.0);
    TRIAL_TEST_WITH(filter.mean(), 6.5174, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 27.632, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.55579, tolerance);
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
    decay::moment_kurtosis<double> filter(one_over_eight, one_over_four, one_over_four, one_over_four);
    TRIAL_TEST_EQ(filter.mean(), 0.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    TRIAL_TEST_EQ(filter.kurtosis(), 0.0);
}

void test_same()
{
    decay::moment_kurtosis<double> filter(one_over_eight, one_over_four, one_over_four, one_over_four);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    TRIAL_TEST_EQ(filter.kurtosis(), 0.0);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    TRIAL_TEST_EQ(filter.kurtosis(), 0.0);
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    TRIAL_TEST_EQ(filter.kurtosis(), 0.0);
}

void test_linear_increase()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    decay::moment_kurtosis<double> filter(one_over_eight, one_over_four, one_over_four, one_over_four);

    // Cumulative kurtosis converges towards 1.8

    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    TRIAL_TEST_EQ(filter.kurtosis(), 0.0);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 1.53333, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.124444, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.32288, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 1.75, tolerance);
    filter.push(3.0);
    TRIAL_TEST_WITH(filter.mean(), 2.08876, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.429707, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.27863, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 1.69807, tolerance);
    filter.push(4.0);
    TRIAL_TEST_WITH(filter.mean(), 2.66608, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.923291, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.23592, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 1.59157, tolerance);
    filter.push(5.0);
    TRIAL_TEST_WITH(filter.mean(), 3.26502, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.60733, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.20177, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 1.50264, tolerance);
    filter.push(6.0);
    TRIAL_TEST_WITH(filter.mean(), 3.88525, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 2.47861, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.1738, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 1.42982, tolerance);
    filter.push(7.0);
    TRIAL_TEST_WITH(filter.mean(), 4.52635, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 3.52889, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.15036, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 1.36931, tolerance);
    filter.push(8.0);
    TRIAL_TEST_WITH(filter.mean(), 5.18786, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 4.7455, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.13038, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 1.31835, tolerance);
    filter.push(9.0);
    TRIAL_TEST_WITH(filter.mean(), 5.86924, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 6.11216, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.1132, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 1.275, tolerance);
    filter.push(10.0);
    TRIAL_TEST_WITH(filter.mean(), 6.56991, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 7.60984, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.09832, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 1.23788, tolerance);
}

void test_exponential_increase()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    decay::moment_kurtosis<double> filter(one_over_eight, one_over_four, one_over_four, one_over_four);

    filter.push(1e0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_WITH(filter.variance(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 0.0, tolerance);
    filter.push(1e1);
    TRIAL_TEST_WITH(filter.mean(), 5.8, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 10.08, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.32288, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 1.75, tolerance);
    filter.push(1e2);
    TRIAL_TEST_WITH(filter.mean(), 41.4734, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1486.96, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.51234, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 2.29479, tolerance);
    filter.push(1e3);
    TRIAL_TEST_WITH(filter.mean(), 331.01, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 164617., tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.64023, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 2.70325, tolerance);
    filter.push(1e4);
    TRIAL_TEST_WITH(filter.mean(), 2812.32, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.70449e7, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.73071, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 3.01147, tolerance);
    filter.push(1e5);
    TRIAL_TEST_WITH(filter.mean(), 24852.2, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.72933e9, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.79586, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 3.24334, tolerance);
    filter.push(1e6);
    TRIAL_TEST_WITH(filter.mean(), 225565.0, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.74265e11, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.84332, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 3.41752, tolerance);
    filter.push(1e7);
    TRIAL_TEST_WITH(filter.mean(), 2.08696e6, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.75214e13, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.87816, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 3.54827, tolerance);
    filter.push(1e8);
    TRIAL_TEST_WITH(filter.mean(), 1.95879e7, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.76054e15, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.9039, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 3.64638, tolerance);
    filter.push(1e9);
    TRIAL_TEST_WITH(filter.mean(), 1.85889e8, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 1.76876e17, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.92298, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 3.71998, tolerance);
}

void test_left_skew()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    decay::moment_kurtosis<double> filter(one_over_eight, one_over_four, one_over_four, one_over_four);

    filter.push(1.0);
    TRIAL_TEST_EQ(filter.mean(), 1.0);
    TRIAL_TEST_EQ(filter.variance(), 0.0);
    TRIAL_TEST_EQ(filter.skewness(), 0.0);
    TRIAL_TEST_EQ(filter.kurtosis(), 0.0);
    filter.push(2.0);
    TRIAL_TEST_WITH(filter.mean(), 1.53333, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 0.124444, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.32288, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 1.75, tolerance);
    filter.push(5.0);
    TRIAL_TEST_WITH(filter.mean(), 2.84615, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 2.07671, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.45479, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 2.16144, tolerance);
    filter.push(15.0);
    TRIAL_TEST_WITH(filter.mean(), 6.5174, tolerance);
    TRIAL_TEST_WITH(filter.variance(), 27.632, tolerance);
    TRIAL_TEST_WITH(filter.skewness(), 1.55579, tolerance);
    TRIAL_TEST_WITH(filter.kurtosis(), 2.48764, tolerance);
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
// main
//-----------------------------------------------------------------------------

int main()
{
    mean_double_suite::run();
    mean_float_suite::run();
    variance_double_suite::run();
    skewness_double_suite::run();
    kurtosis_double_suite::run();

    return boost::report_errors();
}
