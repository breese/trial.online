///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

namespace trial
{
namespace online
{
namespace decay
{

//-----------------------------------------------------------------------------
// Average
//-----------------------------------------------------------------------------

template <typename T, typename MR>
void basic_moment<T, with_mean, MR>::clear()
{
    mean = value_type(0);
    normalization = value_type(0);
}

template <typename T, typename MR>
auto basic_moment<T, with_mean, MR>::value() const -> value_type
{
    return (normalization > value_type(0))
        ? mean / normalization
        : value_type(0);
}

template <typename T, typename MR>
void basic_moment<T, with_mean, MR>::push(value_type input)
{
    const value_type one(1);
    mean = mean_factor * input + (one - mean_factor) * mean;
    normalization = mean_factor + (one - mean_factor) * normalization;
}

//-----------------------------------------------------------------------------
// Average with variance
//-----------------------------------------------------------------------------

template <typename T, typename MR, typename VR>
void basic_moment<T, with_variance, MR, VR>::clear()
{
    super::clear();
    sum.variance = value_type(0);
}

template <typename T, typename MR, typename VR>
auto basic_moment<T, with_variance, MR, VR>::variance() const -> value_type
{
    return (normalization > value_type(0))
        ? sum.variance / normalization
        : value_type(0);
}

template <typename T, typename MR, typename VR>
void basic_moment<T, with_variance, MR, VR>::push(value_type input)
{
    super::push(input);
    const auto mean = super::value();
    const value_type one(1);
    const value_type delta = input - mean;
    sum.variance = var_factor * delta * delta + (one - var_factor) * sum.variance;
    normalization = var_factor + (one - var_factor) * normalization;
}

//-----------------------------------------------------------------------------
// Average with variance and skewness
//-----------------------------------------------------------------------------

template <typename T, typename MR, typename VR, typename SR>
void basic_moment<T, with_skew, MR, VR, SR>::clear()
{
    super::clear();
    sum.skew = value_type(0);
}

template <typename T, typename MR, typename VR, typename SR>
auto basic_moment<T, with_skew, MR, VR, SR>::skew() const -> value_type
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

template <typename T, typename MR, typename VR, typename SR>
void basic_moment<T, with_skew, MR, VR, SR>::push(value_type input)
{
    super::push(input);
    const auto mean = super::value();
    const value_type one(1);
    const value_type delta = input - mean;
    sum.skew = skew_factor * delta * delta * delta + (one - skew_factor) * sum.skew;
    normalization = skew_factor + (one - skew_factor) * normalization;
}

} // namespace decay
} // namespace online
} // namespace trial
