#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "dictionary.h"
#include "vectorList.h"
#include <string>
#include <stdexcept>

#define DEFAULT_DIVISOR 11

using std::cout;
using std::endl;
using std::ostream;
using std::string;

template<class T>
class hash {
public:
    size_t operator()(const T &the_key) const;
};

/* specializzazione col tipo stringa */
template<>
class hash<string> {
public:
    size_t operator()(const string &the_key) const {
        unsigned long hash_value = 0;
        int length = (int) the_key.length();
        for (int i = 0; i < length; i++) {
            // l'hash_value sara' la somma dei codici ASCII dei caratteri della stringa
            hash_value = 5 * hash_value + the_key.at(i);
        }

        return size_t(hash_value);
    }
};

template<class K, class E>
struct mypair;

template<class K, class E>
class hash_table : public dictionary<K, E> {
public:
    // costruttore di default
    hash_table();

    // costruttore con divisore da parametro
    hash_table(int);

    // distruttore
    ~hash_table() = default;

    // metodo che verifica se l'hash table e' vuota
    bool empty() const {
        return (dsize == 0);
    };

    // metodo che ritorna la size dell'hash table
    int size() const {
        return dsize;
    };

    int getDivisor() const {
        return divisor;
    }

    // metodo che elimina l'elemento con chiave k
    void erase(const K &k);

    // metodo che modifica l'elemento con chiave k con il valore e
    void modify(const K &k, const E &e);

    //  void create() {};

    // metodo che cerca una chiave k e ne restituisce la posizione
    int search(const K &) const;

    // cerca un valore con chiave k e ritorna il puntatore all'elemento
    mypair<K, E> *find(const K &) const;

    // metodo che inserisce un nuovo valore
    void insert(mypair<K, E> &);

    // metodo che verifica se il valore e' presente nell'hash table
    bool containsValue(const E &e) const;

    // metodo che ridimensiona la grandezza dell'hash table
    void resize();

    // metodo che ritorna la lista dei valori
    VectorList<E> values() const;

    // metodo che ritorna la lista delle chiavi
    VectorList<K> keys() const;

    E &operator[](K &);

    E operator[](K &) const;

    template<class C, class V>
    friend ostream &operator<<(ostream &os, const hash_table<C, V> &ht); // sovraccarico dell'operatore <<

private:
    mypair<K, E> **table; // the hash table
    hash<K> hashMap;      // maps type K to nonnegative integer
    int dsize;            // number of pairs in dictionary
    int divisor;          // hash function divisor (la lunghezza della tabella)
};

// Costruttore di default
template<class K, class E>
hash_table<K, E>::hash_table() {
    divisor = DEFAULT_DIVISOR;
    dsize = 0;

    table = new mypair<K, E> *[divisor];
    for (int i = 0; i < divisor; i++) {
        table[i] = nullptr;
    }
}

// Costruttore con divisore da parametro
template<class K, class E>
hash_table<K, E>::hash_table(int the_divisor) {
    divisor = the_divisor;
    dsize = 0;

    table = new mypair<K, E> *[divisor];
    for (int i = 0; i < divisor; i++) {
        table[i] = nullptr;
    }
}

// Metodo che cerca l'elemento con chiave k
template<class K, class E>
int hash_table<K, E>::search(const K &the_key) const {
    int i = (int) hashMap(the_key) % divisor; // the home bucket
    int j = i;
    do {
        if (table[j] == nullptr || table[j]->getKey() == the_key)
            return j;
        j = (j + 1) % divisor; // the next bucket
    } while (j != i);

    return j;
}

// Metodo che cerca un valore con chiave k e ritorna il puntatore all'elemento
template<class K, class E>
mypair<K, E> *hash_table<K, E>::find(const K &the_key) const {
    // search the table
    int b = search(the_key);
    // see if a match was found at table[b]
    if (table[b] == nullptr || table[b]->getKey() != the_key)
        return nullptr; // no match
    return table[b];    // matching pair
}

