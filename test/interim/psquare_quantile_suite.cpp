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
    TRIAL_TEST(!filter.empty());

    // Copy constructor
    interim::psquare_median<double, 8> copy(filter);
    TRIAL_TEST(!copy.empty());

    // Copy assignment
    interim::psquare_median<double, 8> assign;
    assign = filter;
    TRIAL_TEST(!assign.empty());

    // Move constructor
    interim::psquare_median<double, 8> mover(std::move(copy));
    TRIAL_TEST(!mover.empty());

    // Move assignment
    interim::psquare_median<double, 8> massign;
    massign = std::move(assign);
    TRIAL_TEST(!massign.empty());
}

void test_empty()
{
    interim::psquare_median<double, 8> filter;
    TRIAL_TEST(filter.empty());
    filter.push(1.0);
    TRIAL_TEST(!filter.empty());
}

void test_clear()
{
    interim::psquare_median<double, 8> filter;
    filter.push(1.0);
    filter.push(2.0);
    filter.push(3.0);
    filter.push(4.0);
    filter.push(5.0);
    TRIAL_TEST(!filter.empty());
    filter.clear();
    TRIAL_TEST(filter.empty());
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
    const auto tolerance = detail::close_to<double>(1e-4);
    interim::basic_psquare_quantile<double, 8, std::ratio<1,2>> filter;

    filter.push(1);
    TRIAL_TEST_WITH(filter.get<0>(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.get<1>(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), 1.0, tolerance);

    filter.push(2);
    TRIAL_TEST_WITH(filter.get<0>(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.get<1>(), 1.5, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), 2.0, tolerance);

    filter.push(3);
    TRIAL_TEST_WITH(filter.get<0>(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.get<1>(), 2.0, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), 3.0, tolerance);

    filter.push(4);
    TRIAL_TEST_WITH(filter.get<0>(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.get<1>(), 2.5, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), 4.0, tolerance);

    filter.push(5);
    TRIAL_TEST_WITH(filter.get<0>(), 2.6, tolerance); // 2.0
    TRIAL_TEST_WITH(filter.get<1>(), 3.5, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), 4.4, tolerance); // 5.0

    filter.push(6);
    TRIAL_TEST_WITH(filter.get<0>(), 3.66667, tolerance); // 3.0
    TRIAL_TEST_WITH(filter.get<1>(), 4.5, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), 5.33333, tolerance); // 6.0

    filter.push(7);
    TRIAL_TEST_WITH(filter.get<0>(), 4.42857, tolerance); // 4.0
    TRIAL_TEST_WITH(filter.get<1>(), 5.5, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), 6.57143, tolerance); // 7.0

    filter.push(8);
    TRIAL_TEST_WITH(filter.get<0>(), 5.0, tolerance);
    TRIAL_TEST_WITH(filter.get<1>(), 6.5, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), 8.0, tolerance);

    filter.push(9);
    TRIAL_TEST_WITH(filter.get<0>(), 6.6, tolerance); // 6.0
    TRIAL_TEST_WITH(filter.get<1>(), 7.5, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), 8.4, tolerance); // 9.0

    filter.push(10);
    TRIAL_TEST_WITH(filter.get<0>(), 7.66667, tolerance); // 7.0
    TRIAL_TEST_WITH(filter.get<1>(), 8.5, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), 9.33333, tolerance); // 10.0

    filter.push(11);
    TRIAL_TEST_WITH(filter.get<0>(), 8.42857, tolerance); // 8.0
    TRIAL_TEST_WITH(filter.get<1>(), 9.5, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), 10.5714, tolerance); // 11.0

    filter.push(12);
    TRIAL_TEST_WITH(filter.get<0>(), 9.0, tolerance);
    TRIAL_TEST_WITH(filter.get<1>(), 10.5, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), 12.0, tolerance);
}

