#ifndef TRIAL_ONLINE_INTERIM_MOMENT_HPP
#define TRIAL_ONLINE_INTERIM_MOMENT_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
// Copyright (C) 2019 Anna Sejersen Riis
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
namespace interim
{

namespace detail
{

template <typename T, std::size_t Window, online::with Moment, online::with UseMoment>
class basic_moment;

} // namespace detail

template <typename T, std::size_t Window, online::with Moment>
class basic_moment;

//! @brief Sliding-window mean estimator

template <typename T, std::size_t Window>
class basic_moment<T, Window, with::mean>
    : protected detail::basic_moment<T, Window, with::mean, with::mean>
{
    using super = detail::basic_moment<T, Window, with::mean, with::mean>;

public:
    using typename super::value_type;
    using typename super::size_type;

    //! @brief Resets filter.
    using super::clear;

    //! @brief Append data point.
    using super::push;

    //! @brief Returns maximum window size.
    using super::capacity;

    //! @brief Returns current window size.
    using super::size;

    //! @brief Returns true if window is empty.
    using super::empty;

    //! @brief Returns true if window is full.
    using super::full;

    //! @brief Returns biased mean.
    using super::mean;
};

//! @brief Sliding-window variance estimator

template <typename T, std::size_t Window>
class basic_moment<T, Window, with::variance>
    : protected detail::basic_moment<T, Window, with::variance, with::variance>
{
    using super = detail::basic_moment<T, Window, with::variance, with::variance>;

public:
    using typename super::value_type;
    using typename super::size_type;

    //! @brief Resets filter.
    using super::clear;

    //! @brief Append data point.
    using super::push;

    //! @brief Returns maximum window size.
    using super::capacity;

    //! @brief Returns current window size.
    using super::size;

    //! @brief Returns true if window is empty.
    using super::empty;

    //! @brief Returns true if window is full.
    using super::full;

    //! @brief Returns biased mean.
    using super::mean;

    //! @brief Returns biased variance.
    using super::variance;
};

//! @brief Sliding-window skewness estimator

template <typename T, std::size_t Window>
class basic_moment<T, Window, with::skewness>
    : protected detail::basic_moment<T, Window, with::skewness, with::skewness>
{
    using super = detail::basic_moment<T, Window, with::skewness, with::skewness>;

public:
    using typename super::value_type;
    using typename super::size_type;

    //! @brief Resets filter.
    using super::clear;

    //! @brief Append data point.
    using super::push;

    //! @brief Returns maximum window size.
    using super::capacity;

    //! @brief Returns current window size.
    using super::size;

    //! @brief Returns true if window is empty.
    using super::empty;

    //! @brief Returns true if window is full.
    using super::full;

    //! @brief Returns biased mean.
    using super::mean;

    //! @brief Returns biased variance.
    using super::variance;

    //! @brief Returns biased skewness.
    using super::skewness;
};

//! @brief Sliding-window kurtosis estimator

template <typename T, std::size_t Window>
class basic_moment<T, Window, with::kurtosis>
    : protected detail::basic_moment<T, Window, with::kurtosis, with::kurtosis>
{
    using super = detail::basic_moment<T, Window, with::kurtosis, with::kurtosis>;

public:
    using typename super::value_type;
    using typename super::size_type;

    //! @brief Resets filter.
    using super::clear;

    //! @brief Append data point.
    using super::push;

    //! @brief Returns maximum window size.
    using super::capacity;

    //! @brief Returns current window size.
    using super::size;

    //! @brief Returns true if window is empty.
    using super::empty;

    //! @brief Returns true if window is full.
    using super::full;

    //! @brief Returns biased mean.
    using super::mean;

    //! @brief Returns biased variance.
    using super::variance;

    //! @brief Returns biased skewness.
    using super::skewness;

    //! @brief Returns biased kurtosis.
    using super::kurtosis;
};

// Convenience

template <typename T, std::size_t Window>
using moment = basic_moment<T, Window, with::mean>;

template <typename T, std::size_t Window>
using moment_variance = basic_moment<T, Window, with::variance>;

template <typename T, std::size_t Window>
using moment_skewness = basic_moment<T, Window, with::skewness>;

template <typename T, std::size_t Window>
using moment_kurtosis = basic_moment<T, Window, with::kurtosis>;

} // namespace interim
} // namespace online
} // namespace trial

#include <trial/online/interim/detail/moment.ipp>

#endif // TRIAL_ONLINE_INTERIM_MOMENT_HPP
