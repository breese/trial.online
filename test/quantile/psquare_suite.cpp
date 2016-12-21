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
#include <trial/online/quantile/psquare.hpp>

typedef std::ratio<1, 4> quantile_25_type;
typedef std::ratio<3, 4> quantile_75_type;
typedef std::ratio<9, 10> quantile_90_type;

//-----------------------------------------------------------------------------

namespace paper_example
{

void test_median()
{
    const double tolerance = 1e-5;
    trial::online::quantile::psquare_median<double> quantile;

    auto params = quantile.parameters();
    TRIAL_ONLINE_TEST_EQUAL(params[0].position, 1);
    TRIAL_ONLINE_TEST_EQUAL(params[1].position, 2);
    TRIAL_ONLINE_TEST_EQUAL(params[2].position, 3);
    TRIAL_ONLINE_TEST_EQUAL(params[3].position, 4);
    TRIAL_ONLINE_TEST_EQUAL(params[4].position, 5);
    TRIAL_ONLINE_TEST_CLOSE(params[0].height, 0.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[1].height, 0.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[2].height, 0.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[3].height, 0.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[4].height, 0.0, tolerance);

    quantile.push(0.02);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 0.02, tolerance); // 0.02
    params = quantile.parameters();
    TRIAL_ONLINE_TEST_EQUAL(params[0].position, 1);
    TRIAL_ONLINE_TEST_EQUAL(params[1].position, 2);
    TRIAL_ONLINE_TEST_EQUAL(params[2].position, 3);
    TRIAL_ONLINE_TEST_EQUAL(params[3].position, 4);
    TRIAL_ONLINE_TEST_EQUAL(params[4].position, 5);
    TRIAL_ONLINE_TEST_CLOSE(params[0].height, 0.02, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[1].height, 0.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[2].height, 0.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[3].height, 0.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[4].height, 0.0, tolerance);

