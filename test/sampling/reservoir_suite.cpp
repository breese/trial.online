///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2016 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <random>
#include <limits>
#include <vector>
#include <trial/online/detail/lightweight_test.hpp>
#include <trial/online/sampling/reservoir.hpp>

using namespace trial::online;

//-----------------------------------------------------------------------------

// Adheres to UniformRandomBitGenerator concept
struct simulate_engine
{
    using result_type = std::size_t;

    simulate_engine(std::initializer_list<result_type> init)
        : data(init.begin(), init.end())
    {}

    result_type operator()()
    {
        assert(index <= data.size());
        return data[index++];
    }

    result_type min()
    {
        return std::numeric_limits<result_type>::min();
    }
    result_type max()
    {
        return std::numeric_limits<result_type>::max();
    }

    std::vector<result_type> data;
    std::vector<result_type>::size_type index {0};
};

//-----------------------------------------------------------------------------

namespace simulate_suite
{

void test_alpha()
{
    std::size_t max = std::numeric_limits<std::size_t>::max();
    const simulate_engine engine = {
        // Accept-reject
        max - 1,        // => 2
        max / 3,        // => 1
        0,              // => 0
        max / 5 - 1,    // => 1
        max / 3,        // 2 * max / 6 => 2
        0,              // => 0
        // Skip count
        0, max / 2 + 1, // skip = 0, => 1
        max / 2, 0,     // skip = 2, => 0
        0, 0            // skip = 0, => 0
    };
    sampling::reservoir<int, simulate_engine> sampler(2, engine);
    TRIAL_TEST_EQ(sampler.size(), 0U);
    TRIAL_TEST_EQ(sampler.count(), 0U);

    // First two are accepted directly
    TRIAL_TEST_EQ(sampler.push(11), true);
    TRIAL_TEST_EQ(sampler.size(), 1U);
    TRIAL_TEST_EQ(sampler.count(), 1U);
    {
        std::vector<int> expected = { 11 };
        TRIAL_TEST_ALL_EQ(sampler.data().begin(), sampler.data().end(),
                          expected.begin(), expected.end());
    }

    TRIAL_TEST_EQ(sampler.push(22), true);
    TRIAL_TEST_EQ(sampler.size(), 2U);
    TRIAL_TEST_EQ(sampler.count(), 2U);
    {
        std::vector<int> expected = { 11, 22 };
        TRIAL_TEST_ALL_EQ(sampler.data().begin(), sampler.data().end(),
                          expected.begin(), expected.end());
    }

    // Next six are accepted by accept-reject
    TRIAL_TEST_EQ(sampler.push(33), false);
    TRIAL_TEST_EQ(sampler.size(), 2U);
    TRIAL_TEST_EQ(sampler.count(), 3U);
    {
        std::vector<int> expected = { 11, 22 };
        TRIAL_TEST_ALL_EQ(sampler.data().begin(), sampler.data().end(),
                          expected.begin(), expected.end());
    }

    TRIAL_TEST_EQ(sampler.push(44), true);
    TRIAL_TEST_EQ(sampler.count(), 4U);
    {
        std::vector<int> expected = { 11, 44 };
        TRIAL_TEST_ALL_EQ(sampler.data().begin(), sampler.data().end(),
                          expected.begin(), expected.end());
    }

    TRIAL_TEST_EQ(sampler.push(55), true);
    TRIAL_TEST_EQ(sampler.count(), 5U);
    {
        std::vector<int> expected = { 55, 44 };
        TRIAL_TEST_ALL_EQ(sampler.data().begin(), sampler.data().end(),
                          expected.begin(), expected.end());
    }

    TRIAL_TEST_EQ(sampler.push(66), true);
    TRIAL_TEST_EQ(sampler.count(), 6U);
    {
        std::vector<int> expected = { 55, 66 };
        TRIAL_TEST_ALL_EQ(sampler.data().begin(), sampler.data().end(),
                          expected.begin(), expected.end());
    }

    TRIAL_TEST_EQ(sampler.push(77), false);
    TRIAL_TEST_EQ(sampler.count(), 7U);
    {
        std::vector<int> expected = { 55, 66 };
        TRIAL_TEST_ALL_EQ(sampler.data().begin(), sampler.data().end(),
                          expected.begin(), expected.end());
    }

    TRIAL_TEST_EQ(sampler.push(88), true);
    TRIAL_TEST_EQ(sampler.count(), 8U);
    {
        std::vector<int> expected = { 88, 66 };
        TRIAL_TEST_ALL_EQ(sampler.data().begin(), sampler.data().end(),
                          expected.begin(), expected.end());
    }

    // Remainder are accepted by skip count
    TRIAL_TEST_EQ(sampler.push(90), true);
    TRIAL_TEST_EQ(sampler.count(), 9U);
    {
        std::vector<int> expected = { 88, 90 };
        TRIAL_TEST_ALL_EQ(sampler.data().begin(), sampler.data().end(),
                          expected.begin(), expected.end());
    }

    TRIAL_TEST_EQ(sampler.push(100), true);
    TRIAL_TEST_EQ(sampler.count(), 10U);
    {
        std::vector<int> expected = { 100, 90 };
        TRIAL_TEST_ALL_EQ(sampler.data().begin(), sampler.data().end(),
                          expected.begin(), expected.end());
    }

    TRIAL_TEST_EQ(sampler.push(110), false);
    TRIAL_TEST_EQ(sampler.count(), 11U);
    {
        std::vector<int> expected = { 100, 90 };
        TRIAL_TEST_ALL_EQ(sampler.data().begin(), sampler.data().end(),
                          expected.begin(), expected.end());
    }

    TRIAL_TEST_EQ(sampler.push(120), false);
    TRIAL_TEST_EQ(sampler.count(), 12U);
    {
        std::vector<int> expected = { 100, 90 };
        TRIAL_TEST_ALL_EQ(sampler.data().begin(), sampler.data().end(),
                          expected.begin(), expected.end());
    }

    TRIAL_TEST_EQ(sampler.push(130), true);
    TRIAL_TEST_EQ(sampler.count(), 13U);
    {
        std::vector<int> expected = { 130, 90 };
        TRIAL_TEST_ALL_EQ(sampler.data().begin(), sampler.data().end(),
                          expected.begin(), expected.end());
    }
}

void run()
{
    test_alpha();
}

} // namespace simulate_suite

