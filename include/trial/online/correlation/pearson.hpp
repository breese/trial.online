#ifndef TRIAL_ONLINE_CORRELATION_PEARSON_HPP
#define TRIAL_ONLINE_CORRELATION_PEARSON_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

// https://en.wikipedia.org/wiki/Pearson_correlation_coefficient

#include <trial/online/average/cumulative_variance.hpp>
#include <trial/online/correlation/covariance.hpp>

namespace trial
{
namespace online
{
namespace correlation
{

template <typename T, template <typename> class Avg>
class basic_pearson
{
    static_assert(std::is_floating_point<T>::value, "T must be a floating-point type");

public:
    using value_type = T;
    using size_type = std::size_t;

    void clear();
    size_type size() const;
    void push(value_type, value_type);
    value_type value() const;

private:
    correlation::covariance<value_type> covariance;
    Avg<value_type> average_x;
    Avg<value_type> average_y;
};

template <typename T>
using pearson = basic_pearson<T, average::cumulative_variance>;

} // namespace correlation
} // namespace online
} // namespace trial

#include <trial/online/correlation/detail/pearson.ipp>

#endif // TRIAL_ONLINE_CORRELATION_PEARSON_HPP
