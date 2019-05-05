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
#include <cmath>

namespace trial
{
namespace online
{
namespace window
{

//-----------------------------------------------------------------------------
// Average without variance
//-----------------------------------------------------------------------------

template <typename T, std::size_t N>
basic_moment<T, N, with::mean>::basic_moment() noexcept
    : window(storage)
{
}

template <typename T, std::size_t N>
auto basic_moment<T, N, with::mean>::capacity() const noexcept -> size_type
{
    assert(window.capacity() == N);

    return window.capacity();
}

template <typename T, std::size_t N>
void basic_moment<T, N, with::mean>::clear() noexcept
{
    member.mean = value_type(0);
    window.clear();
}

template <typename T, std::size_t N>
bool basic_moment<T, N, with::mean>::empty() const noexcept
{
    return window.empty();
}

template <typename T, std::size_t N>
auto basic_moment<T, N, with::mean>::size() const noexcept -> size_type
{
    return window.size();
}

template <typename T, std::size_t N>
bool basic_moment<T, N, with::mean>::full() const noexcept
{
    return window.full();
}

template <typename T, std::size_t N>
auto basic_moment<T, N, with::mean>::mean() const noexcept -> value_type
{
    return member.mean;
}

template <typename T, std::size_t N>
void basic_moment<T, N, with::mean>::push(value_type input) noexcept
{
    if (full())
    {
        member.mean += (input - window.front()) / value_type(size());
}
    else
    {
        member.mean += (input - member.mean) / value_type(size() + 1);
    }
    window.push_back(input);
}

//-----------------------------------------------------------------------------
// Average with variance
//-----------------------------------------------------------------------------

template <typename T, std::size_t N>
basic_moment<T, N, with::variance>::basic_moment() noexcept
    : super()
{
}

template <typename T, std::size_t N>
void basic_moment<T, N, with::variance>::clear() noexcept
{
    super::clear();
    sum.variance = value_type(0);
}

template <typename T, std::size_t N>
void basic_moment<T, N, with::variance>::push(value_type input) noexcept
{
    const value_type old_mean = super::mean();
    if (super::full())
    {
        const value_type old_input = super::window.front();
        super::member.mean += (input - old_input) / value_type(size());
        super::window.push_back(input);
        sum.variance += delta(input, old_mean);
        sum.variance -= delta(old_input, old_mean);
    }
    else
    {
        super::member.mean += (input - super::member.mean) / value_type(size() + 1);
        super::window.push_back(input);
        sum.variance += delta(input, old_mean);
    }
}

template <typename T, std::size_t N>
auto basic_moment<T, N, with::variance>::variance() const noexcept -> value_type
{
    // Rounding errors can cause the variance to become negative
    const auto count = super::size();
    return (count > 0)
        ? std::max(value_type(0), sum.variance / value_type(count))
        : value_type(0);
}

template <typename T, std::size_t N>
auto basic_moment<T, N, with::variance>::unbiased_variance() const noexcept -> value_type
{
    // With Bessel's correction
    // Rounding errors can cause the variance to become negative
    const auto count = super::size();
    return (count > 1)
        ? std::max(value_type(0), sum.variance / (count - 1))
        : value_type(0);
}

template <typename T, std::size_t N>
auto basic_moment<T, N, with::variance>::delta(value_type input, value_type old_mean) noexcept -> value_type
{
    return (input - old_mean) * (input - super::mean());
}

} // namespace window
} // namespace online
} // namespace trial
