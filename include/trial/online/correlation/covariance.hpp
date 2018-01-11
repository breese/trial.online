#ifndef TRIAL_ONLINE_CORRELATION_COVARIANCE_HPP
#define TRIAL_ONLINE_CORRELATION_COVARIANCE_HPP

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
#include <trial/online/average/cumulative.hpp>

// https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance

namespace trial
{
namespace online
{
namespace correlation
{

template <typename T, template <typename, bool> class Avg>
class basic_covariance
{
public:
    using value_type = T;
    using size_type = std::size_t;
    
    static_assert(std::is_floating_point<T>::value, "T must be an floating-point type");

    size_type size() const;
    void clear();
    void push(value_type first, value_type second);
    value_type value() const;

private:
    Avg<value_type, false> average_x;
    Avg<value_type, false> average_y;
    value_type cov = value_type(0);
};

template <typename T>
using covariance = basic_covariance<T, average::basic_cumulative>;

} // namespace correlation
} // namespace online
} // namespace trial

#include <trial/online/correlation/detail/covariance.ipp>

#endif // TRIAL_ONLINE_CORRELATION_COVARIANCE_HPP
