#ifndef TRIAL_ONLINE_CUMULATIVE_COMOMENT_HPP
#define TRIAL_ONLINE_CUMULATIVE_COMOMENT_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/online/cumulative/moment.hpp>

namespace trial
{
namespace online
{
namespace cumulative
{

template <typename T, online::with Moment>
class basic_comoment;

// Covariance

template <typename T>
class basic_comoment<T, with::variance>
{
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    static_assert((!std::is_same<T, bool>::value), "T cannot be bool");

public:
    using value_type = T;
    using size_type = std::size_t;

    void clear() noexcept;
    void push(value_type, value_type) noexcept;

    size_type size() const noexcept;
    value_type variance() const noexcept;
    value_type unbiased_variance() const noexcept;

protected:
    cumulative::basic_moment<value_type, with::mean> x_center;
    cumulative::basic_moment<value_type, with::mean> y_center;
    value_type center {0};
};

// Convenience

template <typename T>
using comean = basic_comoment<T, with::mean>;

template <typename T>
using covariance = basic_comoment<T, with::variance>;

} // namespace cumulative
} // namespace online
} // namespace trial

#include <trial/online/cumulative/detail/comoment.ipp>

#endif // TRIAL_ONLINE_CUMULATIVE_COMOMENT_HPP
