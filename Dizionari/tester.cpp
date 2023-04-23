#include <iostream>
#include <random>

#include "hashtableAperto.h"


using std::cout;
using std::endl;

int main() {
    /*hash_table<string, int> ht(10);
    mypair<string, int> p;
    srand(time(nullptr));
    p.first = "hello";
    p.second = rand() % 10 + 1;
    ht.insert(p);
    p.first = "helol";
    p.second = rand() % 10 + 1;
    ht.insert(p);
    p.first = "mario";
    p.second = rand() % 10 + 1;
    ht.insert(p);
    p.first = "mattia";
    p.second = rand() % 10 + 1;
    ht.insert(p);
    p.first = "emanuele";
    p.second = rand() % 10 + 1;
    ht.insert(p);
    p.first = "davide";
    p.second = rand() % 10 + 1;
    ht.insert(p);
    p.first = "ronaldo";
    p.second = rand() % 10 + 1;
    ht.insert(p);
    p.first = "messi";
    p.second = rand() % 10 + 1;
    ht.insert(p);

    p.first = "siuuu";
    p.second = rand() % 10 + 1;
    ht.insert(p);
    p.first = "clion";
    p.second = rand() % 10 + 1;
    ht.insert(p);
    p.first = "asd";
    p.second = rand() % 10 + 1;
    ht.insert(p);
    p.first = "elefante";
    p.second = rand() % 10 + 1;
    ht.insert(p);

    cout << ht << endl;

    cout << ht.values() << endl;

    ht.modify("hello", 100);

    cout << ht.values() << endl;
    cout << ht.keys() << endl;*/

    open_hash_table<string, int> ht(10);
    return 0;
}