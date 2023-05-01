#ifndef REALIZZAZIONI_BST_H
#define REALIZZAZIONI_BST_H

#include "../linkedBinTree.h"
#include <iostream>
#include <stdexcept>

using namespace std;

class BST {
public:
    bool is_bst();

    void insert(int);

    bool search(int);

    int max();

    int min();

    void print();

    void erase(int k);

    BinTree_pt<int>::node successor(Bintree_pt<int>::node);

    BinTree_pt<int>::node predecessor(Bintree_pt<int>::node);

private:
    Bintree_pt<int> T;

    bool search(int, Bintree_pt<int>::node);

    void print(Bintree_pt<int>::node);

    void isBST(Bintree_pt<int>::node, bool &);

    int max(Bintree_pt<int>::node n);

    int min(Bintree_pt<int>::node n);

    void eraseNode(Bintree_pt<int>::node n, int k);
};

// La funzione erase, se exists, il node indentificato dalla chiave k
void BST::erase(int k) {
    if (!T.alberoBinVuoto() && search(k)) {
        eraseNode(T.root(), k);
    }
}

// Cancellazione di un nodo da un BST e modifica della struttura per conservare le proprietà di un BST
void BST::eraseNode(Bintree_pt<int>::node n, int k) {
    if (k < T.read(n) && !T.leftEmpty(n))
        eraseNode(T.leftNode(n), k);
    if (k > T.read(n) && !T.rightEmpty(n))
        eraseNode(T.rightNode(n), k);
        // CHIAVE TROVATA
    else {
        // CASO 1 -> FOGLIA
        if (T.rightEmpty(n) && T.leftEmpty(n))
            T.deleteBinTree(n);
            // CASO 2 -> IL NODO HA DUE FIGLI
        else if (!T.leftEmpty(n) && !T.rightEmpty(n)) {
            // TROVA IL SUCCESSORE DA SOSTITUIRE
            Bintree_pt<int>::node succ = successor(n);
            // Copio il valore del successore nel nodo corrente
            T.write(n, T.read(succ));
            // Cancello ricorsivamente il successivo
            eraseNode(T.leftNode(n), T.read(succ));
        }
            // CASO 3 -> IL NODO HA SOLO UN FIGLIO
        else {
            Bintree_pt<int>::node child;
            if (T.rightEmpty(n))
                child = T.leftNode(n);
            else
                child = T.rightNode(n);
            T.write(n, T.read(child));
            // cancella ricorsivamente il successivo
            eraseNode(T.leftNode(n), T.read(child));
        }
    }
}

// La funzione ritorna TRUE se il node identificato dalla chiave K esiste, false ALTRIMENTI
bool BST::search(int k) {
    bool exists = false;
    if (!T.alberoBinVuoto()) {
        exists = search(k, T.root());
    }
    return exists;
}

// funzione di ricerca di un nodo
bool BST::search(int k, Bintree_pt<int>::node n) {
    // se ho trovato il nodo restituisco true
    if (T.read(n) == k)
        return true;
    // se la chiave che sto cercando ha un valore minore della chiave del nodo attuale E il nodo attuale ha un figlio sinistro richiamo la funzione di ricerca sul figlio sinistro
    if (k < T.read(n) && !T.leftEmpty(n))
        return search(k, T.leftNode(n));
    // se la chiave che sto cercando ha un valore maggiore della chiave del node attuale AND il node attuale ha un figlio destro richiamo la funzione di ricerca sul figlio destro
    if (k > T.read(n) && !T.rightEmpty(n))
        return search(k, T.rightNode(n));
    // se non ho trovato la chiave restituisco FALSE
    return false;
}

// Inserimento in un BST, rispettando le proprietà
void BST::insert(int k) {
    // la chiave non deve esistere all'interno del BST
    if (!search(k)) {
        if (T.alberoBinVuoto()) {
            // CASO SEMPLICE: ALBERO VUOTO -> INSERISCO L'ELEMENTO COME RADICE
            T.insertRoot(k);
        } else {
            Bintree_pt<int>::node n = T.root();
            bool continua = true;
            // VADO ALLA RICERCA DELLA POSIZIONE IN CUI INSERIRE LA CHIAVE K, tenendo conto delle proprietà di un BST
            while (continua) {
                if (k < T.read(n) && !T.leftEmpty(n))
                    n = T.leftNode(n);
                else if (k > T.read(n) && !T.rightEmpty(n))
                    n = T.rightNode(n);
                else
                    continua = false;
            }
            // INSERISCO il VALORE NELLA POSIZIONE CORRETTA
            if (k < T.read(n)) {
                T.leftInsert(n, k);
            } else {
                T.rightInsert(n, k);
            }
        }
    }
}

