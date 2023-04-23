#include <iostream>
#include <random>
#include <chrono>

#include "linkedList.h"

void generaValori(LinkedList<int> &l);
void testCase(LinkedList<int> l);

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    LinkedList<int> lista;
    generaValori(lista);
    cout << lista << endl;
    testCase(lista);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

    std::cout << "Tempo di esecuzione: " << duration << " ms" << std::endl;
    return 0;
}

void generaValori(LinkedList<int> &l) {
    srand(time(nullptr));
    for (int i = 0; i < 20; i++) {
        int x = rand() % 10 + 1;
        l.headInsert(x);
    }



}

void testCase(LinkedList<int> l) {
    cout << "Multipli di 1: " << l.freq(l, 1) << endl;
    cout << "Multipli di 2: " << l.freq(l, 2) << endl;
    cout << "Multipli di 3: " << l.freq(l, 3) << endl;
    cout << "Multipli di 5: " << l.freq(l, 5) << endl;
    cout << "Multipli di 7: " << l.freq(l, 7) << endl;

    //l.remp(l);
    //cout << l << endl;

    l.hist(l);
}

