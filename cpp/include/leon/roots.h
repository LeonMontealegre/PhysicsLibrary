#ifndef __ROOTS_H__
#define __ROOTS_H__

#include "utils.h"

#define BISECTION_SAME_SIGN_ERR 1

template<typename T>
T roots_bisection(T (*f)(T x), T a, T b, T eps = 1e-4) {
    int s1 = sign(f(a)), s2 = sign(f(b));
    if (s1 != -s2)
        throw BISECTION_SAME_SIGN_ERR;

    T mid, midP;
    do {
        midP = (a + b) / 2;
        mid = f(midP);
        int s3 = sign(mid);
        if (s3 == s1)
            a = midP;
        else if (s3 == s2)
            b = midP;
    } while (std::abs(mid) > eps);

    return midP;
}

template<typename T>
T roots_newton_raphson(T (*f)(T x), T (*df)(T x), T x, T eps = 1e-4) {
    T b;
    do {
        T m = df(x);
        b = f(x);
        x -= b/m;
    } while (std::abs(b) > eps);
    return x;
}

template<typename T>
T roots_mixed(T (*f)(T x), T (*df)(T x), T a, T b, T eps = 1e-4) {
    T y;
    do {

    } while (std::abs(y) > eps);
}

#endif