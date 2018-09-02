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
    : window(N),
      sum()
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
    sum = value_type();
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
    return sum / value_type(size());
}

template <typename T, std::size_t N>
void basic_arithmetic<T, N, with_mean>::push(value_type value)
{
    if (full())
    {
        sum += value - window.front();
        window.push_back(value);
    }
    else
    {
        sum += value;
        window.push_back(value);
    }
}

//-----------------------------------------------------------------------------
// Average with variance
//-----------------------------------------------------------------------------

template <typename T, std::size_t N>
basic_arithmetic<T, N, with_variance>::basic_arithmetic()
    : window(N),
      sum(),
      numerator()
{
    assert(N > 0);
}

template <typename T, std::size_t N>
auto basic_arithmetic<T, N, with_variance>::capacity() const -> size_type
{
    assert(window.capacity() == N);

    return window.capacity();
}

template <typename T, std::size_t N>
void basic_arithmetic<T, N, with_variance>::clear()
{
    sum = value_type();
    numerator = value_type();
    window.clear();
}

template <typename T, std::size_t N>
bool basic_arithmetic<T, N, with_variance>::empty() const
{
    return window.empty();
}

template <typename T, std::size_t N>
auto basic_arithmetic<T, N, with_variance>::size() const -> size_type
{
    return window.size();
}

template <typename T, std::size_t N>
bool basic_arithmetic<T, N, with_variance>::full() const
{
    return window.full();
}

template <typename T, std::size_t N>
void basic_arithmetic<T, N, with_variance>::push(value_type input)
{
    const value_type old_mean = value();
    if (full())
    {
        const value_type old_input = window.front();
        sum += input - old_input;
        window.push_back(input);
        numerator += delta(input, old_mean);
        numerator -= delta(old_input, old_mean);
    }
    else
    {
        sum += input;
        window.push_back(input);
        numerator += delta(input, old_mean);
    }
}

template <typename T, std::size_t N>
auto basic_arithmetic<T, N, with_variance>::value() const -> value_type
{
    if (empty())
        return value_type();
    return sum / value_type(size());
}

template <typename T, std::size_t N>
auto basic_arithmetic<T, N, with_variance>::variance() const -> value_type
{
    // Rounding errors can cause the variance to become negative
    const auto count = size();
    return (count > 0)
        ? std::max(value_type(0), numerator / value_type(count))
        : value_type(0);
}

template <typename T, std::size_t N>
auto basic_arithmetic<T, N, with_variance>::unbiased_variance() const -> value_type
{
    // With Bessel's correction
    // Rounding errors can cause the variance to become negative
    const auto count = size();
    return (count > 1)
        ? std::max(value_type(0), numerator / (count - 1))
        : value_type(0);
}

template <typename T, std::size_t N>
auto basic_arithmetic<T, N, with_variance>::delta(value_type input, value_type old_mean) -> value_type
{
    return (input - old_mean) * (input - value());
}

} // namespace moment
} // namespace online
} // namespace trial
