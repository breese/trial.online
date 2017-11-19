#ifndef TRIAL_ONLINE_SAMPLING_RESERVOIR_HPP
#define TRIAL_ONLINE_SAMPLING_RESERVOIR_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

// Vitter, "An Efficient Algorithm for Sequential Random Sampling", ACM
//   Transactions on Mathematical Software, 13(1), pp. 58-67, 1987.
//
// Erlandson, "Very Fast Reservoir Sampling",
//   http://erikerlandson.github.io/blog/2015/11/20/very-fast-reservoir-sampling/

#include <cstddef>
#include <type_traits>
#include <random>
#include <vector>

namespace trial
{
namespace online
{
namespace sampling
{

// Choose a sample of N items from a set of sequentially added items.
template <typename T, typename UniformRandomBitGenerator>
class reservoir
{
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    static_assert((!std::is_same<T, bool>::value), "T cannot be bool");

public:
    using value_type = T;
    using size_type = std::size_t;

    reservoir(size_type N);
    reservoir(size_type N, const UniformRandomBitGenerator& g);

    bool empty() const;
    size_type size() const;
    size_type count() const;

    void clear();

    // Returns true if sample is changed.
    bool push(value_type);

    const std::vector<value_type>& data() const &;

private:
    const size_type sample_size;
    const size_type threshold;
    std::uniform_int_distribution<size_type> uniform;
    std::geometric_distribution<size_type> geometric;
    UniformRandomBitGenerator generator;
    size_type sample_count {0};
    size_type skip_count {0};
    std::vector<value_type> samples;
};

template <typename T>
using reservoir_default = reservoir<T, std::default_random_engine>;

} // namespace sampling
} // namespace online
} // namespace trial

#include <trial/online/sampling/detail/reservoir.ipp>

#endif // TRIAL_ONLINE_SAMPLING_RESERVOIR_HPP
