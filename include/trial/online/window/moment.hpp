#ifndef TRIAL_ONLINE_WINDOW_MOMENT_HPP
#define TRIAL_ONLINE_WINDOW_MOMENT_HPP

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
namespace window
{

enum type
{
    with_mean = 1,
    with_variance = 2
};

template <typename T, std::size_t N, window::type Moment>
class basic_moment;

template <typename T, std::size_t N>
class basic_moment<T, N, with_mean>
{
public:
    using value_type = T;
    using size_type = std::size_t;

    static_assert(N > 0, "N must be larger than zero");
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    static_assert((!std::is_same<T, bool>::value), "T cannot be bool");

    basic_moment();

    size_type capacity() const;
    void clear();
    bool empty() const;
    bool full() const;
    value_type value() const;
    void push(value_type value);
    size_type size() const;

protected:
    using window_type = boost::circular_buffer<value_type>;
    window_type window;
    struct
    {
        value_type mean = value_type(0);
    } sum;
};

template <typename T, std::size_t N>
class basic_moment<T, N, with_variance>
    : protected basic_moment<T, N, with_mean>
{
    using super = basic_moment<T, N, with_mean>;

public:
    using typename super::value_type;
    using typename super::size_type;

    static_assert(std::is_floating_point<T>::value, "T must be a floating-point type");

    basic_moment();

    using super::capacity;
    void clear();
    using super::empty;
    using super::full;
    using super::value;
    void push(value_type value);
    using super::size;
    value_type variance() const;
    value_type unbiased_variance() const;

protected:
    value_type delta(value_type, value_type);

protected:
    struct
    {
        value_type variance = value_type(0);
    } sum;
};

template <typename T, std::size_t N>
using moment = basic_moment<T, N, with_mean>;

template <typename T, std::size_t N>
using moment_variance = basic_moment<T, N, with_variance>;

} // namespace window
} // namespace online
} // namespace trial

#include <trial/online/window/detail/moment.ipp>

#endif // TRIAL_ONLINE_WINDOW_MOMENT_HPP
