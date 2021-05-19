#include "../include/leon/matrixdyn.h"
#include "../include/leon/linalg.h"
#include "../include/leon/print_utils.h"

#include "expect.h"

int main() {
    // Matrix<1, 1> m(12);

    // std::cout << "Matrix: " << std::endl;
    // std::cout << m << std::endl;

    // auto m2 = invert(m);

    // std::cout << "Inverted Matrix: " << std::endl;
    // std::cout << m2 << std::endl;


    // Matrix<2, 2> m({{1, 3}, {2, 4}});

    // std::cout << "Matrix: " << std::endl;
    // std::cout << m << std::endl;

    // auto m2 = invert(m);

    // std::cout << "Inverted Matrix: " << std::endl;
    // std::cout << m2 << std::endl;


    test("Linear Algebra – Invert", []() {
        MatrixDyn<> d(3, 3, 1);
        MatrixDyn<> d2({{1,3,2}, {-3,-1,-3}, {2,3,1}});

        expect(invert(d)).toEqual(d);
        expect(invert(d2)).toEqual(MatrixDyn<>({{-8,-3,7}, {3,3,3}, {7,-3,-8}}) / 15);
        // expect(d2*d).toEqual(MatrixDyn<>({{6,6,6}, {15,15,15}, {24,24,24}}));
    });


    // Matrix<3, 3> m({{1, 4, 7}, {2, 5, 8}, {3, 6, 1}});

    // std::cout << "Matrix: " << std::endl;
    // std::cout << m << std::endl;

    // auto m2 = invert(m);

    // std::cout << "Inverted Matrix: " << std::endl;
    // std::cout << m2 << std::endl;


    return 0;
}
