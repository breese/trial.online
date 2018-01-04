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
#include <trial/online/average/cumulative.hpp>

//-----------------------------------------------------------------------------

namespace double_suite
{

void test_empty()
{
    trial::online::average::cumulative<double> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
}

void test_same()
{
    trial::online::average::cumulative<int> filter;
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
    trial::online::average::cumulative<int> filter;
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
    trial::online::average::cumulative<int> filter;
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

} // namespace double_suite

//-----------------------------------------------------------------------------

namespace int_suite
{

void test_empty()
{
    trial::online::average::cumulative<int> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0);
}

void test_same()
{
    trial::online::average::cumulative<int> filter;
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
    trial::online::average::cumulative<int> filter;
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

} // namespace int_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    double_suite::run();
    int_suite::run();

    return boost::report_errors();
}
