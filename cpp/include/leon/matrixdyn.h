#ifndef __MATRIXDYN_H__
#define __MATRIXDYN_H__

#include <initializer_list>
#include <assert.h>
#include "utils.h"
#include "vectordyn.h"

// M rows, N cols (MxN)[row][col] matrix
template<typename T = double>
class MatrixDyn {
public:
    // Constructors
    MatrixDyn(uint M_, uint N_, const T& val_ = T(0));
    MatrixDyn(const std::initializer_list<std::initializer_list<T>>& vecs_);
    MatrixDyn(const MatrixDyn<T>& other);

    // Destructor
    ~MatrixDyn();

    // Assignment
    const MatrixDyn<T>& operator = (const MatrixDyn<T>& other);

    // Indexing
    VectorDyn<T>& operator [] (uint i);
    const VectorDyn<T>& operator [] (uint i) const;

    // Binary matrix operations
    MatrixDyn<T> operator + (const MatrixDyn<T>& mat) const;
    MatrixDyn<T> operator - (const MatrixDyn<T>& mat) const;
    MatrixDyn<T> operator * (const MatrixDyn<T>& m) const;
    VectorDyn<T> operator * (const VectorDyn<T>& v) const;

    // Binary scalar operations
    MatrixDyn<T> operator * (const T& scalar) const;
    MatrixDyn<T> operator / (const T& scalar) const;

    // Change operators
    MatrixDyn<T>& operator += (const MatrixDyn<T>& mat);
    MatrixDyn<T>& operator -= (const MatrixDyn<T>& mat);

    MatrixDyn<T>& operator += (const T& scalar);
    MatrixDyn<T>& operator -= (const T& scalar);
    MatrixDyn<T>& operator *= (const T& scalar);
    MatrixDyn<T>& operator /= (const T& scalar);

    // Unary operations
    MatrixDyn<T> operator - () const;

    // Other operations
    T det() const;
    VectorDyn<T> flatten() const;
    MatrixDyn<T> transpose() const;

    // Access operations
    uint num_rows() const;
    uint num_cols() const;

protected:
    uint M, N;
    VectorDyn<T>* rows;
};

// Binary scalar operations (LHS)
template <typename T>
MatrixDyn<T> operator * (const T& scalar, const MatrixDyn<T>& mat);


#include "matrixdyn.inl"

#endif