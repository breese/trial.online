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
namespace correlation
{

template <typename T>
covariance<T>::covariance()
{
}

template <typename T>
auto covariance<T>::size() const -> size_type
{
    return count;
}

template <typename T>
void covariance<T>::clear()
{
    x_mean = value_type(0);
    y_mean = value_type(0);
    cov = value_type(0);
    count = size_type(0);
}

template <typename T>
void covariance<T>::push(value_type x, value_type y)
{
    ++count;
    x_mean += (x - x_mean) / count;
    const auto d_y = y - y_mean;
    y_mean += d_y / count;
    cov += (x - x_mean) * d_y;
}

template <typename T>
auto covariance<T>::value() const -> value_type
{
    if (count == 0)
        return value_type(0);
    return cov / count;
}

} // namespace correlation
} // namespace online
} // namespace trial