//-----------------------------------------------------------------------------

namespace generator_suite
{

void test_default()
{
    sampling::reservoir_default<double> sampler(2);
    sampler.push(11.0);
    TRIAL_TEST_EQ(sampler.count(), 1U);
}

void test_default_random_engine()
{
    std::default_random_engine engine;
    sampling::reservoir<double, decltype(engine)> sampler(2, engine);
    sampler.push(11.0);
    TRIAL_TEST_EQ(sampler.count(), 1U);
}

void test_minstd_rand()
{
    // Linear congruential generator
    std::minstd_rand engine;
    sampling::reservoir<double, decltype(engine)> sampler(2, engine);
    sampler.push(11.0);
    TRIAL_TEST_EQ(sampler.count(), 1U);
}

void test_mt19937()
{
    // Mersenne twister generator
    std::mt19937 engine;
    sampling::reservoir<double, decltype(engine)> sampler(2, engine);
    sampler.push(11.0);
    TRIAL_TEST_EQ(sampler.count(), 1U);
}

void test_ranlux24()
{
    // Subtract with carry generator
    std::ranlux24 engine;
    sampling::reservoir<double, decltype(engine)> sampler(2, engine);
    sampler.push(11.0);
    TRIAL_TEST_EQ(sampler.count(), 1U);
}

void test_knuth_b()
{
    // Knuth shuffle order generator
    std::knuth_b engine;
    sampling::reservoir<double, decltype(engine)> sampler(2, engine);
    sampler.push(11.0);
    TRIAL_TEST_EQ(sampler.count(), 1U);
}

void run()
{
    test_default();
    test_default_random_engine();
    test_minstd_rand();
    test_mt19937();
    test_ranlux24();
    test_knuth_b();
}

} // namespace generator_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    simulate_suite::run();
    generator_suite::run();

    return boost::report_errors();
}
