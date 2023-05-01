#ifndef HISTO_H
#define HISTO_H

#include <iostream>
#include <string>
#include "hash_table.h"

#define DEFAULTSIZE 10

using namespace std;

class histo {
public:
    histo();

    void add(int v);

    void remove(int v);

    int mode();

    double mean();

    void print();

    friend ostream &operator<<(ostream &os, const histo &h);

private:
    hash_table<int, int> hist;

};

histo::histo() : hist(DEFAULTSIZE) {}

void histo::add(int v) {
    mypair<int, int> p;
    if (!hist.find(v)) {
        p.setKey(v);
        p.setValue(1);
        hist.insert(p);
    } else {
        p.setKey(v);
        p.setValue(hist[v] + 1);
        hist.insert(p);
    }
}

void histo::remove(int v) {
    mypair<int, int> p;
    if (hist.containsValue(v)) {
        if (hist[v] >= 2) {
            p.setKey(v);
            p.setValue(hist[v] - 1);
            hist.insert(p);
        } else {
            hist.erase(v);
        }
    }
}

int histo::mode() {

    int max = 0;
    int bestkey;
    VectorList<int> keys = hist.keys();
    VectorList<int>::position p = keys.begin();
    while (!keys.end(p)) {
        int key = keys.read(p);

        if (hist[key] > max) {
            max = hist[key];
            bestkey = key;
        }
        p = keys.next(p);

    }

    return bestkey;
}

double histo::mean() {

    VectorList<int> keys = hist.keys();
    VectorList<int>::position p = keys.begin();

    double result = 0;
    while (!keys.end(p)) {

        result += keys.read(p);

        p = keys.next(p);

    }

    return result / keys.size();

}

void histo::print() {

    VectorList<int> keys = hist.keys();
    VectorList<int>::position p = keys.begin();

    while (!keys.end(p)) {

        int key = keys.read(p);

        cout << key << " ";

        string value(hist[key], '*');

        cout << value << endl;

        p = keys.next(p);
    }
}

ostream &operator<<(ostream &os, const histo &h) {

    VectorList<int> keys = h.hist.keys();
    VectorList<int>::position p = keys.begin();
    while (!keys.end(p)) {

        int key = keys.read(p);

        os << key << " ";

        string value(h.hist[key], '*');

        os << value << endl;

        p = keys.next(p);
    }
    cout << h.hist << endl;
    return os;
}

#endif
