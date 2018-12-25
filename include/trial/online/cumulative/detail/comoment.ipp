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

namespace trial
{
namespace online
{
namespace cumulative
{

//-----------------------------------------------------------------------------
// Co-variance
//-----------------------------------------------------------------------------

template <typename T>
void basic_comoment<T, with::variance>::clear() noexcept
{
    x_center.clear();
    y_center.clear();
    center = value_type(0);
}

template <typename T>
void basic_comoment<T, with::variance>::push(value_type x, value_type y) noexcept
{
    // Using new x moment and old y moment
    x_center.push(x);
    center += (x - x_center.mean()) * (y - y_center.mean());
    y_center.push(y);
}

template <typename T>
auto basic_comoment<T, with::variance>::size() const noexcept -> size_type
{
    assert(x_center.size() == y_center.size());

    return x_center.size();
}

template <typename T>
auto basic_comoment<T, with::variance>::variance() const noexcept -> value_type
{
    if (size() > 0)
        return center / size();
    return value_type(0);
}

template <typename T>
auto covariance<T>::unbiased_variance() const noexcept -> value_type
{
    // With Bessel's correction
    if (size() > 1)
        return center / (size() - 1);
    return value_type(0);
}

} // namespace cumulative
} // namespace online
} // namespace trial
