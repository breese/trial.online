#ifndef TRIAL_ONLINE_CUMULATIVE_DENSITY_ESTIMATOR_HPP
#define TRIAL_ONLINE_CUMULATIVE_DENSITY_ESTIMATOR_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/online/detail/hermite_density.hpp>
#include <trial/online/cumulative/moment.hpp>

namespace trial
{
namespace online
{
namespace cumulative
{

template <typename T, std::size_t Precision = 6>
using hermite_density = online::detail::hermite_density<T,
                                                        Precision,
                                                        online::with::density,
                                                        cumulative::moment<T>>;

template <typename T, std::size_t Precision = 6>
using hermite_cumulated_density = online::detail::hermite_density<T,
                                                                  Precision,
                                                                  online::with::cumulation,
                                                                  cumulative::moment<T>>;

} // namespace cumulative
} // namespace online
} // namespace trial

#endif // TRIAL_ONLINE_CUMULATIVE_DENSITY_ESTIMATOR_HPP
