#ifndef __LINALG_H__
#define __LINALG_H__


#include "utils.h"
#include "vectordyn.h"
#include "matrixdyn.h"
#include "vector.h"
#include "matrix.h"

#include "./print_utils.h"

template<typename T = double>
void gauss_jordan_elim(MatrixDyn<T>& mat) {
    uint M = mat.num_rows();
    uint N = mat.num_cols();
    uint len = min(N, M);
    for (uint k = 0; k < len; k++) {
        T pivot = mat[k][k];

        // Turn pivot to 1
        for (uint j = 0; j < N; j++)
            mat[k][j] /= pivot;

        // Subtract each other row
        for (uint i = 0; i < M; i++) {
            if (i == k) continue;

            T elim_num = mat[i][k];
            for (uint j = 0; j < N; j++)
                mat[i][j] -= (elim_num * mat[i][k]);
        }
    }
}

template<typename T = double>
MatrixDyn<T> lin_solve(const MatrixDyn<T>& A, const MatrixDyn<T>& B) {
    uint M = A.num_rows();
    uint N = A.num_cols();
    uint M2 = B.num_rows();
    uint N2 = B.num_cols();

    assert(M == M2); // Need same # of rows

    // Create augmented [A|B] matrix
    MatrixDyn<T> mat(M, N+N2);
    for (uint i = 0; i < M; i++) {
        for (uint j = 0; j < N; j++)
            mat[i][j] = A[i][j];
        for (uint j = 0; j < N2; j++)
            mat[i][j+N] = B[i][j];
    }

    gauss_jordan_elim(mat);

    MatrixDyn<T> sol(M, N2);
    for (uint i = 0; i < M; i++) {
        for (uint j = 0; j < N2; j++)
            sol[i][j] = mat[i][j+N];
    }
    return sol;
}

template<uint N, uint M, typename T = double>
Vector<N,T> lin_solve(const MatrixDyn<T>& A, const VectorDyn<T>& b) {
    uint M = A.num_rows();
    uint N = A.num_cols();
    uint M2 = b.size();

    assert(M == M2); // Need same # of rows

    // Create augmented [A|b] matrix
    Matrix<T> mat(M, N+1);
    for (uint i = 0; i < M; i++) {
        for (uint j = 0; j < N; j++)
            mat[i][j] = A[i][j];
        mat[i][N] = b[i];
    }

    gauss_jordan_elim(mat);

    VectorDyn<T> sol(M);
    for (uint i = 0; i < M; i++) {
        sol[i] = mat[i][N];
    }
    return sol;
}

template<typename T = double>
MatrixDyn<T> invert(const MatrixDyn<T>& m) {
    uint M = m.num_rows(), N = m.num_cols();
    return lin_solve(m, MatrixDyn<T>(M, N, 1.0));
}

// template<uint N, uint M, typename T = double>
// Vector<N,T> tri_diag_solve(const Matrix<3,M,T>& A, const Vector<N,T>& D) {
//     Vector<N,T> a = A[0], b = A[1], c = A[2], d = D;
//     for (int i = 1; i < N; i++) {
//         double w = a[i] / b[i-1];
//         b[i] -= w * c[i-1];
//         d[i] -= w * d[i-1];
//     }

//     Vector<N,T> x;
//     x[N-1] = d[N-1] / b[N-1];
//     for (int i = N-2; i >= 0; i--)
//         x[i] = (d[i] - c[i] * x[i+1]) / b[i];
//     return x;
// }


template<typename T>
Vector<3, T> cross(const Vector<3, T>& a, const Vector<3, T>& b) {
    Vector<3, T> c(3);
    c[0] =   a[1]*b[2] - a[2]*b[1];
    c[1] = -(a[0]*b[2] - a[2]*b[0]);
    c[2] =   a[0]*b[1] - a[1]*b[0];
    return c;
}

template<typename T>
T cross(const Vector<2, T>& a, const Vector<2, T>& b) {
    return a[0]*b[1] - b[0]*a[1];
}


// NOTE: This is the Laplacian in cartesian coordinates
MatrixDyn<> laplacian_1d(uint N) {
    MatrixDyn<> A(N, N, 1);
    for (int i = 0; i < N; i++) {
        if (i > 0)   A[i][i-1] = 1;
        if (i < N-1) A[i][i+1] = 1;
        A[i][i] = -2;
    }
    return A;
}

// NOTE: This is the Laplacian in cartesian coordinates
MatrixDyn<> laplacian_2d(uint N) {
    auto nxn = MatrixDyn(N, N, 1);
    auto lap1d = laplacian_1d(N);
    return nxn.kron(lap1d) + lap1d.kron(nxn);
}

#endif