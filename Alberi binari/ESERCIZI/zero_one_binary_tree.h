#ifndef ALBERI_ZERO_ONE_BINARY_TREE_H
#define ALBERI_ZERO_ONE_BINARY_TREE_H

#include "linkedBinTree.h"

template<class T>
class zero_one_binary_tree : public BinTree_pt<T> {
public:
    friend BinTree_pt<T>;

    bool is_zero_one(const BinTree_pt <T> &B);

    int zero_nodes(const BinTree_pt <T> &B);

private:
    void is_zero_one(const BinTree_pt <T> &, typename BinTree_pt<T>::node, bool &);

    int zero_nodes(const BinTree_pt <T> &, typename BinTree_pt<T>::node, int depth);

    BinTree_pt <T> tree;
};

template<class T>
bool zero_one_binary_tree<T>::is_zero_one(const BinTree_pt <T> &BT) {
    if (!BT.empty() && (BT.read(BT.root()) == 0)) {
        bool isZeroOne = true;
        is_zero_one2(BT, BT.root(), isZeroOne);
        return isZeroOne;
    } else {
        return false;
    }
}

template<class T>
void zero_one_binary_tree<T>::is_zero_one(const BinTree_pt <T> &BT, typename BinTree_pt<T>::node n, bool &isZeroOne) {
    if (isZeroOne) {
        // se sono una foglia non devo svolgere alcun controllo
        if (BT.rightEmpty(n) && BT.leftEmpty(n)) {
            return;
        } else {
            if (BT.leftEmpty(n) || BT.rightEmpty(n)) {
                // se a un nodo non foglia manca un figlio allora l'albero non è di tipo zero_one
                isZeroOne = false;
                return;
            } else {
                if (BT.read(n) == 0) {
                    if (BT.read(BT.nodeRight(n)) == 0 || BT.read(BT.nodeLeft(n)) == 0) {
                        isZeroOne = false;
                        return;
                    }
                } else {
                    if (BT.read(BT.nodeRight(n)) == 1 || BT.read(BT.nodeLeft(n)) == 1) {
                        isZeroOne = false;
                        return;
                    }
                }
                this->is_zero_one2(BT, BT.nodeLeft(n), isZeroOne);
                this->is_zero_one2(BT, BT.nodeRight(n), isZeroOne);
            }
        }
    }
    return;
}

template<class T>
int zero_one_binary_tree<T>::zero_nodes(const BinTree_pt <T> &B) {
    int num_zero_nodes = 0;
    if (!B.empty()) {
        num_zero_nodes = zero_nodes(B, B.root(), 0);
    }
    return num_zero_nodes;
}

template<class T>
int zero_one_binary_tree<T>::zero_nodes(const BinTree_pt <T> &B,
                                        typename BinTree_pt<T>::node n, int depth) {
    int sx = 0;
    int dx = 0;
    int counter = 0;

    if (!B.leftEmpty(n)) {
        sx += zero_nodes(B, B.nodeLeft(n), depth + 1);
    }
    if (!B.rightEmpty(n)) {
        dx += zero_nodes(B, B.nodeRight(n), depth + 1);
    }
    if (B.read(n) == 0) {
        counter = 1;
    } else {
        counter = 0;
    }
    return (sx + dx + counter);
}

#endif // ALBERI_ZERO_ONE_BINARY_TREE_H
