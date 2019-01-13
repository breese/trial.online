#ifndef TRIAL_ONLINE_CUMULATIVE_MOMENT_HPP
#define TRIAL_ONLINE_CUMULATIVE_MOMENT_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

// Philippe Pebay, "Formulas for Robust, One-Pass Parallel Computation of
//   Covariances and Arbitrary-Order Statistical Moments", technical
//   report SAND2008-6212, 2008.

#include <cstddef> // std::size_t
#include <type_traits>
#include <trial/online/with.hpp>

namespace trial
{
namespace online
{
namespace cumulative
{

template <typename T, online::with Moment>
class basic_moment;

template <typename T>
class basic_moment<T, with::mean>
{
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    static_assert((!std::is_same<T, bool>::value), "T cannot be bool");

public:
    using value_type = T;
    using size_type = std::size_t;

    void clear() noexcept;
    void push(value_type) noexcept;

    size_type size() const noexcept;
    value_type mean() const noexcept;
    value_type unbiased_mean() const noexcept;

protected:
    struct
    {
        value_type mean = 0;
        size_type count = 0;
    } member;
};

// With variance

template <typename T>
class basic_moment<T, with::variance>
    : protected basic_moment<T, with::mean>
{
protected:
    using super = basic_moment<T, with::mean>;

public:
    using typename super::value_type;
    using typename super::size_type;

    void clear() noexcept;
    void push(value_type) noexcept;

    using super::size;
    using super::mean;
    using super::unbiased_mean;
    value_type variance() const noexcept;
    value_type unbiased_variance() const noexcept;

protected:
    struct
    {
        value_type variance = value_type(0);
    } sum;
};

// With skewness

template <typename T>
class basic_moment<T, with::skewness>
    : protected basic_moment<T, with::variance>
{
protected:
    using super = basic_moment<T, with::variance>;

public:
    using typename super::value_type;
    using typename super::size_type;

    void clear() noexcept;
    void push(value_type) noexcept;

    using super::size;
    using super::mean;
    using super::unbiased_mean;
    using super::variance;
    using super::unbiased_variance;
    value_type skewness() const noexcept;
    value_type unbiased_skewness() const noexcept;

protected:
    struct
    {
        value_type skewness = 0;
    } sum;
};

// With kurtosis

template <typename T>
class basic_moment<T, with::kurtosis>
    : public basic_moment<T, with::skewness>
{
protected:
    using super = basic_moment<T, with::skewness>;

public:
    using typename super::value_type;
    using typename super::size_type;

    void clear() noexcept;
    void push(value_type) noexcept;

    using super::mean;
    using super::unbiased_mean;
    using super::variance;
    using super::unbiased_variance;
    using super::skewness;
    using super::unbiased_skewness;
    value_type kurtosis() const noexcept;
    value_type unbiased_kurtosis() const noexcept;

protected:
    struct
    {
        value_type kurtosis = value_type(0);
    } sum;
};

// Convenience

template <typename T>
using moment = basic_moment<T, with::mean>;

template <typename T>
using moment_variance = basic_moment<T, with::variance>;

template <typename T>
using moment_skewness = basic_moment<T, with::skewness>;

template <typename T>
using moment_kurtosis = basic_moment<T, with::kurtosis>;

} // namespace cumulative
} // namespace online
} // namespace trial

#include <trial/online/cumulative/detail/moment.ipp>

#endif // TRIAL_ONLINE_CUMULATIVE_MOMENT_HPP
