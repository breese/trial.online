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
covariance<T, W>::covariance() noexcept
    : window(storage)
{
}

template <typename T, std::size_t W>
auto covariance<T, W>::size() const noexcept -> size_type
{
    return window.size();
}

template <typename T, std::size_t W>
void covariance<T, W>::clear() noexcept
{
    x_moment.clear();
    y_moment.clear();
    window.clear();
}

template <typename T, std::size_t W>
void covariance<T, W>::push(value_type x, value_type y) noexcept
{
    x_moment.push(x);
    y_moment.push(y);
    window.push_back(std::make_pair(x, y));
}

template <typename T, std::size_t W>
auto covariance<T, W>::sum() const noexcept -> value_type
{
    value_type sum(0);
    const auto x_mean = x_moment.mean();
    const auto y_mean = y_moment.mean();
    for (const auto& item : window)
    {
        sum += (item.first - x_mean) * (item.second - y_mean);
    }
    return sum;
}

template <typename T, std::size_t W>
auto covariance<T, W>::value() const noexcept -> value_type
{
    if (size() > 0)
        return sum() / size();
    return value_type(0);
}

template <typename T, std::size_t W>
auto covariance<T, W>::unbiased_value() const noexcept -> value_type
{
    if (size() > 1)
        return sum() / (size() - 1);
    return value_type(0);
}

} // namespace window
} // namespace online
} // namespace trial