    quantile.push(0.5);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 0.02, tolerance); // 0.26
    params = quantile.parameters();
    TRIAL_ONLINE_TEST_EQUAL(params[0].position, 1);
    TRIAL_ONLINE_TEST_EQUAL(params[1].position, 2);
    TRIAL_ONLINE_TEST_EQUAL(params[2].position, 3);
    TRIAL_ONLINE_TEST_EQUAL(params[3].position, 4);
    TRIAL_ONLINE_TEST_EQUAL(params[4].position, 5);
    TRIAL_ONLINE_TEST_CLOSE(params[0].height, 0.02, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[1].height, 0.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[2].height, 0.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[3].height, 0.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[4].height, 0.0, tolerance);

    quantile.push(0.74);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 0.5, tolerance); // 0.5
    params = quantile.parameters();
    TRIAL_ONLINE_TEST_EQUAL(params[0].position, 1);
    TRIAL_ONLINE_TEST_EQUAL(params[1].position, 2);
    TRIAL_ONLINE_TEST_EQUAL(params[2].position, 3);
    TRIAL_ONLINE_TEST_EQUAL(params[3].position, 4);
    TRIAL_ONLINE_TEST_EQUAL(params[4].position, 5);
    TRIAL_ONLINE_TEST_CLOSE(params[0].height, 0.02, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[1].height, 0.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[2].height, 0.74, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[3].height, 0.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[4].height, 0.0, tolerance);

    quantile.push(3.39);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 0.5, tolerance); // 0.62
    params = quantile.parameters();
    TRIAL_ONLINE_TEST_EQUAL(params[0].position, 1);
    TRIAL_ONLINE_TEST_EQUAL(params[1].position, 2);
    TRIAL_ONLINE_TEST_EQUAL(params[2].position, 3);
    TRIAL_ONLINE_TEST_EQUAL(params[3].position, 4);
    TRIAL_ONLINE_TEST_EQUAL(params[4].position, 5);
    TRIAL_ONLINE_TEST_CLOSE(params[0].height, 0.02, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[1].height, 0.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[2].height, 0.74, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[3].height, 3.39, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[4].height, 0.0, tolerance);

    quantile.push(0.83);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 0.74, tolerance); // 0.74
    params = quantile.parameters();
    TRIAL_ONLINE_TEST_EQUAL(params[0].position, 1);
    TRIAL_ONLINE_TEST_EQUAL(params[1].position, 2);
    TRIAL_ONLINE_TEST_EQUAL(params[2].position, 3);
    TRIAL_ONLINE_TEST_EQUAL(params[3].position, 4);
    TRIAL_ONLINE_TEST_EQUAL(params[4].position, 5);
    TRIAL_ONLINE_TEST_CLOSE(params[0].height, 0.02, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[1].height, 0.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[2].height, 0.74, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[3].height, 0.83, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[4].height, 3.39, tolerance);

    quantile.push(22.37);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 0.74, tolerance); // 0.785
    params = quantile.parameters();
    TRIAL_ONLINE_TEST_EQUAL(params[0].position, 1);
    TRIAL_ONLINE_TEST_EQUAL(params[1].position, 2);
    TRIAL_ONLINE_TEST_EQUAL(params[2].position, 3);
    TRIAL_ONLINE_TEST_EQUAL(params[3].position, 5);
    TRIAL_ONLINE_TEST_EQUAL(params[4].position, 6);
    TRIAL_ONLINE_TEST_CLOSE(params[0].height, 0.02, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[1].height, 0.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[2].height, 0.74, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[3].height, 8.04, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[4].height, 22.37, tolerance);

    quantile.push(10.15);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 3.25333, tolerance); // 0.83
    params = quantile.parameters();
    TRIAL_ONLINE_TEST_EQUAL(params[0].position, 1);
    TRIAL_ONLINE_TEST_EQUAL(params[1].position, 2);
    TRIAL_ONLINE_TEST_EQUAL(params[2].position, 4);
    TRIAL_ONLINE_TEST_EQUAL(params[3].position, 6);
    TRIAL_ONLINE_TEST_EQUAL(params[4].position, 7);
    TRIAL_ONLINE_TEST_CLOSE(params[0].height, 0.02, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[1].height, 0.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[2].height, 3.25333, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[3].height, 14.41222, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[4].height, 22.37, tolerance);

    quantile.push(15.43);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 7.53148, tolerance); // 2.11
    params = quantile.parameters();
    TRIAL_ONLINE_TEST_EQUAL(params[0].position, 1);
    TRIAL_ONLINE_TEST_EQUAL(params[1].position, 3);
    TRIAL_ONLINE_TEST_EQUAL(params[2].position, 5);
    TRIAL_ONLINE_TEST_EQUAL(params[3].position, 7);
    TRIAL_ONLINE_TEST_EQUAL(params[4].position, 8);
    TRIAL_ONLINE_TEST_CLOSE(params[0].height, 0.02, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[1].height, 1.57778, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[2].height, 7.53148, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[3].height, 19.3584, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[4].height, 22.37, tolerance);

    quantile.push(38.62);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 7.53148, tolerance); // 3.39
    params = quantile.parameters();
    TRIAL_ONLINE_TEST_EQUAL(params[0].position, 1);
    TRIAL_ONLINE_TEST_EQUAL(params[1].position, 3);
    TRIAL_ONLINE_TEST_EQUAL(params[2].position, 5);
    TRIAL_ONLINE_TEST_EQUAL(params[3].position, 7);
    TRIAL_ONLINE_TEST_EQUAL(params[4].position, 9);
    TRIAL_ONLINE_TEST_CLOSE(params[0].height, 0.02, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[1].height, 1.57778, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[2].height, 7.53148, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[3].height, 19.3584, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[4].height, 38.62, tolerance);

    quantile.push(15.92);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 11.2658, tolerance); // 6.77
    params = quantile.parameters();
    TRIAL_ONLINE_TEST_EQUAL(params[0].position, 1);
    TRIAL_ONLINE_TEST_EQUAL(params[1].position, 4);
    TRIAL_ONLINE_TEST_EQUAL(params[2].position, 6);
    TRIAL_ONLINE_TEST_EQUAL(params[3].position, 7);
    TRIAL_ONLINE_TEST_EQUAL(params[4].position, 10);
    TRIAL_ONLINE_TEST_CLOSE(params[0].height, 0.02, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[1].height, 4.00514, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[2].height, 11.2658, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[3].height, 13.91597, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[4].height, 38.62, tolerance);

    quantile.push(34.60);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 11.2658, tolerance); // 10.15
    params = quantile.parameters();
    TRIAL_ONLINE_TEST_EQUAL(params[0].position, 1);
    TRIAL_ONLINE_TEST_EQUAL(params[1].position, 3);
    TRIAL_ONLINE_TEST_EQUAL(params[2].position, 6);
    TRIAL_ONLINE_TEST_EQUAL(params[3].position, 8);
    TRIAL_ONLINE_TEST_EQUAL(params[4].position, 11);
    TRIAL_ONLINE_TEST_CLOSE(params[0].height, 0.02, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[1].height, 1.75598, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[2].height, 11.2658, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[3].height, 17.97648, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[4].height, 38.62, tolerance);

    quantile.push(10.28);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 8.34625, tolerance); // 10.215
    params = quantile.parameters();
    TRIAL_ONLINE_TEST_EQUAL(params[0].position, 1);
    TRIAL_ONLINE_TEST_EQUAL(params[1].position, 4);
    TRIAL_ONLINE_TEST_EQUAL(params[2].position, 6);
    TRIAL_ONLINE_TEST_EQUAL(params[3].position, 10);
    TRIAL_ONLINE_TEST_EQUAL(params[4].position, 12);
    TRIAL_ONLINE_TEST_CLOSE(params[0].height, 0.02, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[1].height, 3.3787, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[2].height, 8.34625, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[3].height, 23.63396, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[4].height, 38.62, tolerance);

    quantile.push(1.47);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 8.34625, tolerance); // 10.15
    params = quantile.parameters();
    TRIAL_ONLINE_TEST_EQUAL(params[0].position, 1);
    TRIAL_ONLINE_TEST_EQUAL(params[1].position, 4);
    TRIAL_ONLINE_TEST_EQUAL(params[2].position, 7);
    TRIAL_ONLINE_TEST_EQUAL(params[3].position, 10);
    TRIAL_ONLINE_TEST_EQUAL(params[4].position, 13);
    TRIAL_ONLINE_TEST_CLOSE(params[0].height, 0.02, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[1].height, 1.71698, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[2].height, 8.34625, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[3].height, 17.97648, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[4].height, 38.62, tolerance);

    quantile.push(0.4);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 5.85354, tolerance); // 6.77
    params = quantile.parameters();
    TRIAL_ONLINE_TEST_EQUAL(params[0].position, 1);
    TRIAL_ONLINE_TEST_EQUAL(params[1].position, 4);
    TRIAL_ONLINE_TEST_EQUAL(params[2].position, 7);
    TRIAL_ONLINE_TEST_EQUAL(params[3].position, 10);
    TRIAL_ONLINE_TEST_EQUAL(params[4].position, 14);
    TRIAL_ONLINE_TEST_CLOSE(params[0].height, 0.02, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[1].height, 0.527512, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[2].height, 5.85354, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[3].height, 13.29556, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[4].height, 38.62, tolerance);

    quantile.push(0.05);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 5.85354, tolerance); // 3.39
    params = quantile.parameters();
    TRIAL_ONLINE_TEST_EQUAL(params[0].position, 1);
    TRIAL_ONLINE_TEST_EQUAL(params[1].position, 4);
    TRIAL_ONLINE_TEST_EQUAL(params[2].position, 8);
    TRIAL_ONLINE_TEST_EQUAL(params[3].position, 12);
    TRIAL_ONLINE_TEST_EQUAL(params[4].position, 15);
    TRIAL_ONLINE_TEST_CLOSE(params[0].height, 0.02, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[1].height, 0.527512, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[2].height, 5.85354, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[3].height, 17.97648, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[4].height, 38.62, tolerance);
}

