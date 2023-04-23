#ifndef LINEARLIST_H
#define LINEARLIST_H

#include <iostream>
#include <ostream>

using std::cout;
using std::endl;
using std::ostream;

template<class T, class P>
class LinearList {
public:
    typedef T value_type; // Tipo di dato della lista
    typedef P position;   // Tipo di dato della position

    // Crea una lista vuota
    // virtual void create() = 0; sostituita dal costruttore

    // Controlla se la lista è vuota
    virtual bool empty() const = 0;

    // Legge il valore presente in una data position della lista
    virtual value_type read(position) const = 0;

    // Scrive un valore in una data position della lista */
    virtual void write(const value_type &, position) = 0;

    // Ritorna la position del primo elemento della lista
    virtual position begin() const = 0;

    // Controlla se la position passata come parametro è l'ultima della lista

    virtual bool end(position) const = 0;

    // Ritorna la position successiva a quella passata come parametro
    virtual position next(position) const = 0;

    // Ritorna la position precedente a quella passata come parametro
    virtual position prev(position) const = 0;

    // Inserisce un valore in una data position della lista
    virtual void insert(const value_type &, position) = 0;

    // Cancella un valore in una data position della lista
    virtual void erase(position) = 0;

    // funzioni di servizio
    /**
     * Overload dell'operatore << per la stampa della lista
     */
    template<typename T1, typename P1>
    friend ostream &operator<<(ostream &, const LinearList<T1, P1> &);

    /**
     * Cancella tutti gli elementi della lista
     */
    virtual void clear() {
        while (!empty()) {
            erase(begin());
        }
    }

    /**
     * Ritorna la dimensione della lista
     *
     */
    int size() const {
        position p = begin();
        int c = 0;
        while (!end(p)) {
            c++;
            p = next(p);
        }
        return c;
    }

    bool palindroma();

    bool exists(T &e) const;

};

template<class T, class P>
ostream &operator<<(ostream &os, const LinearList<T, P> &list) {
    typename LinearList<T, P>::position p;
    p = list.begin();
    os << "[";
    while (!list.end(p)) {
        if (p != list.begin())
            os << ", " << list.read(p);
        else
            os << list.read(p);
        p = list.next(p);
    }
    os << "]" << endl;
    return os;
}

template<class T, class P>
bool LinearList<T, P>::palindroma() {
    position first = begin();
    position last = end();
    for (int i = 0; i < (size() / 2); i++) {
        if (read(first) != read(last)) {
            return false;
        }
        first = next(first);
        last = prev(last);
    }
    return true;
}

template<class T, class P>
bool LinearList<T, P>::exists(T &e) const {
    position p = begin();
    while (!end(p)) {
        if (read(p) == e)
            return true;
        else
            p = next(p);
    }
    return false;
}

#endif // LINEARLIST_H