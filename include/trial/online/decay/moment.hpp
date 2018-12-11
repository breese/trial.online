#ifndef TRIAL_ONLINE_DECAY_MOMENT_HPP
#define TRIAL_ONLINE_DECAY_MOMENT_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/online/detail/type_traits.hpp>

namespace trial
{
namespace online
{
namespace decay
{

enum type
{
    with_mean = 1,
    with_variance = 2,
    with_skew = 3
};

template <typename T, decay::type Moment>
class basic_moment;

//! @brief Exponential smoothing with compensation for bias towards the initial value.
//!
//! See http://breese.github.io/2015/10/26/on-average.html

template <typename T>
class basic_moment<T, with_mean>
{
protected:
    static_assert(std::is_floating_point<T>::value, "T must be a floating-point type");

public:
    using value_type = T;

    basic_moment(value_type mean_factor) noexcept;

    basic_moment(const basic_moment&) = default;
    basic_moment(basic_moment&&) = default;
    basic_moment& operator= (const basic_moment&) = default;
    basic_moment& operator= (basic_moment&&) = default;

    void clear() noexcept;
    void push(value_type) noexcept;

    value_type value() const noexcept;

protected:
    const value_type mean_factor;
    value_type mean = value_type(0);
    value_type normalization = value_type(0);
};

// With variance

template <typename T>
class basic_moment<T, with_variance>
    : public basic_moment<T, with_mean>
{
protected:
    using super = basic_moment<T, with_mean>;

public:
    using typename super::value_type;

    basic_moment(value_type mean_factor, value_type var_factor) noexcept;

    basic_moment(const basic_moment&) = default;
    basic_moment(basic_moment&&) = default;
    basic_moment& operator= (const basic_moment&) = default;
    basic_moment& operator= (basic_moment&&) = default;

    void clear() noexcept;
    void push(value_type) noexcept;

    using super::value;
    value_type variance() const noexcept;

protected:
    const value_type var_factor;
    struct
    {
        value_type variance = value_type(0);
    } sum;
    value_type normalization = value_type(0);
};

// With skewness

template <typename T>
class basic_moment<T, with_skew>
    : public basic_moment<T, with_variance>
{
protected:
    using super = basic_moment<T, with_variance>;

public:
    using typename super::value_type;

    basic_moment(value_type mean_factor, value_type var_factor, value_type skew_factor) noexcept;

    basic_moment(const basic_moment&) = default;
    basic_moment(basic_moment&&) = default;
    basic_moment& operator= (const basic_moment&) = default;
    basic_moment& operator= (basic_moment&&) = default;

    void clear() noexcept;
    void push(value_type) noexcept;

    using super::value;
    using super::variance;
    value_type skew() const noexcept;

protected:
    const value_type skew_factor;
    struct
    {
        value_type skew = value_type(0);
    } sum;
    value_type normalization = value_type(0);
};

// Convenience

template <typename T>
using moment = basic_moment<T, with_mean>;

template <typename T>
using moment_variance = basic_moment<T, with_variance>;

template <typename T>
using moment_skew = basic_moment<T, with_skew>;

} // namespace decay
} // namespace online
} // namespace trial

#include <trial/online/decay/detail/moment.ipp>

#endif // TRIAL_ONLINE_DECAY_MOMENT_HPP
