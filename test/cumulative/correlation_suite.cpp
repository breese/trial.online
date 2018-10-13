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
#include <trial/online/cumulative/correlation.hpp>

using namespace trial::online;

//-----------------------------------------------------------------------------

namespace double_suite
{

void test_empty()
{
    cumulative::correlation<double> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
}

void test_hinton()
{
    const double tolerance = 1e-5;
    cumulative::correlation<double> filter;
    filter.push(40.0, 58.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1.0, tolerance);
    filter.push(43.0, 73.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1.0, tolerance);
    filter.push(18.0, 56.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.67543, tolerance);
    filter.push(10.0, 47.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.84317, tolerance);
    filter.push(25.0, 58.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.84181, tolerance);
    filter.push(33.0, 54.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.77024, tolerance);
    filter.push(27.0, 45.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.67569, tolerance);
    filter.push(17.0, 32.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.68849, tolerance);
    filter.push(30.0, 68.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.66685, tolerance);
    filter.push(47.0, 69.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.72071, tolerance);
}

void run()
{
    test_empty();
    test_hinton();
}

} // namespace double_suite

//-----------------------------------------------------------------------------

namespace anscombe_quartet
{

void anscombe_I()
{
    const float tolerance = 5e-2;
    cumulative::correlation<double> filter;

    filter.push(10.0, 8.04);
    filter.push(8.0, 6.95);
    filter.push(13.0, 7.58);
    filter.push(9.0, 8.81);
    filter.push(11.0, 8.33);
    filter.push(14.0, 9.96);
    filter.push(6.0, 7.24);
    filter.push(4.0, 4.26);
    filter.push(12.0, 10.84);
    filter.push(7.0, 4.82);
    filter.push(5.0, 5.68);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.816, tolerance);
}

void anscombe_II()
{
    const float tolerance = 5e-2;
    cumulative::correlation<double> filter;

    filter.push(10.0, 9.14);
    filter.push(8.0, 8.14);
    filter.push(13.0, 8.74);
    filter.push(9.0, 8.77);
    filter.push(11.0, 9.26);
    filter.push(14.0, 8.10);
    filter.push(6.0, 6.13);
    filter.push(4.0, 3.10);
    filter.push(12.0, 9.13);
    filter.push(7.0, 7.26);
    filter.push(5.0, 4.74);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.816, tolerance);
}

void anscombe_III()
{
    const float tolerance = 5e-2;
    cumulative::correlation<double> filter;

    filter.push(10.0, 7.46);
    filter.push(8.0, 6.77);
    filter.push(13.0, 12.74);
    filter.push(9.0, 7.11);
    filter.push(11.0, 7.81);
    filter.push(14.0, 8.84);
    filter.push(6.0, 6.08);
    filter.push(4.0, 5.39);
    filter.push(12.0, 8.15);
    filter.push(7.0, 6.42);
    filter.push(5.0, 5.73);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.816, tolerance);
}

void anscombe_IV()
{
    const float tolerance = 5e-2;
    cumulative::correlation<double> filter;

    filter.push(8.0, 6.58);
    filter.push(8.0, 5.76);
    filter.push(8.0, 7.71);
    filter.push(8.0, 8.84);
    filter.push(8.0, 8.47);
    filter.push(8.0, 7.04);
    filter.push(8.0, 5.25);
    filter.push(19.0, 12.50);
    filter.push(8.0, 5.56);
    filter.push(8.0, 7.91);
    filter.push(8.0, 6.89);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.816, tolerance);
}

void run()
{
    // https://en.wikipedia.org/wiki/Anscombe%27s_quartet

    anscombe_I();
    anscombe_II();
    anscombe_III();
    anscombe_IV();
}

} // namespace anscombe_quartet

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    double_suite::run();
    anscombe_quartet::run();

    return boost::report_errors();
}
