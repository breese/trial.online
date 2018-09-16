#ifndef TRIAL_ONLINE_MOMENT_CUMULATIVE_HPP
#define TRIAL_ONLINE_MOMENT_CUMULATIVE_HPP

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
#include <trial/online/moment/types.hpp>

namespace trial
{
namespace online
{
namespace moment
{

template <typename T, moment::type Moment>
class basic_cumulative;

template <typename T>
class basic_cumulative<T, with_mean>
{
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    static_assert((!std::is_same<T, bool>::value), "T cannot be bool");

public:
    using value_type = T;
    using size_type = std::size_t;

    void clear();
    size_type size() const;
    value_type value() const;
    value_type unbiased_value() const;
    void push(value_type);

protected:
    value_type mean = 0;
    size_type count = 0;
};

template <typename T>
class basic_cumulative<T, with_variance>
    : protected basic_cumulative<T, with_mean>
{
    using super = basic_cumulative<T, with_mean>;

public:
    using typename super::value_type;
    using typename super::size_type;

    void clear();
    using typename super::size;
    using typename super::value;
    using typename super::unbiased_value;
    value_type variance() const;
    value_type unbiased_variance() const;
    void push(value_type);

protected:
    struct
    {
        value_type variance = value_type(0);
    } sum;
};

template <typename T>
class basic_cumulative<T, with_skew>
    : protected basic_cumulative<T, with_variance>
{
    using super = basic_cumulative<T, with_variance>;

public:
    using typename super::value_type;
    using typename super::size_type;

    void clear();
    using typename super::size;
    using typename super::value;
    using typename super::variance;
    value_type skew() const;
    void push(value_type);

protected:
    struct
    {
        value_type skew = 0;
    } sum;
};
 
template <typename T>
using cumulative = basic_cumulative<T, with_mean>;

template <typename T>
using cumulative_variance = basic_cumulative<T, with_variance>;

template <typename T>
using cumulative_skew = basic_cumulative<T, with_skew>;

} // namespace moment
} // namespace online
} // namespace trial

#include <trial/online/moment/detail/cumulative.ipp>

#endif // TRIAL_ONLINE_MOMENT_CUMULATIVE_HPP
