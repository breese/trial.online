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

namespace trial
{
namespace online
{
namespace average
{

template <typename T, std::size_t N>
arithmetic<T, N>::arithmetic()
    : window(N),
      sum()
{
}

template <typename T, std::size_t N>
typename arithmetic<T, N>::size_type arithmetic<T, N>::capacity() const
{
    assert(window.capacity() == N);

    return window.capacity();
}

template <typename T, std::size_t N>
void arithmetic<T, N>::clear()
{
    sum = value_type();
    window.clear();
}

template <typename T, std::size_t N>
bool arithmetic<T, N>::empty() const
{
    return window.empty();
}

template <typename T, std::size_t N>
bool arithmetic<T, N>::full() const
{
    return window.full();
}

template <typename T, std::size_t N>
typename arithmetic<T, N>::value_type arithmetic<T, N>::mean() const
{
    if (empty())
        return value_type();
    return sum / value_type(size());
}

template <typename T, std::size_t N>
void arithmetic<T, N>::push(value_type value)
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

template <typename T, std::size_t N>
typename arithmetic<T, N>::size_type arithmetic<T, N>::size() const
{
    return window.size();
}

} // namespace average
} // namespace online
} // namespace trial
