#ifndef _ALBERO_BINARIO_COLLEGATO_H
#define _ALBERO_BINARIO_COLLEGATO_H

#include "../Code/codapt.h"
#include "../Pile/pilapt.h"
#include "../Liste/vectorList/vectorList.h"
#include "linkedBinTree.h"

#include <stdexcept>
#include <bits/stdc++.h>

using namespace std;

template<class T>
class BinTree_pt;

template<class T>
class treeNode {
    friend class BinTree_pt<T>;

public:
    // costruttori
    treeNode() {
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }

    treeNode(T val) {
        value = val;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }

    template<class T1>
    friend ostream &operator<<(ostream &, BinTree_pt<T1> &);

private:
    T value;
    // int level;
    treeNode<T> *parent;
    treeNode<T> *left;
    treeNode<T> *right;
};

template<class T>
class BinTree_pt {
public:
    // ridefinisco i tipi
    typedef T valuetype;
    typedef treeNode<T> *node;

    // costruttore
    BinTree_pt();

    // distruttore
    ~BinTree_pt() = default;

    // metodo per leggere il value di un node
    valuetype read(node n) const {
        return n->value;
    }

    // metodo per verificare se l'albero e' vuoto
    bool empty() const;

    // metodo che verifica se il figlio sinistro di un nodo esiste
    bool leftEmpty(node) const;

    // metodo che verifica se il figlio destro di un nodo esiste
    bool rightEmpty(node) const;

    // metodo che restituisce il nodo radice
    node root() const;

    // metodo che restituisce il genitore del nodo selezionato
    node parent(node n) const;

    // metodo che restituisce il nodo di sinistra del nodo selezionato
    node leftNode(node n) const;

    // metodo che restituisce il nodo di destra del nodo selezionato
    node rightNode(node n) const;

    // metodo per inserire un nodo alla radice dell'albero
    void insertRoot(T insertedValue);

    // metodo per inserire a sinistra un nodo
    void leftInsert(node node_parent, T insertedValue);

    // metodo per inserire a destra un nodo
    void rightInsert(node node_parent, T insertedValue);

    // metodo che elimina un nodo dell'albero
    void deleteSubBinTree(node n);

    // metodo per stampare un albero binario
    void printTree(node pRoot) const;

    // metodo per calcolare l'altezza
    int height(node n) const;

    // metodo per calcolare la profondità
    int depth(node) const;

    // metodo per verificare se un nodo e' foglia
    bool leaf(node n) const;

    // algoritmo dfs
    void dfs(node n) const;

    // metodo per contare i nodi di un livello
    int countNodes(node, int, int) const;

    // metodo che restituisce il numero di nodi
    int getNumNodes() const;

    bool operator==(const BinTree_pt<T> &); // sovraccarico dell'operatore ==

    // Metodo che sovrascrive l'attuale valore del figlio sinistro di un nodo, se esistente
    void leftWrite(node, T);

    // Metodo che sovrascrive l'attuale valore del nodo, se esistente
    void write(node, T);

    // Metodo che sovrascrive l'attuale valore del figlio destro di un nodo, se esistente
    void rightWrite(node, T);

    // Metodo che inverte un albero binario
    void reverseBinTree(node n);

    // Dati due alberi binari A e B, e due nodi u e v, con u appartenente ad A e v appartenente a B, implementare la funzione mutation che scambia i sottoalberi con radice u e v
    void mutation(BinTree_pt<T> A, BinTree_pt<T> B, BinTree_pt<T>::node u, BinTree_pt<T>::node v);

    // Metodo che copia il nodo n dell'albero A nell'albero A1 con nodo n1
    void copy(BinTree_pt<T> A, BinTree_pt<T>::node n, BinTree_pt<T> A1, BinTree_pt<T>::node n1);

    // Metodo che rimuove il sottoalbero con radice in r
    void remove(node r);

private:
    node rootTree;
    int numNodes;

    treeNode<T> *copyNode(treeNode<T> *, treeNode<T> *);

    void deleteNode(treeNode<T> *);

    void deleteLeft(treeNode<T> *);

    void deleteRight(treeNode<T> *);

    bool compareNodes(treeNode<T> *, treeNode<T> *);
};

template<class T>
bool BinTree_pt<T>::compareNodes(treeNode<T> *n1, treeNode<T> *n2) {
    bool equal = true;
    if (n1->value == n2->value) {
        if (equal && leftNode(n1) != nullptr && leftNode(n2) != nullptr) {
            equal = compareNodes(leftNode(n1), leftNode(n2));
        } else return equal;
        if (equal && rightNode(n1) != nullptr && rightNode(n2) != nullptr) {
            equal = compareNodes(rightNode(n1), rightNode(n2));
        } else return equal;
    } else equal = false;
    return equal;
}

