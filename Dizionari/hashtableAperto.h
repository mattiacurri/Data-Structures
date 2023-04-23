#include "dictionary.h"
#include "vectorList.h"
#include <string>
#include <stdexcept>
#include <ostream>

#ifndef REALIZZAZIONI_HASHTABLEAPERTO_H
#define REALIZZAZIONI_HASHTABLEAPERTO_H

using std::string;

template<class T>
class my_hash {
public:
    size_t operator()(const T the_key) const {
        return size_t(the_key);
    }
};


template<>
class my_hash<string> {
public:
    size_t operator()(const string the_key) const {
        unsigned long hash_value = 0;
        int length = (int) the_key.length();
        for (int i = 0; i < length; i++)
            hash_value = 5 * hash_value + the_key.at(i);
        return size_t(hash_value);
    }
};

template<class K, class E>
class open_hash_table : public dictionary<K, E> {
public:
    typedef typename VectorList<mypair<K, E>>::position position;

    //costruttore default
    open_hash_table();

    //costruttore con size stabilita
    open_hash_table(int);

    //costruttore copia
    open_hash_table(const open_hash_table<K, E> &);

    ~open_hash_table();


    //void creaDizionario(); rimpiazzato dal costruttore
    bool empty() const;

    int pos(const K) const;

    void insert(mypair<K, E> &);

    void erase(const K&);

    E recoverValue(const K);

    bool search(const K) const;

    //accessorie
    int size() const;

    bool containsValue(const E &) const;

    //restituisce la lista dei valori memorizzati nel dictionary
    VectorList<E> values() const;

    //restituisce la lista delle chiavi memorizzate nel dictionary
    VectorList<K> keys() const;

    void modify(const K &, const E &, const E &);

    //sovraccarico

    open_hash_table<K, E> &operator=(const open_hash_table<K, E> &);

    bool operator==(const open_hash_table<K, E> &);

    template<class K1, class E1>
    friend ostream &operator<<(ostream &, const open_hash_table<K1, E1> &);

private:
    //numero elementi del dictionary
    int numElems;
    int divisor;
    //lista di trabocco
    VectorList<mypair<K, E>> *tabella;
    my_hash<K> hashm;

};

/*
 * Costruttore
 * POST CONDIZIONARE: Dizionario vuoto
 */
template<class K, class E>
open_hash_table<K, E>::open_hash_table() {
    numElems = 0;
    divisor = 10; //size predefinita
    tabella = new VectorList<mypair<K, E>>[divisor];
}

/*
 * Costruttore
 * POST CONDIZIONARE: Dizionario vuoto
 */
template<class K, class E>
open_hash_table<K, E>::open_hash_table(int dim) {
    numElems = 0;
    divisor = dim; //size decisa dall'utente
    tabella = new VectorList<mypair<K, E>>[divisor];
}

//costruttore copia
template<class K, class E>
open_hash_table<K, E>::open_hash_table(const open_hash_table<K, E> &mp) {
    divisor = mp.divisor;
    numElems = mp.numElems;
    tabella = new VectorList<mypair<K, E>>[divisor];
    for (int i = 0; i < divisor; i++) {
        tabella[i] = mp.tabella[i];
    }
}


//distruttore
template<class K, class E>
open_hash_table<K, E>::~open_hash_table() {
}

/*
 * Verifica se un dictionary è vuoto
 * POST CONDIZIONE: Return TRUE se il dictionary è vuoto, FALSE altrimenti
 */
template<class K, class E>
bool open_hash_table<K, E>::empty() const {
    return numElems == 0;
}

/*
 * Ricava la position data una chiava
 */
template<class K, class E>
int open_hash_table<K, E>::pos(const K key) const {
    int i = (int) hashm(key) % divisor;
    return i;
}

/*
 * Inserisce una coppia <K,E> nel dictionary
 * PRE CONDIZIONE: La K non esiste
 * POST CONDIZIONE: Dizionario con coppia aggiunta
 */
template<class K, class E>
void open_hash_table<K, E>::insert(mypair<K, E> &coppia) {
    int i = pos(coppia.getChiave());
    if (search(coppia.getChiave())) {
        cout << "Chiave " << coppia.getChiave()
             << " gia' esistente, ma e' possibile aggiornarne il E con l'apposita funzione" << endl;
    } else {
        if (!tabella[i].searchElemento(coppia)) {
            tabella[i].insertCoda(coppia);
            numElems++;
        }
    }
}

/*
 * Cancella una coppia K E dal dictionary
 * PRE CONDIZIONE: la K esiste
 * POST CONDIZIONE: dictionary con coppia eliminata
 */
template<class K, class E>
void open_hash_table<K, E>::erase(const K& key) {
    if (numElems > 0) {
        if (search(key)) {
            int i = hashm(key) % divisor;
            position p = tabella[i].primoLista();
            while (tabella[i].leggiLista(p).getChiave() != key) {
                p = tabella[i].succLista(p);
            }
            tabella[i].cancLista(p);
            numElems--;
        } else throw std::out_of_range("CHIAVE NON  ESISTENTE");
    } else throw std::out_of_range("MAPPA VUOTA");

    /*-
     * if (numElems > 0) {
        if (search(key)) {
            int i = hashm(key) % divisor;
            position p = tabella[i].primoLista();
            while (!tabella[i].fineLista(p) && tabella[i].leggiLista(p).getChiave() != key) {
                p = tabella[i].succLista(p);
            }
            tabella[i].cancLista(p);
        } else throw std::out_of_range("CHIAVE NON  ESISTENTE");
    } else throw std::out_of_range("MAPPA VUOTA");
}
     */
}

