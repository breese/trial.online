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

#include <trial/online/moment/cumulative.hpp>
#include <trial/online/covariance/cumulative.hpp>

namespace trial
{
namespace online
{
namespace correlation
{

template <typename T, template <typename, moment::type> class F>
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
    covariance::basic_cumulative<value_type, F> covariance;
    F<value_type, moment::with_variance> x_moment;
    F<value_type, moment::with_variance> y_moment;
};

template <typename T>
using pearson = basic_pearson<T, moment::basic_cumulative>;

} // namespace correlation
} // namespace online
} // namespace trial

#include <trial/online/correlation/detail/pearson.ipp>

#endif // TRIAL_ONLINE_CORRELATION_PEARSON_HPP
