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
#include <trial/online/average/exponential.hpp>

//-----------------------------------------------------------------------------

namespace double_1_8_suite
{

void test_empty()
{
    trial::online::average::exponential<double> filter(0.125);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 0.0);
}

void test_clear()
{
    trial::online::average::exponential<double> filter(0.125);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.0);
    filter.clear();
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 0.0);
}

void test_same()
{
    trial::online::average::exponential<double> filter(0.125);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.0);
}

void test_two()
{
    trial::online::average::exponential<double> filter(0.125);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.0);
    filter.push(4.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 2.6);
}

void test_many()
{
    const double tolerance = 1e-5;

    trial::online::average::exponential<double> filter(0.125);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.0);
    filter.push(2.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.mean(), 1.53333, tolerance);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.mean(), 2.08876, tolerance);
    filter.push(4.0);
    TRIAL_ONLINE_TEST_CLOSE(filter.mean(), 2.66608, tolerance);
}

void test()
{
    test_empty();
    test_clear();
    test_same();
    test_two();
    test_many();
}

} // namespace double_1_8_suite

//-----------------------------------------------------------------------------

namespace float_1_8_suite
{

void test_empty()
{
    trial::online::average::exponential<float> filter(0.125f);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 0.0f);
}

void test_clear()
{
    trial::online::average::exponential<float> filter(0.125f);
    filter.push(1.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.0f);
    filter.clear();
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 0.0f);
}

void test_same()
{
    trial::online::average::exponential<float> filter(0.125f);
    filter.push(1.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.0f);
    filter.push(1.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.0f);
    filter.push(1.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.0f);
}

void test_two()
{
    trial::online::average::exponential<float> filter(0.125f);
    filter.push(1.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 1.0f);
    filter.push(4.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.mean(), 2.6f);
}

void test()
{
    test_empty();
    test_clear();
    test_same();
    test_two();
}

} // namespace float_1_8_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    double_1_8_suite::test();
    float_1_8_suite::test();

    return boost::report_errors();
}