template<class T>
BinTree_pt<T>::BinTree_pt() {
    rootTree = nullptr;
    numNodes = 0;
}

/*template<class T>
BinTree_pt<T>::~BinTree_pt() {
    if (!empty()) {
        deleteSubBinTree(rootTree);
    } else {
        rootTree = nullptr;
        delete rootTree;
    }
}*/

/*
template<class T>
treeNode<T> *BinTree_pt<T>::copyNode(node *toCopy, node *parent) {
    if (toCopy == nullptr)
        return nullptr;
    auto *newNode = new treeNode<T>;
    newNode->parent = parent;
    newNode->value = toCopy->value;
    newNode->left = copyNode(toCopy->left, toCopy);
    newNode->right = copyNode(toCopy->right, toCopy);
    numNodes++;
    return newNode;
}*/

template<class T>
void BinTree_pt<T>::deleteNode(treeNode<T> *toDelete) {
    if (toDelete != nullptr) {
        deleteNode(toDelete->left);
        deleteNode(toDelete->right);
        delete toDelete;
        numNodes--;
    }
}


template<class T>
void BinTree_pt<T>::deleteLeft(treeNode<T> *toDelete) {
    if (toDelete != nullptr) {
        deleteNode(toDelete->left);
        toDelete->left = nullptr;
    }
}

template<class T>
void BinTree_pt<T>::deleteRight(treeNode<T> *toDelete) {
    if (toDelete != nullptr) {
        deleteNode(toDelete->right);
        toDelete->right = nullptr;
    }
}

template<class T>
bool BinTree_pt<T>::empty() const {
    bool tree_empty;
    tree_empty = false;

    if (rootTree == nullptr) {
        tree_empty = true;
    }

    return tree_empty;
}

template<class T>
bool BinTree_pt<T>::leftEmpty(node n) const {
    return (n->left == nullptr);
}

template<class T>
bool BinTree_pt<T>::rightEmpty(node n) const {
    return (n->right == nullptr);
}

template<class T>
typename BinTree_pt<T>::node BinTree_pt<T>::root() const {
    if (!empty()) {
        return rootTree;
    } else {
        throw std::out_of_range("Albero vuoto");
    }
}

template<class T>
typename BinTree_pt<T>::node BinTree_pt<T>::parent(node n) const {
    return n->parent;
}

template<class T>
typename BinTree_pt<T>::node BinTree_pt<T>::leftNode(node n) const {
    if (!leftEmpty(n)) {
        return n->left;
    }
}

template<class T>
typename BinTree_pt<T>::node BinTree_pt<T>::rightNode(node n) const {
    if (!rightEmpty(n)) {
        return n->right;
    }
}

template<class T>
void BinTree_pt<T>::insertRoot(T insertedValue) {
    // verifico che l'albero non sia vuoto
    if (empty()) {
        // creo il nuovo nood
        node insertedNode;
        insertedNode = new treeNode<T>(insertedValue);

        rootTree = insertedNode;
    } else {
        throw std::out_of_range("Albero non vuoto");
    }
}

template<class T>
void BinTree_pt<T>::leftInsert(node node_parent, T insertedValue) {
    // inserisco il nodo solo se il nodo genitore non ha gia' un figlio a sinistra
    if (node_parent->left == nullptr) {
        // creo il nuovo nodo
        node insertedNode;
        insertedNode = new treeNode<T>(insertedValue);

        // assegno i valori dei puntatori del nuovo nodo
        insertedNode->parent = node_parent;
        node_parent->left = insertedNode;

        numNodes++;
    } else {
        throw std::out_of_range("Figlio sinistro gia' presente");
    }
}

template<class T>
void BinTree_pt<T>::leftWrite(node node_parent, T insertedValue) {
    // sovrascrivo il value attuale
    if (node_parent->left != nullptr) {
        node_parent->left->value = insertedValue;
    } else {
        throw std::out_of_range("Figlio sinistro non esistente, usare il metodo leftInsert per inserirlo");
    }
}

template<class T>
void BinTree_pt<T>::write(node n, T insertedValue) {
    // sovrascrivo il value attuale
    if (n != nullptr) {
        n->value = insertedValue;
    } else {
        throw std::out_of_range("Nodo non esistente");
    }
}

template<class T>
void BinTree_pt<T>::rightWrite(node node_parent, T insertedValue) {
    // sovrascrivo il value attuale
    if (node_parent->right != nullptr) {
        node_parent->right->value = insertedValue;
    } else {
        throw std::out_of_range("Figlio destro non esistente, usare il metodo rightInsert per inserirlo");
    }
}

template<class T>
void BinTree_pt<T>::rightInsert(node node_parent, T insertedValue) {
    // inserisco il nodo solo se il nodo genitore non ha gia' un figlio a destra
    if (node_parent->right == nullptr) {
        // creo il nuovo nodo
        node insertedNode;
        insertedNode = new treeNode<T>(insertedValue);

        // assegno i valori dei puntatori del nuovo nodo
        insertedNode->parent = node_parent;
        node_parent->right = insertedNode;

        numNodes++;
    }
}

