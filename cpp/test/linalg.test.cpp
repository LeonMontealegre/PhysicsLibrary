#include "../include/leon/matrix.h"
#include "../include/leon/linalg.h"
#include "../include/leon/print_utils.h"

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


    Matrix<3, 3> m({{1, 4, 7}, {2, 5, 8}, {3, 6, 1}});

    std::cout << "Matrix: " << std::endl;
    std::cout << m << std::endl;

    auto m2 = invert(m);

    std::cout << "Inverted Matrix: " << std::endl;
    std::cout << m2 << std::endl;


    return 0;
}