// Funzione che restituisce il valore massimo di un bst
int BST::max() {
    if (!T.alberoBinVuoto()) {
        return max(T.root());
    } else
        throw out_of_range("ALBERO VUOTO");
}

// Funzione che restituisce il valore massimo di un BST che ha come radice il nodo n. Il valore massimo è la foglia piu' a destra dell'albero
int BST::max(Bintree_pt<int>::node n) {
    if (T.rightEmpty(n))
        return T.read(n);
    else
        return max(T.rightNode(n));
}

// Funzione che restituisce il valore minimo di un bst
int BST::min() {
    if (!T.alberoBinVuoto()) {
        return min(T.root());
    } else
        throw out_of_range("ALBERO VUOTO");
}

// Funzione che restituisce il valore massimo di un BST che ha come radice il nodo n. Il valore minimo è la foglia piu' a sinistra dell'albero
int BST::min(Bintree_pt<int>::node n) {
    if (T.leftEmpty(n))
        return T.read(n);
    else
        return min(T.leftNode(n));
}

// Funzione che restituisce true se l'albero è un BST, false altrimenti
bool BST::is_bst() {
    if (!T.alberoBinVuoto()) {
        bool isBst = true;
        isBST(T.root(), isBst);
        return isBst;
    }
    return true;
}

// Funzione che verifica se un albero è un BST
void BST::isBST(Bintree_pt<int>::node n, bool &isBst) {
    if (isBst) {
        // calcolo MAX e MIN dell'albero avente come radice n
        int min_value = min(n);
        int max_value = max(n);
        // se N è maggiore del massimo o minore del minimo allora l'albero non è un BST
        if (max_value < T.read(n) || min_value > T.read(n))
            isBst = false;
        // verifico se il valore di N esiste gia' nei suoi sottoalberi, nel caso esista gia' allora non è un BST
        if (!T.leftEmpty(n))
            if (search(T.read(n), T.leftNode(n)))
                isBst = false;
        if (!T.rightEmpty(n))
            if (search(T.read(n), T.rightNode(n)))
                isBst = false;
        // se l'albero risulta essere ancora un BST, richiamo la funzione di verifica sui figli di n (se esistono)
        if (isBst) {
            if (!T.leftEmpty(n))
                isBST(T.leftNode(n), isBst);
            if (!T.rightEmpty(n))
                isBST(T.rightNode(n), isBst);
        }
    }
}

// print di un BST
void BST::print() {
    cout << "[ ";
    if (!T.alberoBinVuoto()) {
        print(T.root());
    }
    cout << "]" << endl;
}

// Visita simmetrica
void BST::print(Bintree_pt<int>::node n) {
    if (!T.leftEmpty(n))
        print(T.leftNode(n));
    cout << T.read(n) << " ";
    if (!T.rightEmpty(n))
        print(T.rightNode(n));
}

// Funzione che restituisce il node successore del node n
Bintree_pt<int>::node BST::successor(Bintree_pt<int>::node n) {
    // Se il node ha un figlio destro, il successore è il node più a sinistra del sottoalbero destro di n
    if (!T.rightEmpty(n)) {
        n = T.rightNode(n);
        while (!T.leftEmpty(n)) {
            n = T.leftNode(n);
        }
        return n;
    } else {
        // Altrimenti, il successore è il piu piccolo antenato di n il cui child sinistro è antenato di n
        Bintree_pt<int>::node p;
        if (n != T.root())
            p = T.genitore(n);
        while (p != T.root() && n == T.rightNode(n)) {
            n = p;
            p = T.genitore(p);
        }
        return p;
    }
    // altrimenti non exists un successore
    throw out_of_range("NON exists UN SUCCESSORE");
}

// Funzione che restituisce il node predecessor del node n
Bintree_pt<int>::node BST::predecessor(Bintree_pt<int>::node n) {
    // Se n ha un child sinistro, il predecessor di n è il node più a destra dell sottoalbero sinistro di n
    if (!T.leftEmpty(n)) {
        n = T.leftNode(n);
        while (!T.rightEmpty(n)) {
            n = T.rightNode(n);
        }
        return n;
    } else {
        // Altrimenti, il prececessore è il piu grande antenato di n il cui figlio destro è antenato di n
        Bintree_pt<int>::node p;
        if (n != T.root())
            p = T.genitore(n);
        while (p != T.root() && T.leftNode(n) == n) {
            n = p;
            p = T.genitore(p);
        }
        return p;
    }
    // altrimenti non exists un successore
    throw out_of_range("NON exists UN predecessor");
}

#endif // REALIZZAZIONI_BST_H
