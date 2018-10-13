#ifndef TRIAL_ONLINE_CUMULATIVE_COVARIANCE_HPP
#define TRIAL_ONLINE_CUMULATIVE_COVARIANCE_HPP

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
#include <trial/online/cumulative/moment.hpp>

// https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance

namespace trial
{
namespace online
{
namespace cumulative
{

template <typename T>
class covariance
{
public:
    using value_type = T;
    using size_type = std::size_t;
    
    static_assert(std::is_floating_point<T>::value, "T must be an floating-point type");

    void clear();
    void push(value_type first, value_type second);

    size_type size() const;
    value_type value() const;
    value_type unbiased_value() const;

private:
    basic_moment<value_type, with_mean> x_moment;
    basic_moment<value_type, with_mean> y_moment;
    value_type co_moment = value_type(0);
};

} // namespace cumulative
} // namespace online
} // namespace trial

#include <trial/online/cumulative/detail/covariance.ipp>

#endif // TRIAL_ONLINE_CUMULATIVE_COVARIANCE_HPP
