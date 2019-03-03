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
#include <trial/online/interim/hermite_density.hpp>

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

template <std::size_t Window, std::size_t Precision>
void push(benchmark::State& state)
{
    trial::online::interim::hermite_density<double, Window, Precision> filter;
    std::size_t k = 0;
    for (auto _ : state)
    {
        const auto index = k % values.size();
        filter.push(values[index]);
        ++k;
    }
}

BENCHMARK_TEMPLATE(push, 16, 1);
BENCHMARK_TEMPLATE(push, 16, 2);
BENCHMARK_TEMPLATE(push, 16, 3);
BENCHMARK_TEMPLATE(push, 16, 4);
BENCHMARK_TEMPLATE(push, 16, 5);
BENCHMARK_TEMPLATE(push, 16, 6);
BENCHMARK_TEMPLATE(push, 16, 7);
BENCHMARK_TEMPLATE(push, 16, 8);
BENCHMARK_TEMPLATE(push, 16, 9);
BENCHMARK_TEMPLATE(push, 16, 10);
BENCHMARK_TEMPLATE(push, 16, 11);
BENCHMARK_TEMPLATE(push, 16, 12);

template <std::size_t Window, std::size_t Precision>
void at(benchmark::State& state)
{
    trial::online::interim::hermite_density<double, Window, Precision> filter;
    for (const auto& value : values)
    {
        filter.push(value);
    }
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(filter.at(0.5));
    }
}

BENCHMARK_TEMPLATE(at, 16, 1);
BENCHMARK_TEMPLATE(at, 16, 2);
BENCHMARK_TEMPLATE(at, 16, 3);
BENCHMARK_TEMPLATE(at, 16, 4);
BENCHMARK_TEMPLATE(at, 16, 5);
BENCHMARK_TEMPLATE(at, 16, 6);
BENCHMARK_TEMPLATE(at, 16, 7);
BENCHMARK_TEMPLATE(at, 16, 8);
BENCHMARK_TEMPLATE(at, 16, 9);
BENCHMARK_TEMPLATE(at, 16, 10);
BENCHMARK_TEMPLATE(at, 16, 11);
BENCHMARK_TEMPLATE(at, 16, 12);

template <std::size_t Window, std::size_t Precision>
void until_window(benchmark::State& state)
{
    trial::online::interim::hermite_cumulated_density<double, Window, Precision> filter;
    for (const auto& value : values)
    {
        filter.push(value);
    }
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(filter.until(0.5));
    }
}

BENCHMARK_TEMPLATE(until_window, 16, 1);
BENCHMARK_TEMPLATE(until_window, 16, 2);
BENCHMARK_TEMPLATE(until_window, 16, 3);
BENCHMARK_TEMPLATE(until_window, 16, 4);
BENCHMARK_TEMPLATE(until_window, 16, 5);
BENCHMARK_TEMPLATE(until_window, 16, 6);
BENCHMARK_TEMPLATE(until_window, 16, 7);
BENCHMARK_TEMPLATE(until_window, 16, 8);
BENCHMARK_TEMPLATE(until_window, 16, 9);
BENCHMARK_TEMPLATE(until_window, 16, 10);
BENCHMARK_TEMPLATE(until_window, 16, 11);
BENCHMARK_TEMPLATE(until_window, 16, 12);

template <std::size_t Window, std::size_t Precision, typename Ratio>
void until_position(benchmark::State& state)
{
    trial::online::interim::hermite_cumulated_density<double, Window, Precision> filter;
    for (const auto& value : values)
    {
        filter.push(value);
    }
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(filter.until(Ratio::num / double(Ratio::den)));
    }
}

BENCHMARK_TEMPLATE(until_position, 16, 4, std::ratio<0,100>);
BENCHMARK_TEMPLATE(until_position, 16, 4, std::ratio<10,100>);
BENCHMARK_TEMPLATE(until_position, 16, 4, std::ratio<20,100>);
BENCHMARK_TEMPLATE(until_position, 16, 4, std::ratio<25,100>);
BENCHMARK_TEMPLATE(until_position, 16, 4, std::ratio<30,100>);
BENCHMARK_TEMPLATE(until_position, 16, 4, std::ratio<40,100>);
BENCHMARK_TEMPLATE(until_position, 16, 4, std::ratio<50,100>);
BENCHMARK_TEMPLATE(until_position, 16, 4, std::ratio<60,100>);
BENCHMARK_TEMPLATE(until_position, 16, 4, std::ratio<70,100>);
BENCHMARK_TEMPLATE(until_position, 16, 4, std::ratio<75,100>);
BENCHMARK_TEMPLATE(until_position, 16, 4, std::ratio<80,100>);
BENCHMARK_TEMPLATE(until_position, 16, 4, std::ratio<90,100>);
BENCHMARK_TEMPLATE(until_position, 16, 4, std::ratio<100,100>);

BENCHMARK_MAIN();
