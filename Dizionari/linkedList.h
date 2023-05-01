#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/*
crealista : () → lista 
listavuota : (lista) → boolean
leggilista : (position, lista) → value_type
scrivilista : (value_type,position,lista) → lista
primolista : (lista) → position
finelista : (position, lista) → boolean
succlista : (position, lista) → position
predlista : (position, lista) → position
inslista : (value_type,position,lista) → lista
canclista : (position, lista) → lista
*/

#include "linearList.h"

// TODO: COMMENTARE CODICE
// TODO: RIORDINARE METODI

template<class T>
class LinkedList;

template<class T>
class ListNode {
    friend class LinkedList<T>;

private:
    T value;
    ListNode<T> *previous;
    ListNode<T> *next;
};

template<class T>
class LinkedList : public LinearList<T, ListNode<T> *> {
public:
    typedef typename LinearList<T, ListNode<T> *>::value_type value_type;
    typedef typename LinearList<T, ListNode<T> *>::position position;

    // costruttori
    LinkedList();

    // costruttore per copia
    //LinkedList(const LinkedList<T>&);
    //distruttore
    ~LinkedList();

    // operatori
    bool empty() const;

    value_type read(position) const;

    void write(const value_type &, position);

    position begin() const;

    bool end(position) const;

    position next(position) const;

    position previous(position) const;

    void insert(const value_type &, position &);

    void erase(position);

    int size() const {
        return length;
    };

    // sovraccarico di operatori
    LinkedList<T> &operator=(const LinkedList<T> &); // the assignment operator
    bool operator==(const LinkedList<T> &) const; // tests two list for equality

    // funzioni accessorie
    void headInsert(const value_type &);

    void tailInsert(const value_type &);

    void headErase();

    void tailErase();

    position last() const;

    int getLength() const;

    void swap(position, position);

private:
    ListNode<T> *head;
    int length;
};


template<class T>
LinkedList<T>::LinkedList() {
    head = new ListNode<T>;
    head->next = this->head;
    head->previous = this->head;
    length = 0;
}

template<class T>
LinkedList<T>::~LinkedList() {
    while (!empty()) {
        erase(begin());
    }
    delete head;
}

template<class T>
bool LinkedList<T>::empty() const {
    return (head == head->next);
}

template<class T>
typename LinkedList<T>::position
LinkedList<T>::begin() const {
    return head->next;
}

template<class T>
typename LinkedList<T>::position
LinkedList<T>::last() const {
    return head->previous;
}

template<class T>
bool LinkedList<T>::end(position p) const {
    return (p == head);
}

template<class T>
typename LinkedList<T>::position
LinkedList<T>::next(position p) const {
    return p->next;
}

template<class T>
typename LinkedList<T>::position
LinkedList<T>::previous(position p) const {
    return p->previous;
}

template<class T>
void LinkedList<T>::write(const value_type &a, position p) {
    if (!end(p)) {
        p->value = a;
    } else throw std::out_of_range("POSIZIONE NON VALIDA");
}

/*
    1. allocare la nuova cella
    2. il prev punterà al nuovo elemento
    3. il next della nuova cella sarà a_i
*/
template<class T>
void LinkedList<T>::insert(const value_type &v, position &p) {
    position t = new ListNode<T>;
    t->value = v;

    t->previous = p->previous;
    t->next = p;
    p->previous->next = t;
    p->previous = t;
    length++;
    p = p->previous;
}

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

template<class T>
typename LinkedList<T>::value_type
LinkedList<T>::read(position p) const {
    if (!end(p))
        return (p->value);
    else throw std::out_of_range("POSIZIONE NON VALIDA");
}

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
            position p = L.last();
            for (int i = 0; i < L.size(); i++) {
                position x = begin();
                insert(L.read(p), x);
                p = L.previous(p);
            }
        }
    }
    return *this;
}

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

template<class T>
void LinkedList<T>::tailInsert(const value_type &e) {
    position p = new ListNode<T>;
    p->valore = e;
    position pu = last();
    p->prev = pu;
    p->next = head;
    pu->next = p;
    head->prev = p;
    length++;
}


template<class T>
void LinkedList<T>::headErase() {
    position p = new ListNode<T>;
    p = head->next;
    head->next = head->next->next;
    p = nullptr;
    delete p;
    length--;
}

template<class T>
void LinkedList<T>::tailErase() {
    position p = new ListNode<T>;
    p = last();
    p->prev->next = head;
    p = nullptr;
    delete p;
    length--;
}

template<class T>
int LinkedList<T>::getLength() const {
    return length;
};

template<class T>
void LinkedList<T>::swap(position p1, position p2) {

    if (p1 != p2 && (p1 != nullptr && p2 != nullptr)) {
        value_type temp = read(p1);
        write(read(p2), p1);
        write(temp, p2);
    }
}

#endif // LINKEDLIST_H