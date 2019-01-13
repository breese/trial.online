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
    member.mean = value_type(0);
    member.count = size_type(0);
}

template <typename T>
auto basic_moment<T, with::mean>::size() const noexcept -> size_type
{
    return member.count;
}

template <typename T>
auto basic_moment<T, with::mean>::mean() const noexcept -> value_type
{
    return member.mean;
}

template <typename T>
auto basic_moment<T, with::mean>::unbiased_mean() const noexcept -> value_type
{
    return (member.count > 1)
        ? member.mean * member.count / value_type(member.count - 1)
        : member.mean;
}

template <typename T>
void basic_moment<T, with::mean>::push(value_type input) noexcept
{
    ++member.count;
    member.mean += (input - member.mean) / value_type(member.count);
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
        const auto diff = input - super::mean();
        super::push(input);
        sum.variance += diff * (input - super::mean());
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
void basic_moment<T, with::skewness>::clear() noexcept
{
    super::clear();
    sum.skewness = value_type(0);
}

template <typename T>
auto basic_moment<T, with::skewness>::skewness() const noexcept -> value_type
{
    if (sum.skewness < std::numeric_limits<value_type>::epsilon())
        return value_type(0);
    return std::sqrt(super::size()) * sum.skewness / (std::sqrt(super::sum.variance) * super::sum.variance);
}

template <typename T>
auto basic_moment<T, with::skewness>::unbiased_skewness() const noexcept -> value_type
{
    const auto count = size();
    if (count < 2)
        return value_type(0);
    if (sum.skewness < std::numeric_limits<value_type>::epsilon())
        return value_type(0);
    // Bias-correction from Octave manual
    return skewness() * std::sqrt(count * (count - 1)) / value_type(count - 2);
}

template <typename T>
void basic_moment<T, with::skewness>::push(value_type input) noexcept
{
    // Use old sums
    const auto count = super::size();
    const auto delta = input - super::mean();
    const auto n = count + 1;
    const auto delta_over_n = delta / n;

    sum.skewness += ((delta * delta_over_n * (n - 1) * (n - 2)) - 3 * super::sum.variance) * delta_over_n;

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
    const auto delta = input - super::mean();
    const auto n = count + 1;
    const auto delta_over_n = delta / n;

    const auto expr = delta * delta_over_n * (n - 1) * (n * (n - 3) + 3);
    const auto var_expr = value_type(6) * super::super::sum.variance;
    const auto skewness_expr = value_type(4) * super::sum.skewness;
    sum.kurtosis += ((expr + var_expr) * delta_over_n - skewness_expr) * delta_over_n;

    super::push(input);
}

} // namespace cumulative
} // namespace online
} // namespace trial
