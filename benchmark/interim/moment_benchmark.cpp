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
#include <trial/online/interim/moment.hpp>

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

template <std::size_t Window>
void interim_mean(benchmark::State& state)
{
    auto values = dataset<double>(datasize);
    trial::online::interim::moment<double, Window> filter;
    std::size_t k = 0;
    for (auto _ : state)
    {
        filter.push(values[k % values.size()]);
        benchmark::DoNotOptimize(filter.mean());
        ++k;
    }
}

template <std::size_t Window>
void interim_variance(benchmark::State& state)
{
    auto values = dataset<double>(datasize);
    trial::online::interim::moment_variance<double, Window> filter;
    std::size_t k = 0;
    for (auto _ : state)
    {
        filter.push(values[k % values.size()]);
        benchmark::DoNotOptimize(filter.variance());
        ++k;
    }
}

BENCHMARK_TEMPLATE(interim_mean, 2);
BENCHMARK_TEMPLATE(interim_variance, 2);

BENCHMARK_TEMPLATE(interim_mean, 16);
BENCHMARK_TEMPLATE(interim_variance, 16);

BENCHMARK_TEMPLATE(interim_mean, 256);
BENCHMARK_TEMPLATE(interim_variance, 256);

BENCHMARK_TEMPLATE(interim_mean, 4096);
BENCHMARK_TEMPLATE(interim_variance, 4096);

BENCHMARK_MAIN();
