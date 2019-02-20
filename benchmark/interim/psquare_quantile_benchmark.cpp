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
#include <trial/online/interim/psquare_quantile.hpp>

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
void interim_median(benchmark::State& state)
{
    auto values = dataset<double>(datasize);
    trial::online::interim::psquare_median<double, Window> filter;
    std::size_t k = 0;
    for (auto _ : state)
    {
        filter.push(values[k % values.size()]);
        benchmark::DoNotOptimize(filter.value());
        ++k;
    }
}

BENCHMARK_TEMPLATE(interim_median, 2);
BENCHMARK_TEMPLATE(interim_median, 16);
BENCHMARK_TEMPLATE(interim_median, 256);
BENCHMARK_TEMPLATE(interim_median, 4096);

template <std::size_t Window, std::size_t Index>
void interim_quartile(benchmark::State& state)
{
    auto values = dataset<double>(datasize);
    trial::online::interim::psquare_quartile<double, Window> filter;
    std::size_t k = 0;
    for (auto _ : state)
    {
        filter.push(values[k % values.size()]);
        benchmark::DoNotOptimize(filter.template get<Index>());
        ++k;
    }
}

BENCHMARK_TEMPLATE(interim_quartile, 2, 0);
BENCHMARK_TEMPLATE(interim_quartile, 2, 1);
BENCHMARK_TEMPLATE(interim_quartile, 2, 2);
BENCHMARK_TEMPLATE(interim_quartile, 2, 3);
BENCHMARK_TEMPLATE(interim_quartile, 2, 4);
BENCHMARK_TEMPLATE(interim_quartile, 16, 0);
BENCHMARK_TEMPLATE(interim_quartile, 16, 1);
BENCHMARK_TEMPLATE(interim_quartile, 16, 2);
BENCHMARK_TEMPLATE(interim_quartile, 16, 3);
BENCHMARK_TEMPLATE(interim_quartile, 16, 4);
BENCHMARK_TEMPLATE(interim_quartile, 256, 0);
BENCHMARK_TEMPLATE(interim_quartile, 256, 1);
BENCHMARK_TEMPLATE(interim_quartile, 256, 2);
BENCHMARK_TEMPLATE(interim_quartile, 256, 3);
BENCHMARK_TEMPLATE(interim_quartile, 256, 4);
BENCHMARK_TEMPLATE(interim_quartile, 4096, 0);
BENCHMARK_TEMPLATE(interim_quartile, 4096, 1);
BENCHMARK_TEMPLATE(interim_quartile, 4096, 2);
BENCHMARK_TEMPLATE(interim_quartile, 4096, 3);
BENCHMARK_TEMPLATE(interim_quartile, 4096, 4);

BENCHMARK_MAIN();
