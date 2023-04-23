#ifndef _CODAVT_
#define _CODAVT_

#include <iostream>
#include "coda.h"

#define DEFAULT_SIZE 64

using std::ostream;

// Implementazione della coda con vettore circolare

template<class T>
class Queue_vt {

public:
    typedef typename Queue<T>::value_type value_type;

    // costruttore con vettore di dimensione default
    Queue_vt();

    // Costruttore con dimensione da parametro
    Queue_vt(int);

    // TODO: costruttore di copia?
    Queue_vt(const Queue_vt &);

    // distruttore
    ~Queue_vt();

    // metodo per verificare se la coda e' vuota
    bool empty() const;

    // metodo per leggere l'elemento in testa alla coda
    value_type read() const;

    // metodo per inserire l'elemento in coda alla coda
    void push(const value_type &);

    // metodo per estrarre l'elemento in testa alla coda
    void pop();

    // funzioni accessorie
    // metodo per ottenere la lunghezza della coda
    // TODO
    int getLength() const;

    // metodo che verifica dato un valore se questo e' presente nella coda
    bool exists(value_type &);

    // TODO
    Queue_vt<T> &operator=(const Queue_vt<T> &);

    // TODO
    bool operator==(const Queue_vt<T> &);

    template<class K>
    friend ostream &operator<<(ostream &os, const Queue_vt<K> &q); // sovraccarico dell'operatore <<

private:
    T *elems;
    int head;
    int tail; // lo usiamo come numero di elementi presenti
    int dim;
};

// Costruttore di default
template<class T>
Queue_vt<T>::Queue_vt() {
    dim = DEFAULT_SIZE;
    elems = new T[dim];
    head = 0;
    tail = 0;
}

// Costruttore con dimensione da parametro
template<class T>
Queue_vt<T>::Queue_vt(int n) {
    dim = n;
    elems = new T[dim];
    head = 0;
    tail = 0;
}

// Distruttore
template<class T>
Queue_vt<T>::~Queue_vt() {
    delete[] elems;
}

// Metodo che verifica se la coda e' vuota
template<class T>
bool Queue_vt<T>::empty() const {
    return (tail == 0);
}

// Metodo che restituisce l'elemento in testa alla lista
template<class T>
typename Queue_vt<T>::value_type
Queue_vt<T>::read() const {
    if (!empty()) {
        return (elems[head]);
    } else {
        throw std::out_of_range("Coda vuota");
    }
}

// Metodo che rimuove l'elemento in testa alla coda
template<class T>
void Queue_vt<T>::pop() {
    if (!empty()) {
        head = (head + 1) % dim;
        tail--;
    }
}

// metodo che inserisce un elemento in coda alla lista
template<class T>
void Queue_vt<T>::push(const value_type &a) {
    elems[(tail + head) % dim] = a;
    tail++;
}

// sovraccarico dell'operatore <<
template<class K>
std::ostream &operator<<(std::ostream &os, const Queue_vt<K> &q) {
    os << "[";

    if (!q.empty()) {
        int read = 0;
        int i = q.head % q.dim;
        while (read < q.dim - (q.tail % q.dim)) {
            if (i == (q.head % q.dim)) {
                os << q.elems[i % q.dim];
            } else {
                os << ", " << q.elems[i % q.dim];
            }
            read++;
            i++;
        }

    }
    os << "]" << std::endl;

    return os;
}

// metodo che verifica la presenza di un elemento x nella coda
template<class T>
bool Queue_vt<T>::exists(value_type &x) {
    value_type val;

    while (!empty()) {
        val = this->read();
        if (x == val) {
            return true;
        }
        this->pop();
    }

    return false;

}

#endif // CODAVT_
