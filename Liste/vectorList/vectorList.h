#ifndef VECTORLIST_H
#define VECTORLIST_H

#include "../linearList/linearList.h"
#include "exceptions.h"
#include <iostream>
#include <vector>

#define DEFAULT_DIM 10

using std::vector;

template<class T>
class VectorList : public LinearList<T, int> {
public:

    typedef typename LinearList<T, int>::value_type value_type; // Tipo di dato della lista
    typedef typename LinearList<T, int>::position position; // Tipo di dato della posizione

    // Costruttore di default
    VectorList();

    // Costruttore con dimensione del vettore
    VectorList(int dim);

    // Costruttore di copia
    VectorList(const VectorList<T> &copiedList);

    // Distruttore
    ~VectorList();

    // Crea una lista vuota
    void create();

    // Controlla se la lista e' vuota
    bool empty() const;

    // Legge l'elemento in posizione p
    value_type read(position p) const;

    // Scrive l'elemento in posizione p
    void write(const value_type &v, position p);

    // Restituisce la posizione del primo elemento
    position begin() const;

    // Controlla se la posizione e' l'ultima
    bool end(position p) const;

    // Restituisce la posizione del successivo elemento
    position next(position p) const;

    // Restituisce la posizione dell'elemento precedente
    position prev(position p) const;

    // Inserisce un nodo nella posizione precedente alla posizione p, a cui verra' associato un valore v
    void insert(const value_type &v, position p);

    // Cancella l'elemento in posizione p
    void erase(position p);


    VectorList<T> &operator=(const VectorList<T> &l); // sovraccarico dell'operatore =
    bool operator==(const VectorList<T> &l) const; // sovraccarico dell'operatore ==

    // Inserisce un elemento in coda alla lista
    void tailInsert(value_type &e);

    // Inserisce un elemento in testa alla lista
    void headInsert(value_type &e);

    // Metodo che elimina l'elemento in testa
    void headErase();

    // Metodo che elimina l'elemento in coda
    void tailErase();

    void deleteMultiply();

private:
    // Funzione che utilizza la tecnica di array doubling in caso la dimensione del vettore non basti a contenere gli elementi
    void change_dimension_(T *&, int, int);

    value_type *elem;
    int length; // lunghezza effettiva della lista
    int array_dim;
};

// Costruttore di default
template<class T>
VectorList<T>::VectorList() {
    array_dim = DEFAULT_DIM;
    length = 0;
    this->create();
}

// Costruttore con dimensione del vettore
template<class T>
VectorList<T>::VectorList(int dim) {
    array_dim = dim;
    length = 0;
    this->create();
}

// Costuttore di copia
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

// Crea una lista vuota
template<class T>
void VectorList<T>::create() {
    this->elem = new T[array_dim];
    this->length = 0;
}

// Controlla se la lista e' vuota
template<class T>
bool VectorList<T>::empty() const {
    return (this->length == 0);
}

// Legge l'elemento in posizione p
template<class T>
typename VectorList<T>::position VectorList<T>::begin() const {
    return (1);
}

/* Controlla se la posizione e' l'ultima
 L'implementazione prevede l'utilizzo di una posizione fittizia che rappresenta l'ultima posizione della lista.
 */
template<class T>
bool VectorList<T>::end(position p) const {
    if (p > 0 && p >= length + 1) {
        return (p == length + 1);
    } else {
        return false;
    }
}

// Restituisce la posizione del successivo elemento
template<class T>
typename VectorList<T>::position VectorList<T>::next(position p) const {
    if (p > 0 && p < length + 1) { // precondizione
        return (p + 1);
    } else {
        return (p);
    }
}

// Restituisce la posizione dell'elemento precedente
template<class T>
typename VectorList<T>::position VectorList<T>::prev(position p) const {
    if (p > 1 && p < length + 1) { // precondizione
        return (p - 1);
    } else {
        return (p);
    }
}

