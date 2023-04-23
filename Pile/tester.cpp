#include <iostream>

#include "pilavt.h"
//#include "pilavt.h"
#include <random>

using namespace std;

int main()
{
    // Stack_vt<char> z;
    // Stack_vt<char> x;
    
    //bool e = z.empty();
    //cout << boolalpha << e;
    //cout << endl;
    // z.push('a');
    // cout << z.peek() << endl;
    // z.push('b');
    // z.push('c'); //
    // cout << z << endl;
    // x = z;
    // x.push('s');
    // z.push('x');
    // z.push('a');
    // cout << x << endl;
    // cout << z << endl;
    /*Stack_vt<char> y = z.reverse(z);
    cout << y << endl;
    srand(time(nullptr));
    Stack_vt<int> numeri;
    for (int i = 0; i < 8; i++) {
        numeri.push(rand() % 9 + 1);
    }
    cout << numeri << endl;
    cout << numeri.reverse(numeri) << endl;
    cout << numeri.count(numeri, 5) << endl;
    cout << numeri << endl;
    numeri.remove(numeri, 5);
    cout << numeri << endl;
    cout << numeri.reverse(numeri) << endl;
    cout << (z == x) << endl;
    */
    //Stack_vt<int> num;
    //num.push(2);
    //num.push(19);
    //num.push(1);
    //num.push(7);
    //cout << num << endl;
    //Stack_vt<int> numSorted = num.sortStack(num);
    //cout << numSorted << endl;

    Stack_vt<int> numeri;
    numeri.push(1);
    numeri.push(2);
    numeri.push(192);
    numeri.push(11);
    numeri.push(22);
    numeri.push(23);
    numeri.push(6);
    numeri.push(5);
    numeri.push(4);
    numeri.push(8);
    numeri.push(7);
    numeri.push(6);
    cout << numeri << endl;

    numeri.eraseK(numeri, 9);
    cout << numeri << endl;
    return 0;
}