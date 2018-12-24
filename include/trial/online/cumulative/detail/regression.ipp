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
#include <limits>

namespace trial
{
namespace online
{
namespace cumulative
{

template <typename T>
void regression<T>::clear() noexcept
{
    covariance.clear();
    x_moment.clear();
    y_moment.clear();
}

template <typename T>
auto regression<T>::size() const noexcept -> size_type
{
    assert(x_moment.size() == y_moment.size());

    return x_moment.size();
}

template <typename T>
void regression<T>::push(value_type x, value_type y) noexcept
{
    covariance.push(x, y);
    x_moment.push(x);
    y_moment.push(y);
}

template <typename T>
auto regression<T>::at(value_type position) const noexcept -> value_type
{
    return y_moment.mean() - slope() * (x_moment.mean() - position);
}

template <typename T>
auto regression<T>::slope() const noexcept -> value_type
{
    const auto divisor = x_moment.variance();
    return (divisor == 0)
        ? value_type(0)
        : covariance.value() / divisor;
}

} // namespace cumulative
} // namespace online
} // namespace trial
