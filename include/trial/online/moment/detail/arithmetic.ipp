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
namespace moment
{

//-----------------------------------------------------------------------------
// Average without variance
//-----------------------------------------------------------------------------

template <typename T, std::size_t N>
basic_arithmetic<T, N, with_mean>::basic_arithmetic()
    : window(N)
{
}

template <typename T, std::size_t N>
auto basic_arithmetic<T, N, with_mean>::capacity() const -> size_type
{
    assert(window.capacity() == N);

    return window.capacity();
}

template <typename T, std::size_t N>
void basic_arithmetic<T, N, with_mean>::clear()
{
    sum.mean = value_type(0);
    window.clear();
}

template <typename T, std::size_t N>
bool basic_arithmetic<T, N, with_mean>::empty() const
{
    return window.empty();
}

template <typename T, std::size_t N>
auto basic_arithmetic<T, N, with_mean>::size() const -> size_type
{
    return window.size();
}

template <typename T, std::size_t N>
bool basic_arithmetic<T, N, with_mean>::full() const
{
    return window.full();
}

template <typename T, std::size_t N>
auto basic_arithmetic<T, N, with_mean>::value() const -> value_type
{
    if (empty())
        return value_type();
    return sum.mean / value_type(size());
}

template <typename T, std::size_t N>
void basic_arithmetic<T, N, with_mean>::push(value_type value)
{
    if (full())
    {
        sum.mean += value - window.front();
    }
    else
    {
        sum.mean += value;
    }
    window.push_back(value);
}

//-----------------------------------------------------------------------------
// Average with variance
//-----------------------------------------------------------------------------

template <typename T, std::size_t N>
basic_arithmetic<T, N, with_variance>::basic_arithmetic()
    : super()
{
}

template <typename T, std::size_t N>
void basic_arithmetic<T, N, with_variance>::clear()
{
    super::clear();
    sum.variance = value_type(0);
}

template <typename T, std::size_t N>
void basic_arithmetic<T, N, with_variance>::push(value_type input)
{
    const value_type old_mean = super::value();
    if (super::full())
    {
        const value_type old_input = super::window.front();
        super::sum.mean += input - old_input;
        super::window.push_back(input);
        sum.variance += delta(input, old_mean);
        sum.variance -= delta(old_input, old_mean);
    }
    else
    {
        super::sum.mean += input;
        super::window.push_back(input);
        sum.variance += delta(input, old_mean);
    }
}

template <typename T, std::size_t N>
auto basic_arithmetic<T, N, with_variance>::variance() const -> value_type
{
    // Rounding errors can cause the variance to become negative
    const auto count = super::size();
    return (count > 0)
        ? std::max(value_type(0), sum.variance / value_type(count))
        : value_type(0);
}

template <typename T, std::size_t N>
auto basic_arithmetic<T, N, with_variance>::unbiased_variance() const -> value_type
{
    // With Bessel's correction
    // Rounding errors can cause the variance to become negative
    const auto count = super::size();
    return (count > 1)
        ? std::max(value_type(0), sum.variance / (count - 1))
        : value_type(0);
}

template <typename T, std::size_t N>
auto basic_arithmetic<T, N, with_variance>::delta(value_type input, value_type old_mean) -> value_type
{
    return (input - old_mean) * (input - super::value());
}

} // namespace moment
} // namespace online
} // namespace trial
