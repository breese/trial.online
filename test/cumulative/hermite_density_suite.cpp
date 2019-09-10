///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/online/detail/lightweight_test.hpp>
#include <trial/online/detail/functional.hpp>
#include <trial/online/cumulative/hermite_density.hpp>

using namespace trial::online;

//-----------------------------------------------------------------------------

namespace api_suite
{

void test_ctor()
{
    cumulative::hermite_density<double> filter;
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.lower(), 1.0);

    // Copy constructor
    cumulative::hermite_density<double> copy(filter);
    TRIAL_TEST_EQ(copy.lower(), 1.0);

    // Copy assignment
    cumulative::hermite_density<double> assign;
    assign = filter;
    TRIAL_TEST_EQ(assign.lower(), 1.0);

    // Move constructor
    cumulative::hermite_density<double> mover(std::move(copy));
    TRIAL_TEST_EQ(assign.lower(), 1.0);

    // Move assignment
    cumulative::hermite_density<double> massign;
    massign = std::move(assign);
    TRIAL_TEST_EQ(massign.lower(), 1.0);
}

void run()
{
    test_ctor();
}

} // namespace api_suite

//-----------------------------------------------------------------------------

namespace cumulated_api_suite
{

void test_ctor()
{
    cumulative::hermite_cumulated_density<double> filter;
    filter.push(1.0);
    TRIAL_TEST_EQ(filter.lower(), 1.0);

    // Copy constructor
    cumulative::hermite_cumulated_density<double> copy(filter);
    TRIAL_TEST_EQ(copy.lower(), 1.0);

    // Copy assignment
    cumulative::hermite_cumulated_density<double> assign;
    assign = filter;
    TRIAL_TEST_EQ(assign.lower(), 1.0);

    // Move constructor
    cumulative::hermite_cumulated_density<double> mover(std::move(copy));
    TRIAL_TEST_EQ(assign.lower(), 1.0);

    // Move assignment
    cumulative::hermite_cumulated_density<double> massign;
    massign = std::move(assign);
    TRIAL_TEST_EQ(massign.lower(), 1.0);
}

void run()
{
    test_ctor();
}

} // namespace cumulated_api_suite

//-----------------------------------------------------------------------------

