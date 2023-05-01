#ifndef REALIZZAZIONI_SUMTREE_H
#define REALIZZAZIONI_SUMTREE_H

#include "../linkedBinTree.h"

class sumTree {
public:
    bool isSumTree(BinTree_pt<int> &);

private:
    int isSumTree2(BinTree_pt<int> &, typename BinTree_pt<int>::node n, bool &);
};

/*
 * La funzione restitusce TRUE se un'albero è un sumTree, false altrimenti
 * Un albero è un sumTree se ogni nodo ha come valore la somma dei nodi dei suoi sottoalberi destro e sinistro (se esistono)
 */
bool sumTree::isSumTree(BinTree_pt<int> &bt) {
    bool sumTree = true;
    if (!bt.empty()) {
        // la funzione di verifica è ricorsiva e restituisce un intero, equivalente alla somma di un sottoalbero
        int x = isSumTree2(bt, bt.root(), sumTree);
    }
        // se l'albero è vuoto non è un SumTree
    else
        sumTree = false;
    return sumTree;
}

int sumTree::isSumTree2(BinTree_pt<int> &bt, typename BinTree_pt<int>::node n, bool &sumTree) {
    // se l'albero non è sumTree esco dalla funzione
    if (sumTree) {
        if (bt.leftEmpty(n) && bt.rightEmpty(n)) {
            // se il nodo è foglia ritorno il valore del nodo
            return bt.read(n);
        } else {
            int sx = 0, dx = 0;
            // salvo il valore di somma del sottoalbero sinistro di n (se esiste)
            if (!bt.leftEmpty(n))
                sx = isSumTree2(bt, bt.leftNode(n), sumTree);
            // salvo il valore di somma del sottoalbero destro di n (se esiste)
            if (!bt.rightEmpty(n))
                dx = isSumTree2(bt, bt.rightNode(n), sumTree);
            if (bt.read(n) == sx + dx) {
                // se il nodo n ha come valore la somma dei valori dei suoi sottoalberi allora restituisco il valore del sottoalbero che ha come radice n, altrimenti l'albero non è sumTree ed esco dalla funzione
                return (bt.read(n) * 2);
            } else
                sumTree = false;
        }
    } else
        return 0;
}

#endif // REALIZZAZIONI_SUMTREE_H
