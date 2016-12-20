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

template <typename T>
exponential<T>::exponential(value_type smoothing_factor)
    : smoothing_factor(smoothing_factor),
      average(),
      normalization()
{
    assert(smoothing_factor >= zero);
    assert(smoothing_factor <= one);
}

template <typename T>
void exponential<T>::clear()
{
    average = zero;
    normalization = zero;
}

template <typename T>
typename exponential<T>::value_type exponential<T>::mean() const
{
    if (normalization > zero)
        return average / normalization;
    return zero;
}

template <typename T>
void exponential<T>::push(value_type value)
{
    // Normalization is described in:
    //   http://breese.github.io/2015/10/26/on-average.html
    normalization = smoothing_factor + (one - smoothing_factor) * normalization;
    average = smoothing_factor * value + (one - smoothing_factor) * average;
}

} // namespace average
} // namespace online
} // namespace trial
