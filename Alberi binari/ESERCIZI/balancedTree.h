#ifndef BILANCIALTEZZA_H
#define BILANCIALTEZZA_H

#include <iostream>
#include "../linkedBinTree.h"

template<class _value_type>
class balanced_tree {
/* Stabilisce se l’albero `e bilanciato in altezza.
* Un albero binario `e bilanciato in altezza se a) `e vuoto, o b) se per ogni nodo
* le altezze dei suoi due sottoalberi differiscono al pi`u di uno e i due sottoalberi
* sono bilanciati in altezza.
*/
public:
    bool is_height_balanced(const BinTree_pt<_value_type> &B);

/* Stabilisce se tutti i nodi non foglia dell’albero hanno esattamente due figli */
    bool complete_nodes(const BinTree_pt<_value_type> &B);

private:
    void is_height_balanced(const BinTree_pt<_value_type> &B, typename BinTree_pt<_value_type>::node n, bool &balanced);

    void complete_nodes(const BinTree_pt<_value_type> &B, typename BinTree_pt<_value_type>::node n, bool &b);

};

template<class _value_type>
bool balanced_tree<_value_type>::is_height_balanced(const BinTree_pt<_value_type> &B) {
    if (B.empty()) {
        return true;
    } else {
        bool b = true;
        is_height_balanced(B, B.root(), b);
        return b;
    }
}

template<class _value_type>
void balanced_tree<_value_type>::is_height_balanced(const BinTree_pt<_value_type> &B,
                                                    typename BinTree_pt<_value_type>::node n, bool &balanced) {
    if (balanced) {
        if (B.leftEmpty(n) && B.rightEmpty(n)) {
            return;
        } else {
            int hsx = 0;
            int hdx = 0;
            if (!B.leftEmpty(n)) {
                hsx = B.height(B.leftNode(n));
            }
            if (!B.rightEmpty(n)) {
                hdx = B.height(B.rightNode(n));
            }
            if (abs(hsx - hdx) <= 1) {
                if (!B.leftEmpty(n)) {
                    is_height_balanced(B, B.leftNode(n), balanced);
                }
                if (!B.rightEmpty(n)) {
                    is_height_balanced(B, B.rightNode(n), balanced);
                }
            } else {
                balanced = false;
            }
        }
    }
}

template<class _value_type>
bool balanced_tree<_value_type>::complete_nodes(const BinTree_pt<_value_type> &B) {
    bool b = true;
    if (!B.empty()) {
        complete_nodes(B, B.root(), b);
    }
    return b;
}

template<class _value_type>
void
balanced_tree<_value_type>::complete_nodes(const BinTree_pt<_value_type> &B, typename BinTree_pt<_value_type>::node n,
                                           bool &b) {
    if (b) {
        if (B.leftEmpty(n) && B.rightEmpty(n)) {
            return;
        } else if (!B.leftEmpty(n) && !B.rightEmpty(n)) {
            complete_nodes(B, B.leftNode(n), b);
            complete_nodes(B, B.rightNode(n), b);
        } else {
            b = false;
        }
    }
}

#endif // BILANCIALTEZZA_H