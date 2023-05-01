#ifndef SOMMASOTTOALBERI_H
#define SOMMASOTTOALBERI_H

#include "../linkedBinTree.h"

/* Dato un albero binario di n nodi, contare i sottoalberi che hanno somma dei nodi pari a un intero k */

class checkTree {
public:
    int sum(const BinTree_pt<int> &, int);

private:
    int visitSubTree(const BinTree_pt<int> &, int, BinTree_pt<int>::node);

    int sumSubTree(const BinTree_pt<int> &, BinTree_pt<int>::node);

};

template<class T>
int checkTree::sum(BinTree_pt<int> t, int k) {
    int s = 0;
    if (!B.empty()) {
        sum(t, k, t.root(), s);
    }
}

// La funzione visita un sottoalbero e nel mentre contra il numero di sottoalberi la cui somma dei valori dei nodi è pari a K
int checkTree::visitSubTree(const BinTree_pt<int> &B, int k, BinTree_pt<int>::node n) {
    // valore statico perchè ogni volta che richiamo ricorsivamente la funzione questo non deve variare
    static int count = 0;
    int sum = sumSubTree(B, n);
    // se la somma del sottoalbero avente come radice n è pari a k allora incremento il contatore
    if (sum == k)
        count++;
    // richiamo la funzione di visita sui figli del nodo n (se esistono)
    if (!B.leftEmpty(n)) {
        visitSubTree(B, k, B.leftNode(n));
    }
    if (!B.rightEmpty(n)) {
        visitSubTree(B, k, B.rightNode(n));
    }
    return count;
}

// La funzione restituisce la somma dei valori del sottoalbero avente come radice il nodo n
int checkTree::sumSubTree(const BinTree_pt<int> &B, BinTree_pt<int>::node n) {
    if (B.rightEmpty(n) && B.leftEmpty(n))
        // se il nodo è foglia restituisco il valore del nodo
        return B.read(n);
    else {
        int sx = 0, dx = 0;
        // se il nodo ha un figlio sinistro calcolo la somma dei valori del sottoalbero sinistro
        if (!B.leftEmpty(n))
            sx = sumSubTree(B, B.leftNode(n));
        // se il nodo ha un figlio destro calcolo la somma dei valori del sottoalbero destro
        if (!B.rightEmpty(n))
            dx = sumSubTree(B, B.rightNode(n));
        // restituisco il valore del nodo sommato alla somma dei valori dei suoi sottoAlberi sinistro e destro
        return (B.read(n) + sx + dx);
    }
}

#endif // SOMMASOTTOALBERI_H