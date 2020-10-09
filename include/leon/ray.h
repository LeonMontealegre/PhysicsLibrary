#ifndef __LEON_RAY_H__
#define __LEON_RAY_H__

#include "utils.h"
#include "vector.h"

template<uint N, typename T = double>
class Ray {
public:
    Ray(const Vector<N, T>& origin_, const Vector<N, T>& dir_): origin(origin_), dir(dir_) {
    }
    Ray(const Ray<N,T>& other): Ray(other.origin, other.dir) {
    }

    Vector<N, T> operator [] (const T& t) const {
        return origin + dir*t;
    }

    Vector<N, T> closer(const Vector<N,T>& a, const Vector<N,T>& b) const {
        auto t0 = (a - origin).dot(dir);
        auto t1 = (b - origin).dot(dir);
        if (t0 < t1 && t0 >= 0)
            return a;
        return b;
    }

    Vector<N,T> D() const {
        return dir;
    }

    Vector<N,T> O() const {
        return origin;
    }

private:
    Vector<N, T> origin;
    Vector<N, T> dir;
};

typedef Ray<2> Ray2D;
typedef Ray<3> Ray3D;


#endif