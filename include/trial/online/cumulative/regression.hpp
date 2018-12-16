#ifndef TRIAL_ONLINE_CUMULATIVE_REGRESSION_HPP
#define TRIAL_ONLINE_CUMULATIVE_REGRESSION_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

// https://en.wikipedia.org/wiki/Simple_linear_regression

#include <cstddef>
#include <type_traits>
#include <trial/online/cumulative/covariance.hpp>

namespace trial
{
namespace online
{
namespace cumulative
{

//! @brief Online approximation of simple linear regression.
//!
//! Executes in constant time and space. No heap allocations are performed.

template <typename T>
class regression
{
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
    class covariance<value_type> covariance;
    basic_moment<value_type, with::variance> x_moment;
    basic_moment<value_type, with::variance> y_moment;
};

} // namespace cumulative
} // namespace online
} // namespace trial

#include <trial/online/cumulative/detail/regression.ipp>

#endif // TRIAL_ONLINE_CUMULATIVE_REGRESSION_HPP
