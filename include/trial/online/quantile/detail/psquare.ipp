///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2016 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cmath>
#include <algorithm>
#include <numeric>

namespace trial
{
namespace online
{
namespace quantile
{

template <typename T, typename... Quantiles>
constexpr T psquare<T, Quantiles...>::quantiles[];

template <typename T, typename... Quantiles>
psquare<T, Quantiles...>::parameter_type::parameter_type(size_type position,
                                                         value_type height) noexcept
    : position(position),
      height(height)
{
}

template <typename T, typename... Quantiles>
psquare<T, Quantiles...>::psquare() noexcept
{
    initialize();
}

template <typename T, typename... Quantiles>
void psquare<T, Quantiles...>::initialize() noexcept
{
    count = 0;

    constant_deltas[0] = 0;
    for (size_type i = 0; i < quantile_length; ++i)
    {
        constant_deltas[2 * i + 2] = quantiles[i];
        constant_deltas[2 * i + 1] = (constant_deltas[2 * i] + constant_deltas[2 * i + 2]) / 2;
    }
    constant_deltas[2 * quantile_length + 2] = 1;
    constant_deltas[2 * quantile_length + 1] = (constant_deltas[2 * quantile_length] + constant_deltas[2 * quantile_length + 2]) / 2;

    std::iota(positions.begin(), positions.end(), 1);
    std::uninitialized_fill(heights.begin(), heights.end(), 0);

    for (size_type i = 0; i < desired_positions.size(); ++i)
    {
        desired_positions[i] = 1 + 2 * (quantile_length + 1) * constant_deltas[i];
    }
}

template <typename T, typename... Quantiles>
void psquare<T, Quantiles...>::clear() noexcept
{
    initialize();
}

template <typename T, typename... Quantiles>
bool psquare<T, Quantiles...>::empty() const noexcept
{
    return (count == 0);
}

template <typename T, typename... Quantiles>
void psquare<T, Quantiles...>::push(value_type number) noexcept
{
    if (count >= parameter_length)
    {
        size_type k = 1;
        if (number < heights[0])
        {
            heights[0] = number;
        }
        else if (number >= heights[parameter_length - 1])
        {
            k = parameter_length - 1;
            heights[k] = number;
        }
        else
        {
            k = std::distance(heights.begin(), std::upper_bound(heights.begin(), heights.end(), number));
        }


        for (size_type i = 0; i < k; ++i)
        {
            desired_positions[i] += constant_deltas[i];
        }
        for (size_type i = k; i < parameter_length; ++i)
        {
            positions[i] += 1;
            desired_positions[i] += constant_deltas[i];
        }
        for (size_type i = 1; i <= parameter_length - 2; ++i)
        {
            const value_type deviation = desired_positions[i] - positions[i];
            const int sign = (deviation > 0) ? 1 : ((deviation < 0) ? -1 : 0);
            if (((sign == 1) && ((positions[i + 1] - positions[i]) > 1)) ||
                ((sign == -1) && ((positions[i] - positions[i - 1]) > 1)))
            {
                const value_type height = parabolic(i, sign);
                if ((heights[i - 1] < height) && (height < heights[i + 1]))
                {
                    heights[i] = height;
                }
                else
                {
                    heights[i] = linear(i, sign);
                }
                positions[i] += sign;
            }
        }
    }
    else
    {
        // Insert number in a sorted order

        size_type k = count;
        while ((k > 0) && (heights[k - 1] > number))
        {
            heights[k] = heights[k - 1];
            --k;
        }
        heights[k] = number;
    }
    ++count;
}

template <typename T, typename... Quantiles>
template <typename Q>
typename psquare<T, Quantiles...>::value_type
psquare<T, Quantiles...>::value() const noexcept
{
    using index_type = boost::mp11::mp_find<QuantileList, Q>;

    return get<index_type::value>();
}

template <typename T, typename... Quantiles>
template <std::size_t Index>
typename psquare<T, Quantiles...>::value_type
psquare<T, Quantiles...>::get() const noexcept
{
    static_assert((Index <= boost::mp11::mp_find<QuantileList, maximum_ratio>::value), "Index must be within range");

    // The p-square algorithm assumes that we have more than @c parameter_length
    // observations.
    //
    // For fewer observations we assume that the array contains all observations
    // and that they are sorted; then we can use the rank to find the value.

    if (count > parameter_length)
    {
        return heights[2 * Index];
    }
    else if (count > 1)
    {
        switch (Index)
        {
        case 0:
            // minimum
            return heights[0];

        case 1 + sizeof...(Quantiles):
            // maximum
            return heights[count - 1];

        default:
            {
                // Use linear interpolation because of later switch to continuous approximations
                const auto rank = (count - 1) * quantiles[Index - 1];
                const auto slope = rank - std::floor(rank);
                return heights[rank] + slope * (heights[rank + 1] - heights[rank]);
            }
        }
    }
    else if (count > 0)
    {
        return heights[count - 1];
    }
    else
    {
        return {};
    }
}

template <typename T, typename... Quantiles>
std::vector<typename psquare<T, Quantiles...>::parameter_type>
psquare<T, Quantiles...>::parameters() const
{
    std::vector<parameter_type> result;
    for (size_type i = 0; i < parameter_length; ++i)
    {
        result.emplace_back(positions[i],
                            heights[i]);
    }
    return result;
}

template <typename T, typename... Quantiles>
void psquare<T, Quantiles...>::parameters(const std::vector<parameter_type>& data) noexcept
{
    for (size_type i = 0; i < parameter_length; ++i)
    {
        positions[i] = desired_positions[i] = data[i].position;
        heights[i] = data[i].height;
    }
    // Nudge past special handling
    count = parameter_length;
}

template <typename T, typename... Quantiles>
typename psquare<T, Quantiles...>::value_type
psquare<T, Quantiles...>::linear(size_type index, int sign) const noexcept
{
    assert(index > 0);
    assert(index < parameter_length);
    assert(sign == 1 || sign == -1);

    return heights[index]
        + sign * ((heights[index + sign] - heights[index]) / value_type(positions[index + sign] - positions[index]));
}

template <typename T, typename... Quantiles>
typename psquare<T, Quantiles...>::value_type
psquare<T, Quantiles...>::parabolic(size_type index, int sign) const noexcept
{
    assert(index > 0);
    assert(index < parameter_length);
    assert(sign == 1 || sign == -1);
    assert(positions[index - 1] <= positions[index]);
    assert(positions[index] <= positions[index + 1]);

    const value_type previous_height = heights[index - 1];
    const value_type current_height = heights[index];
    const value_type next_height = heights[index + 1];
    const size_type forward_step = positions[index + 1] - positions[index];
    const size_type backward_step = positions[index] - positions[index - 1];
    const size_type total_step = positions[index + 1] - positions[index - 1];

    return current_height
        + (sign / value_type(total_step))
        * (((backward_step + sign) * ((next_height - current_height) / value_type(forward_step)))
           + ((forward_step - sign) * ((current_height - previous_height) / value_type(backward_step))));
}

} // namespace quantile
} // namespace online
} // namespace trial
