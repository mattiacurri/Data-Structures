#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "../linearList/linearList.h"
// #include "../../Dizionari/hash_table.h" // per la funzione hist
// #include "../../Dizionari/histo.h" // per la funzione hist
#include <vector> // per la funzione vec

// forward declaration necessaria per poter dichiarare la classe ListNode
template<class T>
class LinkedList;

template<class T>
class ListNode {
    friend class LinkedList<T>;

public:

    // Restituisce il nodo successivo rispetto a quello passato implicitamente
    ListNode<T> getNext() {
        return this->next;
    }

private:
    T value;
    ListNode<T> *previous;
    ListNode<T> *next;
};

template<class T>
class LinkedList : public LinearList<T, ListNode<T> *> {
public:
    typedef typename LinearList<T, ListNode<T> *>::value_type value_type; // Tipo di dato della lista
    typedef typename LinearList<T, ListNode<T> *>::position position; // Tipo di dato della posizione

    // costruttore di default
    LinkedList();

    // costruttore di copia
    LinkedList(const LinkedList<T> &);

    // distruttore
    ~LinkedList() = default;

    // controlla se una lista e' vuota
    bool empty() const;

    // legge l'elemento in posizione p
    value_type read(position) const;

    // scrive l'elemento in posizione p
    void write(const value_type &, position);

    // restituisce la posizione del primo elemento
    position begin() const;

    // controlla se la posizione e' l'ultima
    bool end(position) const;

    // restituisce la posizione del successivo elemento
    position next(position) const;

    // restituisce la posizione dell'elemento precedente
    position prev(position) const;

    // inserisce un elemento in posizione p
    void insert(const value_type &, position);

    // cancella l'elemento in posizione p
    void erase(position);

    // sovraccarico di operatori
    LinkedList<T> &operator=(const LinkedList<T> &); // operatore di assegnazione
    bool operator==(const LinkedList<T> &) const; // paragona due liste

    // funzioni accessorie
    // inserisce un elemento in testa alla lista
    void headInsert(const value_type &);

    // inserisce un elemento in coda alla lista
    void tailInsert(const value_type &);

    // cancella l'elemento in testa alla lista
    void headErase();

    // cancella l'elemento in coda alla lista
    void tailErase();

    // restituisce la posizione dell'ultimo elemento
    position lastElem() const;

    // restituisce la lunghezza della lista
    int getLength() const;

    // scambia due elementi
    void swap(position, position);

    // metodo che restituisce il numero di occorrenze dei multipli di k nella lista L
    int freq(LinkedList<int> &L, int k);

    // metodo che stampa la frequenza di ogni elemento presente nella lista L
    void hist(LinkedList<int> &L);

    // metodo che rimuove dalla lista L tutti gli elementi seguiti da un numero dispari
    void remp(LinkedList<int> &L);

    /* metodo che modifica una lista in modo da
     * eliminare gli elementi il cui valore e' un multiplo della rispettiva posizione ordinale occupata nella lista */
    void deleteMultiply();

private:
    ListNode<T> *head;
    int length;
};


// Il costruttore crea il nodo testa, che all'inizio avra' i puntatori next e previous che puntano a se stesso
template<class T>
LinkedList<T>::LinkedList() {
    head = new ListNode<T>;
    head->next = this->head;
    head->previous = this->head;
    length = 0;
}

// Il costruttore di copia inserisce gli elementi della lista da copiare nella lista chiamata implicitamente
template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &copiedList) {
    length = 0;
    // creazione della testa
    head = new ListNode<T>;
    head->next = head;
    head->previous = head;
    position p = copiedList.begin();
    position p1 = this->begin();
    while (!copiedList.end(p)) {
        // la insert provvedera' man mano che inserisce gli elementi a settare la giusta length della nuova lista
        this->insert(copiedList.read(p), p1);
        p1 = this->next(p1);
        p = copiedList.next(p);
    }
}


// Restituisce true se la lista e' vuota, false altrimenti
template<class T>
bool LinkedList<T>::empty() const {
    return (head == head->next);
}

// Restituisce il valore dell'elemento in posizione p
template<class T>
typename LinkedList<T>::position
LinkedList<T>::begin() const {
    return head->next;
}

// Restituisce l'ultimo elemento della lista, che corrisponde al nodo puntato dal puntatore previous del nodo testa
template<class T>
typename LinkedList<T>::position
LinkedList<T>::lastElem() const {
    return head->previous;
}

// Restituisce true se la posizione e' l'ultima, false altrimenti
template<class T>
bool LinkedList<T>::end(position p) const {
    return (p == head);
}

// Restituisce la posizione del successivo elemento
template<class T>
typename LinkedList<T>::position
LinkedList<T>::next(position p) const {
    return p->next;
}

// Restituisce la posizione dell'elemento precedente
template<class T>
typename LinkedList<T>::position
LinkedList<T>::prev(position p) const {
    return p->previous;
}

// Scrive l'elemento a in posizione p
template<class T>
void LinkedList<T>::write(const value_type &a, position p) {
    if (!end(p)) {
        p->value = a;
    } else {
        throw std::out_of_range("POSIZIONE NON VALIDA");
    }
}

