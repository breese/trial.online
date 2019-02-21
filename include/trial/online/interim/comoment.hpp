#ifndef TRIAL_ONLINE_INTERIM_COMOMENT_HPP
#define TRIAL_ONLINE_INTERIM_COMOMENT_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/online/cumulative/comoment.hpp>

namespace trial
{
namespace online
{
namespace interim
{

template <typename T, std::size_t Window, online::with Moment>
class basic_comoment;

//! @brief Sliding-window covariance estimator

template <typename T, std::size_t Window>
class basic_comoment<T, Window, with::variance>
{
    static_assert(std::is_floating_point<T>::value, "T must be an floating-point type");

public:
    using value_type = T;
    using size_type = std::size_t;

    //! @brief Resets filter.
    void clear() noexcept;

    //! @brief Appends data point.
    void push(value_type first, value_type second) noexcept;

    //! @brief Returns maximum window size.
    size_type capacity() const noexcept;

    //! @brief Returns current window size.
    size_type size() const noexcept;

    //! @brief Returns true if window is empty.
    bool empty() const noexcept;

    //! @brief Returns true if window is full.
    bool full() const noexcept;

    //! @brief Returns covariance.
    value_type variance() const noexcept;

protected:
    cumulative::basic_comoment<value_type, with::variance> active;
    cumulative::basic_comoment<value_type, with::variance> passive;
};

// Convenience

template <typename T, std::size_t Window>
using covariance = basic_comoment<T, Window, with::variance>;

} // namespace interim
} // namespace online
} // namespace trial

#include <trial/online/interim/detail/comoment.ipp>

#endif // TRIAL_ONLINE_INTERIM_COMOMENT_HPP
