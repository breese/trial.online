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
// Average without variance
//-----------------------------------------------------------------------------

template <typename T>
void basic_moment<T, with::mean>::clear()
{
    mean = value_type(0);
    count = size_type(0);
}

template <typename T>
auto basic_moment<T, with::mean>::size() const -> size_type
{
    return count;
}

template <typename T>
auto basic_moment<T, with::mean>::value() const -> value_type
{
    return mean;
}

template <typename T>
auto basic_moment<T, with::mean>::unbiased_value() const -> value_type
{
    return (count > 1)
        ? mean * count / value_type(count - 1)
        : mean;
}

template <typename T>
void basic_moment<T, with::mean>::push(value_type input)
{
    ++count;
    mean += (input - mean) / value_type(count);
}

//-----------------------------------------------------------------------------
// Average with variance
//-----------------------------------------------------------------------------

template <typename T>
void basic_moment<T, with::variance>::clear()
{
    super::clear();
    sum.variance = value_type(0);
}

template <typename T>
auto basic_moment<T, with::variance>::variance() const -> value_type
{
    const auto count = super::size();
    return (count > 0)
        ? sum.variance / value_type(count)
        : value_type(0);
}

template <typename T>
auto basic_moment<T, with::variance>::unbiased_variance() const -> value_type
{
    const auto count = super::size();
    return (count > 1)
        ? sum.variance / value_type(count - 1)
        : value_type(0);
}

template <typename T>
void basic_moment<T, with::variance>::push(value_type input)
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
// Average with variance and skewness
//-----------------------------------------------------------------------------

template <typename T>
void basic_moment<T, with::skew>::clear()
{
    super::clear();
    sum.skew = value_type(0);
}

template <typename T>
auto basic_moment<T, with::skew>::skew() const -> value_type
{
    if (sum.skew < std::numeric_limits<value_type>::epsilon())
        return value_type(0);
    return std::sqrt(super::size()) * sum.skew / (std::sqrt(super::sum.variance) * super::sum.variance);
}

template <typename T>
auto basic_moment<T, with::skew>::unbiased_skew() const -> value_type
{
    const auto count = size();
    if (count < 2)
        return value_type(0);
    if (sum.skew < std::numeric_limits<value_type>::epsilon())
        return value_type(0);
    return skew() * std::sqrt(count * (count -1 )) / value_type(count - 2);
}

template <typename T>
void basic_moment<T, with::skew>::push(value_type input)
{
    // Use old mean and variance
    const auto count = super::size();
    const auto delta = input - super::value();
    const auto delta_over_count = delta / (count + 1);

    sum.skew += ((delta * delta_over_count * count * (count - 1)) - 3 * super::sum.variance) * delta_over_count;

    super::push(input);
}

} // namespace cumulative
} // namespace online
} // namespace trial
