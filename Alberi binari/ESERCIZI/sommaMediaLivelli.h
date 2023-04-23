#ifndef REALIZZAZIONI_SOMMAMEDIALIVELLI_H
#define REALIZZAZIONI_SOMMAMEDIALIVELLI_H

#include "../linkedBinTree.h"

template<class T>
class sub_mean_bin {
public:
    VectorList<double> mean(BinTree_pt<T> &);

private:
    T sumLevel(BinTree_pt<T>, int);

    T sumLevel(BinTree_pt<T> B, typename BinTree_pt<T>::node n, int k, int current_depth);

};

template<class T>
VectorList<double> sub_mean_bin<T>::mean(BinTree_pt<T> &tree) {
    double sum[tree.height(tree.root()) + 1];
    double nodes[tree.height(tree.root()) + 1];
    for (int i = 0; i < tree.height(tree.root()) + 1; i++) {
        double a = sumLevel(tree, i);
        sum[i] = a;
        double b = tree.countNodes(tree.root(), i, 0);
        nodes[i] = b;
    }
    VectorList<double> list;
    for (int i = 0; i <= tree.height(tree.root()); i++) {
        double x = sum[i];
        double y = nodes[i];
        double med = x / y;
        list.insert(med, i + 1);
    }
    return list;
}

template<class T>
T sub_mean_bin<T>::sumLevel(BinTree_pt<T> B, int k) {
    T sum = 0;

    if (k >= 0 && k <= B.height(B.root())) {
        sum = sumLevel(B, B.root(), k, 0);
    }

    return sum;
}

template<class T>
T sub_mean_bin<T>::sumLevel(BinTree_pt<T> B, typename BinTree_pt<T>::node n, int k, int current_depth) {
    T sx = 0;
    T dx = 0;
    if (current_depth == k) {
        return B.read(n);
    } else {
        if (!B.leftEmpty(n)) {
            sx += sumLevel(B, B.leftNode(n), k, current_depth + 1);
        }
        if (!B.rightEmpty(n)) {
            dx += sumLevel(B, B.rightNode(n), k, current_depth + 1);
        }
    }
    return (sx + dx);

}

#endif