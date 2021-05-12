#include "vectordyn.h"


// Constructors
template <typename T>
VectorDyn<T>::VectorDyn(uint N_, const T& val) {
    vals = new T[(N = N_)];
    for (uint i = 0; i < N; i++)
        vals[i] = val;
}
template<typename T>
VectorDyn<T>::VectorDyn(uint N_, const T* vals_) {
    vals = new T[(N = N_)];
    for (uint i = 0; i < N; i++)
        vals[i] = vals_[i];
}
template<typename T>
VectorDyn<T>::VectorDyn(const std::initializer_list<T>& vals_) {
    vals = new T[(N = vals_.size())];

    uint i = 0;
    for (auto val : vals_) {
        if (i >= N) // out of bounds
            throw 1;
        vals[i] = val;
        i++;
    }
}
template<typename T>
VectorDyn<T>::VectorDyn(const VectorDyn<T>& other) {
    vals = new T[(N = other.N)];
    for (uint i = 0; i < N; i++)
        vals[i] = other.vals[i];
}


// Destructor
template<typename T>
VectorDyn<T>::~VectorDyn() {
    if (!vals)
        return;
    delete [] vals;
    vals = NULL;
}


// Assignment
template<typename T>
const VectorDyn<T>& VectorDyn<T>::operator = (const VectorDyn<T>& other) {
    assert(N == other.N);
    for (uint i = 0; i < N; i++)
        vals[i] = other.vals[i];
    return *this;
}


// Indexing
template<typename T>
T& VectorDyn<T>::operator [] (uint i) {
    return vals[i];
}
template<typename T>
const T& VectorDyn<T>::operator [] (uint i) const {
    return vals[i];
}


// Binary vector operations
template<typename T>
VectorDyn<T> VectorDyn<T>::operator + (const VectorDyn<T>& vec) const {
    assert(N == vec.N);
    VectorDyn<T> result(N);
    for (uint i = 0; i < N; i++)
        result.vals[i] = vals[i] + vec.vals[i];
    return result;
}
template<typename T>
VectorDyn<T> VectorDyn<T>::operator - (const VectorDyn<T>& vec) const {
    assert(N == vec.N);
    VectorDyn<T> result(N);
    for (uint i = 0; i < N; i++)
        result.vals[i] = vals[i] - vec.vals[i];
    return result;
}
template<typename T>
VectorDyn<T> VectorDyn<T>::operator * (const VectorDyn<T>& vec) const {
    assert(N == vec.N);
    VectorDyn<T> result(N);
    for (uint i = 0; i < N; i++)
        result.vals[i] = vals[i] * vec.vals[i];
    return result;
}


// Binary scalar operations
template<typename T>//, typename T2>
VectorDyn<T> VectorDyn<T>::operator * (const T& scalar) const {
    VectorDyn<T> result(N);
    for (uint i = 0; i < N; i++)
        result.vals[i] = vals[i] * scalar;
    return result;
}
template<typename T>//, typename T2>
VectorDyn<T> VectorDyn<T>::operator / (const T& scalar) const {
    VectorDyn<T> result(N);
    for (uint i = 0; i < N; i++)
        result.vals[i] = vals[i] / scalar;
    return result;
}


// Change operators
template<typename T>
VectorDyn<T>& VectorDyn<T>::operator += (const VectorDyn<T>& vec) {
    assert(N == vec.N);
    for (uint i = 0; i < N; i++)
        vals[i] += vec.vals[i];
    return *this;
}
template<typename T>
VectorDyn<T>& VectorDyn<T>::operator -= (const VectorDyn<T>& vec) {
    assert(N == vec.N);
    for (uint i = 0; i < N; i++)
        vals[i] -= vec.vals[i];
    return *this;
}
template<typename T>
VectorDyn<T>& VectorDyn<T>::operator *= (const VectorDyn<T>& vec) {
    assert(N == vec.N);
    for (uint i = 0; i < N; i++)
        vals[i] *= vec.vals[i];
    return *this;
}
template<typename T>
VectorDyn<T>& VectorDyn<T>::operator /= (const VectorDyn<T>& vec) {
    assert(N == vec.N);
    for (uint i = 0; i < N; i++)
        vals[i] /= vec.vals[i];
    return *this;
}

