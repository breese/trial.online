#ifndef TRIAL_ONLINE_AVERAGE_CUMULATIVE_HPP
#define TRIAL_ONLINE_AVERAGE_CUMULATIVE_HPP

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

namespace trial
{
namespace online
{
namespace average
{

template <typename T, bool WithVariance>
class basic_cumulative;

template <typename T>
class basic_cumulative<T, false>
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
class basic_cumulative<T, true>
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
    value_type mean = 0;
    value_type numerator = value_type(0);
    size_type count = 0;
};

template <typename T>
using cumulative = basic_cumulative<T, false>;

template <typename T>
using cumulative_variance = basic_cumulative<T, true>;

} // namespace average
} // namespace online
} // namespace trial

#include <trial/online/average/detail/cumulative.ipp>

#endif // TRIAL_ONLINE_AVERAGE_CUMULATIVE_HPP
