#ifndef UTILS_H
#define UTILS_H

typedef unsigned int uint;

template<typename T>
int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

template<typename A, typename B>
A max(A a, B b) {
    return (a > b ? a : b);
}
template<typename A, typename B>
A min(A a, B b) {
    return (a < b ? a : b);
}

#endif