template<class T>
void BinTree_pt<T>::deleteSubBinTree(node n) {
    if (n->parent == nullptr) {
        deleteNode(n);
        rootTree = nullptr;
    } else {
        if (n->parent->left == n)
            deleteLeft(n->parent);
        else
            deleteRight(n->parent);
    }
}

template<class T>
void BinTree_pt<T>::printTree(node pRoot) const {
    if (pRoot == nullptr) {
        return;
    }
    Stack<node> cStack;
    node dx;
    node sx;

    cout << pRoot->value << " : ";
    dx = pRoot->right;
    sx = pRoot->left;

    if (sx != nullptr) {
        cout << sx->value << " ";
        cStack.push(sx);
    }
    if (dx != nullptr) {
        cout << dx->value << " ";
        cStack.push(dx);
    }

    cout << endl;

    while (!cStack.empty()) {
        node rChild;
        rChild = cStack.read();
        printTree(rChild);
        cStack.pop();
    }
}

template<class T>
int BinTree_pt<T>::height(node n) const {
    if (!empty()) {
        if (leftEmpty(n) && rightEmpty(n)) {
            return 0;
        } else {
            int height_sx = 0;
            int height_dx = 0;
            if (!leftEmpty(n)) {
                height_sx = height(leftNode(n));
                height_sx++;
            }
            if (!rightEmpty(n)) {
                height_dx = height(rightNode(n));
                height_dx++;
            }
            return max(height_dx, height_sx);
        }
    } else {
        throw std::out_of_range("Albero non vuoto, altezza non trovata");
    }
}

template<class T>
int BinTree_pt<T>::depth(node endPath) const {
    int x = 0;
    node n = endPath;
    if (!empty()) {
        if (leftEmpty(n) && rightEmpty(n)) {
            return 0;
        } else {
            while (n != root()) {
                x++;
                n = n->parent;
            }
            return x;
        }
    }
    return x;
}

template<class T>
bool BinTree_pt<T>::leaf(node n) const {
    bool isLeaf = false;

    if (n->left == nullptr && n->right == nullptr) {
        isLeaf = true;
    }

    return isLeaf;
}

//SOVRACCARICO STAMPA (usa di default la preVisita)
template<class T1>
ostream &operator<<(ostream &os, BinTree_pt<T1> &T) {
    if (T.empty()) {
        os << "Albero vuoto" << endl;
    } else {
        os << "[ ";
    }
    T.dfs(T.root());
    os << "] " << endl;
    return os;
}

// preVisita
template<class T>
void BinTree_pt<T>::dfs(node n) const {
    if (n != nullptr) {
        cout << n->value << " ";
        dfs(n->left);
        dfs(n->right);
    }
}

template<class T>
int BinTree_pt<T>::countNodes(node n, int k, int current_depth) const {
    int sx = 0;
    int dx = 0;
    if (current_depth == k) {
        return 1;
    } else {
        if (!leftEmpty(n)) {
            sx += countNodes(n->left, k, current_depth + 1);
        }
        if (!rightEmpty(n)) {
            dx += countNodes(n->right, k, current_depth + 1);
        }
    }
    return (sx + dx);
}

template<class T>
void BinTree_pt<T>::remove(node r) {
    if (!leftEmpty(r)) {
        deleteSubBinTree(leftNode(r));
    }
    if (!rightEmpty(r)) {
        deleteBinTree(rightNode(r));
    }
}

template<class T>
int BinTree_pt<T>::getNumNodes() const {
    return this->numNodes;
}

/*
- Scrivere un programma ricorsivo che cancella da un albero binario di nodi con value intero tutte le foglie di value pari
- Modificare la struttura cella in modo da poter memorizzare per ogni nodo n il numero di nodi che si trovano nel sottoalbero con radice in n. Modificare di conseguenza la stampa di un albero binario in modo che visualizzi, per ogni nodo n, l'etichetta di n e il numero di nodi del sottoalbero radicato in n
- Dati due alberi binari A e B, e due nodi u e v, con u appartenente ad A e v appartenente a B, implementare la funzione mutation che scambia i sottoalberi con radice u e v
- Scrivere un programma in grado di acquisire e rappresentare con un albero di analisi (parse tree) un'espressione aritmetica. Fornire la funzione per la valutazione dell'espressione rappresentata da un albero. */