/*
 * Recupera il E associato a una K
 * PRE CONDIZIONE: Esiste la K
 * POST CONDIZIONE: Ritorna il E associato alla K
 */
template<class K, class E>
E open_hash_table<K, E>::recoverValue(const K key) {
    if (search(key)) {
        E v;
        int i = hashm(key) % divisor;
        position p = tabella[i].primoLista();
        bool trov = false;
        while (!tabella[i].fineLista(p) && !trov) {
            if (tabella[i].leggiLista(p).getChiave() == key) {
                v = tabella[i].leggiLista(p).getValore();
                trov = true;
            } else p = tabella[i].succLista(p);
        }
        return v;
    }
    throw std::out_of_range("CHIAVE NON ESISTENTE");
}

//Restituisce il numero di elementi del dictionary
template<class K, class E>
int open_hash_table<K, E>::size() const {
    return numElems;
}

//Resituisce TRUE se la K key esiste, false altrimenti
template<class K, class E>
bool open_hash_table<K, E>::search(const K key) const {
    bool trov = false;
    int i = hashm(key) % divisor;
    position p = tabella[i].primoLista();
    while (!tabella[i].fineLista(p) && !trov) {
        if (tabella[i].leggiLista(p).getChiave() == key) {
            return true;
        } else p = tabella[i].succLista(p);
    }
    return trov;
}


//Verifica se un E esiste
template<class K, class E>
bool open_hash_table<K, E>::containsValue(const E &e) const {
    for (int i = 0; i < divisor; i++) {
        position p = tabella[i].primoLista();
        while (!tabella[i].fineLista(p)) {
            if (tabella[i].leggiLista(p).getValore() == e) return true;
            else p = tabella[i].succLista(p);
        }
    }
    return false;
}

//restituisce la lista dei valori memorizzati nel dictionary
template<class K, class E>
VectorList<E> open_hash_table<K, E>::values() const {
    VectorList<E> list;
    for (int i = 0; i < divisor; i++) {
        position p = tabella[i].primoLista();
        while (!tabella[i].fineLista(p)) {

            list.insertCoda(tabella[i].leggiLista(p).getValore());
            p = tabella[i].succLista(p);
        }
    }
    return list;
}

//restituisce la lista delle chiavi memorizzate nel dictionary
template<class K, class E>
VectorList<K> open_hash_table<K, E>::keys() const {
    VectorList<K> list;
    for (int i = 0; i < divisor; i++) {
        if (!tabella[i].listaVuota())
            list.insertCoda(tabella[i].leggiLista(tabella[i].primoLista()).getChiave());
    }
    return list;
}

/*
 * Modifica del E associato a una K esistente
 */
template<class K, class E>
void open_hash_table<K, E>::modify(const K &key, const E &e,
                                     const E &nuovoValore) {
    int i = pos(key);
    if (tabella[i].listaVuota()) {
        cout << "Il valore della chiave " << key << " non esiste" << endl;
    } else {
        position p = tabella[i].primoLista();
        bool trov = false;
        while (!tabella[i].fineLista(p) && !trov) {
            if (tabella[i].leggiLista(p).getValore() != e) p = tabella[i].succLista(p);
            else trov = true;
        }
        mypair<K, E> newCoppia(key, nuovoValore);
        if (trov) {
            tabella[i].scriviLista(newCoppia, p);
        }
    }

}

template<class K, class E>
open_hash_table<K, E> &open_hash_table<K, E>::operator=(const open_hash_table<K, E> &mp) {
    if (this != &mp) {
        divisor = mp.divisor;
        numElems = mp.numElems;
        tabella = new VectorList<mypair<K, E>>[divisor];
        for (int i = 0; i < divisor; i++) {
            tabella[i] = mp.tabella[i];
        }
    }
    return *this;
}

template<class K, class E>
bool open_hash_table<K, E>::operator==(const open_hash_table<K, E> &coppia) {
    if (this->numElems != coppia.size()) return false;
    else {
        for (int i = 0; i < divisor; i++) {
            VectorList<mypair<K, E>> list1 = tabella[i], list2 = coppia.tabella[i];
            if (!(list1 == list2))
                return false;
        }
    }
    return true;
}

template<class K1, class E1>
ostream &operator<<(ostream &os, const open_hash_table<K1, E1> &mappa) {
    for (int i = 0; i < mappa.divisor; i++) {
        VectorList<mypair<K1, E1>> list = mappa.tabella[i];
        if (!list.listaVuota()) {
            os << "{";
            typename open_hash_table<K1, E1>::position position = list.primoLista();
            while (!list.fineLista(position)) {
                mypair<K1, E1> coppia(list.leggiLista(position));
                if (list.primoLista() == position) os << coppia;
                else os << ", " << coppia;
                position = list.succLista(position);
            }
            os << "}" << endl;
        }
    }
    return os;
}


#endif //REALIZZAZIONI_HASHTABLEAPERTO_H
