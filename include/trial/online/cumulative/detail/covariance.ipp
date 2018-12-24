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
namespace cumulative
{

template <typename T>
auto covariance<T>::size() const noexcept -> size_type
{
    return x_moment.size();
}

template <typename T>
void covariance<T>::clear() noexcept
{
    x_moment.clear();
    y_moment.clear();
    co_moment = value_type(0);
}

template <typename T>
void covariance<T>::push(value_type x, value_type y) noexcept
{
    x_moment.push(x);
    // Using new x moment and old y moment
    co_moment += (x - x_moment.mean()) * (y - y_moment.mean());
    y_moment.push(y);
}

template <typename T>
auto covariance<T>::value() const noexcept -> value_type
{
    if (size() > 0)
        return co_moment / size();
    return value_type(0);
}

template <typename T>
auto covariance<T>::unbiased_value() const noexcept -> value_type
{
    // With Bessel's correction
    if (size() > 1)
        return co_moment / (size() - 1);
    return value_type(0);
}

} // namespace cumulative
} // namespace online
} // namespace trial
