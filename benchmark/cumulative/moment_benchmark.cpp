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
#include <trial/online/cumulative/moment.hpp>

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

void cumulative_mean(benchmark::State& state)
{
    auto values = dataset<double>(datasize);
    trial::online::cumulative::moment<double> filter;
    std::size_t k = 0;
    for (auto _ : state)
    {
        filter.push(values[k % values.size()]);
        benchmark::DoNotOptimize(filter.mean());
        ++k;
    }
}

BENCHMARK(cumulative_mean);

void cumulative_variance(benchmark::State& state)
{
    auto values = dataset<double>(datasize);
    trial::online::cumulative::moment_variance<double> filter;
    std::size_t k = 0;
    for (auto _ : state)
    {
        filter.push(values[k % values.size()]);
        benchmark::DoNotOptimize(filter.variance());
        ++k;
    }
}

BENCHMARK(cumulative_variance);

void cumulative_skewness(benchmark::State& state)
{
    auto values = dataset<double>(datasize);
    trial::online::cumulative::moment_skewness<double> filter;
    std::size_t k = 0;
    for (auto _ : state)
    {
        filter.push(values[k % values.size()]);
        benchmark::DoNotOptimize(filter.skewness());
        ++k;
    }
}

BENCHMARK(cumulative_skewness);

void cumulative_kurtosis(benchmark::State& state)
{
    auto values = dataset<double>(datasize);
    trial::online::cumulative::moment_kurtosis<double> filter;
    std::size_t k = 0;
    for (auto _ : state)
    {
        filter.push(values[k % values.size()]);
        benchmark::DoNotOptimize(filter.kurtosis());
        ++k;
    }
}

BENCHMARK(cumulative_kurtosis);

BENCHMARK_MAIN();