void test_25_quantile()
{
    const double tolerance = 1e-5;
    trial::online::quantile::psquare<double, quantile_25_type> quantile;
    quantile.push(0.02);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 0.02, tolerance); // 0.02
    quantile.push(0.5);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 0.02, tolerance); // 0.02
    quantile.push(0.74);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 0.02, tolerance); // 0.14
    quantile.push(3.39);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 0.02, tolerance); // 0.26
    quantile.push(0.83);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 0.5, tolerance); // 0.38
    quantile.push(22.37);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 0.74, tolerance); // 0.75
    quantile.push(10.15);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 0.74, tolerance); // 0.56
    quantile.push(15.43);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 0.74, tolerance); // 0.62
    quantile.push(38.62);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 0.74, tolerance); // 0.68
    quantile.push(15.92);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 2.83414, tolerance); // 0.74
    quantile.push(34.60);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 2.83414, tolerance); // 0.7625
    quantile.push(10.28);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 1.24651, tolerance); // 0.785
    quantile.push(1.47);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 2.62173, tolerance); // 0.8075
    quantile.push(0.4);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 1.13148, tolerance); // 0.74
    quantile.push(0.05);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 0.195157, tolerance); // 0.56
}

void test_75_quantile()
{
    const double tolerance = 1e-4;
    trial::online::quantile::psquare<double, quantile_75_type> quantile;
    quantile.push(0.02);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 0.02, tolerance); // 0.02
    quantile.push(0.5);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 0.5, tolerance); // 0.5
    quantile.push(0.74);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 0.74, tolerance); // 0.68
    quantile.push(3.39);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 0.74, tolerance); // 2.065
    quantile.push(0.83);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 0.83, tolerance); // 1.47
    quantile.push(22.37);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 0.74, tolerance); // 3.39
    quantile.push(10.15);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 3.25333, tolerance); // 8.46
    quantile.push(15.43);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 7.53148, tolerance); // 12.79
    quantile.push(38.62);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 12.6492, tolerance); // 17.165
    quantile.push(15.92);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 17.6706, tolerance); // 15.92
    quantile.push(34.60);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 17.6706, tolerance); // 20.7575
    quantile.push(10.28);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 21.5847, tolerance); // 19.145
    quantile.push(1.47);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 21.5847, tolerance); // 17.5325
    quantile.push(0.4);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 17.7765, tolerance); // 15.92
    quantile.push(0.05);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 21.9882, tolerance); // 15.7975
}

