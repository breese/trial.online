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

// https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance

namespace trial
{
namespace online
{
namespace correlation
{

template <typename T>
class covariance
{
public:
    using value_type = T;
    using size_type = std::size_t;
    
    static_assert(std::is_floating_point<T>::value, "T must be an floating-point type");

    covariance();

    size_type size() const;
    void clear();
    void push(value_type first, value_type second);
    value_type value() const;

private:
    value_type x_mean = value_type(0);
    value_type y_mean = value_type(0);
    value_type cov = value_type(0);
    size_type count = size_type(0);
};

} // namespace correlation
} // namespace online
} // namespace trial

#include <trial/online/correlation/detail/covariance.ipp>

#endif // TRIAL_ONLINE_CORRELATION_COVARIANCE_HPP
