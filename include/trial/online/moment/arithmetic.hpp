#ifndef TRIAL_ONLINE_MOMENT_ARITHMETIC_HPP
#define TRIAL_ONLINE_MOMENT_ARITHMETIC_HPP

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
#include <trial/online/moment/types.hpp>

namespace trial
{
namespace online
{
namespace moment
{

template <typename T, std::size_t N, moment::type Moment>
class basic_arithmetic;

template <typename T, std::size_t N>
class basic_arithmetic<T, N, with_mean>
{
public:
    using value_type = T;
    using size_type = std::size_t;

    static_assert(N > 0, "N must be larger than zero");
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    static_assert((!std::is_same<T, bool>::value), "T cannot be bool");

    basic_arithmetic();

    size_type capacity() const;
    void clear();
    bool empty() const;
    bool full() const;
    value_type value() const;
    void push(value_type value);
    size_type size() const;

private:
    using window_type = boost::circular_buffer<value_type>;
    window_type window;
    value_type sum;
};

template <typename T, std::size_t N>
class basic_arithmetic<T, N, with_variance>
{
public:
    using value_type = T;
    using size_type = std::size_t;

    static_assert(N > 0, "N must be larger than zero");
    static_assert(std::is_floating_point<T>::value, "T must be a floating-point type");

    basic_arithmetic();

    size_type capacity() const;
    void clear();
    bool empty() const;
    bool full() const;
    value_type value() const;
    void push(value_type value);
    size_type size() const;
    value_type variance() const;
    value_type unbiased_variance() const;

private:
    value_type delta(value_type, value_type);

private:
    using window_type = boost::circular_buffer<value_type>;
    window_type window;
    value_type sum;
    value_type numerator;
};

template <typename T, std::size_t N>
using arithmetic = basic_arithmetic<T, N, with_mean>;

template <typename T, std::size_t N>
using arithmetic_variance = basic_arithmetic<T, N, with_variance>;

} // namespace moment
} // namespace online
} // namespace trial

#include <trial/online/moment/detail/arithmetic.ipp>

#endif // TRIAL_ONLINE_MOMENT_ARITHMETIC_HPP
