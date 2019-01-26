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
#include <trial/online/cumulative/regression.hpp>

using namespace trial::online;

//-----------------------------------------------------------------------------

template <typename T>
using cumulative_linear = cumulative::regression<T>;

namespace cumulative_double
{

void test_ctor()
{
    cumulative_linear<double> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
}

void test_same()
{
    const double tolerance = 1e-5;
    cumulative_linear<double> filter;

    filter.push(1.0, 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_CLOSE(filter.slope(), 0.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(0), 1.0, tolerance);

    filter.push(1.0, 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    TRIAL_ONLINE_TEST_CLOSE(filter.slope(), 0.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(0), 1.0, tolerance);

    filter.push(1.0, 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 3);
    TRIAL_ONLINE_TEST_CLOSE(filter.slope(), 0.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(0), 1.0, tolerance);
}

void test_linear_increase()
{
    const double tolerance = 1e-5;
    cumulative_linear<double> filter;

    filter.push(0.0, 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_CLOSE(filter.slope(), 0.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(0), 0.0, tolerance);

    filter.push(1.0, 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    TRIAL_ONLINE_TEST_CLOSE(filter.slope(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(0), 0.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(1.0), 1.0, tolerance);

    filter.push(2.0, 2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 3);
    TRIAL_ONLINE_TEST_CLOSE(filter.slope(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(0), 0.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(2.0), 2.0, tolerance);

    filter.push(3.0, 3.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 4);
    TRIAL_ONLINE_TEST_CLOSE(filter.slope(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(0), 0.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(3.0), 3.0, tolerance);

    filter.push(4.0, 4.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 5);
    TRIAL_ONLINE_TEST_CLOSE(filter.slope(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(0), 0.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(4.0), 4.0, tolerance);
}

void test_linear_increase__offset()
{
    const double tolerance = 1e-5;
    cumulative_linear<double> filter;

    filter.push(2.0, 2.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.slope(), 0.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(0), 2.0, tolerance);

    filter.push(3.0, 3.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.slope(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(0), 0.0, tolerance);

    filter.push(4.0, 4.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.slope(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(0), 0.0, tolerance);
}

void test_linear_decrease()
{
    const double tolerance = 1e-5;
    cumulative_linear<double> filter;

    filter.push(2.0, 2.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.slope(), 0.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(0), 2.0, tolerance);

    filter.push(1.0, 1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.slope(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(0), 0.0, tolerance);

    filter.push(0.0, 0.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.slope(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(0), 0.0, tolerance);

    filter.push(-1.0, -1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.slope(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(0), 0.0, tolerance);

    filter.push(-2.0, -2.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.slope(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(0), 0.0, tolerance);
}

void test_scatter()
{
    const double tolerance = 1e-5;
    cumulative_linear<double> filter;

    filter.push(1.0, 1.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.slope(), 0.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(0), 1.0, tolerance);

    filter.push(2.0, 2.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.slope(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(0), 0.0, tolerance);

    filter.push(3.0, 1.3);
    TRIAL_ONLINE_TEST_CLOSE(filter.slope(), 0.15, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(0), 1.13333, tolerance);

    filter.push(4.0, 3.75);
    TRIAL_ONLINE_TEST_CLOSE(filter.slope(), 0.755, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(0), 0.125, tolerance);

    filter.push(5.0, 2.25);
    TRIAL_ONLINE_TEST_CLOSE(filter.slope(), 0.425, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(0), 0.785, tolerance);
}

void run()
{
    test_ctor();
    test_same();
    test_linear_increase();
    test_linear_increase__offset();
    test_linear_decrease();
    test_scatter();
}

} // namespace cumulative_double

//-----------------------------------------------------------------------------

namespace anscombe_quartet
{

void anscombe_I()
{
    const float tolerance = 5e-2f;
    cumulative_linear<float> filter;

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
    TRIAL_ONLINE_TEST_CLOSE(filter.slope(), 0.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(0), 3.0, tolerance);
}

void anscombe_II()
{
    const float tolerance = 5e-2f;
    cumulative_linear<float> filter;

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
    TRIAL_ONLINE_TEST_CLOSE(filter.slope(), 0.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(0), 3.0, tolerance);
}

void anscombe_III()
{
    const float tolerance = 5e-2f;
    cumulative_linear<float> filter;

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
    TRIAL_ONLINE_TEST_CLOSE(filter.slope(), 0.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(0), 3.0, tolerance);
}

void anscombe_IV()
{
    const float tolerance = 5e-2f;
    cumulative_linear<float> filter;

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
    TRIAL_ONLINE_TEST_CLOSE(filter.slope(), 0.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.at(0), 3.0, tolerance);
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
    cumulative_double::run();
    anscombe_quartet::run();

    return boost::report_errors();
}
