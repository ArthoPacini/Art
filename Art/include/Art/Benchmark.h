

#ifndef _BENCHMARK_H_
#define _BENCHMARK_H_

#include <iostream>
#include <chrono>
#include <thread>

namespace art
{
class Benchmark
{
private:
    std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<long, std::ratio<1, 1000000000>>> beginBenchmark;
    std::string messagePre;
    std::string messagePos;
    std::string messageLap;
    std::uint64_t laps;

public:
    Benchmark(std::string m1 = "", std::string m2 = "", std::string m3 = "Average: ")
    {
        beginBenchmark = std::chrono::steady_clock::now();
        messagePre = m1;
        messagePos = m2;
        messageLap = m3;
        laps = 0;
    }

    void lap()
    {
        ++laps;
    }

    ~Benchmark()
    {
        auto endBenchmark = std::chrono::steady_clock::now();
        auto runTime = endBenchmark - beginBenchmark;
        std::cout << "[Benchmark]: " << messagePre << std::chrono::duration<double, std::milli>(runTime).count() << " ms " << messagePos << '\n';

        if (laps != 0)
            std::cout << "[Benchmark]: " << messageLap << (std::chrono::duration<double, std::milli>(runTime).count() / laps) << " ms " << '\n';
    }
};
} // namespace art

#endif