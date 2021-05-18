#include "../include/leon/matrixdyn.h"
// #include "../include/leon/matrix.h"

#include <iostream>
#include "expect.h"

int main() {
    test("MatrixDyn – Basic Arithmetic", []() {
        MatrixDyn<> d(3, 3, 1);
        MatrixDyn<> d2({{1,2,3}, {4,5,6}, {7,8,9}});

        expect(d*d2).toEqual(MatrixDyn<>({{12,15,18}, {12,15,18}, {12,15,18}}));
        expect(d2*d).toEqual(MatrixDyn<>({{6,6,6}, {15,15,15}, {24,24,24}}));
    });
    test("MatrixDyn – Advanced Arithmetic", []() {
        MatrixDyn<> d(3, 3, 1);
        MatrixDyn<> d2({{1,2,3}, {4,5,6}, {7,8,9}});
        MatrixDyn<> d3({{1,3,2}, {-3,-1,-3}, {2,3,1}});
        MatrixDyn<> d4({{4,-3}, {-3, 5}});

        expect(d.det()).toEqual(0);
        expect(d2.det()).toEqual(0);
        expect(d3.det()).toEqual(-15);
        expect(d4.det()).toEqual(11);
    });


    return 0;
}
