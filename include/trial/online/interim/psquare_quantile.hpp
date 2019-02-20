///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#ifndef TRIAL_ONLINE_INTERIM_PSQUARE_QUANTILE_HPP
#define TRIAL_ONLINE_INTERIM_PSQUARE_QUANTILE_HPP

#include <trial/online/quantile/psquare.hpp>

namespace trial
{
namespace online
{
namespace interim
{

//! @brief Sliding-window quantile estimator
//!
//! Uses a leapfrogging sliding-window.
//!
//! With normal sliding-windows, once the window is full, the oldest data point
//! is removed every time a new data time is inserted.
//!
//! Leapfrogging sliding-window use a double-buffering technique where the
//! oldest data points are removed in bulk every once in a while.
//!
//! Leapfrogging uses an active and an inactive window. New data points are
//! inserted into the active window. When the active window becomes full,
//! the inactive window is cleared, and the two windows swap roles.
//!
//! The quantile is calculated as a dynamically weighted average of the
//! corresponding quantiles of the two windows. The weight depends on the
//! size of the active window; the more data point it contains, the higher
//! its weight.
//!
//! A consequence of this design is that the quantiles of the inactive window
//! gradually decays as more data is inserted, and eventually it can be removed
//! when its weight decays to zero.

template <typename T, std::size_t Window, typename... Quantiles>
class basic_psquare_quantile
{
    using QuantileList = boost::mp11::mp_sort<boost::mp11::mp_list<quantile::minimum_ratio, Quantiles..., quantile::maximum_ratio>, std::ratio_less>;

    static_assert(Window > 0, "Window must be larger than zero");
    static_assert(Window % 2 == 0, "Window must be event");

public:
    using value_type = T;
    using size_type = std::size_t;

    basic_psquare_quantile() noexcept;
    basic_psquare_quantile(const basic_psquare_quantile&) noexcept = default;
    basic_psquare_quantile(basic_psquare_quantile&&) noexcept = default;
    basic_psquare_quantile& operator= (const basic_psquare_quantile&) noexcept = default;
    basic_psquare_quantile& operator= (basic_psquare_quantile&&) noexcept = default;

    //! @brief Resets filter.

    void clear() noexcept;

    //! @brief Appends data point.

    void push(value_type input) noexcept;

    //! @brief Returns true when no data points.

    bool empty() const noexcept;

    //! @brief Returns quantile by ratio.

    template < typename Q = boost::mp11::mp_at_c<QuantileList, 1 + sizeof...(Quantiles) / 2> >
    value_type value() const noexcept;

    //! @brief Returns quantile by index.

    template <std::size_t Index = 1 + sizeof...(Quantiles) / 2>
    value_type get() const noexcept;

private:
    quantile::psquare<value_type, Quantiles...> first;
    quantile::psquare<value_type, Quantiles...> second;
    quantile::psquare<value_type, Quantiles...> *active;
    quantile::psquare<value_type, Quantiles...> *inactive;
};

template <typename T, std::size_t Window>
using psquare_median = basic_psquare_quantile<T, Window, quantile::median_ratio>;

template <typename T, std::size_t Window>
using psquare_quartile = basic_psquare_quantile<T, Window, quantile::lower_quartile_ratio, quantile::median_ratio, quantile::upper_quartile_ratio>;

} // namespace interim
} // namespace online
} // namespace trial

#include <trial/online/interim/detail/psquare_quantile.ipp>

#endif // TRIAL_ONLINE_INTERIM_PSQUARE_QUANTILE_HPP