void test_linear_increase_with_approximation()
{
    const auto tolerance = detail::close_to<double>(1e-4);
    interim::basic_psquare_quantile<double, 12, std::ratio<1,2>> filter;

    filter.push(1);
    TRIAL_TEST_WITH(filter.get<0>(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.get<1>(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), 1.0, tolerance);

    filter.push(2);
    TRIAL_TEST_WITH(filter.get<0>(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.get<1>(), 1.5, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), 2.0, tolerance);

    filter.push(3);
    TRIAL_TEST_WITH(filter.get<0>(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.get<1>(), 2.0, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), 3.0, tolerance);

    filter.push(4);
    TRIAL_TEST_WITH(filter.get<0>(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.get<1>(), 2.5, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), 4.0, tolerance);

    filter.push(5);
    TRIAL_TEST_WITH(filter.get<0>(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.get<1>(), 3.0, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), 5.0, tolerance);

    // Switch to P^2 approximation

    filter.push(6);
    TRIAL_TEST_WITH(filter.get<0>(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.get<1>(), 3.0, tolerance); // 3.5
    TRIAL_TEST_WITH(filter.get<2>(), 6.0, tolerance);

    // Switch to interpolation

    filter.push(7);
    TRIAL_TEST_WITH(filter.get<0>(), 2.71429, tolerance); // 2.0
    TRIAL_TEST_WITH(filter.get<1>(), 4.14286, tolerance); // 4.5
    TRIAL_TEST_WITH(filter.get<2>(), 6.28571, tolerance); // 7.0

    filter.push(8);
    TRIAL_TEST_WITH(filter.get<0>(), 4.0, tolerance); // 3.0
    TRIAL_TEST_WITH(filter.get<1>(), 5.25, tolerance); // 5.5
    TRIAL_TEST_WITH(filter.get<2>(), 7.0, tolerance); // 8.0

    filter.push(9);
    TRIAL_TEST_WITH(filter.get<0>(), 5.0, tolerance); // 4.0
    TRIAL_TEST_WITH(filter.get<1>(), 6.33333, tolerance); // 6.5
    TRIAL_TEST_WITH(filter.get<2>(), 8.0, tolerance); // 9.0

    filter.push(10);
    TRIAL_TEST_WITH(filter.get<0>(), 5.8, tolerance); // 5.0
    TRIAL_TEST_WITH(filter.get<1>(), 7.4, tolerance); // 7.5
    TRIAL_TEST_WITH(filter.get<2>(), 9.2, tolerance); // 10.0

    filter.push(11);
    TRIAL_TEST_WITH(filter.get<0>(), 6.45455, tolerance); // 6.0
    TRIAL_TEST_WITH(filter.get<1>(), 8.45455, tolerance); // 8.5
    TRIAL_TEST_WITH(filter.get<2>(), 10.5455, tolerance); // 11.0

    filter.push(12);
    TRIAL_TEST_WITH(filter.get<0>(), 7.0, tolerance); // 7.0
    TRIAL_TEST_WITH(filter.get<1>(), 9.0, tolerance); // 9.5
    TRIAL_TEST_WITH(filter.get<2>(), 12.0, tolerance); // 12.0

    filter.push(13);
    TRIAL_TEST_WITH(filter.get<0>(), 8.71429, tolerance); // 8.0
    TRIAL_TEST_WITH(filter.get<1>(), 10.1429, tolerance); // 10.5
    TRIAL_TEST_WITH(filter.get<2>(), 12.2857, tolerance); // 13.0

    filter.push(14);
    TRIAL_TEST_WITH(filter.get<0>(), 10.0, tolerance); // 9.0
    TRIAL_TEST_WITH(filter.get<1>(), 11.25, tolerance); // 11.5
    TRIAL_TEST_WITH(filter.get<2>(), 13.0, tolerance); // 14.0
}

void test_linear_decrease()
{
    const auto tolerance = detail::close_to<double>(1e-4);
    interim::basic_psquare_quantile<double, 12, std::ratio<1,2>> filter;

    filter.push(100);
    TRIAL_TEST_WITH(filter.get<0>(), 100.0, tolerance);
    TRIAL_TEST_WITH(filter.get<1>(), 100.0, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), 100.0, tolerance);

    filter.push(99);
    TRIAL_TEST_WITH(filter.get<0>(), 99.0, tolerance);
    TRIAL_TEST_WITH(filter.get<1>(), 99.5, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), 100.0, tolerance);

    filter.push(98);
    TRIAL_TEST_WITH(filter.get<0>(), 98.0, tolerance);
    TRIAL_TEST_WITH(filter.get<1>(), 99.0, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), 100.0, tolerance);

    filter.push(97);
    TRIAL_TEST_WITH(filter.get<0>(), 97.0, tolerance);
    TRIAL_TEST_WITH(filter.get<1>(), 98.5, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), 100.0, tolerance);

    filter.push(96);
    TRIAL_TEST_WITH(filter.get<0>(), 96.0, tolerance);
    TRIAL_TEST_WITH(filter.get<1>(), 98.0, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), 100.0, tolerance);

    // Switch to P^2 approximation

    filter.push(95);
    TRIAL_TEST_WITH(filter.get<0>(), 95.0, tolerance);
    TRIAL_TEST_WITH(filter.get<1>(), 97.0, tolerance); // 97.5
    TRIAL_TEST_WITH(filter.get<2>(), 100.0, tolerance);

    // Switch to interpolation

    filter.push(94);
    TRIAL_TEST_WITH(filter.get<0>(), 94.7143, tolerance); // 94.0
    TRIAL_TEST_WITH(filter.get<1>(), 96.1429, tolerance); // 96.5
    TRIAL_TEST_WITH(filter.get<2>(), 98.2857, tolerance); // 99.0

    filter.push(93);
    TRIAL_TEST_WITH(filter.get<0>(), 94.0, tolerance); // 93.0
    TRIAL_TEST_WITH(filter.get<1>(), 95.25, tolerance); // 95.5
    TRIAL_TEST_WITH(filter.get<2>(), 97.0, tolerance); // 98.0

    filter.push(92);
    TRIAL_TEST_WITH(filter.get<0>(), 93.0, tolerance); // 92.0
    TRIAL_TEST_WITH(filter.get<1>(), 94.3333, tolerance); // 94.5
    TRIAL_TEST_WITH(filter.get<2>(), 96.0, tolerance); // 97.0

    filter.push(91);
    TRIAL_TEST_WITH(filter.get<0>(), 91.8, tolerance); // 91.0
    TRIAL_TEST_WITH(filter.get<1>(), 93.4, tolerance); // 93.5
    TRIAL_TEST_WITH(filter.get<2>(), 95.2, tolerance); // 96.0

    filter.push(90);
    TRIAL_TEST_WITH(filter.get<0>(), 90.4545, tolerance); // 90.0
    TRIAL_TEST_WITH(filter.get<1>(), 92.4545, tolerance); // 92.5
    TRIAL_TEST_WITH(filter.get<2>(), 94.5455, tolerance); // 95.0

    filter.push(89);
    TRIAL_TEST_WITH(filter.get<0>(), 89.0, tolerance); // 89.0
    TRIAL_TEST_WITH(filter.get<1>(), 91.0, tolerance); // 91.5
    TRIAL_TEST_WITH(filter.get<2>(), 94.0, tolerance); // 94.0

    filter.push(88);
    TRIAL_TEST_WITH(filter.get<0>(), 88.7143, tolerance); // 88.0
    TRIAL_TEST_WITH(filter.get<1>(), 90.1429, tolerance); // 90.5
    TRIAL_TEST_WITH(filter.get<2>(), 92.2857, tolerance); // 93.0

    filter.push(87);
    TRIAL_TEST_WITH(filter.get<0>(), 88.0, tolerance); // 87.0
    TRIAL_TEST_WITH(filter.get<1>(), 89.25, tolerance); // 89.5
    TRIAL_TEST_WITH(filter.get<2>(), 91.0, tolerance); // 92.0
}

