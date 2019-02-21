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
#include <trial/online/interim/regression.hpp>

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
void cumulative_push(benchmark::State& state)
{
    auto values = dataset<double>(datasize);
    trial::online::interim::regression<double, Window> filter;
    std::size_t k = 0;
    for (auto _ : state)
    {
        filter.push(k, values[k % values.size()]);
        benchmark::DoNotOptimize(filter.at(0.5));
        ++k;
    }
}

BENCHMARK_TEMPLATE(cumulative_push, 2);
BENCHMARK_TEMPLATE(cumulative_push, 16);
BENCHMARK_TEMPLATE(cumulative_push, 256);
BENCHMARK_TEMPLATE(cumulative_push, 4096);

template <std::size_t Window>
void cumulative_intercept(benchmark::State& state)
{
    auto values = dataset<double>(datasize);
    trial::online::interim::regression<double, Window> filter;
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

BENCHMARK_TEMPLATE(cumulative_intercept, 2);
BENCHMARK_TEMPLATE(cumulative_intercept, 16);
BENCHMARK_TEMPLATE(cumulative_intercept, 256);
BENCHMARK_TEMPLATE(cumulative_intercept, 4096);

BENCHMARK_MAIN();
