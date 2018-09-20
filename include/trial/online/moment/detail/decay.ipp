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
namespace moment
{

//-----------------------------------------------------------------------------
// Average
//-----------------------------------------------------------------------------

template <typename T, typename MR>
void basic_decay<T, with_mean, MR>::clear()
{
    mean = value_type(0);
}

template <typename T, typename MR>
auto basic_decay<T, with_mean, MR>::value() const -> value_type
{
    return mean;
}

template <typename T, typename MR>
void basic_decay<T, with_mean, MR>::push(value_type input)
{
    const value_type one(1);
    mean = mean_factor * input + (one - mean_factor) * mean;
}

//-----------------------------------------------------------------------------
// Average with variance
//-----------------------------------------------------------------------------

template <typename T, typename MR, typename VR>
void basic_decay<T, with_variance, MR, VR>::clear()
{
    super::clear();
    sum.variance = value_type(0);
}

template <typename T, typename MR, typename VR>
auto basic_decay<T, with_variance, MR, VR>::variance() const -> value_type
{
    return sum.variance;
}

template <typename T, typename MR, typename VR>
void basic_decay<T, with_variance, MR, VR>::push(value_type input)
{
    super::push(input);
    const auto mean = super::value();
    const value_type one(1);
    const value_type delta = input - mean;
    sum.variance = var_factor * delta * delta + (one - var_factor) * sum.variance;
}

} // namespace moment
} // namespace online
} // namespace trial
