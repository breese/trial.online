///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2016 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>

namespace trial
{
namespace online
{
namespace average
{

template <typename T, typename S>
exponential<T, S>::exponential()
    : average(),
      normalization()
{
}

template <typename T, typename S>
void exponential<T, S>::clear()
{
    average = {};
    normalization = {};
}

template <typename T, typename S>
typename exponential<T, S>::value_type exponential<T, S>::value() const
{
    if (normalization > value_type(0))
        return average / normalization;
    return {};
}

template <typename T, typename S>
void exponential<T, S>::push(value_type value)
{
    // Normalization is described in:
    //   http://breese.github.io/2015/10/26/on-average.html
    const value_type one(1);
    normalization = smoothing_factor + (one - smoothing_factor) * normalization;
    average = smoothing_factor * value + (one - smoothing_factor) * average;
}

} // namespace average
} // namespace online
} // namespace trial
