#ifndef __LINALG_H__
#define __LINALG_H__

#include "utils.h"
#include "vector.h"
#include "matrix.h"

template<uint N, uint M, typename T = double>
void gauss_jordan_elim(Matrix<N,M,T>& mat) {
    uint len = min(N, M);
    for (uint k = 0; k < len; k++) {
        T pivot = mat[k][k];

        // Turn pivot to 1
        for (uint i = 0; i < N; i++)
            mat[i][k] /= pivot;

        // Subtract each other row
        for (uint j = 0; j < M; j++) {
            if (j == k) continue;

            T elim_num = mat[k][j];
            for (uint i = 0; i < N; i++)
                mat[i][j] -= (elim_num * mat[i][k]);
        }
    }
}

template<uint N, uint M, uint N2, typename T = double>
Matrix<N2,M,T> lin_solve(const Matrix<N,M,T>& A, const Matrix<N2,M,T>& B) {
    // Create augmented [A|B] matrix
    Matrix<N+N2, M, T> mat;
    for (uint i = 0; i < N; i++)
        mat[i] = A[i];
    for (uint i = 0; i < N2; i++)
        mat[i+N] = B[i];

    gauss_jordan_elim(mat);

    Matrix<N2,M,T> sol;
    for (uint i = 0; i < N2; i++)
        sol[i] = mat[i+N];
    return sol;
}

template<uint N, uint M, typename T = double>
Vector<N,T> lin_solve(const Matrix<N,M,T>& A, const Vector<N,T>& b) {
    // Create augmented [A|b] matrix
    Matrix<N+1, M, T> mat;
    for (uint i = 0; i < N; i++)
        mat[i] = A[i];
    mat[N] = b;

    gauss_jordan_elim(mat);
    return mat[N];
}

template<uint N, uint M, typename T = double>
Matrix<N,M,T> invert(const Matrix<N,M,T>& m) {
    return lin_solve(Matrix<N,M,T>(1.0), m);
}

template<uint N, uint M, typename T = double>
Vector<N,T> tri_diag_solve(const Matrix<3,M,T>& A, const Vector<N,T>& D) {
    Vector<N,T> a = A[0], b = A[1], c = A[2], d = D;
    for (int i = 1; i < N; i++) {
        double w = a[i] / b[i-1];
        b[i] -= w * c[i-1];
        d[i] -= w * d[i-1];
    }

    Vector<N,T> x;
    x[N-1] = d[N-1] / b[N-1];
    for (int i = N-2; i >= 0; i--)
        x[i] = (d[i] - c[i] * x[i+1]) / b[i];
    return x;
}

// NOTE: This is the Laplacian in cartesian coordinates
template<int N>
Matrix<N, N> laplacian_1d() {
    Matrix<N, N> A(1);
    for (int i = 0; i < N; i++) {
        if (i > 0)   A[i][i-1] = 1;
        if (i < N-1) A[i][i+1] = 1;
        A[i][i] = -2;
    }
    return A;
}

// NOTE: This is the Laplacian in cartesian coordinates
template<int N>
Matrix<N*N, N*N> laplacian_2d() {
    Matrix<N*N, N*N> A = Matrix<N,N>(1).kron(laplacian_1d<N>());
    Matrix<N*N, N*N> B = laplacian_1d<N>().kron(Matrix<N,N>(1));
    return A+B;
}

#endif