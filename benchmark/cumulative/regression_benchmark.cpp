///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <random>
#include <algorithm>
#include <benchmark/benchmark.h>
#include <trial/online/cumulative/regression.hpp>

const std::size_t datasize = 1<<15;

template <typename T>
std::vector<T> dataset(std::size_t size)
{
    std::vector<T> values(size);
    std::random_device device;
    std::default_random_engine generator(device());
    std::normal_distribution<T> distribution(0.0);
    std::generate(values.begin(), values.end(), [&] { return distribution(generator); });
    return values;
}

void cumulative_push(benchmark::State& state)
{
    auto values = dataset<double>(datasize);
    trial::online::cumulative::regression<double> filter;
    std::size_t k = 0;
    for (auto _ : state)
    {
        filter.push(k, values[k % values.size()]);
        benchmark::DoNotOptimize(filter.at(0.5));
        ++k;
    }
}

BENCHMARK(cumulative_push);

void cumulative_intercept(benchmark::State& state)
{
    auto values = dataset<double>(datasize);
    trial::online::cumulative::regression<double> filter;
    for (auto&& value : values)
    {
        filter.push(value, value);
    }
    std::size_t k = 0;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(filter.at(0.0));
        ++k;
    }
}

BENCHMARK(cumulative_intercept);

BENCHMARK_MAIN();
