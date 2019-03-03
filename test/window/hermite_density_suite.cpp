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
#include <trial/online/window/hermite_density.hpp>

using namespace trial::online;

//-----------------------------------------------------------------------------

namespace density_suite
{

void test_ctor()
{
    window::hermite_density<double, 4, 6> filter;
}

void test_same()
{
    const auto tolerance = detail::close_to<double>(1e-5, 1e-5);
    window::hermite_density<double, 4, 6> filter;

    filter.push(0.0);
    TRIAL_ONLINE_TEST_WITH(filter.lower(), 0.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.upper(), 0.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.at(0.0), 1.23416, tolerance);

    filter.push(0.0);
    TRIAL_ONLINE_TEST_WITH(filter.lower(), 0.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.upper(), 0.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.at(0.0), 1.23416, tolerance);

    filter.push(0.0);
    TRIAL_ONLINE_TEST_WITH(filter.lower(), 0.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.upper(), 0.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.at(0.0), 1.23416, tolerance);

    filter.push(0.0);
    TRIAL_ONLINE_TEST_WITH(filter.lower(), 0.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.upper(), 0.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.at(0.0), 1.23416, tolerance);

    // Window full
    filter.push(0.0);
    TRIAL_ONLINE_TEST_WITH(filter.lower(), 0.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.upper(), 0.0, tolerance);
    TRIAL_ONLINE_TEST_WITH(filter.at(0.0), 1.23416, tolerance);
}

void run()
{
    test_ctor();
    test_same();
}

} // namespace density_suite

//-----------------------------------------------------------------------------

int main()
{
    density_suite::run();

    return boost::report_errors();
}
