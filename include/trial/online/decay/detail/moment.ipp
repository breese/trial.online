///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cmath>

namespace trial
{
namespace online
{
namespace decay
{

//-----------------------------------------------------------------------------
// Mean
//-----------------------------------------------------------------------------

template <typename T>
basic_moment<T, with::mean>::basic_moment(value_type mean_factor) noexcept
    : mean_factor(mean_factor)
{
    assert(mean_factor > 0.0);
    assert(mean_factor <= 1.0);
}

template <typename T>
void basic_moment<T, with::mean>::clear() noexcept
{
    mean = value_type(0);
    normalization = value_type(0);
}

template <typename T>
auto basic_moment<T, with::mean>::value() const noexcept -> value_type
{
    return (normalization > value_type(0))
        ? mean / normalization
        : value_type(0);
}

template <typename T>
void basic_moment<T, with::mean>::push(value_type input) noexcept
{
    const value_type one(1);
    mean += mean_factor * (input - mean);
    normalization += mean_factor * (one - normalization);
}

//-----------------------------------------------------------------------------
// Mean with variance
//-----------------------------------------------------------------------------

template <typename T>
basic_moment<T, with::variance>::basic_moment(value_type mean_factor,
                                              value_type var_factor) noexcept
    : super(mean_factor),
      var_factor(var_factor)
{
    assert(var_factor > 0.0);
    assert(var_factor <= 1.0);
}

template <typename T>
void basic_moment<T, with::variance>::clear() noexcept
{
    super::clear();
    sum.variance = value_type(0);
}

template <typename T>
auto basic_moment<T, with::variance>::variance() const noexcept -> value_type
{
    return (normalization > value_type(0))
        ? sum.variance / normalization
        : value_type(0);
}

template <typename T>
void basic_moment<T, with::variance>::push(value_type input) noexcept
{
    super::push(input);
    const auto mean = super::value();
    const value_type one(1);
    const value_type delta = input - mean;
    sum.variance += var_factor * (delta * delta - sum.variance);
    normalization += var_factor * (one - normalization);
}

//-----------------------------------------------------------------------------
// Mean with variance and skewness
//-----------------------------------------------------------------------------

template <typename T>
basic_moment<T, with::skew>::basic_moment(value_type mean_factor,
                                          value_type var_factor,
                                          value_type skew_factor) noexcept
    : super(mean_factor, var_factor),
      skew_factor(skew_factor)
{
    assert(skew_factor > 0.0);
    assert(skew_factor <= 1.0);
}

template <typename T>
void basic_moment<T, with::skew>::clear() noexcept
{
    super::clear();
    sum.skew = value_type(0);
}

template <typename T>
auto basic_moment<T, with::skew>::skew() const noexcept -> value_type
{
    if (normalization > value_type(0))
    {
        const auto var = super::variance();
        return (var > std::numeric_limits<value_type>::epsilon())
            ? sum.skew / (var * std::sqrt(var)) / normalization
            : value_type(0);
    }
    return value_type(0);
}

template <typename T>
void basic_moment<T, with::skew>::push(value_type input) noexcept
{
    super::push(input);
    const auto mean = super::value();
    const value_type one(1);
    const value_type delta = input - mean;
    sum.skew += skew_factor * (delta * delta * delta - sum.skew);
    normalization += skew_factor * (one - normalization);
}

} // namespace decay
} // namespace online
} // namespace trial
