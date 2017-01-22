///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/online/detail/lightweight_test.hpp>
#include <trial/online/impulse/finite.hpp>

//-----------------------------------------------------------------------------

namespace double_1_suite
{

void test_half()
{
    const double tolerance = 1e-5;
    trial::online::impulse::finite<double> filter({0.5});
    TRIAL_ONLINE_TEST_EQUAL(filter.capacity(), 1);
    TRIAL_ONLINE_TEST(filter.empty());
    TRIAL_ONLINE_TEST(!filter.full());
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.0, tolerance);
    filter.push(1);
    TRIAL_ONLINE_TEST(!filter.empty());
    TRIAL_ONLINE_TEST(filter.full());
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1 * 0.5, tolerance);
    filter.push(3);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 3 * 0.5, tolerance);
    filter.push(5);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 5 * 0.5, tolerance);
}

void test_quarter()
{
    const double tolerance = 1e-5;
    trial::online::impulse::finite<double> filter({0.25});
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    filter.push(1);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1 * 0.25, tolerance);
    filter.push(1);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1 * 0.25, tolerance);
    filter.push(2);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2 * 0.25, tolerance);
    filter.push(3);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 3 * 0.25, tolerance);
}

void test()
{
    test_half();
    test_quarter();
}

} // namespace double_1_suite

namespace double_2_suite
{

void test_half_half()
{
    const double tolerance = 1e-5;
    trial::online::impulse::finite<double> filter({0.5, 0.5});
    TRIAL_ONLINE_TEST_EQUAL(filter.capacity(), 2);
    TRIAL_ONLINE_TEST(filter.empty());
    TRIAL_ONLINE_TEST(!filter.full());
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    filter.push(1);
    TRIAL_ONLINE_TEST(!filter.empty());
    TRIAL_ONLINE_TEST(!filter.full());
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 0.5, tolerance);
    filter.push(3);
    TRIAL_ONLINE_TEST(!filter.empty());
    TRIAL_ONLINE_TEST(filter.full());
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 3 * 0.5 + 1 * 0.5, tolerance);
    filter.push(6);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 6 * 0.5 + 3 * 0.5, tolerance);
}

void test_half_quarter()
{
    const double tolerance = 1e-5;
    trial::online::impulse::finite<double> filter({0.5, 0.25});
    filter.push(1);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1 * 0.5, tolerance);
    filter.push(3);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 3 * 0.5 + 1 * 0.25, tolerance);
    filter.push(6);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 6 * 0.5 + 3 * 0.25, tolerance);
    filter.push(9);
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 9 * 0.5 + 6 * 0.25, tolerance);
}

void test()
{
    test_half_half();
    test_half_quarter();
}

} // namespace double_2_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    double_1_suite::test();
    double_2_suite::test();

    return boost::report_errors();
}
