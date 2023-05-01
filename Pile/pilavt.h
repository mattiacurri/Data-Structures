#ifndef PILAVT_H
#define PILAVT_H

#define DEFAULT_SIZE 64

#include <iostream>
#include "pila.h"
#include "exceptions.h"

template<class T>
class Stack_vt {
public:
    // rinomino i tipi
    typedef T valuetype;

    // costruttori
    Stack_vt();

    Stack_vt(int);

    // costruttore di copia
    Stack_vt(const Stack_vt<T> &src);

    // distruttore
    ~Stack_vt();

    // operatori

    // metodo che verifica se una pila e' vuota
    bool empty() const;

    // metodo che restituisce l'elemento al top
    valuetype peek() const;

    // metodo che elimina l'elemento al top restituendolo
    valuetype pop();

    // metodo che inserisce un elemento al top
    void push(const valuetype &);

    template<class K>
    friend std::ostream &operator<<(std::ostream &os, const Stack_vt<K> &s); // sovraccarico dell'operatore <<

    Stack_vt &operator=(const Stack_vt &src); // sovraccarico dell'operatore =
    bool operator==(const Stack_vt<T> &src); // sovraccarico dell'operatore ==

    Stack_vt<int> sortStack(Stack_vt<int> &);

    // data una pila di interi, eliminare tutti gli elementi maggiori di k
    Stack_vt<int> eraseK(Stack_vt<int> &, int);

private:
    valuetype *elems;
    int maxLength;
    int head;
};

// Costruttore di default
template<class T>
Stack_vt<T>::Stack_vt() {
    elems = new valuetype[DEFAULT_SIZE];
    maxLength = DEFAULT_SIZE;
    head = 0;
}

// Costruttore con dimensione da parametro
template<class T>
Stack_vt<T>::Stack_vt(int N) {
    elems = new valuetype[N];
    maxLength = N;
    head = 0;
}

// Costruttore di copia
template<class T>
Stack_vt<T>::Stack_vt(const Stack_vt<T> &src) {
    this->maxLength = src.maxLength;
    this->head = src.head;

    // allocazione dello spazio
    this->elems = new T[maxLength];

    // copia degli elems
    for (int i = 0; i <= head; ++i) {
        this->elems[i] = src.elems[i];
    }
}

// Distruttore
template<class T>
Stack_vt<T>::~Stack_vt() {
    delete[] elems;
};

// metodo che verifica se una pila e' vuota
template<class T>
bool Stack_vt<T>::empty() const {
    return head == 0;
}

// metodo che restituisce l'elemento al top
template<class T>
T Stack_vt<T>::peek() const {
    if (this->empty()) {
        throw EmptyStackException();
    }
    return this->elems[head - 1];
}

// metodo che elimina l'elemento al top restituendolo
template<class T>
T Stack_vt<T>::pop() {
    T tmp;
    if (!empty()) {
        tmp = this->peek();
        head -= 1;
    } else {
        throw EmptyStackException();
    }
    return tmp;
}

// metodo che inserisce un elemento in cima allo stack
template<class T>
void Stack_vt<T>::push(const valuetype &el) {
    try {
        if (head != maxLength) {
            elems[head] = el;
            head++;
        } else {
            throw IndexOutOfBoundException(maxLength + 1, this->maxLength, __LINE__, __FILE__);
        }
    }
    catch (IndexOutOfBoundException &e) {
        std::cerr << e.what() << std::endl;
        throw;
    }
}

// sovraccarico dell'operatore <<
template<class K>
std::ostream &operator<<(std::ostream &os, const Stack_vt<K> &s) {
    os << "BOT[";
    if (!s.empty()) {
        int i = 0;
        while (i < s.head - 1) {
            os << s.elems[i] << "|";
            i++;
        }
        os << s.elems[i];
    }
    os << "]TOP" << std::endl;

    return os;
}

// sovraccarico dell'operatore =
template<class T>
Stack_vt<T> &Stack_vt<T>::operator=(const Stack_vt<T> &src) {
    // elimino il vecchio vettore di elems dello stack
    delete[] elems;

    // verifico che lo stack copiato e' vuoto
    if (src.empty()) {
        head = 0;
        maxLength = 0;
    } else {
        // assegno i valori di head e maxLength del vettore elems dello stack copiato
        head = src.head;
        maxLength = src.maxLength;

        // alloco il vettore di elems
        elems = new T[maxLength];

        // copio gli elems nello Stack
        for (int i = head; i >= 0; i--) {
            elems[i] = src.elems[i];
        }
    }
    return *this;
}

// sovraccarico dell'operatore ==
template<class T>
bool Stack_vt<T>::operator==(const Stack_vt<T> &src) {
    if (this->head != src.head) {
        return false;
    } else {
        for (int i = 0; i < this->head; i++) {
            if (this->elems[i] != src.elems[i]) {
                return false;
            }
        }
    }
    return true;
}

template<class T>
Stack_vt<int> Stack_vt<T>::sortStack(Stack_vt<int> &S) {
    Stack_vt<int> output;
    while (!S.empty()) {
        int val = S.pop();
        while (!output.empty() && output.peek() > val) {
            S.push(output.pop());
        }
        output.push(val);
    }
    return output;
}

template<>
Stack_vt<int> Stack_vt<int>::eraseK(Stack_vt<int> &S, int k) {
    Stack_vt<int> temp;
    while (!S.empty()) {
        if (S.peek() < k) {
            temp.push(S.pop());
        } else {
            S.pop();
        }
    }
    while (!temp.empty()) {
        S.push(temp.peek());
        temp.pop();
    }
    return S;
}

#endif // PILAVT_H

