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
#include <ratio>
#include <benchmark/benchmark.h>
#include <trial/online/cumulative/hermite_density.hpp>

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

auto values = dataset<double>(datasize);

template <std::size_t Precision>
void push(benchmark::State& state)
{
    trial::online::cumulative::hermite_density<double, Precision> filter;
    std::size_t k = 0;
    for (auto _ : state)
    {
        const auto index = k % values.size();
        filter.push(values[index]);
        ++k;
    }
}

BENCHMARK_TEMPLATE(push, 1);
BENCHMARK_TEMPLATE(push, 2);
BENCHMARK_TEMPLATE(push, 3);
BENCHMARK_TEMPLATE(push, 4);
BENCHMARK_TEMPLATE(push, 5);
BENCHMARK_TEMPLATE(push, 6);
BENCHMARK_TEMPLATE(push, 7);
BENCHMARK_TEMPLATE(push, 8);
BENCHMARK_TEMPLATE(push, 9);
BENCHMARK_TEMPLATE(push, 10);
BENCHMARK_TEMPLATE(push, 11);
BENCHMARK_TEMPLATE(push, 12);

template <std::size_t Precision>
void at(benchmark::State& state)
{
    trial::online::cumulative::hermite_density<double, Precision> filter;
    for (const auto& value : values)
    {
        filter.push(value);
    }
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(filter.at(0.5));
    }
}

BENCHMARK_TEMPLATE(at, 1);
BENCHMARK_TEMPLATE(at, 2);
BENCHMARK_TEMPLATE(at, 3);
BENCHMARK_TEMPLATE(at, 4);
BENCHMARK_TEMPLATE(at, 5);
BENCHMARK_TEMPLATE(at, 6);
BENCHMARK_TEMPLATE(at, 7);
BENCHMARK_TEMPLATE(at, 8);
BENCHMARK_TEMPLATE(at, 9);
BENCHMARK_TEMPLATE(at, 10);
BENCHMARK_TEMPLATE(at, 11);
BENCHMARK_TEMPLATE(at, 12);

template <std::size_t Precision>
void until_window(benchmark::State& state)
{
    trial::online::cumulative::hermite_cumulated_density<double, Precision> filter;
    for (const auto& value : values)
    {
        filter.push(value);
    }
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(filter.until(0.5));
    }
}

BENCHMARK_TEMPLATE(until_window, 1);
BENCHMARK_TEMPLATE(until_window, 2);
BENCHMARK_TEMPLATE(until_window, 3);
BENCHMARK_TEMPLATE(until_window, 4);
BENCHMARK_TEMPLATE(until_window, 5);
BENCHMARK_TEMPLATE(until_window, 6);
BENCHMARK_TEMPLATE(until_window, 7);
BENCHMARK_TEMPLATE(until_window, 8);
BENCHMARK_TEMPLATE(until_window, 9);
BENCHMARK_TEMPLATE(until_window, 10);
BENCHMARK_TEMPLATE(until_window, 11);
BENCHMARK_TEMPLATE(until_window, 12);

template <std::size_t Precision, typename Ratio>
void until_position(benchmark::State& state)
{
    trial::online::cumulative::hermite_cumulated_density<double, Precision> filter;
    for (const auto& value : values)
    {
        filter.push(value);
    }
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(filter.until(Ratio::num / double(Ratio::den)));
    }
}

BENCHMARK_TEMPLATE(until_position, 4, std::ratio<0,100>);
BENCHMARK_TEMPLATE(until_position, 4, std::ratio<10,100>);
BENCHMARK_TEMPLATE(until_position, 4, std::ratio<20,100>);
BENCHMARK_TEMPLATE(until_position, 4, std::ratio<25,100>);
BENCHMARK_TEMPLATE(until_position, 4, std::ratio<30,100>);
BENCHMARK_TEMPLATE(until_position, 4, std::ratio<40,100>);
BENCHMARK_TEMPLATE(until_position, 4, std::ratio<50,100>);
BENCHMARK_TEMPLATE(until_position, 4, std::ratio<60,100>);
BENCHMARK_TEMPLATE(until_position, 4, std::ratio<70,100>);
BENCHMARK_TEMPLATE(until_position, 4, std::ratio<75,100>);
BENCHMARK_TEMPLATE(until_position, 4, std::ratio<80,100>);
BENCHMARK_TEMPLATE(until_position, 4, std::ratio<90,100>);
BENCHMARK_TEMPLATE(until_position, 4, std::ratio<100,100>);

BENCHMARK_MAIN();
