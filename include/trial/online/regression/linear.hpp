#ifndef TRIAL_ONLINE_REGRESSION_LINIEAR_HPP
#define TRIAL_ONLINE_REGRESSION_LINIEAR_HPP

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
#include <trial/online/moment/types.hpp>
#include <trial/online/correlation/covariance.hpp>

namespace trial
{
namespace online
{
namespace regression
{

//! @brief Online approximation of simple linear regression.
//!
//! Executes in constant time and space. No heap allocations are performed.

template <typename T, template <typename, moment::type> class Avg>
class basic_linear
{
    static_assert(std::is_floating_point<T>::value, "T must be an floating-point type");

public:
    using value_type = T;
    using size_type = std::size_t;

    void clear();
    size_type size() const;

    //! @brief Append data point.

    void push(value_type x, value_type y);

    //! @brief Regression slope.
    //!
    //! @returns Slope of the regression line.

    value_type slope() const;

    //! @brief Regression intercept.
    //!
    //! @returns Where regression line crosses the y axis.

    value_type intercept() const;

    //! @brief Regression correlation.
    //!
    //! @returns Correlation between x and y.

    value_type correlation() const;

private:
    correlation::basic_covariance<value_type, Avg> covariance;
    Avg<value_type, moment::with_variance> x_moment;
    Avg<value_type, moment::with_variance> y_moment;
};

template <typename T, template <typename, moment::type> class Avg>
using linear = basic_linear<T, Avg>;

} // namespace regression
} // namespace online
} // namespace trial

#include <trial/online/regression/detail/linear.ipp>

#endif // TRIAL_ONLINE_REGRESSION_LINIEAR_HPP
