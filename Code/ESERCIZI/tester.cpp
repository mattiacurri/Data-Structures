#include <iostream>
#include "bins.h"

using std::cout;
using std::endl;

int main() {
    Bins b;
    b.insert(7);
    b.insert(8);
    b.insert(9);
    // b.erase(2);
    cout << b.mean(2) << endl;
    cout << b.freq(2) << endl;
    return 0;
}