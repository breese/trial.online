///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>

namespace trial
{
namespace online
{
namespace sampling
{

template <typename T, typename UniformRandomBitGenerator>
reservoir<T, UniformRandomBitGenerator>::reservoir(size_type N)
    : sample_size(N),
      threshold(4 * N),
      uniform(0, N - 1)
{
    samples.reserve(N);
}

template <typename T, typename UniformRandomBitGenerator>
reservoir<T, UniformRandomBitGenerator>::reservoir(size_type N,
                                                   const UniformRandomBitGenerator& g)
    : sample_size(N),
      threshold(4 * N),
      uniform(0, N - 1),
      generator(g)
{
    samples.reserve(N);
}

template <typename T, typename UniformRandomBitGenerator>
bool reservoir<T, UniformRandomBitGenerator>::empty() const
{
    return samples.empty();
}

template <typename T, typename UniformRandomBitGenerator>
auto reservoir<T, UniformRandomBitGenerator>::size() const -> size_type
{
    return samples.size();
}

template <typename T, typename UniformRandomBitGenerator>
auto reservoir<T, UniformRandomBitGenerator>::count() const -> size_type
{
    return sample_count;
}

template <typename T, typename UniformRandomBitGenerator>
void reservoir<T, UniformRandomBitGenerator>::clear()
{
    sample_count = 0;
    skip_count = 0;
}

template <typename T, typename UniformRandomBitGenerator>
bool reservoir<T, UniformRandomBitGenerator>::push(value_type element)
{
    if (sample_count >= threshold)
    {
        // Use skip count

        if (skip_count == 0)
        {
            // Determine next skip count with geometric distribution
            const typename decltype(geometric)::param_type geoparam(sample_size / double(sample_count));
            skip_count = geometric(generator, geoparam);

            // Determine sample index with uniform distribution
            const auto index = uniform(generator);
            samples[index] = element;
            ++sample_count;
            return true;
        }
        --skip_count;
    }
    else if (sample_count >= sample_size)
    {
        // Use accept-reject

        // Determine sample index with uniform distribution in range [0; sample_count)
        const typename decltype(uniform)::param_type uniparam(0, sample_count);
        const auto index = uniform(generator, uniparam);
        if (index < sample_size)
        {
            samples[index] = element;
            ++sample_count;
            return true;
        }
    }
    else
    {
        // Accept unconditionally

        assert(sample_count < sample_size);
        samples.push_back(element);
        ++sample_count;
        return true;
    }
    ++sample_count;
    return false;
}

template <typename T, typename UniformRandomBitGenerator>
auto reservoir<T, UniformRandomBitGenerator>::data() const & -> const std::vector<value_type>&
{
    return samples;
}

} // namespace sampling
} // namespace online
} // namespace trial
