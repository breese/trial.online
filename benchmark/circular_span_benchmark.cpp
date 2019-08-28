///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>
#include <trial/circular/span.hpp>

void empty(benchmark::State& state)
{
    int storage[8];
    trial::circular::span<int> window(storage);
    window.assign({ 1, 2, 3, 4, 5, 6, 7, 8 });

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(window.empty());
    }
}

BENCHMARK(empty);

void full(benchmark::State& state)
{
    int storage[8];
    trial::circular::span<int> window(storage);
    window.assign({ 1, 2, 3, 4, 5, 6, 7, 8 });

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(window.full());
    }
}

BENCHMARK(full);

void push_back(benchmark::State& state)
{
    int storage[256];
    trial::circular::span<int> window(storage);

    for (auto _ : state)
    {
        window.push_back(42);
    }
}

BENCHMARK(push_back);

void push_front(benchmark::State& state)
{
    int storage[256];
    trial::circular::span<int> window(storage);

    for (auto _ : state)
    {
        window.push_front(42);
    }
}

BENCHMARK(push_front);

void push_back_pop_front(benchmark::State& state)
{
    int storage[256];
    trial::circular::span<int> window(storage);
    window.assign({1, 2, 3, 4, 5});

    for (auto _ : state)
    {
        window.push_back(42);
        window.pop_front();
    }
}

BENCHMARK(push_back_pop_front);

void push_front_pop_back(benchmark::State& state)
{
    int storage[256];
    trial::circular::span<int> window(storage);
    window.assign({1, 2, 3, 4, 5});

    for (auto _ : state)
    {
        window.push_front(42);
        window.pop_back();
    }
}

BENCHMARK(push_front_pop_back);

BENCHMARK_MAIN();
