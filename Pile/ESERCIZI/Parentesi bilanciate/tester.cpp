#include <iostream>
#include "bilanciate.h"

using std::string;

void runTestCases();

int main() {
    runTestCases();

    return 0;
}

void runTestCases() {
    Bilanciate<char> x;
    cout << "Primo test: ";
    x.test("for (i=0) to 10"); // bilanciate
    cout << "Secondo test: ";
    x.test("(3+2)/[3-(2-1)])"); // non bilanciate
    cout << "Terzo test: ";
    x.test("{1-(3+2)/[3-(2-1)]"); // non bilanciate
    cout << "Quarto test: ";
    x.test("{1-(3+2)/[3-(2-1))]}"); // non bilanciate
    cout << "Quinto test: ";
    x.test("{1-(3+2)/([3-(2-1)]}"); // non bilanciate
    cout << "Sesto test: ";
    x.test("{1-(3+2)/([3-(2-1)]}"); // non bilanciate
    cout << "Settimo test: ";
    x.test("{1-(3+2)/([3-(2-1)]"); // non bilanciate

}
