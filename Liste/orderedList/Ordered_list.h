
#include "List_vector.h"
#include <iostream>
#include <ostream>

#ifndef REALIZZAZIONI_ORDERED_LIST_H
#define REALIZZAZIONI_ORDERED_LIST_H

template<class T>
class Ordered_list {
public:
    typedef typename List_vector<T>::tipoelem tipoelem;
    typedef typename List_vector<T>::posizione posizione;

    //METODI
    void insList(const tipoelem &); // inserisce un elemento
    void cancLista(const tipoelem &); // rimuove un elemento
    bool ricerca(const tipoelem &); // cerca un elemento
    void fusione(const Ordered_list<T> &);  // fonde con una lista ordinata
    bool sottoLista(const Ordered_list<T> &S1,
                    const Ordered_list<T> &S2); //restituisce TRUE se S2 è sottolista di S1, FALSE altrimenti
    void differenza(Ordered_list<T> &S1, const Ordered_list<T> &S2); //CANCELLA DA S1 TUTTI GLI ELEMENTI DI S2

    //FUNZIONI DI LISTA
    tipoelem leggiLista(posizione) const;

    posizione primoLista() const;

    posizione ultimoLista() const;

    posizione precLista(posizione) const;

    posizione succLista(posizione) const;

    bool fineLista(posizione) const;


    //Costruttore
    Ordered_list();

    //Distruttore
    ~Ordered_list();

    //override operatori
    template<class T1>
    friend ostream &operator<<(ostream &, const Ordered_list<T1> &);

private:
    List_vector <T> L;
};

template<class T1>
ostream &operator<<(ostream &os, const Ordered_list<T1> &l) {
    os << l.L;
    return os;

}

template<class T>
Ordered_list<T>::Ordered_list() {}

template<class T>
Ordered_list<T>::~Ordered_list() {
}


template<class T>
void Ordered_list<T>::insList(const tipoelem &e) {
    posizione pos = L.primoLista();
    while (!L.fineLista(pos) && L.leggiLista(pos) < e) {
        pos = L.succLista(pos);
    }
    L.insLista(e, pos);
}

template<class T>
bool Ordered_list<T>::ricerca(const tipoelem &e) {
    posizione pos = L.primoLista();
    bool trov = false;
    while (!L.fineLista(pos) && !trov) {
        if (L.leggiLista(pos) == e) trov = true;
        else pos = L.succLista(pos);
    }
    return trov;
}

template<class T>
void Ordered_list<T>::cancLista(const tipoelem &e) {
    if (ricerca(e)) {
        posizione p = L.primoLista();
        bool continua = true;
        while (continua) {
            if (e == L.leggiLista(p)) {
                L.cancLista(p);
                continua = false;
            } else p = L.succLista(p);
        }
    }
}

template<class T>
void Ordered_list<T>::fusione(const Ordered_list<T> &l) {
    posizione p = l.L.primoLista();
    while (!l.L.fineLista(p)) {
        this->insList(l.L.leggiLista(p));
        p = l.L.succLista(p);
    }
}

template<class T>
bool Ordered_list<T>::sottoLista(const Ordered_list<T> &S1, const Ordered_list<T> &S2) {
    if (S2.L.lunghezza() > S1.L.lunghezza()) return false;
    bool isSottolista = true;
    posizione p1 = S1.L.primoLista();
    posizione p2 = S2.L.primoLista();
    while (isSottolista && !S2.L.fineLista(p2) && !S1.L.fineLista(p1)) {
        while (!S2.L.fineLista(p2) && !S1.L.fineLista(p1) && (S2.L.leggiLista(p2) == S1.L.leggiLista(p1))) {
            p1 = S1.L.succLista(p1);
            p2 = S2.L.succLista(p2);
        }
        if (!S1.L.fineLista(p1)) {
            p1 = S1.L.succLista(p1);
        }
        if (!S2.L.fineLista(p2)) {
            p2 = S2.L.primoLista();
        }
    }
    if (!S2.L.fineLista(p2)) isSottolista = false;
    return isSottolista;
}

template<class T>
void Ordered_list<T>::differenza(Ordered_list<T> &S1, const Ordered_list<T> &S2) {
    posizione p2 = S2.L.primoLista();
    while (!S2.L.fineLista(p2)) {
        T elem = S2.L.leggiLista(p2);
        while (S1.L.ricercaElemento(elem))
            S1.cancLista(elem);
        p2 = S2.L.succLista(p2);
    }
}


template<class T>
typename Ordered_list<T>::tipoelem Ordered_list<T>::leggiLista(posizione p) const {
    return L.leggiLista(p);
}

template<class T>
typename Ordered_list<T>::posizione Ordered_list<T>::primoLista() const {
    return L.primoLista();
}

template<class T>
typename Ordered_list<T>::posizione Ordered_list<T>::ultimoLista() const {
    return L.ultimoLista();
}

template<class T>
typename Ordered_list<T>::posizione Ordered_list<T>::precLista(posizione p) const {
    return L.precLista(p);
}

template<class T>
typename Ordered_list<T>::posizione Ordered_list<T>::succLista(posizione p) const {
    return L.succLista(p);
}

template<class T>
bool Ordered_list<T>::fineLista(posizione p) const {
    return L.fineLista(p);
}

#endif //REALIZZAZIONI_ORDERED_LIST_H
