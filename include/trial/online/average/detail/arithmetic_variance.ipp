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
#include <algorithm>
#include <cmath>
#include <limits>

namespace trial
{
namespace online
{
namespace average
{

template <typename T, std::size_t N>
arithmetic_variance<T, N>::arithmetic_variance()
    : window(N),
      sum(),
      numerator()
{
    assert(N > 0);
}

template <typename T, std::size_t N>
typename arithmetic_variance<T, N>::size_type arithmetic_variance<T, N>::capacity() const
{
    assert(window.capacity() == N);

    return window.capacity();
}

template <typename T, std::size_t N>
void arithmetic_variance<T, N>::clear()
{
    sum = value_type();
    numerator = value_type();
    window.clear();
}

template <typename T, std::size_t N>
bool arithmetic_variance<T, N>::empty() const
{
    return window.empty();
}

template <typename T, std::size_t N>
bool arithmetic_variance<T, N>::full() const
{
    return window.full();
}

template <typename T, std::size_t N>
typename arithmetic_variance<T, N>::value_type arithmetic_variance<T, N>::value() const
{
    if (empty())
        return value_type();
    return sum / value_type(size());
}

template <typename T, std::size_t N>
void arithmetic_variance<T, N>::push(value_type value)
{
    const value_type old_mean = this->value();
    if (full())
    {
        const value_type old_value = window.front();
        sum += value - old_value;
        window.push_back(value);
        numerator += delta(value, old_mean);
        numerator -= delta(old_value, old_mean);
    }
    else
    {
        sum += value;
        window.push_back(value);
        numerator += delta(value, old_mean);
    }
}

template <typename T, std::size_t N>
typename arithmetic_variance<T, N>::size_type arithmetic_variance<T, N>::size() const
{
    return window.size();
}

template <typename T, std::size_t N>
typename arithmetic_variance<T, N>::value_type arithmetic_variance<T, N>::variance() const
{
    if (size() < 2)
        return value_type();
    // Rounding errors can cause the variance to become negative
    return std::max(value_type(), numerator / (size() - 1));
}

template <typename T, std::size_t N>
typename arithmetic_variance<T, N>::value_type
arithmetic_variance<T, N>::delta(value_type value, value_type old_mean)
{
    return (value - old_mean) * (value - this->value());
}

} // namespace average
} // namespace online
} // namespace trial
