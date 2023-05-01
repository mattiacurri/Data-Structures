#ifndef PILAPT_H

#include <algorithm>
#include "pila.h"
#include "exceptions.h"

using std::ostream;
using std::cout;
using std::endl;
// TODO: commentare i metodi

// forward declaration della class 'Stack_pt'
template<class T>
class Stack_pt;

// definizione della classe StackNode
template<class T>
class StackNode {
public:
    friend class Stack_pt<T>;

    template<class K>
    friend ostream &operator<<(ostream &os, const Stack_pt<K> &s);

private:
    T elem;
    StackNode *next;
};

template<class T>
class Stack_pt {
public:
    typedef T valuetype;

    Stack_pt();

    Stack_pt(const Stack_pt<T> &);

    ~Stack_pt();

    bool empty() const;

    valuetype peek() const;

    valuetype read() const;

    valuetype pop();

    void push(valuetype);

    void print() const;

    Stack_pt<T> &operator=(const Stack_pt<T> &); // sovraccarico dell'operatore =
    bool operator==(const Stack_pt<T> &); // sovraccarico dell'operatore ==

    template<class K>
    friend ostream &operator<<(ostream &os, const Stack_pt<K> &s); // sovraccarico dell'operatore <<

    // FUNZIONI ACCESSORIE
    // metodo che rimuove tutti gli elementi k dallo stack
    void remove(Stack_pt<T> &, T);

    // metodo che conta le occorrenze dell'elemento k nello stack
    int count(Stack_pt<T> &, T);

    // metodo che inverte lo stack
    Stack_pt<T> reverse(Stack_pt<T> &S);


private:
    StackNode<T> *head;
};

// Costruttore di default
template<class T>
Stack_pt<T>::Stack_pt() {
    head = nullptr;
}

// Distruttore
template<class T>
Stack_pt<T>::~Stack_pt() {
    while (!empty()) {
        pop();
    }
};

// Costruttore di copia
template<class T>
Stack_pt<T>::Stack_pt(const Stack_pt<T> &src) {
    // inizializzo il valore della testa della pila
    head = nullptr;

    // verifico che la pila copiata non e' vuota
    if (!src.empty()) {
        Stack_pt<T> tmp;
        StackNode<T> *nodo_letto = src.head;

        // copio gli elementi dello stack da copiare in uno stack temporaneo
        // in questo modo ho invertito lo stack da copiare
        while (nodo_letto != nullptr) {
            tmp.push(nodo_letto->elem);
            nodo_letto = nodo_letto->next;
        }

        // inserisco gli elementi nello stack di destinazione
        nodo_letto = tmp.head;
        while (nodo_letto != nullptr) {
            this->push(nodo_letto->elem);
            nodo_letto = nodo_letto->next;
        }

    }
}

template<class T>
typename Stack_pt<T>::valuetype Stack_pt<T>::read() const {
    T readElem;

    // verifico che la pila non sia vuota
    if (!empty()) {
        readElem = head->elem;
    }
    return readElem;
}

template<class T>
bool Stack_pt<T>::empty() const {
    return head == nullptr;
}

template<class T>
T Stack_pt<T>::peek() const {
    if (!empty()) {
        return head->elem;
    } else {
        throw EmptyStackException();
    }
}

template<class T>
T Stack_pt<T>::pop() {
    StackNode<T> *tmp;
    T e;
    if (!empty()) {
        tmp = this->head; // memorizzo il vecchio top
        e = this->head->elem;
        this->head = this->head->next;
    }
    return e;
}

template<class T>
void Stack_pt<T>::push(valuetype el) {
    StackNode<T> *tmp = new StackNode<T>;
    tmp->elem = el;
    tmp->next = head;
    head = tmp;
}

template<class T>
void Stack_pt<T>::print() const {
    if (!empty()) {
        StackNode<T> *toPrint;
        toPrint = head;

        while (toPrint != nullptr) {
            // stampo il valore del nodo della pila
            T toPrintValue;
            toPrintValue = toPrint->value;

            cout << toPrintValue << "\n" << endl;

            // vado avanti
            toPrint = toPrint->next;
        }
    } else {
        cout << "La pila e' vuota \n" << endl;
    }
}

template<class K>
ostream &operator<<(ostream &os, const Stack_pt<K> &p) {
    StackNode<K> *tmp = nullptr;
    os << "TOP [";

    if (!p.empty()) {
        tmp = p.head;

        while (tmp->next != nullptr) {
            os << tmp->elem << "|";
            tmp = tmp->next;
        }
        os << tmp->elem;
    }

    os << "] BOT" << std::endl;
    delete tmp;
    return os;
}

template<class T>
Stack_pt<T> &Stack_pt<T>::operator=(const Stack_pt<T> &src) {
    if (this != &src) {
        Stack_pt<T> tmp;
        head = nullptr;
        // verifico che la pila copiata non e' vuota
        if (!src.empty()) {
            StackNode<T> *nodo_letto = src.head;
            while (nodo_letto != nullptr) {
                tmp.push(nodo_letto->elem);
                nodo_letto = nodo_letto->next;
            }
            nodo_letto = tmp.head;
            this->~Stack_pt();
            while (nodo_letto != nullptr) {
                this->push(nodo_letto->elem);
                nodo_letto = nodo_letto->next;
            }
        }
    }
    return *this;
}

template<class T>
bool Stack_pt<T>::operator==(const Stack_pt<T> &src) {
    StackNode<T> *destN = head;
    StackNode<T> *srcN = src.head;
    // verifico che esistano
    while (destN != nullptr && srcN != nullptr) {
        // effettuo il confronto
        if (destN->elem != srcN->elem) {
            destN = nullptr;
            srcN = nullptr;
            delete destN, srcN;
            return false;
        } else {
            destN = destN->next;
            srcN = srcN->next;
        }
    }
    if (destN == srcN) {
        destN = nullptr;
        srcN = nullptr;
        delete destN, srcN;
        return true;
    } else {
        destN = nullptr;
        srcN = nullptr;
        delete destN, srcN;
        return false;
    }

}

// FUNZIONI ACCESSORIE
// metodo che rimuove le occorrenze di k da S
template<class T>
void Stack_pt<T>::remove(Stack_pt<T> &S, T k) {
    Stack_pt<T> tmp;
    // fase di ricerca
    while (!S.empty()) {
        if (S.peek() != k) {
            tmp.push(S.pop());
        } else {
            S.pop();
        }
    }
    // aggiusto la pila
    while (!tmp.empty()) {
        S.push(tmp.pop());
    }
}

// metodo che conta le occorrenze di k in S
template<class T>
int Stack_pt<T>::count(Stack_pt<T> &S, T k) {
    int count = 0;
    Stack_pt<T> tmp;
    while (!S.empty()) {
        if (S.peek() == k) {
            count++;
        }
        tmp.push(S.pop());
    }
    while (!tmp.empty()) {
        S.push(tmp.pop());
    }
    return count;
}

// Metodo che restituisce la lista di input invertito
template<class T>
Stack_pt<T> Stack_pt<T>::reverse(Stack_pt<T> &S) {
    Stack_pt<T> temp;
    StackNode<T> *t = S.head;
    while (t != nullptr) {
        temp.push(t->elem);
        t = t->next;
    }
    S = temp;
    return S;
}


#endif // PILAPT_H
