#ifndef TRIAL_ONLINE_AVERAGE_ARITHMETIC_HPP
#define TRIAL_ONLINE_AVERAGE_ARITHMETIC_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2016 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cstddef> // std::size_t
#include <type_traits>
#include <boost/circular_buffer.hpp>

namespace trial
{
namespace online
{
namespace average
{

template <typename T, std::size_t N>
class arithmetic
{
public:
    using value_type = T;
    using size_type = std::size_t;

    static_assert(N > 0, "N must be larger than zero");
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    static_assert((!std::is_same<T, bool>::value), "T cannot be bool");

    arithmetic();

    size_type capacity() const;
    void clear();
    bool empty() const;
    bool full() const;
    value_type mean() const;
    void push(value_type value);
    size_type size() const;

private:
    using window_type = boost::circular_buffer<value_type>;
    window_type window;
    value_type sum;
};

} // namespace average
} // namespace online
} // namespace trial

#include <trial/online/average/detail/arithmetic.ipp>

#endif // TRIAL_ONLINE_AVERAGE_ARITHMETIC_HPP
