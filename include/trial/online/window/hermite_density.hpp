#ifndef TRIAL_ONLINE_WINDOW_HERMITE_DENSITY_HPP
#define TRIAL_ONLINE_WINDOW_HERMITE_DENSITY_HPP

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
#include <trial/online/window/moment.hpp>

namespace trial
{
namespace online
{
namespace window
{

template <typename T, std::size_t Window, std::size_t Precision = 6>
using hermite_density = detail::hermite_density<T,
                                                Precision,
                                                online::with::density,
                                                window::moment<T, Window>>;

template <typename T, std::size_t Window, std::size_t Precision = 6>
using hermite_cumulated_density = detail::hermite_density<T,
                                                          Precision,
                                                          online::with::cumulation,
                                                          window::moment<T, Window>>;

} // namespace window
} // namespace online
} // namespace trial

#endif // TRIAL_ONLINE_WINDOW_HERMITE_DENSITY_HPP
