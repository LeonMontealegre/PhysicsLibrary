#include "matrixdyn.h"

#include <iostream>
#include "print_utils.h"


// Constructors
template<typename T>
MatrixDyn<T>::MatrixDyn(uint N_, uint M_, const T& val_): N(N_), M(M_) {
    // Allocates with VectorDyn constructor w/ M rows
    cols = (VectorDyn<T>*)malloc(sizeof(VectorDyn<T>[N]));
    for (uint i = 0; i < N; i++)
        (void)(new (&cols[i]) VectorDyn<T>(M, val_));
}

template<typename T>
MatrixDyn<T>::MatrixDyn(const std::initializer_list<std::initializer_list<T>>& vecs_) {
    N = vecs_.size();

    // Allocates with VectorDyn constructor w/ M rows
    cols = (VectorDyn<T>*)malloc(sizeof(VectorDyn<T>[N]));

    uint i = 0;
    for (auto vec_ : vecs_) {
        (void)(new (&cols[i]) VectorDyn<T>(vec_));
        M = cols[i].size(); // Assumes that all columns have same size
        i++;
    }
}

template<typename T>
MatrixDyn<T>::MatrixDyn(const MatrixDyn<T>& other): MatrixDyn<T>(other.N, other.M) {
    for (uint i = 0; i < N; i++)
        cols[i] = other[i];
}


// Destructor
template<typename T>
MatrixDyn<T>::~MatrixDyn() {
    if (!cols)
        return;

    // Manually call destructors since we used `malloc` in constructor
    for (uint i = 0; i < N; i++)
        cols[i].~VectorDyn<T>();
    free(cols);

    cols = NULL;
}


// Assignment
template<typename T>
const MatrixDyn<T>& MatrixDyn<T>::operator = (const MatrixDyn<T>& other) {
    assert(N == other.N && M == other.M);
    for (uint i = 0; i < N; i++)
        cols[i] = other[i];
    return *this;
}


// Indexing
template<typename T>
VectorDyn<T>& MatrixDyn<T>::operator [] (uint i) {
    return cols[i];
}

template<typename T>
const VectorDyn<T>& MatrixDyn<T>::operator [] (uint i) const {
    return cols[i];
}


// Binary matrix operations
template<typename T>
MatrixDyn<T> MatrixDyn<T>::operator + (const MatrixDyn<T>& mat) const {
    assert(N == mat.N && M == mat.M);
    MatrixDyn<T> result(N, M);
    for (uint i = 0; i < N; i++)
        result.cols[i] = cols[i] + mat.cols[i];
    return result;
}

template<typename T>
MatrixDyn<T> MatrixDyn<T>::operator - (const MatrixDyn<T>& mat) const {
    assert(N == mat.N && M == mat.M);
    MatrixDyn<T> result(N, M);
    for (uint i = 0; i < N; i++)
        result.cols[i] = cols[i] - mat.cols[i];
    return result;
}

template<typename T>
MatrixDyn<T> MatrixDyn<T>::operator * (const MatrixDyn<T>& m) const {
    assert(N == m.M);
    uint K = m.N;
    MatrixDyn<T> result(K, M);
    auto t_mat = this->transpose();
    for (uint i = 0; i < M; i++) {
        for (uint j = 0; j < K; j++)
            result[j][i] = t_mat[i].dot(m[j]);
    }
    return result;
}

template<typename T>
VectorDyn<T> MatrixDyn<T>::operator * (const VectorDyn<T>& v) const {
    assert(N == v.size());
    VectorDyn<T> result(M);
    auto t_mat = this->transpose();
    for (uint i = 0; i < M; i++)
        result[i] = t_mat[i].dot(v);
    return result;
}


// Binary scalar operations
template<typename T>
MatrixDyn<T> MatrixDyn<T>::operator * (const T& scalar) const {
    MatrixDyn<T> result;
    for (uint i = 0; i < N; i++)
        result.cols[i] = cols[i] * scalar;
    return result;
}

template<typename T>
MatrixDyn<T> MatrixDyn<T>::operator / (const T& scalar) const {
    MatrixDyn<T> result;
    for (uint i = 0; i < N; i++)
        result.cols[i] = cols[i] / scalar;
    return result;
}


// Change operators
template<typename T>
MatrixDyn<T>& MatrixDyn<T>::operator += (const MatrixDyn<T>& mat) {
    assert(N == mat.N && M == mat.M);
    for (uint i = 0; i < N; i++)
        cols[i] += mat[i];
    return *this;
}

template<typename T>
MatrixDyn<T>& MatrixDyn<T>::operator -= (const MatrixDyn<T>& mat) {
    assert(N == mat.N && M == mat.M);
    for (uint i = 0; i < N; i++)
        cols[i] -= mat[i];
    return *this;
}

template<typename T>
MatrixDyn<T>& MatrixDyn<T>::operator += (const T& scalar) {
    for (uint i = 0; i < N; i++)
        cols[i] += scalar;
    return *this;
}

template<typename T>
MatrixDyn<T>& MatrixDyn<T>::operator -= (const T& scalar) {
    for (uint i = 0; i < N; i++)
        cols[i] -= scalar;
    return *this;
}

template<typename T>
MatrixDyn<T>& MatrixDyn<T>::operator *= (const T& scalar) {
    for (uint i = 0; i < N; i++)
        cols[i] *= scalar;
    return *this;
}

template<typename T>
MatrixDyn<T>& MatrixDyn<T>::operator /= (const T& scalar) {
    for (uint i = 0; i < N; i++)
        cols[i] /= scalar;
    return *this;
}


// Unary operations
template<typename T>
MatrixDyn<T> MatrixDyn<T>::operator - () const {
    MatrixDyn<T> result(N, M);
    for (uint i = 0; i < N; i++)
        result.cols[i] = -cols[i];
    return result;
}


// Other operations
template<typename T>
T MatrixDyn<T>::det() const {
    assert(N == M); // Only square matrices have determinants

    if (N == 2)
        return cols[0][0]*cols[1][1] - cols[1][0]*cols[0][1];
    int sign = +1;
    T det(0);
    for (uint l = 0; l < N; l++) {
        MatrixDyn<T> m2(N-1, M-1);
        for (uint i = 0; i < l; i++) {
            for (uint j = 1; j < M; j++)
                m2[i][j-1] = cols[i][j];
        }
        for (uint i = l+1; i < N; i++) {
            for (uint j = 1; j < M; j++)
                m2[i-1][j-1] = cols[i][j];
        }
        det += sign * cols[l][0] * m2.det();
        sign *= -1;
    }
    return det;
}

template<typename T>
VectorDyn<T> MatrixDyn<T>::flatten() const {
    VectorDyn<T> v(N*M);
    uint k = 0;
    for (uint i = 0; i < N; i++) {
        for (uint j = 0; j < M; j++)
            v[k++] = cols[i][j];
    }
    return v;
}

template<typename T>
MatrixDyn<T> MatrixDyn<T>::transpose() const {
    MatrixDyn<T> m(M, N);
    for (uint i = 0; i < N; i++) {
        for (uint j = 0; j < M; j++)
            m[j][i] = cols[i][j];
    }
    return m;
}

// Access operations
template<typename T>
uint MatrixDyn<T>::num_cols() const {
    return N;
}

template<typename T>
uint MatrixDyn<T>::num_rows() const {
    return M;
}