// Restituisce l'elemento in posizione p
template<class T>
typename VectorList<T>::value_type VectorList<T>::read(position p) const {
    if (p > 0 && p < length + 1) { // precondizione
        return elem[p - 1];
    } else {
        throw std::out_of_range("Posizione non valida");
    }
}

// Inserisce un nodo nella posizione precedente alla posizione p, a cui verra' associato un valore v
template<class T>
void VectorList<T>::write(const value_type &v, position p) {
    if (p > 0 && p < length + 1) { // precondizione
        elem[p - 1] = v;
    }
}

// Cancella l'elemento in posizione p
template<class T>
void VectorList<T>::erase(position p) {
    if ((p > 0) && (p < length + 1)) // precondizione
    {
        if (!empty()) {
            for (int i = p - 1; i < (length - 1); i++) {
                elem[i] = elem[i + 1];
            }
            length--;
        }
    }
}

// Sovraccarico dell'operatore =
template<class T>
VectorList<T> &VectorList<T>::operator=(const VectorList<T> &l) {
    if (this != &l) {
        // assegno le dimensioni del vettore l al vettore in cui copiarlo
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

// Sovraccarico dell'operatore ==
template<class T>
bool VectorList<T>::operator==(const VectorList<T> &l) const {
    // se le due liste hanno lunghezze diverse, sono gia' diverse
    if (l.length != this->length) {
        return false;
    } else {
        // confronta elemento per elemento
        for (int i = 0; i < this->length; i++) {
            if (this->elem[i] != l.elem[i]) {
                return false;
            }
        }
    }
    return true;
}

// Funzione che utilizza la tecnica di array doubling per aumentare la dimensione del vettore
template<class T>
void VectorList<T>::change_dimension_(T *&a, int oldDim, int newDim) {
    T *temp = new T[newDim];
    int number;
    // confronto le dimensioni passate per capire l'indice da usare per la copia
    oldDim < newDim ? number = oldDim : number = newDim;
    for (int i = 0; i < number; i++) {
        temp[i] = a[i];
    }
    delete[] a;
    a = temp;
}

/* Inserisce un elemento in posizione p
    La funzione di insert inserisce l'elemento prima della posizione p passata come parametro
 */
template<class T>
void VectorList<T>::insert(const value_type &v, position p) {
    // controllo se necessito di effettuare l'array doubling
    if (length == array_dim) {
        change_dimension_(elem, array_dim, array_dim * 2);
        array_dim = array_dim * 2;
    }
    // controllo che p sia una posizione valida
    if (p > 0 && p <= length + 1) {
        // scalo gli elementi
        for (int i = length; i >= p; i--) {
            elem[i] = elem[i - 1];
        }
        elem[p - 1] = v;
        length++;
    }
}

// Inserisce un elemento in coda
template<class T>
void VectorList<T>::tailInsert(value_type &e) {
    position p = length + 1;
    insert(e, p);
}

// Inserisce un elemento in testa
template<class T>
void VectorList<T>::headInsert(value_type &e) {
    position p = begin();
    insert(e, p);
}

template<class T>
void VectorList<T>::headErase() {
    if (empty()) {
        return;
    }

    for (int i = 0; i < length; i++) {
        elem[i] = elem[i + 1];
    }

    length--;
}

template<class T>
void VectorList<T>::tailErase() {
    if (empty()) {
        return;
    }

    this->length--;
}

template<class T>
void VectorList<T>::deleteMultiply() {
    std::vector<int> pos;
    for (int i = 0; i < length; i++) {
        cout << elem[i] << "  " << i + 1 << endl;
        if (elem[i] % (i + 1) == 0) {
            pos.push_back(i);
        }
    }
    for (auto j: pos) {
        cout << j << " ";
    }
    cout << endl;
    int removed = 0;

    for (int j = 0; j < pos.size(); j++) {
        erase(pos[j] + 1 - removed);
        removed++;
    }

}

#endif // VECTORLIST_H
