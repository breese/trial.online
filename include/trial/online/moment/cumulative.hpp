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
    void push(value_type);

private:
    value_type mean = 0;
    size_type count = 0;
};

template <typename T>
class basic_cumulative<T, with_variance>
{
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    static_assert((!std::is_same<T, bool>::value), "T cannot be bool");

public:
    using value_type = T;
    using size_type = std::size_t;

    void clear();
    size_type size() const;
    value_type value() const;
    value_type variance() const;
    void push(value_type);

private:
    basic_cumulative<value_type, with_mean> mean;
    value_type numerator = value_type(0);
};

template <typename T>
using cumulative = basic_cumulative<T, with_mean>;

template <typename T>
using cumulative_variance = basic_cumulative<T, with_variance>;

} // namespace moment
} // namespace online
} // namespace trial

#include <trial/online/moment/detail/cumulative.ipp>

#endif // TRIAL_ONLINE_MOMENT_CUMULATIVE_HPP
