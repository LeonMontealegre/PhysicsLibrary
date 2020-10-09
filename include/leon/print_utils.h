#ifndef __PRINT_UTILS_H__
#define __PRINT_UTILS_H__

#include <iostream>
#include "utils.h"
#include "matrix.h"

template<uint N, typename T = double>
std::ostream& operator << (std::ostream& out, const Vector<N,T>& v) {
    for (uint j = 0; j < N; j++) {
        out << "[";
        out << v[j]; // "%2.2f"
        out << "]" << std::endl;
    }
    return out;
}

template<uint N, uint M, typename T = double>
std::ostream& operator << (std::ostream& out, const Matrix<N,M,T>& m) {
    for (uint j = 0; j < M; j++) {
        out << "[";
        for (uint i = 0; i < N; i++) {
            if (m[i][j] >= 0)
                out << " ";
            out << m[i][j]; // "%2.1f"
            if (i < N-1)
                out << " ";
        }
        out << "]";
        if (j < M-1)
            out << std::endl;
    }
    return out;
}

#endif