#include "../include/leon/vectordyn.h"
#include "../include/leon/vector.h"
#include "../include/leon/print_utils.h"

int main() {
    Vector<3> v({3, 5, 7});

    std::cout << v << std::endl;

    return 0;
}
