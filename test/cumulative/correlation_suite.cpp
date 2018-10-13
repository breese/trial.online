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
// main
//-----------------------------------------------------------------------------

int main()
{
    double_suite::run();

    return boost::report_errors();
}