// Dati due alberi binari A e B, e due nodi u e v, con u appartenente ad A e v appartenente a B, implementare la funzione mutation che scambia i sottoalberi con radice u e v
template<class T>
void BinTree_pt<T>::mutation(BinTree_pt<T> A, BinTree_pt<T> B, BinTree_pt<T>::node u, BinTree_pt<T>::node v) {
    BinTree_pt<T> A1;
    A1.insertRoot(u->value);

    BinTree_pt<T> B1;
    B1.insertRoot(v->value);

    copy(A, u, A1, A1.root());
    copy(B, v, B1, B1.root());

    A.deleteSubBinTree(u); // funzione che rimuove solo il sottoalbero sinistro e il sottoalbero destro radicati in u
    B.deleteSubBinTree(v); // funzione che rimuove solo il sottoalbero sinistro e il sottoalbero destro radicati in v
    cout << "A1: " << A1 << endl;
    cout << "B1: " << B1 << endl;

    copy(A1, A1.root(), B, v);
    copy(B1, B1.root(), A, u);
}

template<class T>
void BinTree_pt<T>::copy(BinTree_pt<T> A, BinTree_pt<T>::node n, BinTree_pt<T> A1, BinTree_pt<T>::node n1) {
    A1.write(n1, A.read(n));
    if (!A.leftEmpty(n)) {
        if (A1.leftEmpty(n)) {
            A1.leftInsert(n1, A.read(A.leftNode(n)));
        } else if (!A1.leftEmpty(n)) {
            A1.leftWrite(n1, A.read(A.leftNode(n)));
        }
        copy(A, A.leftNode(n), A1, A1.leftNode(n1));
    }
    if (!A.rightEmpty(n)) {
        if (A1.rightEmpty(n)) {
            A1.rightInsert(n1, A.read(A.rightNode(n)));
        } else if (!A1.rightEmpty(n)) {
            A1.rightWrite(n1, A.read(A.rightNode(n)));
        }
        copy(A, A.rightNode(n), A1, A1.rightNode(n1));
    }
}

template<class T>
bool BinTree_pt<T>::operator==(const BinTree_pt<T> &BT) {
    if (numNodes != BT.numNodes) {
        return false;
    }
    return compareNodes(root(), BT.root());
}

// Con metodi da aggiustare
/*
template<class T>
void BinTree_pt<T>::reverseBinTree(node n) {
    T left;
    T right;
    if (!rightEmpty(n) && !leftEmpty(n)) {
        left = read(leftNode(n));
        leftWrite(n, read(rightNode(n)));
        rightWrite(n, left);
    }
    if (!rightEmpty(n) && leftEmpty(n)) {
        leftInsert(n, read(rightNode(n)));
        deleteRight(n);
        n = leftNode(n);
    }
    if (rightEmpty(n) && !leftEmpty(n)) {
        if (leftNode(parent(n)) == n) {
            if (leftEmpty(rightNode(parent(n)))) {
                left = read(leftNode(n));
                rightInsert(rightNode(parent(n)), left);
                deleteLeft(n);
                n = rightNode(rightNode(parent(n)));
            } else {
                left = read(leftNode(n));
                rightWrite(rightNode(parent(n)), read(leftNode(n)));
                leftWrite(n, left);
                n = rightNode(rightNode(parent(n)));
            }
        } else {
            if (rightEmpty(leftNode(parent(n)))) {
                left = read(leftNode(n));
                rightInsert(leftNode(parent(n)), left);
                deleteLeft(n);
                n = rightNode(leftNode(parent(n)));
            } else {
                left = read(leftNode(n));
                rightWrite(leftNode(parent(n)), read(leftNode(n)));
                leftWrite(n, left);
                n = rightNode(rightNode(parent(n)));
            }
        }
    }
    if (!leftEmpty(n)) {
        reverseBinTree(leftNode(n));
    }
    if (!rightEmpty(n)) {
        reverseBinTree(rightNode(n));
    }
}*/

// da aggiustare
template<class T>
void BinTree_pt<T>::reverseBinTree(node n) {
    if (n->left != nullptr && n->right != nullptr) {
        node tmp = n->left;
        n->left = n->right;
        n->right = tmp;
    } else if (n->left != nullptr && n->right == nullptr) {
        n->right = n->left;
        n->left = nullptr;
    } else if (n->left == nullptr && n->right != nullptr) {
        n->left = n->right;
        n->right = nullptr;
    }

    if (n->left != nullptr) {
        reverseBinTree(n->left);
    }
    if (n->right != nullptr) {
        reverseBinTree(n->right);
    }
}

template<class T>
treeNode<T> *BinTree_pt<T>::copyNode(treeNode<T> *toCopy, treeNode<T> *parent) {
    if (toCopy == nullptr)
        return nullptr;
    treeNode<T> *newNode = new treeNode<T>;
    newNode->padre = parent;
    newNode->value = toCopy->value;
    newNode->left = copyNode(toCopy->left, toCopy);
    newNode->right = copyNode(toCopy->right, toCopy);
    numNodes++;
    return newNode;
}


#endif
