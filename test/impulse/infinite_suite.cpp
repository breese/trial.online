///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <trial/online/detail/lightweight_test.hpp>
#include <trial/online/impulse/infinite.hpp>

//-----------------------------------------------------------------------------

namespace api_suite
{

void test_empty()
{
    trial::online::impulse::infinite<double> filter({1.0}, {1.0});
    TRIAL_ONLINE_TEST(filter.empty());
    filter.push(1);
    TRIAL_ONLINE_TEST(!filter.empty());
}

void test_value()
{
    trial::online::impulse::infinite<double> filter({1.0}, {1.0});
    TRIAL_ONLINE_TEST(filter.empty());
    TRIAL_ONLINE_TEST_EQUAL(filter.value(), 0.0);
}

void test()
{
    test_empty();
    test_value();
}

} // namespace api_suite

//-----------------------------------------------------------------------------

namespace double_1_1_suite
{

void test_input_one_output_one()
{
    const double tolerance = 1e-5;
    std::vector<double> history;
    trial::online::impulse::infinite<double> filter({1.0}, {1.0});
    filter.push(1);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1 * 1.0, tolerance);
    filter.push(2);
    history.push_back(filter.value());   
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2 * 1.0 - history[0] * 1.0, tolerance);
    filter.push(3);
    history.push_back(filter.value());   
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 3 * 1.0 - history[1] * 1.0, tolerance);
}

void test_input_one_output_one_scale_half()
{
    const double tolerance = 1e-5;
    const double scale = 2.0;
    std::vector<double> history;
    trial::online::impulse::infinite<double> filter({1.0}, {1.0}, scale);
    filter.push(1);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), (1 * 1.0) / scale, tolerance);
    filter.push(2);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), (2 * 1.0 - history[0]) / scale, tolerance);
    filter.push(3);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), (3 * 1.0 - history[1]) / scale, tolerance);
}

void test_input_half_output_half()
{
    const double tolerance = 1e-5;
    std::vector<double> history;
    trial::online::impulse::infinite<double> filter({0.5}, {0.5});
    filter.push(1);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1 * 0.5, tolerance);
    filter.push(2);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2 * 0.5 - history[0] * 0.5, tolerance);
    filter.push(3);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 3 * 0.5 - history[1] * 0.5, tolerance);
}

void test_input_half_output_quarter()
{
    const double tolerance = 1e-5;
    std::vector<double> history;
    trial::online::impulse::infinite<double> filter({0.5}, {0.25});
    filter.push(1);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1 * 0.5, tolerance);
    filter.push(2);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2 * 0.5 - history[0] * 0.25, tolerance);
    filter.push(3);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 3 * 0.5 - history[1] * 0.25, tolerance);
}

void test()
{
    test_input_one_output_one();
    test_input_one_output_one_scale_half();
    test_input_half_output_half();
    test_input_half_output_quarter();
}

} // namespace double_1_1_suite

//-----------------------------------------------------------------------------

namespace double_1_2_suite
{

void test_input_half_output_half_half()
{
    const double tolerance = 1e-5;
    std::vector<double> history;
    trial::online::impulse::infinite<double> filter({0.5}, {0.5, 0.5});
    filter.push(1);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1 * 0.5, tolerance);
    filter.push(2);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2 * 0.5 - history[0] * 0.5, tolerance);
    filter.push(3);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 3 * 0.5 - history[1] * 0.5 - history[0] * 0.5, tolerance);
    filter.push(4);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 4 * 0.5 - history[2] * 0.5 - history[1] * 0.5, tolerance);
}

void test_input_half_output_half_quarter()
{
    const double tolerance = 1e-5;
    std::vector<double> history;
    trial::online::impulse::infinite<double> filter({0.5}, {0.5, 0.25});
    filter.push(1);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1 * 0.5, tolerance);
    filter.push(2);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2 * 0.5 - history[0] * 0.5, tolerance);
    filter.push(3);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 3 * 0.5 - history[1] * 0.5 - history[0] * 0.25, tolerance);
    filter.push(4);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 4 * 0.5 - history[2] * 0.5 - history[1] * 0.25, tolerance);
}

void test()
{
    test_input_half_output_half_half();
    test_input_half_output_half_quarter();
}

} // namespace double_1_2_suite

//-----------------------------------------------------------------------------

namespace double_2_1_suite
{

void test_input_half_half_output_half()
{
    const double tolerance = 1e-5;
    std::vector<double> history;
    trial::online::impulse::infinite<double> filter({0.5, 0.5}, {0.5});
    filter.push(1);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1 * 0.5, tolerance);
    filter.push(2);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2 * 0.5 + 1 * 0.5 - history[0] * 0.5, tolerance);
    filter.push(3);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 3 * 0.5 + 2 * 0.5 - history[1] * 0.5, tolerance);
    filter.push(4);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 4 * 0.5 + 3 * 0.5 - history[2] * 0.5, tolerance);
}

void test_input_half_quarter_output_half()
{
    const double tolerance = 1e-5;
    std::vector<double> history;
    trial::online::impulse::infinite<double> filter({0.5, 0.25}, {0.5});
    filter.push(1);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 1 * 0.5, tolerance);
    filter.push(2);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 2 * 0.5 + 1 * 0.25 - history[0] * 0.5, tolerance);
    filter.push(3);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 3 * 0.5 + 2 * 0.25 - history[1] * 0.5, tolerance);
    filter.push(4);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 4 * 0.5 + 3 * 0.25 - history[2] * 0.5, tolerance);
}

void test()
{
    test_input_half_half_output_half();
    test_input_half_quarter_output_half();
}

} // namespace double_2_1_suite

//-----------------------------------------------------------------------------

namespace double_3_3_suite
{

void test_first()
{
    const double tolerance = 1e-5;
    std::vector<double> history;
    double input[] = {1.0, 0.2, 0.3};
    double output[] = {0.1, 0.5, 0.25};
    trial::online::impulse::infinite<double> filter(input, output);
    filter.push(10);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 10 * input[0], tolerance);
    filter.push(5);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 5 * input[0] + 10 * input[1] - output[0] * history[0], tolerance);
    filter.push(20);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), 20 * input[0] + 5 * input[1] + 10 * input[2] - output[0] * history[1] - output[1] * history[0], tolerance);
    filter.push(-10);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), -10 * input[0] + 20 * input[1] + 5 * input[2] - output[0] * history[2] - output[1] * history[1] - output[2] * history[0], tolerance);
    filter.push(-5);
    history.push_back(filter.value());
    TRIAL_ONLINE_TEST_CLOSE(filter.value(), -5 * input[0] - 10 * input[1] + 20 * input[2] - output[0] * history[3] - output[1] * history[2] - output[2] * history[1], tolerance);
}

void test()
{
    test_first();
}

} // namespace double_3_3_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    api_suite::test();
    double_1_1_suite::test();
    double_1_2_suite::test();
    double_2_1_suite::test();
    double_3_3_suite::test();

    return boost::report_errors();
}
