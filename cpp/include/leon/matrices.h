#ifndef __MATRICES_H__
#define __MATRICES_H__

#include "constants.h"
#include "utils.h"
#include "matrix.h"

template<uint N, typename T = double>
Matrix<N,N,T> identity() {
    return Matrix<N,N,T>(1);
}

// Apsect is w/h
template<typename T = float>
Matrix<4,4,T> perspective(T fov, T aspect, T near, T far) {
    Matrix<4,4,T> mat = identity<4,T>();

    T y_scale = 1 / tan(fov / 2 * PI / 180);
    T x_scale = y_scale / aspect;
    T frustum_len = far - near;

    mat[0][0] = x_scale;
    mat[1][1] = y_scale;

    mat[2][2] = -((far + near) / frustum_len);
    mat[2][3] = -1;

    mat[3][2] = -((2 * near * far) / frustum_len);
    mat[3][3] = 0;

    return mat;
}

template<typename T = float>
Matrix<4,4,T> translate_mat(T dx, T dy, T dz) {
    Matrix<4,4,T> mat = identity<4,T>();

    mat[3][0] = dx;
    mat[3][1] = dy;
    mat[3][2] = dz;

    return mat;
}

template<typename T = float>
Matrix<4,4,T> rotate_x_mat(T roll) {
    Matrix<4,4,T> mat = identity<4,T>();

    T c = cos(roll), s = sin(roll);
    mat[1][1] = c;
    mat[1][2] = s;
    mat[2][1] = -s;
    mat[2][2] = c;

    return mat;
}

template<typename T = float>
Matrix<4,4,T> rotate_y_mat(T pitch) {
    Matrix<4,4,T> mat = identity<4,T>();

    T c = cos(pitch), s = sin(pitch);
    mat[0][0] = c;
    mat[0][2] = -s;
    mat[2][0] = s;
    mat[2][2] = c;

    return mat;
}

template<typename T = float>
Matrix<4,4,T> rotate_z_mat(T yaw) {
    Matrix<4,4,T> mat = identity<4,T>();

    T c = cos(yaw), s = sin(yaw);
    mat[0][0] = c;
    mat[0][1] = s;
    mat[1][0] = -s;
    mat[1][1] = c;

    return mat;
}

template<typename T = float>
Matrix<4,4,T> scale_mat(T sx, T sy, T sz) {
    Matrix<4,4,T> mat = identity<4,T>();

    mat[0][0] = sx;
    mat[1][1] = sy;
    mat[2][2] = sz;

    return mat;
}


#endif