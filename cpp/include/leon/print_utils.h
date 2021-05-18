#ifndef __PRINT_UTILS_H__
#define __PRINT_UTILS_H__

#include <iostream>
#include "utils.h"
#include "vectordyn.h"
#include "matrixdyn.h"

// TODO: fix the fact that these only work for like single-digit integers

template<typename T = double>
std::ostream& operator << (std::ostream& out, const VectorDyn<T>& v) {
    out << "┌ ┐" << std::endl;
    for (uint j = 0; j < v.size(); j++) {
        out << "│";
        out << v[j]; // "%2.2f"
        out << "│" << std::endl;
    }
    out << "└ ┘" << std::endl;
    return out;
}

template<typename T = double>
std::ostream& operator << (std::ostream& out, const MatrixDyn<T>& m) {
    uint N = m.num_cols();
    uint M = m.num_rows();

    out << "┌";
    for (uint i = 0; i < N; i++)
        out << "   ";
    out << "┐" << std::endl;

    for (uint j = 0; j < M; j++) {
        out << "│";
        for (uint i = 0; i < N; i++) {
            if (m[i][j] >= 0)
                out << " ";
            out << m[i][j] << " ";
        }
        out << "│" << std::endl;
    }

    out << "└";
    for (uint i = 0; i < N; i++)
        out << "   ";
    out << "┘";

    return out;
}

#endif