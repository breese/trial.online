#ifndef TRIAL_ONLINE_INTERIM_REGRESSION_HPP
#define TRIAL_ONLINE_INTERIM_REGRESSION_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/online/interim/moment.hpp>
#include <trial/online/interim/comoment.hpp>

namespace trial
{
namespace online
{
namespace interim
{

template <typename T, std::size_t Window>
class regression
    : protected basic_comoment<T, Window, with::variance>
{
    using covariance = basic_comoment<T, Window, with::variance>;

public:
    using value_type = T;
    using size_type = std::size_t;

    //! @brief Resets filter.

    void clear() noexcept;

    //! @brief Appends data point.

    void push(value_type x, value_type y) noexcept;

    //! @brief Returns current window size.

    using covariance::size;

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
    interim::basic_moment<value_type, Window, with::variance> x_moment;
    interim::basic_moment<value_type, Window, with::mean> y_moment;
};

} // namespace interim
} // namespace online
} // namespace trial

#include <trial/online/interim/detail/regression.ipp>

#endif // TRIAL_ONLINE_INTERIM_REGRESSION_HPP
