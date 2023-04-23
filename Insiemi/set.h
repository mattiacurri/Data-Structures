#ifndef INSIEME_H
#define INSIEME_H

#include <iostream>
#include "../Dizionari/hash_table.h"

using std::ostream;
// Implementazione con liste ordinate

template<class T>
class set;

template<class T>
class node {
    friend class set<T>;

    // sovraccarico dell'operatore <<
    template<class U>
    friend ostream &operator<<(ostream &os, const set<U> &s);

public:
    node() = default;

private:
    T e;
    node<T> *next;
    node<T> *prev;
};

template<class T>
class set {
public:
    typedef T valuetype;

    // costruttore
    set();

    // costruttore di copia
    set(const set &);

    // distruttore
    ~set();

    // operatori
    // metodo che verifica se l'insieme e' vuoto
    bool empty() const;

    // metodo che inserisce un elemento
    void insert(const T &v);

    // metodo che verifica se un elemento e' presente
    bool member(const T &v) const;

    // metodo che cancella un elemento, se presente
    void erase(const T &v);

    // operazione di unione
    set<T> union_(set<T> &);

    // operazione di intersezione
    set<T> intersection(set<T> &);

    // operazione di differenza
    set<T> difference(set<T> &);

    // verifica se un insieme e' sottoinsieme dell'altro
    bool sottoInsieme(set<T> &);

    //sovraccarico dell'operatore <<
    template<class U>
    friend ostream &operator<<(ostream &os, const set<U> &s);

    bool operator==(const set &); // sovraccarico dell'operatore ==

    set &operator=(const set &); // sovraccarico dell'operatore =

    //funzioni accessorie
    node<T> *last() const; // ritorna l'ultimo elemento della lista

private:
    node<T> *head;
    int numElems;
};

// Costruttore
template<class T>
set<T>::set() {
    head = nullptr;
    numElems = 0;
}

// Costruttore di copia
template<class T>
set<T>::set(const set<T> &src) {
    head = nullptr;
    numElems = src.numElems;
    if (!src.empty()) {
        node<T> *srcNode;
        srcNode = src.head;

        // copio tutti i nodi dell'insieme
        while (srcNode != nullptr) {
            // creo il nodo da inserire
            node<T> *toInsN;
            toInsN = new node<T>;

            // assegno i valori al nodo
            toInsN->e = srcNode->e;
            toInsN->next = nullptr;

            // inserisco il nodo nella lista
            if (head == nullptr) {
                head = toInsN;
            } else {
                // inserisco in fondo il nodo
                node<T> *cmpN;
                cmpN = head;

                while (cmpN->next != nullptr) {
                    cmpN = cmpN->next;
                }
                cmpN->next = toInsN;
            }
            srcNode = srcNode->next;
        }
    }
}

// Distruttore
template<class T>
set<T>::~set() {
    if (head != nullptr) {
        node<T> *tmp = head;
        while (head != nullptr) {
            tmp = head;
            head = head->next;
            delete tmp;
        }
    }
}

// Metodo che verifica se l'insieme e' vuoto
template<class T>
bool set<T>::empty() const {
    return (head == nullptr);
}

// Metodo che inserisce un elemento nell'insieme
template<class T>
void set<T>::insert(const T &v) {
    // controllo se l'elemento gia' esiste
    if (!member(v)) {
        auto *tmp = new node<T>;
        tmp->e = v;
        tmp->prev = nullptr;
        tmp->next = head;
        head = tmp;
        numElems++;
    } else {
        throw std::invalid_argument("Elemento gia' presente");
    }
}

// Metodo che controlla se un elemento e' presente nell'insieme
template<class T>
bool set<T>::member(const T &v) const {
    node<T> *tmp = head;
    bool trov = false;
    while (tmp != nullptr && !trov) {
        if (tmp->e == v) {
            return true;
        } else {
            tmp = tmp->next;
        }
    }
    return false;
}

// Metodo che elimina un elemento nell'insieme
template<class T>
void set<T>::erase(const T &v) {
    if (member(v)) {
        node<T> *tmp = head;
        while (tmp->e != v) {
            tmp = tmp->next;
        }
        if (tmp == head) head = tmp->next;
        else tmp->prev->next = tmp->next;
        delete tmp;
        numElems--;
    }
}

