///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <iterator>

namespace trial
{
namespace online
{
namespace impulse
{

template <typename T>
template <std::size_t P, std::size_t Q>
infinite<T>::infinite(const value_type (&input_coefficients)[P],
                      const value_type (&output_coefficients)[Q],
                      value_type output_scale)
    : input{{window_type(P)}, {std::begin(input_coefficients), std::end(input_coefficients)}},
      output{{window_type(Q)}, output_scale, {std::begin(output_coefficients), std::end(output_coefficients)}}
{
}

template <typename T>
template <std::size_t P, std::size_t Q>
infinite<T>::infinite(value_type (&&input_coefficients)[P],
                      value_type (&&output_coefficients)[Q],
                      value_type output_scale)
    : input{{window_type(P)}, {std::make_move_iterator(std::begin(input_coefficients)), std::make_move_iterator(std::end(input_coefficients))}},
      output{{window_type(Q)}, output_scale, {std::make_move_iterator(std::begin(output_coefficients)), std::make_move_iterator(std::end(output_coefficients))}}
{
}

template <typename T>
void infinite<T>::clear()
{
    // Keep coefficients
    input.window.clear();
    output.window.clear();
}

template <typename T>
bool infinite<T>::empty() const
{
    return input.window.empty();
}

template <typename T>
auto infinite<T>::value() const -> value_type
{
    if (output.window.empty())
        return value_type();
    return output.window.front();
}

template <typename T>
void infinite<T>::push(value_type in)
{
    input.window.push_front(in);
    const auto feedforward = std::inner_product(input.window.begin(), input.window.end(), input.coefficients.begin(), value_type());
    const auto feedback = std::inner_product(output.window.begin(), output.window.end(), output.coefficients.begin(), value_type());
    output.window.push_front((feedforward - feedback) / output.scale);
}

} // namespace impulse
} // namespace online
} // namespace trial
