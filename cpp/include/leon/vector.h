#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <initializer_list>
#include <cmath>
#include <assert.h>
#include "vectordyn.h"
#include "utils.h"

template <uint N, typename T = double>
class Vector: public VectorDyn<T> {
public:
    // Constructors
    Vector(const T& val = T()): VectorDyn<T>(N, val) {}
    Vector(const T* vals_): VectorDyn<T>(N, vals_) {}
    Vector(const std::initializer_list<T>& vals_): VectorDyn<T>(vals_) {
        if (VectorDyn<T>::N != N)
            throw 1; // `vals_` has size > templated N
    }
    Vector(const Vector<N, T>& other): VectorDyn<T>(other) {}
};

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

#include "vector.inl"

#endif