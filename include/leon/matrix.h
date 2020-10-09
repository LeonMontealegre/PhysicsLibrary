#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <initializer_list>
#include "utils.h"
#include "vector.h"

// N cols, M rows (MxN) matrix
template<uint N, uint M, typename T = double>
class Matrix {
public:
    Matrix(const T& val_ = T(0)) {
        for (uint i = 0; i < N; i++) {
            cols[i] = Vector<M,T>();
            if (i < M)
                cols[i][i] = val_;
        }
    }
    Matrix(const std::initializer_list<std::initializer_list<T>>& vecs_) {
        uint i = 0;
        for (auto vec_ : vecs_) {
            if (i >= N) // out of bounds
                throw 1;
            cols[i] = Vector<M,T>(vec_);
            i++;
        }
    }
    Matrix(const Matrix<N,M,T>& m) {
        for (uint i = 0; i < N; i++) {
            for (uint j = 0; j < M; j++)
                cols[i][j] = m[i][j];
        }
    }
    Matrix(const Vector<N*M,T>& v) {
        uint k = 0;
        for (uint i = 0; i < N; i++) {
            for (uint j = 0; j < M; j++)
                cols[i][j] = v[k++];
        }
    }
    const Matrix<N,M,T>& operator = (const Matrix<N,M,T>& m) {
        for (uint i = 0; i < N; i++) {
            for (uint j = 0; j < M; j++)
                cols[i][j] = m[i][j];
        }
        return *this;
    }
    const Matrix<N,M,T>& operator = (const Vector<N*M,T>& v) {
        uint k = 0;
        for (uint i = 0; i < N; i++) {
            for (uint j = 0; j < M; j++)
                cols[i][j] = v[k++];
        }
        return *this;
    }

    template<uint K>
    Matrix<M,K,T> operator * (const Matrix<K,N,T>& m) const {
        Matrix<K,M,T> result;
        Matrix<M,N,T> t_mat = this->transpose();
        for (uint i = 0; i < M; i++) {
            for (uint j = 0; j < K; j++)
                result[j][i] = t_mat[i].dot(m[j]);
        }
        return result;
    }

    Vector<M,T> operator * (const Vector<N,T>& v) const {
        Vector<M,T> result;
        Matrix<M,N,T> t_mat = this->transpose();
        for (uint i = 0; i < M; i++)
            result[i] = t_mat[i].dot(v);
        return result;
    }


    // Binary matrix operations
    Matrix<N,M,T> operator + (const Matrix<N,M,T>& mat) const {
        Matrix<N,M,T> result;
        for (uint i = 0; i < N; i++)
            result.cols[i] = cols[i] + mat.cols[i];
        return result;
    }
    Matrix<N,M,T> operator - (const Matrix<N,M,T>& mat) const {
        Matrix<N,M,T> result;
        for (uint i = 0; i < N; i++)
            result.cols[i] = cols[i] - mat.cols[i];
        return result;
    }

    // Binary scalar operations
    template<typename T2>
    Matrix<N,M,T> operator * (const T2& scalar) const {
        Matrix<N,M,T> result;
        for (uint i = 0; i < N; i++)
            result.cols[i] = cols[i] * scalar;
        return result;
    }
    template<typename T2>
    Matrix<N,M,T> operator / (const T2& scalar) const {
        Matrix<N,M,T> result;
        for (uint i = 0; i < N; i++)
            result.cols[i] = cols[i] / scalar;
        return result;
    }

    // Change operators
    Matrix<N,M,T>& operator += (const Matrix<N,M,T>& mat) {
        for (uint i = 0; i < N; i++)
            cols[i] += mat.cols[i];
        return *this;
    }
    Matrix<N,M,T>& operator -= (const Matrix<N,M,T>& mat) {
        for (uint i = 0; i < N; i++)
            cols[i] -= mat.cols[i];
        return *this;
    }

    template<typename T2>
    Matrix<N,M,T>& operator += (const T2& scalar) {
        for (uint i = 0; i < N; i++)
            cols[i] += scalar;
        return *this;
    }
    template<typename T2>
    Matrix<N,M,T>& operator -= (const T2& scalar) {
        for (uint i = 0; i < N; i++)
            cols[i] -= scalar;
        return *this;
    }
    template<typename T2>
    Matrix<N,M,T>& operator *= (const T2& scalar) {
        for (uint i = 0; i < N; i++)
            cols[i] *= scalar;
        return *this;
    }
    template<typename T2>
    Matrix<N,M,T>& operator /= (const T2& scalar) {
        for (uint i = 0; i < N; i++)
            cols[i] /= scalar;
        return *this;
    }

    // Unary operations
    Matrix<N,M,T> operator - () const {
        Matrix<N,M,T> result;
        for (uint i = 0; i < N; i++)
            result.cols[i] = -cols[i];
        return result;
    }

    Vector<M,T>& operator [] (uint i) {
        return cols[i];
    }
    const Vector<M,T>& operator [] (uint i) const {
        return cols[i];
    }

    template<uint P, uint Q, typename T2>
    Matrix<N*P,M*Q,T> kron(const Matrix<P, Q, T2>& B) const {
        Matrix<N*P,M*Q,T> m;
        for (uint i = 0; i < N; i++) {
            for (uint j = 0; j < M; j++) {
                const T& a_ij = cols[i][j];
                for (uint i2 = 0; i2 < P; i2++) {
                    for (uint j2 = 0; j2 < Q; j2++)
                        m[i*P + i2][j*Q + j2] = a_ij * B[i2][j2];
                }
            }
        }
        return m;
    }

    T det() const {
        if (N == 2)
            return cols[0][0]*cols[1][1] - cols[1][0]*cols[0][1];
        T det(0);
        for (uint l = 0; l < N; l++) {
            Matrix<N-1,M-1,T> m2;
            for (uint i = 0; i < l; i++) {
                for (uint j = 1; j < M; j++)
                    m2[i][j-1] = cols[i][j];
            }
            for (uint i = l+1; i < N; i++) {
                for (uint j = 1; j < M; j++)
                    m2[i-1][j-1] = cols[i][j];
            }
            det += m2.det();
        }
        return det;
    }

    Vector<N*M,T> flatten() const {
        Vector<N*M,T> v;
        uint k = 0;
        for (uint i = 0; i < N; i++) {
            for (uint j = 0; j < M; j++)
                v[k++] = cols[i][j];
        }
        return v;
    }

    Matrix<M,N,T> transpose() const {
        Matrix<M,N,T> m;
        for (uint i = 0; i < N; i++) {
            for (uint j = 0; j < M; j++)
                m[j][i] = cols[i][j];
        }
        return m;
    }

    uint num_cols() const {
        return N;
    }
    uint num_rows() const {
        return M;
    }

private:
    Vector<M,T> cols[N];
};

// Binary scalar operations (LHS)
template <uint N, uint M, typename T, typename T2>
Matrix<N,M,T> operator * (const T2& scalar, const Matrix<N,M,T>& mat) {
    Matrix<N,M,T> result;
    for (uint i = 0; i < N; i++)
        result[i] = scalar * mat[i];
    return result;
}



typedef Matrix<4,4> Matrix4;
typedef Matrix<4,4,float> Matrix4f;


#endif