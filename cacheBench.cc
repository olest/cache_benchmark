#include <benchmark/benchmark.h>

#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <limits>

static void cacheBench(benchmark::State& s)
{
    int bytes = 1 << s.range(0);
    int count = (bytes/sizeof(int)) / 2;

    std::vector<int> v(count);

    // fill the vector with random numbers
    std::random_device rnd_device;
    std::mt19937 mersenne_engine {rnd_device()};  // Generates random integers
    std::uniform_int_distribution<int> dist {std::numeric_limits<int>::min(), std::numeric_limits<int>::max()};
                           
    auto gen = [&dist, &mersenne_engine](){
        return dist(mersenne_engine);
    };
    generate(begin(v), end(v), gen);

    std::vector<int> indizes;
    std::uniform_int_distribution<int> dist2{0, count};
    auto gen2 = [&dist2, &mersenne_engine](){
        return dist2(mersenne_engine);
    };
    generate(begin(indizes), end(indizes), gen2);

    while (s.KeepRunning()) {
        long sum = 0;
        for (int i : indizes)
            sum+=v[i];
        benchmark::DoNotOptimize(sum);
    }

    s.SetBytesProcessed(long(s.iterations()) * long(bytes));
    s.SetLabel(std::to_string(bytes/1024) + "kb");
}

BENCHMARK(cacheBench)->DenseRange(13,26)->ReportAggregatesOnly(true);

BENCHMARK_MAIN();

