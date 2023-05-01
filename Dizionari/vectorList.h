#ifndef VECTORLIST_H
#define VECTORLIST_H

/*
crealista : ( ) → lista 
listavuota : ( lista) → boolean
leggilista : (posizione, lista) → value_type
scrivilista : (value_type,posizione,lista) → lista
primolista : (lista) → posizione
finelista : (posizione, lista) → boolean
succlista : (posizione, lista) → posizione
predlista : (posizione, lista) → posizione
inslista : (value_type,posizione,lista) → lista
canclista : (posizione, lista) → lista
*/

// TODO: documentare meglio i metodi

#include "linearList.h"
#include "exceptions.h"

template<class T>
class VectorList : public LinearList<T, int> {
public:
    typedef typename LinearList<T, int>::value_type value_type;
    typedef typename LinearList<T, int>::position position;

    // costruttori
    VectorList();

    VectorList(int);

    // costruttore di copia
    VectorList(const VectorList<T> &);

    // distruttore
    ~VectorList();

    // operatori
    void create();

    bool empty() const;

    value_type read(position) const;

    void write(const value_type &, position);

    position begin() const;

    bool end(position) const;

    position next(position) const;

    position prev(position) const;

    void insert(const value_type &, position);

    void erase(position);

    // sovraccarico di operatori
    VectorList<T> &operator=(const VectorList<T> &); // the assignment operator
    bool operator==(const VectorList<T> &) const; // tests two list for equality

    // funzioni accessorie
    void tailInsert(const VectorList::value_type &);

private:
    void change_dimension_(T *&, int, int);

    value_type *elem;
    int length;
    int array_dim;
};

// Costruttori
template<class T>
VectorList<T>::VectorList() {
    array_dim = 10;
    length = 0;
    this->create();
}

template<class T>
VectorList<T>::VectorList(int dim) {
    array_dim = dim;
    length = 0;
    this->create();
}

template<class T>
VectorList<T>::VectorList(const VectorList<T> &copiedList) {
    // assegno i valori di lunghezza del vettore e della lista
    array_dim = copiedList.array_dim;
    length = copiedList.length;

    // alloco la lista
    this->elem = new T[array_dim];

    // copio i valori
    for (int i = 0; i < length; i++) {
        this->elem[i] = copiedList.elem[i];
    }
}

// Distruttore
template<class T>
VectorList<T>::~VectorList() {
    delete[] elem;
}

template<class T>
void VectorList<T>::create() {
    this->elem = new T[array_dim];
    this->length = 0;
}

template<class T>
bool VectorList<T>::empty() const {
    if (this->length == 0) {
        return true;
    } else {
        return false;
    }
}

template<class T>
typename VectorList<T>::position VectorList<T>::begin() const {
    return (1);
}

template<class T>
bool VectorList<T>::end(position p) const {
    if (p > 0 && p >= length + 1) {
        return (p == length + 1);
    } else {
        return false;
    }
}

template<class T>
typename VectorList<T>::position VectorList<T>::next(position p) const {
    if (p > 0 && p < length + 1) {
        return (p + 1);
    } else {
        return (p);
    }
}

template<class T>
typename VectorList<T>::position VectorList<T>::prev(position p) const {
    if (p > 1 && p < length + 1) {
        return (p - 1);
    } else {
        return (p);
    }
}

template<class T>
typename VectorList<T>::value_type VectorList<T>::read(position p) const {
    if (p > 0 && p < length + 1) {
        return elem[p - 1];
    } else {
        throw PositionOutOfRange();
    }
}

template<class T>
void VectorList<T>::write(const value_type &v, position p) {
    if (p > 0 && p < length + 1) {
        elem[p - 1] = v;
    }
}

template<class T>
void VectorList<T>::erase(position p) {
    if ((0 < p) && (p < length + 1)) // precondizione
    {
        if (!empty()) {
            for (int i = p - 1; i < (length - 1); i++) {
                elem[i] = elem[i + 1];
            }
            length--;
        }
    }
}

template<class T>
VectorList<T> &VectorList<T>::operator=(const VectorList<T> &l) {
    if (this != &l) {
        this->array_dim = l.array_dim;
        this->length = l.length;
        delete this->elem;
        this->elem = new T[array_dim];
        for (int i = 0; i < l.array_dim; i++) {
            this->elem[i] = l.elem[i];
        }
    }
    return *this;
}

template<class T>
bool VectorList<T>::operator==(const VectorList<T> &l) const {
    if (l.length != this->length) {
        return false;
    } else {
        for (int i = 0; i < this->length; i++) {
            if (this->elem[i] != l.elem[i]) {
                return false;
            }
        }
    }
    return true;
}

template<class T>
void VectorList<T>::change_dimension_(T *&a, int oldDim, int newDim) {
    T *temp = new T[newDim];
    int number;
    oldDim < newDim ? number = oldDim : number = newDim;
    for (int i = 0; i < number; i++) {
        temp[i] = a[i];
    }
    delete[] a;
    a = temp;
}

template<class T>
void VectorList<T>::insert(const value_type &v, position p) {
    if (length == array_dim) {
        change_dimension_(elem, array_dim, array_dim * 2);
        array_dim = array_dim * 2;
    }
    if (p > 0 && p <= length + 1) {
        for (int i = length; i >= p; i--) {
            elem[i] = elem[i - 1];
        }
        elem[p - 1] = v;
        length++;
    }
}

template<class T>
void VectorList<T>::tailInsert(const VectorList::value_type &e) {
    position p = length + 1;
    insert(e, p);
}

#endif // VECTORLIST_H
