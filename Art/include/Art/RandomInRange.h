#ifndef _RANDOM_IN_RANGE_H_
#define _RANDOM_IN_RANGE_H_

#include <random>
#include <cmath>

namespace art
{
    //This is just a really nice random number generator
    template <typename T>
    T randomInRange(T range_start = std::numeric_limits<T>::min(), T range_end = std::numeric_limits<T>::max())
    {
        std::mt19937 rng;
        rng.seed( std::random_device()() );
        std::uniform_int_distribution<T> dist(range_start, range_end);
        return dist(rng);
    }
}

#endif