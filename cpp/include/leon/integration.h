#ifndef __INTEGRATION_H__
#define __INTEGRATION_H__

template<typename I, typename T>
T integrate(T (*f)(T x), T a, T b, int N, const I& W) {
    T h = (b - a) / N;
    T sum = 0;
    for (int i = 0; i <= N; i++)
        sum += f(i*h) * h * W(i, N);
    return sum;
}

template<typename T>
T integrate_trap(T (*f)(T x), T a, T b, int N) {
    return integrate(f, a, b, N, [](int i, int N) -> T {
        return (i == 0 || i == N) ? (1.0/2.0) : (1.0);
    });
}

template<typename T>
T integrate_simp(T (*f)(T x), T a, T b, int N) {
    // Requires odd number of points
    if (N % 2 == 1)
        N++;
    return integrate(f, a, b, N, [](int i, int N) -> T {
        return (i == 0 || i == N) ? (1.0/3.0) :
                     (i % 2 == 0) ? (2.0/3.0) : (4.0/3.0);
    });
}

// Function for a single 3-point Gaussian Quadrature
//  from -1 to 1
template<typename T, typename I>
T gauss_3p_1(const I& f) {
    static T C[3] = { 0.555555555, 0.888888888, 0.555555555};
    static T X[3] = {-0.774596669, 0.000000000, 0.774596669};
    T sum = 0.0;
    for (int i = 0; i < 3; i++)
        sum += C[i] * f(X[i]);
    return sum;
}

// Function for a single 3-point Gaussian Quadrature
//  over an interval a to b, (transformed to -1 to 1)
template<typename T>
T gauss_3p(T (*f)(T x), T a, T b) {
    return gauss_3p_1<T>([&f, a, b](T x) -> T {
        return f((b - a)/2 * x + (b+a)/2) * (b-a)/2;
    });
}

// Integration function for a 3-point Gaussian Quadrature
//  over a whole domain [a, b] with N samples
template<typename T>
T integrate_gauss_3p(T (*f)(T x), T a, T b, int N) {
    T h = (b - a) / (N - 1);
    T sum = 0;
    for (int i = 0; i < N-1; i++) {
        sum += gauss_3p(f, a + i*h, a + (i+1)*h);
    }
    return sum;
}

#endif