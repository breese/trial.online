///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <utility>

namespace trial
{
namespace online
{
namespace interim
{

template <typename T, std::size_t W>
void basic_comoment<T, W, with::variance>::clear() noexcept
{
    active.clear();
    passive.clear();
}

template <typename T, std::size_t W>
void basic_comoment<T, W, with::variance>::push(value_type first, value_type second) noexcept
{
    const bool is_active_full = active.size() >= W;
    if (is_active_full)
    {
        std::swap(active, passive);
        active.clear();
    }
    active.push(first, second);
}

template <typename T, std::size_t W>
auto basic_comoment<T, W, with::variance>::capacity() const noexcept -> size_type
{
    return W;
}

template <typename T, std::size_t W>
auto basic_comoment<T, W, with::variance>::size() const noexcept -> size_type
{
    return (passive.size() == 0) ? active.size() : W;
}

template <typename T, std::size_t W>
bool basic_comoment<T, W, with::variance>::empty() const noexcept
{
    return size() == 0;
}

template <typename T, std::size_t W>
bool basic_comoment<T, W, with::variance>::full() const noexcept
{
    return size() == W;
}

template <typename T, std::size_t W>
auto basic_comoment<T, W, with::variance>::variance() const noexcept -> value_type
{
    if (passive.size() == 0)
        return active.variance();
    if (active.size() <= 1) // Insufficient data points to calculate variance
        return passive.variance();

    // Squared weighted combined variance
    const auto sz = active.size() - 1;
    const auto passive_weight = (W - sz) * (W - sz);
    const auto active_weight = 2 * sz;
    return (passive_weight * passive.variance() + active_weight * active.variance())
        / (passive_weight + active_weight);
}

} // namespace interim
} // namespace online
} // namespace trial
