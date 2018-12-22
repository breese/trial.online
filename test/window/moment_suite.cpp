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
#include <trial/online/window/moment.hpp>

using namespace trial::online;

//-----------------------------------------------------------------------------

namespace average_double_1_suite
{

void test_ctor()
{
    window::moment<double, 1> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.capacity(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), true);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
}

void test_many()
{
    window::moment<double, 1> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.capacity(), 1);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), true);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    filter.push(2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), true);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 2.0);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), true);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 3.0);
}

void run()
{
    test_ctor();
    test_many();
}

} // namespace average_double_1_suite

//-----------------------------------------------------------------------------

namespace average_double_2_suite
{

void test_ctor()
{
    window::moment<double, 2> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.capacity(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), true);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
}

void test_one()
{
    window::moment<double, 2> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
}

void test_same()
{
    window::moment<double, 2> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), true);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
}

void test_two()
{
    window::moment<double, 2> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 2.0);
}

void test_three()
{
    window::moment<double, 2> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 2.0);
    filter.push(0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.5);
}

void test_clear()
{
    window::moment<double, 2> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    filter.clear();
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    filter.push(2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 2.0);
}

void run()
{
    test_ctor();
    test_same();
    test_one();
    test_two();
    test_three();
    test_clear();
}

} // namespace average_double_2_suite

//-----------------------------------------------------------------------------

namespace average_double_4_suite
{

void test_ctor()
{
    window::moment<double, 4> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.capacity(), 4);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), true);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
}

void test_same()
{
    window::moment<double, 4> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 3);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), true);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 4);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
}

void test_linear_increase()
{
    window::moment<double, 4> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    filter.push(2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.5);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 2.0);
    filter.push(4.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 2.5);
    filter.push(5.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 3.5);
    filter.push(6.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 4.5);
}

void test_linear_increase_from_offset()
{
    window::moment<double, 4> filter;
    filter.push(10.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 10.0);
    filter.push(11.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 10.5);
    filter.push(12.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 11.0);
    filter.push(13.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 11.5);
    filter.push(14.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 12.5);
    filter.push(15.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 13.5);
}

void test_linear_decrease()
{
    window::moment<double, 4> filter;
    filter.push(10.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 10.0);
    filter.push(9.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 9.5);
    filter.push(8.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 9.0);
    filter.push(7.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 8.5);
    filter.push(6.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 7.5);
    filter.push(5.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 6.5);
}

void run()
{
    test_ctor();
    test_same();
    test_linear_increase();
    test_linear_increase_from_offset();
    test_linear_decrease();
}

} // namespace average_double_4_suite

//-----------------------------------------------------------------------------

namespace average_float_2_suite
{

void test_ctor()
{
    window::moment<float, 2> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.capacity(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), true);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0f);
}

void test_one()
{
    window::moment<float, 2> filter;
    filter.push(1.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0f);
}

void test_same()
{
    window::moment<float, 2> filter;
    filter.push(1.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    filter.push(1.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0f);
    filter.push(1.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), true);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0f);
}

void test_two()
{
    window::moment<float, 2> filter;
    filter.push(1.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0f);
    filter.push(3.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 2.0f);
}

void test_three()
{
    window::moment<float, 2> filter;
    filter.push(1.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0f);
    filter.push(3.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 2.0f);
    filter.push(0.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.5f);
}

void test_clear()
{
    window::moment<float, 2> filter;
    filter.push(1.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    filter.clear();
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    filter.push(2.0f);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 2.0f);
}

void run()
{
    test_ctor();
    test_same();
    test_one();
    test_two();
    test_three();
    test_clear();
}

} // namespace average_float_2_suite

//-----------------------------------------------------------------------------

namespace average_int_2_suite
{

void test_ctor()
{
    window::moment<int, 2> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.capacity(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), true);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0);
}

void test_one()
{
    window::moment<int, 2> filter;
    filter.push(1);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1);
}

void test_same()
{
    window::moment<int, 2> filter;
    filter.push(1);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1);
    filter.push(1);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1);
    filter.push(1);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), true);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1);
}

void test_two()
{
    window::moment<int, 2> filter;
    filter.push(1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1);
    filter.push(3);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 2);
}

void test_three()
{
    window::moment<int, 2> filter;
    filter.push(1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1);
    filter.push(3);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 2);
    filter.push(0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1); // Rounded down
}

void test_clear()
{
    window::moment<int, 2> filter;
    filter.push(1);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    filter.clear();
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    filter.push(2);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 2);
}

void run()
{
    test_ctor();
    test_same();
    test_one();
    test_two();
    test_three();
    test_clear();
}

} // namespace average_int_2_suite

//-----------------------------------------------------------------------------

namespace variance_double_1_suite
{

void test_ctor()
{
    window::moment_variance<double, 1> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.capacity(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), true);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
}

void test_many()
{
    window::moment_variance<double, 1> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.capacity(), 1);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), true);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
    filter.push(2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), true);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), true);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 3.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
}

void run()
{
    test_ctor();
    test_many();
}

} // namespace variance_double_1_suite

//-----------------------------------------------------------------------------

namespace variance_double_2_suite
{

void test_ctor()
{
    window::moment_variance<double, 2> filter;
    TRIAL_ONLINE_TEST_EQUAL(filter.capacity(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), true);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
}

void test_one()
{
    window::moment_variance<double, 2> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
}

void test_same()
{
    window::moment_variance<double, 2> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.empty(), false);
    TRIAL_ONLINE_TEST_EQUAL(filter.full(), true);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 2);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
}

void test_two()
{
    window::moment_variance<double, 2> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 2.0);
}

void test_three()
{
    window::moment_variance<double, 2> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 0.0);
    filter.push(3.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 2.0);
    filter.push(0.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 1.5);
    TRIAL_ONLINE_TEST_EQUAL(filter.variance(), 2.25);
    TRIAL_ONLINE_TEST_EQUAL(filter.unbiased_variance(), 4.5);
}

void test_clear()
{
    window::moment_variance<double, 2> filter;
    filter.push(1.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
    filter.clear();
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 0);
    filter.push(2.0);
    TRIAL_ONLINE_TEST_EQUAL(filter.size(), 1);
}

void run()
{
    test_ctor();
    test_same();
    test_one();
    test_two();
    test_three();
    test_clear();
}

} // namespace variance_double_2_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    average_double_1_suite::run();
    average_double_2_suite::run();
    average_double_4_suite::run();
    average_float_2_suite::run();
    average_int_2_suite::run();

    variance_double_1_suite::run();
    variance_double_2_suite::run();

    return boost::report_errors();
}