/*
    Inserisce un nuovo nodo prima della posizione p a cui viene associato il valore v
    Procedimento:
    1. allocare la nuova cella
    2. il previous punterà al nuovo elemento
    3. il next della nuova cella sarà p
*/
template<class T>
void LinkedList<T>::insert(const value_type &v, position p) {
    position t = new ListNode<T>;
    t->value = v;

    t->previous = p->previous;
    t->next = p;
    p->previous->next = t;
    p->previous = t;
    length++;
    p = p->previous;
}

// Cancella l'elemento in posizione p, aggiustando i puntatori del precedente e del successivo elemento di conseguenza
template<class T>
void LinkedList<T>::erase(position p) {
    if (!empty() && !end(p)) {
        position tmp = p->next;
        p->previous->next = p->next;
        p->next->previous = p->previous;
        delete p;
        p = tmp;
        length--;
    } else throw std::out_of_range("POSIZIONE NON VALIDA");
}

// Legge il valore associato alla posizione p
template<class T>
typename LinkedList<T>::value_type
LinkedList<T>::read(position p) const {
    if (!end(p))
        return (p->value);
    else {
        throw std::out_of_range("POSIZIONE NON VALIDA");
    }
}

// Sovraccarico dell'operatore =
template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &L) {
    if (this != &L) // per evitare l'autoassegnamento
    {
        // deallocare tutta la lista this
        this->~LinkedList();

        length = 0;

        // creazione della sentinella per this
        head = new ListNode<T>;
        head->next = head;
        head->previous = head;

        if (!L.empty()) {
            position p = L.lastElem();
            for (int i = 0; i < L.size(); i++) {
                position x = begin();
                insert(L.read(p), x);
                p = L.prev(p);
            }
        }
    }
    return *this;
}

// Sovraccarico dell'operatore ==
template<class T>
bool LinkedList<T>::operator==(const LinkedList<T> &L) const {
    if (L.size() != length)
        return false;
    position p, pL;
    p = begin();
    pL = L.begin();
    while (!end(p)) {
        if (p->value != pL->value)
            return false;
        p = p->next;
        pL = pL->next;
    }
    return true;
}

// Inserisce un elemento in testa alla lista, aggiornando i puntatori di conseguenza
template<class T>
void LinkedList<T>::headInsert(const value_type &e) {
    position p = new ListNode<T>;
    p->value = e;
    head->next->previous = p;
    p->next = head->next;
    p->previous = head;
    head->next = p;
    length++;
}

// Inserisce un elemento in coda alla lista, aggiornando i puntatori di conseguenza
template<class T>
void LinkedList<T>::tailInsert(const value_type &e) {
    position p = new ListNode<T>;
    p->value = e;
    position pu = lastElem();
    p->previous = pu;
    p->next = head;
    pu->next = p;
    head->previous = p;
    length++;
}

// Elimina l'elemento in testa alla lista, aggiornando i puntatori di conseguenza
template<class T>
void LinkedList<T>::headErase() {
    if (!empty()) {
        position p = new ListNode<T>;
        p = head->next;
        head->next = head->next->next;
        p = nullptr;
        delete p;
        length--;
    } else {
        throw std::out_of_range("LISTA VUOTA");
    }
}

// Elimina l'elemento in coda alla lista, aggiornando i puntatori di conseguenza
template<class T>
void LinkedList<T>::tailErase() {
    if (!empty()) {
        position p = new ListNode<T>;
        p = lastElem();
        if (p->next == head) {
            p = nullptr;
            delete p;
            length--;
        }
        else {
            cout << "p->value: " << p->value << endl;
            p->previous->next = head;
            p = nullptr;
            delete p;
            length--;
        }
    } else {
        throw std::out_of_range("LISTA VUOTA");
    }
}

// Restituisce la lunghezza della lista
template<class T>
int LinkedList<T>::getLength() const {
    return length;
}

// Scambia due elementi di posizione
template<class T>
void LinkedList<T>::swap(position p1, position p2) {
    // controllo che le posizioni siano diverse e che esistano
    if (p1 != p2 && (p1 != nullptr && p2 != nullptr)) {
        value_type temp = read(p1);
        write(read(p2), p1);
        write(temp, p2);
    }
}

// metodo che restituisce il numero di occorrenze dei multipli di k nella lista L
template<>
int LinkedList<int>::freq(LinkedList<int> &L, int k) {
    int counter = 0;
    position p = L.begin();
    while (!end(p)) {
        if (p->value % k == 0) {
            counter++;
        }
        p = p->next;
    }
    return counter;
}

// metodo che stampa la frequenza di ogni elemento presente nella lista L
//template<>
//void LinkedList<int>::hist(LinkedList<int> &L) {
//    histo h;
//    position p = L.begin();
//    while (!end(p)) {
//        h.add(p->value);
//        p = p->next;
//    }
//    cout << h << endl;
//}

// metodo che rimuove dalla lista L tutti gli elementi seguiti da un numero dispari
template<>
void LinkedList<int>::remp(LinkedList<int> &L) {
    LinkedList<int>::position p = L.begin();
    while (p->next != lastElem()) {
        if (p->next->value % 2 == 1) {
            L.erase(p);
        }
        p = L.next(p);
    }
}

template<class T>
void LinkedList<T>::deleteMultiply() {
    LinkedList<int>::position p = begin();
    while (p->next != lastElem()) {

    }
}

#endif // LINKEDLIST_H
