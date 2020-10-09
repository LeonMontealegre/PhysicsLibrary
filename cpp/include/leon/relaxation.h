#ifndef __RELAXATION_H__
#define __RELAXATION_H__

#include "utils.h"

template<typename T>
void gauss_seidel_2d(T grid, uint w, uint h, uint N) {
    while (N > 0) {
        for (int i = 1; i < w-1; i++) {
            for (int j = 1; j < h-1; j++)
                grid[i][j] = (grid[i-1][j] + grid[i][j-1] + grid[i+1][j] + grid[i][j+1]) / 4;
        }
        N--;
    }
}

#endif