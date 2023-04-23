#ifndef CODAPT_H
#define CODAPT_H

#include <iostream>
#include "coda.h"

using std::ostream;

// forward declaration della classe Queue_pt
template<class T>
class Queue_pt;

// Nodo per la classe Queue_pt
template<class T>
class QueueNode {
    friend class Queue_pt<T>;

    template<class K>
    friend ostream &operator<<(ostream &os, const Queue_pt<K> &q);

private:
    QueueNode<T> *next;
    T value;
};

template<class T>
class Queue_pt {

public:
    typedef typename Queue<T>::value_type value_type;

    // costruttore di default
    Queue_pt();

    // costruttore di copia
    Queue_pt(const Queue_pt &);

    // distruttore
    ~Queue_pt();

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
    int getLength() const;
    // metodo che verifica dato un valore se questo e' presente nella coda
    bool exists(const value_type &);

    Queue_pt<T> &operator=(const Queue_pt<T> &); // sovraccarico dell'operatore =

    bool operator==(const Queue_pt<T> &); // sovraccarico dell'operatore ==

    template<class K>
    friend ostream &operator<<(ostream &os, const Queue_pt<K> &q); // sovraccarico dell'operatore <<

private:
    QueueNode<T> *head;
    QueueNode<T> *tail;
    int length;
};

// Costruttore
template<class T>
Queue_pt<T>::Queue_pt() {
    head = tail = nullptr;
    length = 0;
}

// costruttore di copia
template<class T>
Queue_pt<T>::Queue_pt(const Queue_pt<T> &src) {
    // inizializzo la length a 0 perche' la push si occupera' di assegnare il giusto valore
    length = 0;

    // inizializzo i puntatori di head e tail
    head = nullptr;
    tail = nullptr;

    // verifico che la coda da copiare non e' vuota
    if (!src.empty()) {
        QueueNode<T> *srcN;
        srcN = src.head;

        while (srcN != nullptr) {
            push(srcN->value);
            srcN = srcN->next;
        }
    }
}

/* Distruttore */
template<class T>
Queue_pt<T>::~Queue_pt() {
    while (!empty()) {
        pop();
    }
}

/* Metodo che verifica se la coda e' vuota */
template<class T>
bool Queue_pt<T>::empty() const {
    return (head == nullptr);
}

/* Metodo che legge l'elemento in testa alla coda */
template<class T>
typename Queue_pt<T>::value_type
Queue_pt<T>::read() const {
    if (!empty()) {
        return (head->value);
    } else {
        throw std::out_of_range("Coda vuota");
    }
}

/* Metodo che rimuove l'elemento in testa alla coda
tail : elemento più recente
head : elemento più vecchio
quando tolgo, tolgo il più vecchio (dovrò cambiare il riferimento di h, prima devo salvarmi il vecchio indirizzo di h perchè lì dovrò fare la delete)
per inserire t->next punta al next, e nuovo->next = NULL, t viene spostato di 1
*/
template<class T>
void Queue_pt<T>::pop() {
    QueueNode<T> *oldHead = head;
    if (!empty()) {
        head = head->next;
        if (head == nullptr) {
            tail = head;
        }
        length--;
    } else {
        throw std::out_of_range("Coda vuota");
    }
    delete oldHead;
}

// metodo che inserisce un elemento in coda alla lista
template<class T>
void Queue_pt<T>::push(const value_type &v) {
    QueueNode<T> *n = new QueueNode<T>;
    n->next = nullptr;
    n->value = v;
    if (empty()) {
        head = n;
    } else {
        tail->next = n;
    }
    tail = n;
    length++;
}

// metodo che restituisce la lunghezza della coda
template<class T>
int Queue_pt<T>::getLength() const {
    return length;
}

// sovraccarico dell'operatore =
template<class T>
Queue_pt<T> &Queue_pt<T>::operator=(const Queue_pt<T> &q) {
    if (this != &q) {
        this->~Queue_pt();
        // inizializzo nuovamente la coda
        head = nullptr;
        tail = nullptr;
        length = 0;
        if (!q.empty()) {
            QueueNode<T> *qNode;
            qNode = q.head;
            while (qNode != nullptr) {
                push(qNode->value);
                qNode = qNode->next;
            }
        }
    }
    return *this;
}

// sovraccarico dell'operatore ==
template<class T>
bool Queue_pt<T>::operator==(const Queue_pt<T> &c) {
    if (length != c.length) {
        return false;
    } else {
        QueueNode<T> *tmp1 = head;
        QueueNode<T> *tmp2 = tail;
        while (tmp1 != nullptr) {
            if (tmp1->value != tmp2->value) return false;
        }
        return true;
    }
}

// sovraccarico dell'operatore <<
template<class K>
ostream &operator<<(ostream &os, const Queue_pt<K> &q) {

    QueueNode<K> *tmp = q.head;
    int i = 0;
    while (tmp != nullptr) {
        os << i << ": [" << tmp->value << "]" << std::endl;
        tmp = tmp->next;
        i++;
    }
    delete tmp;

    return os;
}

// metodo che verifica la presenza di un elemento x nella coda
template<class T>
bool Queue_pt<T>::exists(const value_type &x) {
    value_type val;
    QueueNode<T> *tmp = head;
    while (tmp != nullptr) {
        if (tmp->value == x) {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

#endif // CODAPT_H
