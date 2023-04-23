#ifndef BINS_H
#define BINS_H

#include <vector>
#include "../codapt.h"

using std::cout;
using std::endl;

class Bins {
public:
    void insert(int k);

    void erase(int c);

    double mean(int c);

    int freq(int c);

private:
    Queue_pt<int> bin[3];
};

void Bins::insert(int k) {
    if (k > 9) {
        throw std::out_of_range("Numero maggiore di 9");
    } else if (k >= 1 && k <= 3) {
        bin[0].push(k);
    } else if (k >= 4 && k <= 6) {
        bin[1].push(k);
    } else {
        bin[2].push(k);
    }
}

void Bins::erase(int c) {
    if (c > 2 || c < 0) {
        throw std::out_of_range("Bin non esistente");
    } else {
        bin[c].pop();
    }
}

double Bins::mean(int c) {
    if (c > 2 || c < 0) {
        throw std::out_of_range("Bin non esistente");
    } else if (bin[c].empty()) {
        return 0;
    } else {
        Queue_pt<int> tmp = bin[c];
        int sum = 0;
        int count = 0;
        while (!tmp.empty()) {
            sum += tmp.read();
            count++;
            tmp.pop();
        }
        return (double) sum / count;
    }
}

int Bins::freq(int c) {
    if (c > 2 || c < 0) {
        throw std::out_of_range("Bin non esistente");
    } else {
        return bin[c].getLength();
    }
}

#endif //BINS_H
