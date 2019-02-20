#include <trial/online/detail/lightweight_test.hpp>
#include <trial/online/detail/functional.hpp>
#include <trial/online/interim/psquare_quantile.hpp>

using namespace trial::online;

//-----------------------------------------------------------------------------

namespace api_suite
{

void test_ctor()
{
    interim::psquare_median<double, 8> filter;
    filter.push(1);
    TRIAL_ONLINE_TEST(!filter.empty());

    // Copy constructor
    interim::psquare_median<double, 8> copy(filter);
    TRIAL_ONLINE_TEST(!copy.empty());

    // Copy assignment
    interim::psquare_median<double, 8> assign;
    assign = filter;
    TRIAL_ONLINE_TEST(!assign.empty());

    // Move constructor
    interim::psquare_median<double, 8> mover(std::move(copy));
    TRIAL_ONLINE_TEST(!mover.empty());

    // Move assignment
    interim::psquare_median<double, 8> massign;
    massign = std::move(assign);
    TRIAL_ONLINE_TEST(!massign.empty());
}

void test_empty()
{
    interim::psquare_median<double, 8> filter;
    TRIAL_ONLINE_TEST(filter.empty());
    filter.push(1.0);
    TRIAL_ONLINE_TEST(!filter.empty());
}

void test_clear()
{
    interim::psquare_median<double, 8> filter;
    filter.push(1.0);
    filter.push(2.0);
    filter.push(3.0);
    filter.push(4.0);
    filter.push(5.0);
    TRIAL_ONLINE_TEST(!filter.empty());
    filter.clear();
    TRIAL_ONLINE_TEST(filter.empty());
}

void run()
{
    test_ctor();
    test_empty();
    test_clear();
}

} // namespace api_suite

//-----------------------------------------------------------------------------

namespace double_quartile_suite
{

void test_linear_increase()
{
    const double tolerance = 1e-4;
    interim::basic_psquare_quantile<double, 8, std::ratio<1,2>> filter;

    filter.push(1);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<0>(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<1>(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<2>(), 1.0, tolerance);

    filter.push(2);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<0>(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<1>(), 1.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<2>(), 2.0, tolerance);

    filter.push(3);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<0>(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<1>(), 2.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<2>(), 3.0, tolerance);

    filter.push(4);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<0>(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<1>(), 2.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<2>(), 4.0, tolerance);

    filter.push(5);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<0>(), 2.6, tolerance); // 2.0
    TRIAL_ONLINE_TEST_CLOSE(filter.get<1>(), 3.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<2>(), 4.4, tolerance); // 5.0

    filter.push(6);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<0>(), 3.66667, tolerance); // 3.0
    TRIAL_ONLINE_TEST_CLOSE(filter.get<1>(), 4.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<2>(), 5.33333, tolerance); // 6.0

    filter.push(7);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<0>(), 4.42857, tolerance); // 4.0
    TRIAL_ONLINE_TEST_CLOSE(filter.get<1>(), 5.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<2>(), 6.57143, tolerance); // 7.0

    filter.push(8);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<0>(), 5.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<1>(), 6.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<2>(), 8.0, tolerance);

    filter.push(9);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<0>(), 6.6, tolerance); // 6.0
    TRIAL_ONLINE_TEST_CLOSE(filter.get<1>(), 7.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<2>(), 8.4, tolerance); // 9.0

    filter.push(10);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<0>(), 7.66667, tolerance); // 7.0
    TRIAL_ONLINE_TEST_CLOSE(filter.get<1>(), 8.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<2>(), 9.33333, tolerance); // 10.0

    filter.push(11);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<0>(), 8.42857, tolerance); // 8.0
    TRIAL_ONLINE_TEST_CLOSE(filter.get<1>(), 9.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<2>(), 10.5714, tolerance); // 11.0

    filter.push(12);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<0>(), 9.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<1>(), 10.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<2>(), 12.0, tolerance);
}

void test_linear_increase_with_approximation()
{
    const double tolerance = 1e-4;
    interim::basic_psquare_quantile<double, 12, std::ratio<1,2>> filter;

    filter.push(1);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<0>(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<1>(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<2>(), 1.0, tolerance);

    filter.push(2);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<0>(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<1>(), 1.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<2>(), 2.0, tolerance);

    filter.push(3);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<0>(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<1>(), 2.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<2>(), 3.0, tolerance);

    filter.push(4);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<0>(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<1>(), 2.5, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<2>(), 4.0, tolerance);

    filter.push(5);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<0>(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<1>(), 3.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<2>(), 5.0, tolerance);

    // Switch to P^2 approximation

    filter.push(6);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<0>(), 1.0, tolerance);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<1>(), 3.0, tolerance); // 3.5
    TRIAL_ONLINE_TEST_CLOSE(filter.get<2>(), 6.0, tolerance);

    // Switch to interpolation

    filter.push(7);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<0>(), 2.71429, tolerance); // 2.0
    TRIAL_ONLINE_TEST_CLOSE(filter.get<1>(), 4.14286, tolerance); // 4.5
    TRIAL_ONLINE_TEST_CLOSE(filter.get<2>(), 6.28571, tolerance); // 7.0

    filter.push(8);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<0>(), 4.0, tolerance); // 3.0
    TRIAL_ONLINE_TEST_CLOSE(filter.get<1>(), 5.25, tolerance); // 5.5
    TRIAL_ONLINE_TEST_CLOSE(filter.get<2>(), 7.0, tolerance); // 8.0

    filter.push(9);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<0>(), 5.0, tolerance); // 4.0
    TRIAL_ONLINE_TEST_CLOSE(filter.get<1>(), 6.33333, tolerance); // 6.5
    TRIAL_ONLINE_TEST_CLOSE(filter.get<2>(), 8.0, tolerance); // 9.0

    filter.push(10);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<0>(), 5.8, tolerance); // 5.0
    TRIAL_ONLINE_TEST_CLOSE(filter.get<1>(), 7.4, tolerance); // 7.5
    TRIAL_ONLINE_TEST_CLOSE(filter.get<2>(), 9.2, tolerance); // 10.0

    filter.push(11);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<0>(), 6.45455, tolerance); // 6.0
    TRIAL_ONLINE_TEST_CLOSE(filter.get<1>(), 8.45455, tolerance); // 8.5
    TRIAL_ONLINE_TEST_CLOSE(filter.get<2>(), 10.5455, tolerance); // 11.0

    filter.push(12);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<0>(), 7.0, tolerance); // 7.0
    TRIAL_ONLINE_TEST_CLOSE(filter.get<1>(), 9.0, tolerance); // 9.5
    TRIAL_ONLINE_TEST_CLOSE(filter.get<2>(), 12.0, tolerance); // 12.0

    filter.push(13);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<0>(), 8.71429, tolerance); // 8.0
    TRIAL_ONLINE_TEST_CLOSE(filter.get<1>(), 10.1429, tolerance); // 10.5
    TRIAL_ONLINE_TEST_CLOSE(filter.get<2>(), 12.2857, tolerance); // 13.0

    filter.push(14);
    TRIAL_ONLINE_TEST_CLOSE(filter.get<0>(), 10.0, tolerance); // 9.0
    TRIAL_ONLINE_TEST_CLOSE(filter.get<1>(), 11.25, tolerance); // 11.5
    TRIAL_ONLINE_TEST_CLOSE(filter.get<2>(), 13.0, tolerance); // 14.0
}

void run()
{
    test_linear_increase();
    test_linear_increase_with_approximation();
}

} // namespace double_quartile_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    api_suite::run();
    double_quartile_suite::run();

    return boost::report_errors();
}
