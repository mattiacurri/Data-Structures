#include <iostream>
// #include "codapt.h"
#include "codavt.h"

using namespace std;

int main() {

    Queue_vt<int> C;
    for (int i = 0; i < 10; i++) {
        C.push(i);
    }
    cout << C << endl;

    C.pop();
    C.pop();
    C.push(1000);
    C.pop();
    C.push(1001);
    C.pop();
    C.push(1002);
    C.pop();
    C.push(1003);
    C.push(1004);
    C.push(1005);
    C.push(1006);
    C.push(1007);
    C.pop();
    C.pop();
    cout << C << endl;

    // Queue_vt<int> X(C);

    // cout << X.getLength() << endl;
    // cout << C.getLength() << endl;
}
