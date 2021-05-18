#ifndef __VECTORDYN_H__
#define __VECTORDYN_H__

#include <initializer_list>
#include <cmath>
#include <assert.h>
#include "utils.h"

template <typename T = double>
class VectorDyn {
public:
    // Constructors
    VectorDyn(uint N_, const T& val = T());
    VectorDyn(uint N_, const T* vals_);
    VectorDyn(const std::initializer_list<T>& vals_);
    VectorDyn(const VectorDyn<T>& other);

    // Destructor
    ~VectorDyn();

    // Assignment
    const VectorDyn<T>& operator = (const VectorDyn<T>& other) ;

    // Indexing
    T& operator [] (uint i);
    const T& operator [] (uint i) const;

    // Binary vector operations
    VectorDyn<T> operator + (const VectorDyn<T>& vec) const;
    VectorDyn<T> operator - (const VectorDyn<T>& vec) const;
    VectorDyn<T> operator * (const VectorDyn<T>& vec) const;

    // Binary scalar operations
    VectorDyn<T> operator * (const T& scalar) const;
    VectorDyn<T> operator / (const T& scalar) const;

    // Change operators
    VectorDyn<T>& operator += (const VectorDyn<T>& vec);
    VectorDyn<T>& operator -= (const VectorDyn<T>& vec);
    VectorDyn<T>& operator *= (const VectorDyn<T>& vec);
    VectorDyn<T>& operator /= (const VectorDyn<T>& vec);

    VectorDyn<T>& operator += (const T& scalar);
    VectorDyn<T>& operator -= (const T& scalar);
    VectorDyn<T>& operator *= (const T& scalar);
    VectorDyn<T>& operator /= (const T& scalar);

    // Unary operations
    VectorDyn<T> operator - () const;

    // Other operations
    T dot(const VectorDyn<T>& vec) const;
    T len2() const;
    T len() const;
    VectorDyn<T> norm() const;

    // Access operations
    const T* operator * () const;
    uint size() const;

    // Static functions
    static VectorDyn<T> round(const VectorDyn<T>& v);
    static VectorDyn<T> floor(const VectorDyn<T>& v);

    static VectorDyn<T> min(const VectorDyn<T>& v, const VectorDyn<T>& m);
    static VectorDyn<T> min(const VectorDyn<T>& v, const T& m);

    static VectorDyn<T> max(const VectorDyn<T>& v, const VectorDyn<T>& m);
    static VectorDyn<T> max(const VectorDyn<T>& v, const T& m);

    static VectorDyn<T> clamp(const VectorDyn<T>& v, const VectorDyn<T>& min_, const VectorDyn<T>& max_);
    static VectorDyn<T> clamp(const VectorDyn<T>& v, const T& min_, const T& max_);

protected:
    uint N;
    T* vals;
};


// Binary scalar operations (LHS)
template <typename T>
VectorDyn<T> operator * (const T& scalar, const VectorDyn<T>& vec);


#include "vectordyn.inl"

#endif