// Metodo che inserisce una nuova coppia
template<class K, class E>
void hash_table<K, E>::insert(mypair<K, E> &the_pair) {
    // search the table for a matching element
    if ((double) dsize >= (double) divisor * 0.7) {
        resize();
    }

    int i = search(the_pair.first);

    // check if matching element found
    if (table[i] == nullptr) {
        // no matching element and table not full
        table[i] = new mypair<K, E>(the_pair);
        dsize++;
    } else {
        // check if duplicate or table full
        if (table[i]->getKey() == the_pair.getKey()) {
            // duplicate, change table[i]->second
            table[i]->second = the_pair.second;
        } else
            throw std::out_of_range("Dizionario pieno");
    }
}

// Metodo che elimina l'elemento con chiave k
template<class K, class E>
void hash_table<K, E>::erase(const K &key) {
    if (dsize > 0) {
        if (find(key)) {
            int i = hashMap(key) % divisor;
            int j = i;
            bool elim = false;
            do {

                if (table[j]->getKey() == key) {
                    table[j] = nullptr;
                    dsize--;
                    elim = true;
                }
                j = (j + 1) % divisor;
            } while (j != i && !elim);
        } else
            throw std::out_of_range("CHIAVE NON ESISTENTE");
    } else
        throw std::out_of_range("MAPPA VUOTA");
}

// Metodo che modifica il valore della chiave k
template<class K, class E>
void hash_table<K, E>::modify(const K &k, const E &e) {
    for (int i = 0; i < divisor; i++) {
        if (table[i] != nullptr && table[i]->getKey() == k) {
            table[i]->second = e;
            return;
        }
    }
}

// Metodo che verifica se il valore e' presente nell'hash table
template<class K, class E>
bool hash_table<K, E>::containsValue(const E &e) const {
    for (int i = 0; i < divisor; i++) {
        if (table[i] != nullptr) {
            cout << "table[i]->second: " << table[i]->second << endl;
        }
        if (table[i] != nullptr && table[i]->second == e)
            return true;
    }
    return false;
}

// Metodo che ridimensiona l'hash table
template<class K, class E>
void hash_table<K, E>::resize() {
    mypair<K, E> **old_table = table;
    divisor *= 2;
    table = new mypair<K, E> *[divisor];
    for (int i = 0; i < divisor; i++) {
        table[i] = nullptr;
    }
    for (int j = 0; j < divisor / 2; j++) {
        table[j] = old_table[j];
    }
    delete[] old_table;
    this->divisor = divisor;
}

// sovraccarico dell'operatore <<
template<class C, class V>
ostream &operator<<(ostream &os, const hash_table<C, V> &ht) {

    for (int i = 0; i < ht.divisor; i++) {

        os << i << ": [";
        if (ht.table[i] != nullptr) {
            os << ht.table[i]->getKey() << "," << ht.table[i]->getValue();
        }
        os << "]" << endl;
    }
    return os;
}

template<class K, class E>
VectorList<E> hash_table<K, E>::values() const {
    VectorList<E> L;
    for (int i = 0; i < divisor; i++) {
        if (table[i] != nullptr) {
            L.tailInsert(table[i]->second);
        }
    }
    return L;
}

template<class K, class E>
VectorList<K> hash_table<K, E>::keys() const {
    VectorList<K> keys;
    for (int i = 0; i < divisor; i++) {
        if (table[i] != nullptr) {
            keys.tailInsert(table[i]->first);
        }
    }
    return keys;
}

template<class K, class E>
E &hash_table<K, E>::operator[](K &key) {
    if (find(key)) {
        return find(key)->second;
    } else {
        throw std::out_of_range("CHIAVE NON ESISTENTE");
    }
}

template<class K, class E>
E hash_table<K, E>::operator[](K &key) const {
    if (find(key)) {
        return find(key)->second;
    } else {
        throw std::out_of_range("CHIAVE NON ESISTENTE");
    }
}

#endif