void test()
{
    test_median();
    test_25_quantile();
    test_75_quantile();
}

} // namespace paper_example

//-----------------------------------------------------------------------------

namespace double_90_suite
{

void test_empty()
{
    trial::online::quantile::psquare<double, quantile_90_type> quantile;
    TRIAL_ONLINE_TEST_EQUAL(quantile.value(), 0.0);
}

void test_one()
{
    trial::online::quantile::psquare<double, quantile_90_type> quantile;
    quantile.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(quantile.value(), 1.0);
}

void test_accumulate_one()
{
    trial::online::quantile::psquare<double, quantile_90_type> quantile;
    quantile.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(quantile.value(), 1.0);
    quantile.push(2.0);
    TRIAL_ONLINE_TEST_EQUAL(quantile.value(), 2.0);
    quantile.push(3.0);
    TRIAL_ONLINE_TEST_EQUAL(quantile.value(), 3.0);
    quantile.push(4.0);
    TRIAL_ONLINE_TEST_EQUAL(quantile.value(), 4.0);
    quantile.push(5.0);
    TRIAL_ONLINE_TEST_EQUAL(quantile.value(), 5.0);
    quantile.push(6.0);
    TRIAL_ONLINE_TEST_EQUAL(quantile.value(), 3.0); // 5.9
    quantile.push(7.0);
    TRIAL_ONLINE_TEST_EQUAL(quantile.value(), 4.0); // 6.8
    quantile.push(8.0);
    TRIAL_ONLINE_TEST_EQUAL(quantile.value(), 5.0); // 7.7
    quantile.push(9.0);
    TRIAL_ONLINE_TEST_EQUAL(quantile.value(), 6.0); // 8.6
    quantile.push(10.0);
    TRIAL_ONLINE_TEST_EQUAL(quantile.value(), 7.0); // 9.5
    quantile.push(11.0);
    TRIAL_ONLINE_TEST_EQUAL(quantile.value(), 8.0); // 10.4
}

void test()
{
    test_empty();
    test_accumulate_one();
}

} // namespace double_90_suite

//-----------------------------------------------------------------------------

namespace double_approx_suite
{

void test_count_100()
{
    const double tolerance = 1e-4;
    trial::online::quantile::psquare_median<double> quantile;
    // Approximate normal distribution with expectation 1 and spread 1 after 100 iterations.
    quantile.parameters({
            { 20, -2.0 },
            { 40, 0.5 },
            { 60, 1.0 },
            { 80, 1.5 },
            { 100, 4.0 } });

    quantile.push(1000.0);
    TRIAL_ONLINE_TEST_CLOSE(quantile.value(), 1.02378, tolerance);
    auto params = quantile.parameters();
    TRIAL_ONLINE_TEST_EQUAL(params.size(), 5);
    TRIAL_ONLINE_TEST_EQUAL(params[0].position, 20);
    TRIAL_ONLINE_TEST_EQUAL(params[1].position, 41);
    TRIAL_ONLINE_TEST_EQUAL(params[2].position, 61);
    TRIAL_ONLINE_TEST_EQUAL(params[3].position, 81);
    TRIAL_ONLINE_TEST_EQUAL(params[4].position, 101);
    TRIAL_ONLINE_TEST_CLOSE(params[0].height, -2.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[1].height, 0.5725, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[2].height, 1.02378, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[3].height, 25.2863, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(params[4].height, 1000.0, tolerance);
}

void test()
{
    test_count_100();
}

} // namespace double_approx_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    paper_example::test();
    double_90_suite::test();
    double_approx_suite::test();

    return boost::report_errors();
}
