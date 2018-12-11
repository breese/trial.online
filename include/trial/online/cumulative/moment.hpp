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

    void clear();
    void push(value_type);

    size_type size() const;
    value_type value() const;
    value_type unbiased_value() const;

protected:
    value_type mean = 0;
    size_type count = 0;
};

template <typename T>
class basic_moment<T, with::variance>
    : protected basic_moment<T, with::mean>
{
    using super = basic_moment<T, with::mean>;

public:
    using typename super::value_type;
    using typename super::size_type;

    void clear();
    void push(value_type);

    using super::size;
    using super::value;
    using super::unbiased_value;
    value_type variance() const;
    value_type unbiased_variance() const;

protected:
    struct
    {
        value_type variance = value_type(0);
    } sum;
};

template <typename T>
class basic_moment<T, with::skew>
    : protected basic_moment<T, with::variance>
{
    using super = basic_moment<T, with::variance>;

public:
    using typename super::value_type;
    using typename super::size_type;

    void clear();
    void push(value_type);

    using super::size;
    using super::value;
    using super::unbiased_value;
    using super::variance;
    using super::unbiased_variance;
    value_type skew() const;
    value_type unbiased_skew() const;

protected:
    struct
    {
        value_type skew = 0;
    } sum;
};
 
template <typename T>
using moment = basic_moment<T, with::mean>;

template <typename T>
using moment_variance = basic_moment<T, with::variance>;

template <typename T>
using moment_skew = basic_moment<T, with::skew>;

} // namespace cumulative
} // namespace online
} // namespace trial

#include <trial/online/cumulative/detail/moment.ipp>

#endif // TRIAL_ONLINE_CUMULATIVE_MOMENT_HPP
