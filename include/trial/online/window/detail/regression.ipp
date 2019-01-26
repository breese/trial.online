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
namespace window
{

template <typename T, std::size_t W>
void regression<T, W>::clear() noexcept
{
    covariance::clear();
    x_moment.clear();
}

template <typename T, std::size_t W>
auto regression<T, W>::size() const noexcept -> size_type
{
    return covariance::size();
}

template <typename T, std::size_t W>
void regression<T, W>::push(value_type x, value_type y) noexcept
{
    covariance::push(x, y);
    x_moment.push(x);
}

template <typename T, std::size_t W>
auto regression<T, W>::at(value_type position) const noexcept -> value_type
{
    const auto y_mean = covariance::sum.y / covariance::size();
    return y_mean - slope() * (x_moment.mean() - position);
}

template <typename T, std::size_t W>
auto regression<T, W>::slope() const noexcept -> value_type
{
    const auto divisor = x_moment.variance();
    return (divisor == 0)
        ? value_type(0)
        : covariance::variance() / divisor;
}

} // namespace window
} // namespace online
} // namespace trial