// overloading <<
template<class U>
ostream &operator<<(ostream &os, const set<U> &s) {
    node<U> *p = s.head;
    while (p != nullptr) {
        os << p->e << " ";
        p = p->next;
    }
    return os;
}

// Operazione di unione
template<class T>
set<T> set<T>::union_(set<T> &b) {
    set<T> unionSet;
    if (empty() == false || b.empty() == false) {
        node<T> *tmp;
        tmp = head;
        while (tmp != nullptr) {
            unionSet.insert(tmp->e);
            tmp = tmp->next;
        }

        node<T> *tmp2;
        tmp2 = b.h;
        while (tmp2 != nullptr) {
            if (!unionSet.member(tmp2->e)) {
                unionSet.insert(tmp2->e);
            }
            tmp2 = tmp2->next;
        }
    }
    return unionSet;
}

// Operazione di intersezione
template<class T>
set<T> set<T>::intersection(set<T> &b) {
    set<T> newSet;

    // verifico che almeno uno dei due insiemi non sia vuoto
    if (!empty() || !b.empty()) {
        // leggo i valori dal primo insieme
        node<T> *n;
        n = head;

        while (n != nullptr) {
            // inserisco solo gli elementi in comune con b
            if (b.member(n->e)) {
                newSet.insert(n->e);
            }
            n = n->next;
        }
    }
    return newSet;
}

// Operazione di differenza
template<class T>
set<T> set<T>::difference(set<T> &b) {
    set<T> diffSet;

    // verifico che almeno uno dei due insiemi non sia vuoto
    if (!empty() || !b.empty()) {
        // leggo i valori dal primo insieme
        node<T> *a;
        a = head;

        while (a != nullptr) {
            // inserisco solo gli elementi che appartengono ad 'a' ma non a 'b'
            if (!b.member(a->e)) {
                diffSet.insert(a->e);
            }
            a = a->next;
        }
    }
    return diffSet;
}

// Metodo che restituisce l'ultimo elemento nell'insieme
/* Gli insiemi non hanno una posizione definita per gli elementi,
 * la funzione restituisce l'ultimo elemento nell'ordine in cui sono memorizzati */
template<class T>
node<T> *set<T>::last() const {
    node<T> *tmp = head;
    while (tmp->next != nullptr) {
        tmp = tmp->next;
    }
    return tmp;
}

// sovraccarico dell'operatore ==
template<class T>
bool set<T>::operator==(const set &s) {
    if (numElems != s.numElems) return false;
    else {
        node<T> *tmp1 = head, *tmp2 = s.head;
        while (tmp1 != nullptr && tmp2 != nullptr) {
            if (tmp1->e != tmp2->e) return false;
            tmp2 = tmp2->next;
            tmp1 = tmp1->next;
        }
    }
    return true;
}

// sovraccarico dell'operatore =
template<class T>
set<T> &set<T>::operator=(const set<T> &e) {
    if (this != &e) {
        this->~set();
        head = nullptr;
        numElems = e.numElems;
        if (e.empty() == false) {
            node<T> *n;
            n = head;

            // copio tutti i nodi dell'insieme
            while (n != nullptr) {
                // creo il nodo da inserire
                node<T> *insN;
                insN = new node<T>;

                // assegno i valori al nodo
                insN->e = n->e;
                insN->next = nullptr;

                // inserisco il nodo nella lista
                if (head == nullptr) {
                    head = insN;
                } else {
                    // inserisco in fondo il nodo
                    node<T> *cmpN;
                    cmpN = head;

                    while (cmpN->next != nullptr) {
                        cmpN = cmpN->next;
                    }
                    cmpN->next = insN;
                }
                n = n->next;
            }
        }
    }
    return *this;
}

// Metodo che verifica se un insieme e' sottoinsieme dell'altro
template<class T>
bool set<T>::sottoInsieme(set<T> &S2) {
    hash_table<T, T> mappa;
    //riempio la mappa con gli elementi di S2
    node<T> *tmp = S2.head;
    while (tmp != nullptr) {
        mypair<T, T> coppia(tmp->e, tmp->e);
        mappa.insert(coppia);
        tmp = tmp->next;
    }

    // ora controllo
    tmp = this->head;
    while (tmp != nullptr) {
        if (!mappa.containsValue(tmp->e)) return false;
        else tmp = tmp->next;
    }
    return true;
}

#endif // INSIEME_H