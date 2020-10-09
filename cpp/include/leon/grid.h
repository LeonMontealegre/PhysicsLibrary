#ifndef __GRID_H__
#define __GRID_H__

#include "utils.h"
#include "vector.h"
#include "matrix.h"

template<uint N, uint M, typename T = double>
class Grid2D {
public:
    const Grid2D& operator = (const Matrix<N,M,T>& m) {
        for (uint i = 0; i < N; i++) {
            for (uint j = 0; j < M; j++) {
                if (!is_fixed(i, j))
                    grid[i][j] = m[i][j];
            }
        }
        return *this;
    }

    void set_fixed(uint i, uint j) {
        fixed_vals[i][j] = true;
    }

    bool is_fixed(uint i, uint j) const {
        return fixed_vals[i][j];
    }

    Vector<M,T>& operator [] (uint i) {
        return grid[i];
    }
    const Vector<M,T>& operator [] (uint i) const {
        return grid[i];
    }

    const Matrix<M,N,T>& operator *() const {
        return grid;
    }

private:
    Matrix<N,M,T> grid;
    Matrix<N,M,bool> fixed_vals;
};

#endif