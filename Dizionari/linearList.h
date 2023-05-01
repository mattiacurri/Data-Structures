#ifndef LINEARLIST_H
#define LINEARLIST_H

/*
crealista : ( ) → lista 
listavuota : ( lista) → boolean
leggilista : (posizione, lista) → tipoelem
scrivilista : (tipoelem,posizione,lista) → lista
primolista : (lista) → posizione
finelista : (posizione, lista) → boolean
succlista : (posizione, lista) → posizione
predlista : (posizione, lista) → posizione
inslista : (tipoelem,posizione,lista) → lista
canclista : (posizione, lista) → lista
*/

#include <iostream>
#include <ostream>

using std::cout;
using std::endl;
using std::ostream;

template<class T, class P>
class LinearList {
public:
    typedef T value_type;
    typedef P position;

    virtual void create() = 0;

    virtual bool empty() const = 0;

    virtual value_type read(position) const = 0;

    virtual void write(const value_type &, position) = 0;

    virtual position begin() const = 0;

    virtual bool end(position) const = 0;

    virtual position next(position) const = 0;

    virtual position prev(position) const = 0;

    virtual void insert(const value_type &, position) = 0;

    virtual void erase(position) = 0;

    // funzioni di servizio
    template<typename T1, typename P1>
    friend ostream &operator<<(ostream &, const LinearList<T1, P1> &);

    int size() const {
        position p = begin();
        int c = 0;
        while (!end(p)) {
            c++;
            p = next(p);
        }
        return c;
    }  // returns the size of the list

    /*
    Implementabili
    virtual void push_front(const value_type &); // insert a new element at the beginning
    virtual void push_back(const value_type &); // insert a new element at the end
    virtual void pop_front(); // removes the first element
    virtual void pop_back(); // removes the last element
    */

    virtual void clear() {
        while (!empty()) {
            erase(begin());
        }
    } // erases all the elements

};

/* sovraccarica <<. Attenzione se il tipo restituito da read non e' primitivo, allora
 * anche per questo tipo bisogna sovraccaricare l'operatore <<
 */
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

#endif // LINEARLIST_H