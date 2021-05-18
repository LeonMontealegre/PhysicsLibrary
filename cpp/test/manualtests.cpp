#include "../include/leon/vectordyn.h"
#include "../include/leon/matrixdyn.h"
#include "../include/leon/vector.h"
#include "../include/leon/print_utils.h"

int main() {
    Vector<3> v({3, 5, 7});

    std::cout << v << std::endl;

    MatrixDyn<> d(3, 3, 1);

    std::cout << d << std::endl;

    MatrixDyn<> d2({{1,4,7}, {2,5,8}, {3,6,9}});

    std::cout << (d * d2) << std::endl;

    return 0;
}
