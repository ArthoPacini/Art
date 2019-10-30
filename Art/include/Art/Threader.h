#ifndef _THREADER_H_
#define _THREADER_H_

#include <thread>
#include <vector>
#include <utility>

namespace art {
	
template <typename T>
class Threader
{
    std::vector<std::pair<std::uint64_t, std::uint64_t>> bounds;
    std::uint64_t threads;

public:
    Threader() {}
    Threader(const std::vector<T> &v, const std::uint64_t threadCount = std::thread::hardware_concurrency())
    {
        threads = threadCount;
        bounds = getThreadBounds(v, threadCount);
    }

    const std::uint64_t size() const
    {
        return threads;
    }

    inline std::uint64_t fast_mod(const std::uint64_t input, const std::uint64_t ceil)
    {
        return input >= ceil ? input % ceil : input;
    }

    std::vector<std::pair<std::uint64_t, std::uint64_t>> getThreadBounds(const std::vector<T> &v, const std::uint64_t threadCount = std::thread::hardware_concurrency())
    {
        const std::uint64_t vectorSize = v.size();
        const double dataChunckTemp = static_cast<double>(static_cast<double>(static_cast<double>(vectorSize) / static_cast<double>(threadCount)));
        std::uint64_t dataChunck = static_cast<std::uint64_t>((dataChunckTemp - std::floor(dataChunckTemp)) >= 0.5 ? std::ceil(dataChunckTemp) : std::floor(dataChunckTemp));

        std::vector<std::pair<std::uint64_t, std::uint64_t>> threadBounds;
        threadBounds.reserve(threadCount);

        //First
        threadBounds.emplace_back(std::make_pair<std::uint64_t, std::uint64_t>(0, static_cast<std::uint64_t>(dataChunck - 1)));

        //Intermediary
        for (std::uint64_t i = 1; i < threadCount - 1; ++i)
            threadBounds.emplace_back(std::make_pair<std::uint64_t, std::uint64_t>(i * dataChunck, i * dataChunck + dataChunck - 1));

        //Last
        threadBounds.emplace_back(std::make_pair<std::uint64_t, std::uint64_t>(((threadCount - 2) * dataChunck) + dataChunck, static_cast<std::uint64_t>(vectorSize - 1)));

        return threadBounds;
    }

    std::uint64_t begin(std::uint64_t t)
    {
        return bounds[t].first;
    }

    std::uint64_t end(std::uint64_t t)
    {
        return bounds[t].second;
    }
};

}

#endif
