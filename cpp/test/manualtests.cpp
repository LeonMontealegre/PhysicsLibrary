#include "../include/leon/vectordyn.h"
#include "../include/leon/matrix.h"
#include "../include/leon/vector.h"
#include "../include/leon/print_utils.h"

int main() {
    Vector<3> v({3, 5, 7});

    std::cout << v << std::endl;

    Matrix<3,3> d(1);

    std::cout << d << std::endl;

    Matrix<3,3> d2({{1,2,3}, {4,5,6}, {7,8,9}});

    std::cout << (d2) << std::endl;

    std::cout << ((d * d2) * d2) << std::endl;

    return 0;
}