void test_linear_decrease_negative()
{
    const auto tolerance = detail::close_to<double>(1e-4);
    interim::basic_psquare_quantile<double, 12, std::ratio<1,2>> filter;

    filter.push(-1);
    TRIAL_TEST_WITH(filter.get<0>(), -1.0, tolerance);
    TRIAL_TEST_WITH(filter.get<1>(), -1.0, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), -1.0, tolerance);

    filter.push(-2);
    TRIAL_TEST_WITH(filter.get<0>(), -2.0, tolerance);
    TRIAL_TEST_WITH(filter.get<1>(), -1.5, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), -1.0, tolerance);

    filter.push(-3);
    TRIAL_TEST_WITH(filter.get<0>(), -3.0, tolerance);
    TRIAL_TEST_WITH(filter.get<1>(), -2.0, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), -1.0, tolerance);

    filter.push(-4);
    TRIAL_TEST_WITH(filter.get<0>(), -4.0, tolerance);
    TRIAL_TEST_WITH(filter.get<1>(), -2.5, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), -1.0, tolerance);

    filter.push(-5);
    TRIAL_TEST_WITH(filter.get<0>(), -5.0, tolerance);
    TRIAL_TEST_WITH(filter.get<1>(), -3.0, tolerance);
    TRIAL_TEST_WITH(filter.get<2>(), -1.0, tolerance);

    // Switch to P^2 approximation

    filter.push(-6);
    TRIAL_TEST_WITH(filter.get<0>(), -6.0, tolerance);
    TRIAL_TEST_WITH(filter.get<1>(), -4.0, tolerance); // -3.5
    TRIAL_TEST_WITH(filter.get<2>(), -1.0, tolerance);

    // Switch to interpolation

    filter.push(-7);
    TRIAL_TEST_WITH(filter.get<0>(), -6.28571, tolerance); // -7.0
    TRIAL_TEST_WITH(filter.get<1>(), -4.85714, tolerance); // -4.5
    TRIAL_TEST_WITH(filter.get<2>(), -2.71429, tolerance); // -2.0

    filter.push(-8);
    TRIAL_TEST_WITH(filter.get<0>(), -7.0, tolerance); // -8.0
    TRIAL_TEST_WITH(filter.get<1>(), -5.75, tolerance); // -5.5
    TRIAL_TEST_WITH(filter.get<2>(), -4.0, tolerance); // -3.0

    filter.push(-9);
    TRIAL_TEST_WITH(filter.get<0>(), -8.0, tolerance); // -9.0
    TRIAL_TEST_WITH(filter.get<1>(), -6.66667, tolerance); // -6.5
    TRIAL_TEST_WITH(filter.get<2>(), -5.0, tolerance); // -4.0

    filter.push(-10);
    TRIAL_TEST_WITH(filter.get<0>(), -9.2, tolerance); // -10.0
    TRIAL_TEST_WITH(filter.get<1>(), -7.6, tolerance); // -7.5
    TRIAL_TEST_WITH(filter.get<2>(), -5.8, tolerance); // -5.0

    filter.push(-11);
    TRIAL_TEST_WITH(filter.get<0>(), -10.5455, tolerance); // -11.0
    TRIAL_TEST_WITH(filter.get<1>(), -8.54545, tolerance); // -8.5
    TRIAL_TEST_WITH(filter.get<2>(), -6.45455, tolerance); // -6.0

    filter.push(-12);
    TRIAL_TEST_WITH(filter.get<0>(), -12.0, tolerance); // -12.0
    TRIAL_TEST_WITH(filter.get<1>(), -10.0, tolerance); // -9.5
    TRIAL_TEST_WITH(filter.get<2>(), -7.0, tolerance); // -7.0

    filter.push(-13);
    TRIAL_TEST_WITH(filter.get<0>(), -12.2857, tolerance); // -13.0
    TRIAL_TEST_WITH(filter.get<1>(), -10.8571, tolerance); // -10.5
    TRIAL_TEST_WITH(filter.get<2>(), -8.71429, tolerance); // -8.0

    filter.push(-14);
    TRIAL_TEST_WITH(filter.get<0>(), -13.0, tolerance); // -14.0
    TRIAL_TEST_WITH(filter.get<1>(), -11.75, tolerance); // -11.5
    TRIAL_TEST_WITH(filter.get<2>(), -10.0, tolerance); // -9.0
}

void run()
{
    test_linear_increase();
    test_linear_increase_with_approximation();
    test_linear_decrease();
    test_linear_decrease_negative();
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
