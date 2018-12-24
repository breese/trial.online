///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <limits>

namespace trial
{
namespace online
{
namespace cumulative
{

//-----------------------------------------------------------------------------
// Mean
//-----------------------------------------------------------------------------

template <typename T>
void basic_moment<T, with::mean>::clear() noexcept
{
    mean = value_type(0);
    count = size_type(0);
}

template <typename T>
auto basic_moment<T, with::mean>::size() const noexcept -> size_type
{
    return count;
}

template <typename T>
auto basic_moment<T, with::mean>::value() const noexcept -> value_type
{
    return mean;
}

template <typename T>
auto basic_moment<T, with::mean>::unbiased_value() const noexcept -> value_type
{
    return (count > 1)
        ? mean * count / value_type(count - 1)
        : mean;
}

template <typename T>
void basic_moment<T, with::mean>::push(value_type input) noexcept
{
    ++count;
    mean += (input - mean) / value_type(count);
}

//-----------------------------------------------------------------------------
// Mean with variance
//-----------------------------------------------------------------------------

template <typename T>
void basic_moment<T, with::variance>::clear() noexcept
{
    super::clear();
    sum.variance = value_type(0);
}

template <typename T>
auto basic_moment<T, with::variance>::variance() const noexcept -> value_type
{
    const auto count = super::size();
    return (count > 0)
        ? sum.variance / value_type(count)
        : value_type(0);
}

template <typename T>
auto basic_moment<T, with::variance>::unbiased_variance() const noexcept -> value_type
{
    const auto count = super::size();
    return (count > 1)
        ? sum.variance / value_type(count - 1)
        : value_type(0);
}

template <typename T>
void basic_moment<T, with::variance>::push(value_type input) noexcept
{
    if (super::size() > 0)
    {
        const auto diff = input - super::value();
        super::push(input);
        sum.variance += diff * (input - super::value());
    }
    else
    {
        super::push(input);
    }
}

//-----------------------------------------------------------------------------
// Mean with variance and skewness
//-----------------------------------------------------------------------------

template <typename T>
void basic_moment<T, with::skew>::clear() noexcept
{
    super::clear();
    sum.skew = value_type(0);
}

template <typename T>
auto basic_moment<T, with::skew>::skew() const noexcept -> value_type
{
    if (sum.skew < std::numeric_limits<value_type>::epsilon())
        return value_type(0);
    return std::sqrt(super::size()) * sum.skew / (std::sqrt(super::sum.variance) * super::sum.variance);
}

template <typename T>
auto basic_moment<T, with::skew>::unbiased_skew() const noexcept -> value_type
{
    const auto count = size();
    if (count < 2)
        return value_type(0);
    if (sum.skew < std::numeric_limits<value_type>::epsilon())
        return value_type(0);
    // Bias-correction from Octave manual
    return skew() * std::sqrt(count * (count - 1)) / value_type(count - 2);
}

template <typename T>
void basic_moment<T, with::skew>::push(value_type input) noexcept
{
    // Use old sums
    const auto count = super::size();
    const auto delta = input - super::value();
    const auto n = count + 1;
    const auto delta_over_n = delta / n;

    sum.skew += ((delta * delta_over_n * (n - 1) * (n - 2)) - 3 * super::sum.variance) * delta_over_n;

    super::push(input);
}

//-----------------------------------------------------------------------------
// Mean with variance, skewness, and kurtosis
//-----------------------------------------------------------------------------

template <typename T>
void basic_moment<T, with::kurtosis>::clear() noexcept
{
    super::clear();
    sum.kurtosis = value_type(0);
}

template <typename T>
auto basic_moment<T, with::kurtosis>::kurtosis() const noexcept -> value_type
{
    if (sum.kurtosis < std::numeric_limits<value_type>::epsilon())
        return value_type(0);
    return super::size() * sum.kurtosis / (super::super::sum.variance * super::super::sum.variance);
}

template <typename T>
auto basic_moment<T, with::kurtosis>::unbiased_kurtosis() const noexcept -> value_type
{
    const auto count = super::size();
    if (count < 4)
        return value_type(0);
    if (sum.kurtosis < std::numeric_limits<value_type>::epsilon())
        return value_type(0);
    // Bias-correction from Octave manual
    return value_type(3) + (count - 1) / value_type((count - 2) * (count - 3)) * ((count + 1) * kurtosis() - value_type(3) * (count - 1));
}

template <typename T>
void basic_moment<T, with::kurtosis>::push(value_type input) noexcept
{
    // Use old sums
    const auto count = super::size();
    const auto delta = input - super::value();
    const auto n = count + 1;
    const auto delta_over_n = delta / n;

    const auto expr = delta * delta_over_n * (n - 1) * (n * (n - 3) + 3);
    const auto var_expr = value_type(6) * super::super::sum.variance;
    const auto skew_expr = value_type(4) * super::sum.skew;
    sum.kurtosis += ((expr + var_expr) * delta_over_n - skew_expr) * delta_over_n;

    super::push(input);
}

} // namespace cumulative
} // namespace online
} // namespace trial
