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
#include <trial/online/with.hpp>
#include <trial/circular/array.hpp>

namespace trial
{
namespace online
{
namespace window
{

template <typename T, std::size_t N, online::with Moment>
class basic_moment;

template <typename T, std::size_t N>
class basic_moment<T, N, with::mean>
{
public:
    using value_type = T;
    using size_type = std::size_t;

    static_assert(N > 0, "N must be larger than zero");
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    static_assert((!std::is_same<T, bool>::value), "T cannot be bool");

    basic_moment() noexcept = default;

    void clear() noexcept;
    void push(value_type value) noexcept;

    size_type capacity() const noexcept;
    bool empty() const noexcept;
    bool full() const noexcept;
    value_type mean() const noexcept;
    size_type size() const noexcept;

protected:
    struct
    {
        circular::array<value_type, N> window;
        value_type mean = value_type(0);
    } member;
};

template <typename T, std::size_t N>
class basic_moment<T, N, with::variance>
    : protected basic_moment<T, N, with::mean>
{
    using super = basic_moment<T, N, with::mean>;

public:
    using typename super::value_type;
    using typename super::size_type;

    static_assert(std::is_floating_point<T>::value, "T must be a floating-point type");

    basic_moment() noexcept;

    void clear() noexcept;
    void push(value_type value) noexcept;

    using super::capacity;
    using super::empty;
    using super::full;
    using super::mean;
    using super::size;
    value_type variance() const noexcept;
    value_type unbiased_variance() const noexcept;

protected:
    value_type delta(value_type, value_type) noexcept;

protected:
    struct
    {
        value_type variance = value_type(0);
    } sum;
};

template <typename T, std::size_t N>
using moment = basic_moment<T, N, with::mean>;

template <typename T, std::size_t N>
using moment_variance = basic_moment<T, N, with::variance>;

} // namespace window
} // namespace online
} // namespace trial

#include <trial/online/window/detail/moment.ipp>

#endif // TRIAL_ONLINE_WINDOW_MOMENT_HPP
