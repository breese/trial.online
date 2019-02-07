#ifndef TRIAL_ONLINE_QUANTILE_PSQUARE_HPP
#define TRIAL_ONLINE_QUANTILE_PSQUARE_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2016 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

// Jain and Chlamtac, "The [Piecewise-parabolic Prediction]-Square Algorithm
//   for Dynamic Calculation of Percentiles and Histograms without Storing
//   Observations", Communications of the ACM, 28(10), pp. 1076-1086, 1985.
//
// Raatikainen, "Sequential Procedure for Simultaneous Estimation of Several
//   Percentiles", Transactions of the Society for Computer Simulations, 7(1),
//   pp. 21-44, 1990.

#include <cstddef> // std::size_t
#include <vector>
#include <array>
#include <ratio>
#include <boost/mp11/list.hpp>
#include <boost/mp11/algorithm.hpp>
#include <trial/online/detail/type_traits.hpp>

namespace trial
{
namespace online
{
namespace quantile
{

using minimum_ratio = std::ratio<0, 1>;
using maximum_ratio = std::ratio<1, 1>;

template <typename T, typename... Quantiles>
class psquare
{
    static_assert(std::is_floating_point<T>::value, "T must be a floating-point type");
    static_assert((sizeof...(Quantiles) > 0), "There must be at least one quantile");

    using QuantileList = boost::mp11::mp_sort<boost::mp11::mp_list<minimum_ratio, Quantiles..., maximum_ratio>, std::ratio_less>;
    static_assert(boost::mp11::mp_all_of<QuantileList, detail::is_ratio>::value, "Quantiles must be ratios");

public:
    using value_type = T;
    using size_type = std::size_t;

    psquare();
    psquare(const psquare&);

    void clear();
    bool empty() const;

    void push(value_type);

    // Get value by type.
    // Select middle quantile parameter by default.
    template < typename Q = boost::mp11::mp_at_c<QuantileList, 1 + sizeof...(Quantiles) / 2> >
    value_type value() const;

    // Get value by index.
    template <std::size_t Index = 1 + sizeof...(Quantiles) / 2>
    value_type get() const;

    struct parameter_type
    {
        parameter_type(size_type position,
                       value_type height);

        bool operator== (const parameter_type& other)
        {
            return ((position == other.position) &&
                    (height == other.height));
        }

        size_type position;
        value_type height;
    };
    std::vector<parameter_type> parameters() const;
    void parameters(const std::vector<parameter_type>&);

private:
    void initialize();
    value_type linear(size_type, int) const;
    value_type parabolic(size_type, int) const;

private:
    static constexpr size_type quantile_length = sizeof...(Quantiles);
    static constexpr size_type parameter_length = 2 * quantile_length + 3;
    static constexpr value_type quantiles[quantile_length] = { (Quantiles::num / value_type(Quantiles::den))... };

    size_type count {0};
    std::array<size_type, parameter_length> positions;
    std::array<value_type, parameter_length> heights;
    std::array<value_type, parameter_length> desired_positions;
    std::array<value_type, parameter_length> constant_deltas;
};

// Convenience types
using median_ratio = std::ratio<1, 2>;
using lower_quartile_ratio = std::ratio<1, 4>;
using upper_quartile_ratio = std::ratio<3, 4>;

template <typename T> using psquare_median = psquare<T, median_ratio>;
template <typename T> using psquare_quartile = psquare<T, lower_quartile_ratio, median_ratio, upper_quartile_ratio>;

} // namespace quantile
} // namespace online
} // namespace trial

#include <trial/online/quantile/detail/psquare.ipp>

#endif // TRIAL_ONLINE_QUANTILE_PSQUARE_HPP
