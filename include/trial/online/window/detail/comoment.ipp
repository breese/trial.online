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
basic_comoment<T, W, with::variance>::basic_comoment() noexcept
    : window(storage)
{
}

template <typename T, std::size_t W>
auto basic_comoment<T, W, with::variance>::size() const noexcept -> size_type
{
    return window.size();
}

template <typename T, std::size_t W>
void basic_comoment<T, W, with::variance>::clear() noexcept
{
    window.clear();
    sum.x = sum.y = sum.xy = value_type(0);
}

template <typename T, std::size_t W>
void basic_comoment<T, W, with::variance>::push(value_type x, value_type y) noexcept
{
    if (window.full())
    {
        const auto front_x = window.front().first;
        const auto front_y = window.front().second;
        sum.x += x - front_x;
        sum.y += y - front_y;
        sum.xy += x * y - front_x * front_y;
    }
    else
    {
        sum.x += x;
        sum.y += y;
        sum.xy += x * y;
    }
    window.push_back(std::make_pair(x, y));
}

template <typename T, std::size_t W>
auto basic_comoment<T, W, with::variance>::cosum() const noexcept -> value_type
{
    return sum.xy - sum.x * sum.y / size();
}

template <typename T, std::size_t W>
auto basic_comoment<T, W, with::variance>::variance() const noexcept -> value_type
{
    if (size() > 0)
        return cosum() / size();
    return value_type(0);
}

template <typename T, std::size_t W>
auto basic_comoment<T, W, with::variance>::unbiased_variance() const noexcept -> value_type
{
    if (size() > 1)
        return cosum() / (size() - 1);
    return value_type(0);
}

} // namespace window
} // namespace online
} // namespace trial
