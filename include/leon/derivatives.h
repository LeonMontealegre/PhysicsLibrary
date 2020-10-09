#ifndef __DERIVATIVES_H__
#define __DERIVATIVES_H__

template<typename T>
T derivative_f_diff(T (*f)(T x), T x, T h) {
    return (f(x + h) - f(x)) / h;
}

template<typename T>
T derivative_c_diff(T (*f)(T x), T x, T h) {
    return (f(x + h/2) - f(x - h/2)) / h;
}

template<typename T>
T derivative_5p(T (*f)(T x), T x, T h) {
    return (f(x-2*h) + 8*f(x+h) - 8*f(x-h) - f(x+2*h)) / (12*h);
}

#endif