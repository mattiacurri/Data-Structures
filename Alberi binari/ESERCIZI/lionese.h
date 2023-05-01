
#ifndef REALIZZAZIONI_LIONESE_H
#define REALIZZAZIONI_LIONESE_H

#include "../linkedBinTree.h"

template<class T>
class lionese {
public:
    bool isLionese(BinTree_pt<T> &BT);

private:
    void checkLionese(BinTree_pt<T> &BT, typename BinTree_pt<T>::node n, bool &isLionese);
};

// La funzione restituisce true se l'albero è lionese, false altrimenti
// Un albero si definisce lionese se tutti i figli destri di nodi sono pari e tutti i figli sinistri sono dispari. La radice dell’albero può contenere qualsiasi valore in quanto non è né figlio destro né sinistro
template<class T>
bool lionese<T>::isLionese(BinTree_pt<T> &BT) {
    if (!BT.alberoBinVuoto()) {
        bool lionese = true;
        checkLionese(BT, BT.root(), lionese);
        return lionese;
    }
    // se l'albero è vuoto allora non è lionese
    return false;
}

template<class T>
void lionese<T>::checkLionese(BinTree_pt<T> &BT, typename BinTree_pt<T>::node n, bool &isLionese) {
    if (!BT.leftEmpty(n) && !BT.rightEmpty(n)) {
        // Ignoro la radice
        if (BT.root() != n) {
            if (!BT.leftEmpty(n)) {
                // Se il figlio sinistro di n è pari allora l'albero non è lionese ed esco dalla funzione, altrimenti continuo a verificare
                if (BT.read(BT.leftNode(n)) % 2 != 1)
                    isLionese = false;
                else
                    checkLionese(BT, BT.leftNode(n), isLionese);
            }
            if (isLionese && !BT.rightEmpty(n)) {
                // Se il figlio destro di n è pari allora l'albero non è lionese ed esco dalla funzione, altrimenti continuo a verificare
                if (BT.read(BT.rightNode(n)) % 2 != 0)
                    isLionese = false;
                else
                    checkLionese(BT, BT.rightNode(n), isLionese);
            }
        }
    }
}

#endif // REALIZZAZIONI_LIONESE_H
