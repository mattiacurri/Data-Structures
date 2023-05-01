#ifndef LINKEDLIST_EO_STRINGS_H
#define LINKEDLIST_EO_STRINGS_H

#include <iostream>
#include "linkedList.h"

using std::string;

class eo_strings {
public:
// inserisce una stringa nella corrispondente lista
    void inserisci(string s);

// rimuove la stringa dalla corrispondente lista
    void rimuovi(string s);

// rimuove le stringhe di lunghezza pari che iniziano con il carattere c
    void rimuovi(char c);

// restituisce il numero di stringhe di lunghezza pari
    int freq_pari();

// visualizza le stringhe di lunghezza dispari ordinate per lunghezza
    void visualizza_dispari();

private:
    LinkedList <string> pari;
    LinkedList <string> dispari;
};

void eo_strings::inserisci(string s) {
    if (s.length() % 2 == 0) {
        pari.tailInsert(s);
    } else {
        dispari.tailInsert(s);
    }
}

void eo_strings::rimuovi(string s) {
    LinkedList<string>::position p = pari.begin();
    while (!pari.end(p)) {
        string toRemove = pari.read(p);
        if (toRemove == s) {
            if (toRemove.length() % 2 == 0) {
                pari.erase(p);
            } else {
                dispari.erase(p);
            }
        }
        p = pari.next(p);
    }
    cout << pari;
}

void eo_strings::rimuovi(char c) {
    LinkedList<string>::position p = pari.begin();
    while (!pari.end(p)) {
        string s = pari.read(p);
        if (s[0] == c) {
            pari.erase(p);
        }
        p = pari.next(p);
    }
}

int eo_strings::freq_pari() {
    return pari.getLength();
}

void eo_strings::visualizza_dispari() {
    int len[dispari.getLength()];
    auto p = dispari.begin();
    string a;
    int i = 0;
    while (!dispari.end(p)) {
        a = dispari.read(p);
        len[i] = a.size();
        p = dispari.next(p);
        i++;
    }

    cout << endl;
    for (i = 0; i < dispari.getLength(); i++) {
        int temp = len[i];
        if (temp >= len[0]) {
            int z = temp;
            temp = len[0];
            len[0] = z;
            len[i] = temp;
        }
    }

    cout << "[ ";
    for (i = 0; i < dispari.getLength(); i++) {
        p = dispari.begin();
        while (!dispari.end(p)) {
            string x = dispari.read(p);
            if (x.length() == len[i]) {
                cout << x << " ";
            }
            p = dispari.next(p);
        }
    }
    cout << "]";
}

#endif //LINKEDLIST_EO_STRINGS_H
