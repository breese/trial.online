#ifndef TRIAL_ONLINE_WINDOW_REGRESSION_HPP
#define TRIAL_ONLINE_WINDOW_REGRESSION_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cstddef>
#include <type_traits>
#include <trial/online/window/moment.hpp>
#include <trial/online/window/comoment.hpp>

namespace trial
{
namespace online
{
namespace window
{

template <typename T, std::size_t Window>
class regression
    : protected basic_comoment<T, Window, with::variance>
{
    using covariance = basic_comoment<T, Window, with::variance>;

    static_assert(std::is_floating_point<T>::value, "T must be an floating-point type");

public:
    using value_type = T;
    using size_type = std::size_t;

    void clear() noexcept;
    size_type size() const noexcept;

    //! @brief Append data point.

    void push(value_type x, value_type y) noexcept;

    //! @brief Predicts value at postion.
    //!
    //! at(0) is the intercept where the regression line crosses the y axis.
    //!
    //! @returns Predicted value at given position.

    value_type at(value_type position) const noexcept;

    //! @brief Regression slope.
    //!
    //! @returns Slope of the regression line.

    value_type slope() const noexcept;

private:
    basic_moment<value_type, Window, with::variance> x_moment;
};

} // namespace window
} // namespace online
} // namespace trial

#include <trial/online/window/detail/regression.ipp>

#endif // TRIAL_ONLINE_WINDOW_REGRESSION_HPP