template<typename T>//, typename T2>
VectorDyn<T>& VectorDyn<T>::operator += (const T& scalar) {
    for (uint i = 0; i < N; i++)
        vals[i] += scalar;
    return *this;
}
template<typename T>//, typename T2>
VectorDyn<T>& VectorDyn<T>::operator -= (const T& scalar) {
    for (uint i = 0; i < N; i++)
        vals[i] -= scalar;
    return *this;
}
template<typename T>//, typename T2>
VectorDyn<T>& VectorDyn<T>::operator *= (const T& scalar) {
    for (uint i = 0; i < N; i++)
        vals[i] *= scalar;
    return *this;
}
template<typename T>//, typename T2>
VectorDyn<T>& VectorDyn<T>::operator /= (const T& scalar) {
    for (uint i = 0; i < N; i++)
        vals[i] /= scalar;
    return *this;
}


// Unary operations
template<typename T>
VectorDyn<T> VectorDyn<T>::operator - () const {
    VectorDyn<T> result(N);
    for (uint i = 0; i < N; i++)
        result.vals[i] = -vals[i];
    return result;
}


// Other operations
template<typename T>
T VectorDyn<T>::dot(const VectorDyn<T>& vec) const {
    assert(N == vec.N);

    T sum(0);
    for (uint i = 0; i < N; i++)
        sum += vals[i] * vec.vals[i];
    return sum;
}
template<typename T>
T VectorDyn<T>::len2() const {
    return dot(*this);
}
template<typename T>
T VectorDyn<T>::len() const {
    return std::sqrt(len2());
}
template<typename T>
VectorDyn<T> VectorDyn<T>::norm() const {
    return (*this) / len();
}


// Access operations
template<typename T>
const T* VectorDyn<T>::operator * () const {
    return vals;
}
template<typename T>
uint VectorDyn<T>::size() const {
    return N;
}


// Static functions
template<typename T>
VectorDyn<T> VectorDyn<T>::round(const VectorDyn<T>& v) {
    uint N = v.size();
    T result[N];
    for (uint i = 0; i < N; i++)
        result[i] = std::round(v[i]);
    return VectorDyn<T>(N, result);
}

template<typename T>
VectorDyn<T> VectorDyn<T>::floor(const VectorDyn<T>& v) {
    uint N = v.size();
    T result[N];
    for (uint i = 0; i < N; i++)
        result[i] = std::floor(v[i]);
    return VectorDyn<T>(N, result);
}

template<typename T>
VectorDyn<T> VectorDyn<T>::min(const VectorDyn<T>& v, const VectorDyn<T>& m) {
    uint N = v.size();
    T result[N];
    for (uint i = 0; i < N; i++)
        result[i] = min(v[i], m[i]);
    return VectorDyn<T>(N, result);
}
template<typename T>
VectorDyn<T> VectorDyn<T>::min(const VectorDyn<T>& v, const T& m) {
    uint N = v.size();
    T result[N];
    for (uint i = 0; i < N; i++)
        result[i] = min(v[i], m);
    return VectorDyn<T>(N, result);
}

template<typename T>
VectorDyn<T> VectorDyn<T>::max(const VectorDyn<T>& v, const VectorDyn<T>& m) {
    assert(v.size() == m.size());
    uint N = v.size();
    T result[N];
    for (uint i = 0; i < N; i++)
        result[i] = max(v[i], m[i]);
    return VectorDyn<T>(N, result);
}
template<typename T>
VectorDyn<T> VectorDyn<T>::max(const VectorDyn<T>& v, const T& m) {
    uint N = v.size();
    T result[N];
    for (uint i = 0; i < N; i++)
        result[i] = max(v[i], m);
    return VectorDyn<T>(N, result);
}

template<typename T>
VectorDyn<T> VectorDyn<T>::clamp(const VectorDyn<T>& v, const VectorDyn<T>& min_, const VectorDyn<T>& max_) {
    return min(max(v, min_), max_);
}
template<typename T>
VectorDyn<T> VectorDyn<T>::clamp(const VectorDyn<T>& v, const T& min_, const T& max_) {
    return min(max(v, min_), max_);
}


// Binary scalar operations (LHS)
template <typename T>
VectorDyn<T> operator * (const T& scalar, const VectorDyn<T>& vec) {
    uint N = vec.size();
    VectorDyn<T> result(N);
    for (uint i = 0; i < N; i++)
        result[i] = scalar * vec[i];
    return result;
}
