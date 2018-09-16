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
#include <trial/online/moment/normalized_decay.hpp>

using one_eight = std::ratio<1, 8>;

//-----------------------------------------------------------------------------

namespace mean_double_suite
{

void test_empty()
{
    trial::online::moment::normalized_decay<double, one_eight> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
}

void test_same()
{
    trial::online::moment::normalized_decay<double, one_eight> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
}

void test_increasing()
{
    const double tolerance = 1e-5;

    trial::online::moment::normalized_decay<double, one_eight> filter;
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

void test_clear()
{
    trial::online::moment::normalized_decay<double, one_eight> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    filter.clear();
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
}

void test()
{
    test_empty();
    test_same();
    test_increasing();
    test_clear();
}

} // namespace mean_double_suite

//-----------------------------------------------------------------------------

namespace mean_float_suite
{

void test_empty()
{
    trial::online::moment::normalized_decay<float, one_eight> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0f);
}

void test_same()
{
    trial::online::moment::normalized_decay<float, one_eight> filter;
    filter.push(1.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0f);
    filter.push(1.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0f);
    filter.push(1.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0f);
}

void test_increasing()
{
    const float tolerance = 1e-5;
    trial::online::moment::normalized_decay<float, one_eight> filter;
    filter.push(1.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0f);
    filter.push(2.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1.53333f, tolerance);
    filter.push(3.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2.08876f, tolerance);
    filter.push(4.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2.66608f, tolerance);
    filter.push(5.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 3.26502f, tolerance);
    filter.push(6.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 3.88525f, tolerance);
    filter.push(7.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 4.52635f, tolerance);
    filter.push(8.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 5.18786f, tolerance);
    filter.push(9.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 5.86924f, tolerance);
    filter.push(10.0f);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 6.56991f, tolerance);
}

void test_clear()
{
    trial::online::moment::normalized_decay<float, one_eight> filter;
    filter.push(1.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0f);
    filter.clear();
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0f);
}

void test()
{
    test_empty();
    test_same();
    test_increasing();
    test_clear();
}

} // namespace mean_float_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    mean_double_suite::test();
    mean_float_suite::test();

    return boost::report_errors();
}