namespace density_suite
{

void test_same()
{
    const auto tolerance = detail::close_to<double>(1e-5, 1e-5);
    cumulative::hermite_density<double, 6> filter;

    filter.push(0.0);
    TRIAL_TEST_WITH(filter.lower(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.upper(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0.0), 1.23416, tolerance);

    filter.push(0.0);
    TRIAL_TEST_WITH(filter.lower(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.upper(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0.0), 1.23416, tolerance);

    filter.push(0.0);
    TRIAL_TEST_WITH(filter.lower(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.upper(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0.0), 1.23416, tolerance);
}

void test_normal()
{
    const auto tolerance = detail::close_to<double>(1e-5, 1e-5);
    cumulative::hermite_density<double, 6> filter;

    filter.push(0.439589003175523);
    TRIAL_TEST_WITH(filter.lower(), 0.439589003175523, tolerance);
    TRIAL_TEST_WITH(filter.upper(), 0.439589003175523, tolerance);
    TRIAL_TEST_WITH(filter.at(0.0), 0.720309, tolerance);

    filter.push(-0.78519559181148);
    TRIAL_TEST_WITH(filter.lower(), -0.78519559181148, tolerance);
    TRIAL_TEST_WITH(filter.upper(), 0.439589003175523, tolerance);
    TRIAL_TEST_WITH(filter.at(0.0), 0.384261, tolerance);

    filter.push(0.456384224654062);
    TRIAL_TEST_WITH(filter.lower(), -0.78519559181148, tolerance);
    TRIAL_TEST_WITH(filter.upper(), 0.456384224654062, tolerance);
    TRIAL_TEST_WITH(filter.at(0.0), 0.485061, tolerance);

    filter.push(-0.687724133387156);
    TRIAL_TEST_WITH(filter.lower(), -0.78519559181148, tolerance);
    TRIAL_TEST_WITH(filter.upper(), 0.456384224654062, tolerance);
    TRIAL_TEST_WITH(filter.at(0.0), 0.418589, tolerance);

    filter.push(0.551498121887421);
    TRIAL_TEST_WITH(filter.lower(), -0.78519559181148, tolerance);
    TRIAL_TEST_WITH(filter.upper(), 0.551498121887421, tolerance);
    TRIAL_TEST_WITH(filter.at(0.0), 0.433151, tolerance);

    filter.push(-1.60671552054184);
    TRIAL_TEST_WITH(filter.lower(), -1.60671552054184, tolerance);
    TRIAL_TEST_WITH(filter.upper(), 0.551498121887421, tolerance);
    TRIAL_TEST_WITH(filter.at(0.0), 0.352902, tolerance);

    filter.push(0.885630762890633);
    TRIAL_TEST_WITH(filter.lower(), -1.60671552054184, tolerance);
    TRIAL_TEST_WITH(filter.upper(), 0.885630762890633, tolerance);
    TRIAL_TEST_WITH(filter.at(0.0), 0.288993, tolerance);

    filter.push(0.2679419655957);
    TRIAL_TEST_WITH(filter.lower(), -1.60671552054184, tolerance);
    TRIAL_TEST_WITH(filter.upper(), 0.885630762890633, tolerance);
    TRIAL_TEST_WITH(filter.at(0.0), 0.380939, tolerance);

    filter.push(-0.171664002714432);
    TRIAL_TEST_WITH(filter.lower(), -1.60671552054184, tolerance);
    TRIAL_TEST_WITH(filter.upper(), 0.885630762890633, tolerance);
    TRIAL_TEST_WITH(filter.at(0.0), 0.465866, tolerance);

    filter.push(1.13113614229517);
    TRIAL_TEST_WITH(filter.lower(), -1.60671552054184, tolerance);
    TRIAL_TEST_WITH(filter.upper(), 1.13113614229517, tolerance);
    TRIAL_TEST_WITH(filter.at(0.0), 0.392664, tolerance);
}

void run()
{
    test_same();
    test_normal();
}

} // namespace density_suite

//-----------------------------------------------------------------------------

namespace cumulated_density_suite
{

void test_same()
{
    const auto tolerance = detail::close_to<double>(1e-5, 1e-5);
    cumulative::hermite_cumulated_density<double, 6> filter;

    filter.push(0.0);
    TRIAL_TEST_WITH(filter.lower(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.upper(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.until(0.0), 0.602252, tolerance);

    filter.push(0.0);
    TRIAL_TEST_WITH(filter.lower(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.upper(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.until(0.0), 0.602252, tolerance);

    filter.push(0.0);
    TRIAL_TEST_WITH(filter.lower(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.upper(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.until(0.0), 0.602252, tolerance);
}

void test_normal()
{
    const auto tolerance = detail::close_to<double>(1e-5, 1e-5);
    cumulative::hermite_cumulated_density<double, 6> filter;

    filter.push(0.439589003175523);
    TRIAL_TEST_WITH(filter.lower(), 0.439589003175523, tolerance);
    TRIAL_TEST_WITH(filter.upper(), 0.439589003175523, tolerance);
    TRIAL_TEST_WITH(filter.until(0.0), -0.0651075, tolerance); // Runge's phenomenon
    TRIAL_TEST_WITH(filter.until(0.5), 0.440364, tolerance);
    TRIAL_TEST_WITH(filter.until(1.0), 0.886722, tolerance);

    filter.push(-0.78519559181148);
    TRIAL_TEST_WITH(filter.lower(), -0.78519559181148, tolerance);
    TRIAL_TEST_WITH(filter.upper(), 0.439589003175523, tolerance);
    TRIAL_TEST_WITH(filter.until(0.0), 0.474208, tolerance);
    TRIAL_TEST_WITH(filter.until(0.5), 0.682912, tolerance);
    TRIAL_TEST_WITH(filter.until(1.0), 0.888194, tolerance);

    filter.push(0.456384224654062);
    TRIAL_TEST_WITH(filter.lower(), -0.78519559181148, tolerance);
    TRIAL_TEST_WITH(filter.upper(), 0.456384224654062, tolerance);
    TRIAL_TEST_WITH(filter.until(0.0), 0.288362, tolerance);
    TRIAL_TEST_WITH(filter.until(0.5), 0.593122, tolerance);
    TRIAL_TEST_WITH(filter.until(1.0), 0.882767, tolerance);

    filter.push(-0.687724133387156);
    TRIAL_TEST_WITH(filter.lower(), -0.78519559181148, tolerance);
    TRIAL_TEST_WITH(filter.upper(), 0.456384224654062, tolerance);
    TRIAL_TEST_WITH(filter.until(0.0), 0.476185, tolerance);
    TRIAL_TEST_WITH(filter.until(0.5), 0.694598, tolerance);
    TRIAL_TEST_WITH(filter.until(1.0), 0.895763, tolerance);

    filter.push(0.551498121887421);
    TRIAL_TEST_WITH(filter.lower(), -0.78519559181148, tolerance);
    TRIAL_TEST_WITH(filter.upper(), 0.551498121887421, tolerance);
    TRIAL_TEST_WITH(filter.until(0.0), 0.347478, tolerance);
    TRIAL_TEST_WITH(filter.until(0.5), 0.610028, tolerance);
    TRIAL_TEST_WITH(filter.until(1.0), 0.874285, tolerance);

    filter.push(-1.60671552054184);
    TRIAL_TEST_WITH(filter.lower(), -1.60671552054184, tolerance);
    TRIAL_TEST_WITH(filter.upper(), 0.551498121887421, tolerance);
    TRIAL_TEST_WITH(filter.until(0.0), 0.45673, tolerance);
    TRIAL_TEST_WITH(filter.until(0.5), 0.681563, tolerance);
    TRIAL_TEST_WITH(filter.until(1.0), 0.906213, tolerance);

    filter.push(0.885630762890633);
    TRIAL_TEST_WITH(filter.lower(), -1.60671552054184, tolerance);
    TRIAL_TEST_WITH(filter.upper(), 0.885630762890633, tolerance);
    TRIAL_TEST_WITH(filter.until(0.0), 0.364932, tolerance);
    TRIAL_TEST_WITH(filter.until(0.5), 0.582583, tolerance);
    TRIAL_TEST_WITH(filter.until(1.0), 0.853997, tolerance);

    filter.push(0.2679419655957);
    TRIAL_TEST_WITH(filter.lower(), -1.60671552054184, tolerance);
    TRIAL_TEST_WITH(filter.upper(), 0.885630762890633, tolerance);
    TRIAL_TEST_WITH(filter.until(0.0), 0.340262, tolerance);
    TRIAL_TEST_WITH(filter.until(0.5), 0.600618, tolerance);
    TRIAL_TEST_WITH(filter.until(1.0), 0.876021, tolerance);

    filter.push(-0.171664002714432);
    TRIAL_TEST_WITH(filter.lower(), -1.60671552054184, tolerance);
    TRIAL_TEST_WITH(filter.upper(), 0.885630762890633, tolerance);
    TRIAL_TEST_WITH(filter.until(0.0), 0.395576, tolerance);
    TRIAL_TEST_WITH(filter.until(0.5), 0.669832, tolerance);
    TRIAL_TEST_WITH(filter.until(1.0), 0.910088, tolerance);

    filter.push(1.13113614229517);
    TRIAL_TEST_WITH(filter.lower(), -1.60671552054184, tolerance);
    TRIAL_TEST_WITH(filter.upper(), 1.13113614229517, tolerance);
    TRIAL_TEST_WITH(filter.until(0.0), 0.355698, tolerance);
    TRIAL_TEST_WITH(filter.until(0.5), 0.603301, tolerance);
    TRIAL_TEST_WITH(filter.until(1.0), 0.860696, tolerance);
}

void run()
{
    test_same();
    test_normal();
}

} // namespace cumulated_density_suite

//-----------------------------------------------------------------------------

int main()
{
    api_suite::run();
    cumulated_api_suite::run();
    density_suite::run();
    cumulated_density_suite::run();

    return boost::report_errors();
}
