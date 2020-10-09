#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <initializer_list>
#include <cmath>
#include "utils.h"

template <uint N, typename T = double>
class Vector {
public:
    Vector(const T& val = T()) {
        for (uint i = 0; i < N; i++)
            vals[i] = val;
    }
    Vector(const T vals_[N]) {
        for (uint i = 0; i < N; i++)
            vals[i] = vals_[i];
    }
    Vector(const std::initializer_list<T>& vals_) {
        uint i = 0;
        for (auto val : vals_) {
            if (i >= N) // out of bounds
                throw 1;
            vals[i] = val;
            i++;
        }
    }
    Vector(const Vector<N, T>& other) {
        for (uint i = 0; i < N; i++)
            vals[i] = other.vals[i];
    }
    const Vector<N,T>& operator = (const Vector<N,T>& other) {
        for (uint i = 0; i < N; i++)
            vals[i] = other.vals[i];
        return *this;
    }

    T& operator [] (uint i) {
        return vals[i];
    }
    const T& operator [] (uint i) const {
        return vals[i];
    }

    // Binary vector operations
    Vector<N,T> operator + (const Vector<N,T>& vec) const {
        Vector<N,T> result;
        for (uint i = 0; i < N; i++)
            result.vals[i] = vals[i] + vec.vals[i];
        return result;
    }
    Vector<N,T> operator - (const Vector<N,T>& vec) const {
        Vector<N,T> result;
        for (uint i = 0; i < N; i++)
            result.vals[i] = vals[i] - vec.vals[i];
        return result;
    }
    Vector<N,T> operator * (const Vector<N,T>& vec) const {
        Vector<N,T> result;
        for (uint i = 0; i < N; i++)
            result.vals[i] = vals[i] * vec.vals[i];
        return result;
    }

    // Binary scalar operations
    template<typename T2>
    Vector<N,T> operator * (const T2& scalar) const {
        Vector<N,T> result;
        for (uint i = 0; i < N; i++)
            result.vals[i] = vals[i] * scalar;
        return result;
    }
    template<typename T2>
    Vector<N,T> operator / (const T2& scalar) const {
        Vector<N,T> result;
        for (uint i = 0; i < N; i++)
            result.vals[i] = vals[i] / scalar;
        return result;
    }

    // Change operators
    Vector<N,T>& operator += (const Vector<N,T>& vec) {
        for (uint i = 0; i < N; i++)
            vals[i] += vec.vals[i];
        return *this;
    }
    Vector<N,T>& operator -= (const Vector<N,T>& vec) {
        for (uint i = 0; i < N; i++)
            vals[i] -= vec.vals[i];
        return *this;
    }
    Vector<N,T>& operator *= (const Vector<N,T>& vec) {
        for (uint i = 0; i < N; i++)
            vals[i] *= vec.vals[i];
        return *this;
    }
    Vector<N,T>& operator /= (const Vector<N,T>& vec) {
        for (uint i = 0; i < N; i++)
            vals[i] /= vec.vals[i];
        return *this;
    }

    template<typename T2>
    Vector<N,T>& operator += (const T2& scalar) {
        for (uint i = 0; i < N; i++)
            vals[i] += scalar;
        return *this;
    }
    template<typename T2>
    Vector<N,T>& operator -= (const T2& scalar) {
        for (uint i = 0; i < N; i++)
            vals[i] -= scalar;
        return *this;
    }
    template<typename T2>
    Vector<N,T>& operator *= (const T2& scalar) {
        for (uint i = 0; i < N; i++)
            vals[i] *= scalar;
        return *this;
    }
    template<typename T2>
    Vector<N,T>& operator /= (const T2& scalar) {
        for (uint i = 0; i < N; i++)
            vals[i] /= scalar;
        return *this;
    }

    // Unary operations
    Vector<N,T> operator - () const {
        Vector<N,T> result;
        for (uint i = 0; i < N; i++)
            result.vals[i] = -vals[i];
        return result;
    }


    // Other operations
    T dot(const Vector<N,T>& vec) const {
        T sum(0);
        for (uint i = 0; i < N; i++)
            sum += vals[i] * vec.vals[i];
        return sum;
    }
    T len2() const {
        return dot(*this);
    }
    T len() const {
        return std::sqrt(len2());
    }

