#include "matrixdyn.h"

#include <iostream>
#include "print_utils.h"


// Constructors
template<typename T>
MatrixDyn<T>::MatrixDyn(uint M_, uint N_, const T& val_): M(M_), N(N_) {
    // Allocates with VectorDyn constructor w/ M rows
    rows = (VectorDyn<T>*)malloc(sizeof(VectorDyn<T>[M]));
    for (uint i = 0; i < M; i++) {
        (void)(new (&rows[i]) VectorDyn<T>(N));
        if (i < N)
            rows[i][i] = val_;
    }
}

template<typename T>
MatrixDyn<T>::MatrixDyn(const std::initializer_list<std::initializer_list<T>>& vecs_) {
    M = vecs_.size();

    // Allocates with VectorDyn constructor w/ M rows
    rows = (VectorDyn<T>*)malloc(sizeof(VectorDyn<T>[M]));

    uint i = 0;
    for (auto vec_ : vecs_) {
        (void)(new (&rows[i]) VectorDyn<T>(vec_));
        N = rows[i].size(); // Assumes that all columns have same size
        i++;
    }
}

template<typename T>
MatrixDyn<T>::MatrixDyn(const MatrixDyn<T>& other): MatrixDyn<T>(other.M, other.N) {
    for (uint i = 0; i < M; i++)
        rows[i] = other[i];
}


// Destructor
template<typename T>
MatrixDyn<T>::~MatrixDyn() {
    if (!rows)
        return;

    // Manually call destructors since we used `malloc` in constructor
    for (uint i = 0; i < M; i++)
        rows[i].~VectorDyn<T>();
    free(rows);

    rows = NULL;
}


// Assignment
template<typename T>
const MatrixDyn<T>& MatrixDyn<T>::operator = (const MatrixDyn<T>& other) {
    assert(M == other.M && N == other.N);
    for (uint i = 0; i < M; i++)
        rows[i] = other[i];
    return *this;
}


// Indexing
template<typename T>
VectorDyn<T>& MatrixDyn<T>::operator [] (uint i) {
    return rows[i];
}

template<typename T>
const VectorDyn<T>& MatrixDyn<T>::operator [] (uint i) const {
    return rows[i];
}


// Binary matrix operations
template<typename T>
MatrixDyn<T> MatrixDyn<T>::operator + (const MatrixDyn<T>& mat) const {
    assert(M == mat.M && N == mat.N);
    MatrixDyn<T> result(M, N);
    for (uint i = 0; i < M; i++)
        result.rows[i] = rows[i] + mat.rows[i];
    return result;
}

template<typename T>
MatrixDyn<T> MatrixDyn<T>::operator - (const MatrixDyn<T>& mat) const {
    assert(M == mat.M && N == mat.N);
    MatrixDyn<T> result(M, N);
    for (uint i = 0; i < M; i++)
        result.rows[i] = rows[i] - mat.rows[i];
    return result;
}

template<typename T>
MatrixDyn<T> MatrixDyn<T>::operator * (const MatrixDyn<T>& m) const {
    assert(N == m.M); // M x N  x  N x K for matrix multiplication
    uint K = m.N;
    MatrixDyn<T> result(M, K);
    auto t_m = m.transpose();
    for (uint i = 0; i < M; i++) {
        for (uint j = 0; j < K; j++)
            result[i][j] = rows[i].dot(t_m[j]);
    }
    return result;
}

template<typename T>
VectorDyn<T> MatrixDyn<T>::operator * (const VectorDyn<T>& v) const {
    assert(N == v.size());
    VectorDyn<T> result(M);
    for (uint i = 0; i < M; i++)
        result[i] = rows[i].dot(v);
    return result;
}


// Binary scalar operations
template<typename T>
MatrixDyn<T> MatrixDyn<T>::operator * (const T& scalar) const {
    MatrixDyn<T> result(M, N);
    for (uint i = 0; i < M; i++)
        result.rows[i] = rows[i] * scalar;
    return result;
}

