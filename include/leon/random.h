#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <random>
#include <ctime>

#include "constants.h"
#include "utils.h"
#include "vector.h"

long rand_init(long seed = time(NULL)) {
    srand(seed);
    return seed;
}

template<typename T>
T rand(T a = 0, T b = 1) {
    return a + static_cast<T>(rand()) / (static_cast<T>(RAND_MAX/(b - a)));
}

template<typename T>
T* rand_sequence(int N, T a = 0, T b = 1) {
    T* seq = new T[N];
    for (uint i = 0; i < N; i++)
        seq[i] = rand(a, b);
    return seq;
}

template<uint N, typename T>
Vector<N, T> rand_pos(const Vector<N, T>& min, const Vector<N, T>& max) {
    T pos[N];
    for (uint i = 0; i < N; i++)
        pos[i] = rand(min[i], max[i]);
    return Vector<N, T>(pos);
}

template<uint N, typename T>
Vector<N, T> rand_point(double r) {
    // generate random angles
    double angles[N-1];
    for (uint i = 0; i < N-2; i++)
        angles[i] = rand(0.0, PI);
    angles[N-2] = rand(0.0, 2*PI);

    // calculate cartesian points
    T x[N];
    for (uint i = 0; i < N; i++) {
        x[i] = r;
        for (uint j = 0; j < i; j++)
            x[i] *= sin(angles[j]);
        // all but last terms get multiplied by cos(angles[N-1])
        if (i < N-1)
            x[i] *= cos(angles[N-2]);
    }

    return Vector<N, T>(x);
}


#endif