#ifndef __INTEGRATORS_H__
#define __INTEGRATORS_H__

template<typename T, typename F, typename I>
T rk4_single(const I& f, F t0, F h, T w0) {
    T K1 = h * f(t0        , w0         );
    T K2 = h * f(t0 + 0.5*h, w0 + 0.5*K1);
    T K3 = h * f(t0 + 0.5*h, w0 + 0.5*K2);
    T K4 = h * f(t0 +     h, w0 +     K3);
    return w0 + (K1 + 2.0*K2 + 2.0*K3 + K4) / 6.0;
}

template<typename T, typename F>
T euler_single(T (*f)(F t, T w), F t0, F h, T w0) {
    T K1 = h * f(t0, w0);
    return w0 + K1;
}

#endif