    const T* operator * () const {
        return vals;
    }

    Vector<N,T> norm() const {
        return (*this) / len();
    }

private:
    T vals[N];
};


template <uint N, typename T = double>
Vector<N, T> round(const Vector<N, T>& v) {
    T result[N];
    for (uint i = 0; i < N; i++)
        result[i] = std::round(v[i]);
    return Vector<N, T>(result);
}
template <uint N, typename T = double>
Vector<N, T> floor(const Vector<N, T>& v) {
    T result[N];
    for (uint i = 0; i < N; i++)
        result[i] = std::floor(v[i]);
    return Vector<N, T>(result);
}

template <uint N, typename T = double>
Vector<N, T> min(const Vector<N, T>& v, const Vector<N, T>& m) {
    T result[N];
    for (uint i = 0; i < N; i++)
        result[i] = min(v[i], m[i]);
    return Vector<N, T>(result);
}
template <uint N, typename T = double>
Vector<N, T> min(const Vector<N, T>& v, const T& m) {
    T result[N];
    for (uint i = 0; i < N; i++)
        result[i] = min(v[i], m);
    return Vector<N, T>(result);
}
template <uint N, typename T = double>
Vector<N, T> max(const Vector<N, T>& v, const Vector<N, T>& m) {
    T result[N];
    for (uint i = 0; i < N; i++)
        result[i] = max(v[i], m[i]);
    return Vector<N, T>(result);
}
template <uint N, typename T = double>
Vector<N, T> max(const Vector<N, T>& v, const T& m) {
    T result[N];
    for (uint i = 0; i < N; i++)
        result[i] = max(v[i], m);
    return Vector<N, T>(result);
}
template <uint N, typename T = double>
Vector<N, T> clamp(const Vector<N, T>& v, const Vector<N, T>& min_, const Vector<N, T>& max_) {
    return min(max(v, min_), max_);
}
template <uint N, typename T = double>
Vector<N, T> clamp(const Vector<N, T>& v, const T& min_, const T& max_) {
    return min(max(v, min_), max_);
}


// Binary scalar operations (LHS)
template <uint N, typename T, typename T2>
Vector<N,T> operator * (const T2& scalar, const Vector<N,T>& vec) {
    Vector<N,T> result;
    for (uint i = 0; i < N; i++)
        result[i] = scalar * vec[i];
    return result;
}

template<typename T>
Vector<3,T> cross(const Vector<3,T>& a, const Vector<3,T>& b) {
    Vector<3,T> c;
    c[0] =   a[1]*b[2] - a[2]*b[1];
    c[1] = -(a[0]*b[2] - a[2]*b[0]);
    c[2] =   a[0]*b[1] - a[1]*b[0];
    return c;
}

template<typename T>
T cross(const Vector<2,T>& a, const Vector<2,T>& b) {
    return a[0]*b[1] - b[0]*a[1];
}



typedef Vector<2, double> Vec2;
typedef Vector<3, double> Vec3;
typedef Vector<4, double> Vec4;

typedef Vector<2, float> Vec2f;
typedef Vector<3, float> Vec3f;
typedef Vector<4, float> Vec4f;

typedef Vector<2, int> Vec2i;
typedef Vector<3, int> Vec3i;
typedef Vector<4, int> Vec4i;

typedef Vector<2, unsigned int> Vec2ui;
typedef Vector<3, unsigned int> Vec3ui;
typedef Vector<4, unsigned int> Vec4ui;

Vec2 Vec(double x, double y) {
    return Vec2({x, y});
}
Vec3 Vec(double x, double y, double z) {
    return Vec3({x, y, z});
}
Vec4 Vec(double x, double y, double z, double w) {
    return Vec4({x, y, z, w});
}

Vec2f Vecf(float x, float y) {
    return Vec2f({x, y});
}
Vec3f Vecf(float x, float y, float z) {
    return Vec3f({x, y, z});
}
Vec4f Vecf(float x, float y, float z, float w) {
    return Vec4f({x, y, z, w});
}


#endif