template<typename T>
MatrixDyn<T> MatrixDyn<T>::operator / (const T& scalar) const {
    MatrixDyn<T> result(M, N);
    for (uint i = 0; i < M; i++)
        result.rows[i] = rows[i] / scalar;
    return result;
}


// Change operators
template<typename T>
MatrixDyn<T>& MatrixDyn<T>::operator += (const MatrixDyn<T>& mat) {
    assert(M == mat.M && N == mat.N);
    for (uint i = 0; i < M; i++)
        rows[i] += mat[i];
    return *this;
}

template<typename T>
MatrixDyn<T>& MatrixDyn<T>::operator -= (const MatrixDyn<T>& mat) {
    assert(M == mat.M && N == mat.N);
    for (uint i = 0; i < M; i++)
        rows[i] -= mat[i];
    return *this;
}

template<typename T>
MatrixDyn<T>& MatrixDyn<T>::operator += (const T& scalar) {
    for (uint i = 0; i < M; i++)
        rows[i] += scalar;
    return *this;
}

template<typename T>
MatrixDyn<T>& MatrixDyn<T>::operator -= (const T& scalar) {
    for (uint i = 0; i < M; i++)
        rows[i] -= scalar;
    return *this;
}

template<typename T>
MatrixDyn<T>& MatrixDyn<T>::operator *= (const T& scalar) {
    for (uint i = 0; i < M; i++)
        rows[i] *= scalar;
    return *this;
}

template<typename T>
MatrixDyn<T>& MatrixDyn<T>::operator /= (const T& scalar) {
    for (uint i = 0; i < M; i++)
        rows[i] /= scalar;
    return *this;
}


// Unary operations
template<typename T>
MatrixDyn<T> MatrixDyn<T>::operator - () const {
    MatrixDyn<T> result(M, N);
    for (uint i = 0; i < M; i++)
        result.rows[i] = -rows[i];
    return result;
}


// Other operations
template<typename T>
T MatrixDyn<T>::det() const {
    assert(M == N); // Only square matrices have determinants

    // 2x2 determinant
    if (M == 2)
        return rows[0][0]*rows[1][1] - rows[1][0]*rows[0][1];

    T det(0);
    int sign = +1;
    for (uint l = 0; l < N; l++) {
        MatrixDyn<T> m2(N-1, N-1);
        for (uint i = 1; i < N; i++) {
            for (uint j = 0; j < l; j++)
                m2[i-1][j] = rows[i][j];
        }
        for (uint i = 1; i < N; i++) {
            for (uint j = l+1; j < N; j++)
                m2[i-1][j-1] = rows[i][j];
        }
        det += sign * rows[0][l] * m2.det();
        sign *= -1;
    }
    return det;
}

template<typename T>
VectorDyn<T> MatrixDyn<T>::flatten() const {
    VectorDyn<T> v(M*N);
    uint k = 0;
    for (uint i = 0; i < M; i++) {
        for (uint j = 0; j < N; j++)
            v[k++] = rows[i][j];
    }
    return v;
}

template<typename T>
MatrixDyn<T> MatrixDyn<T>::transpose() const {
    MatrixDyn<T> m(N, M);
    for (uint i = 0; i < M; i++) {
        for (uint j = 0; j < N; j++)
            m[j][i] = rows[i][j];
    }
    return m;
}

// Access operations
template<typename T>
uint MatrixDyn<T>::num_rows() const {
    return M;
}

template<typename T>
uint MatrixDyn<T>::num_cols() const {
    return N;
}


// Binary scalar operations (LHS)
template <typename T>
MatrixDyn<T> operator * (const T& scalar, const MatrixDyn<T>& mat) {
    uint M = mat.num_rows();
    uint N = mat.num_cols();
    MatrixDyn<T> result(M, N);
    for (uint i = 0; i < M; i++)
        result[i] = scalar * mat[i];
    return result;
}
