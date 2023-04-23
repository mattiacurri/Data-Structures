#include <iostream>
#include "set.h"

int main() {
    set<int> A;
    A.insert(10);
    set<int> B;
    B = A;
    std::cout << B.sottoInsieme(A) << std::endl;
    std::cout << A << std::endl;
}