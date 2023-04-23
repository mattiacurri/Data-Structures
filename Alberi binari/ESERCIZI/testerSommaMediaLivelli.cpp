#include <iostream>
#include "sommaMediaLivelli.h"

int main() {
    BinTree_pt<int> tree;
    tree.insertRoot(1);
    tree.leftInsert(tree.root(), 2);
    tree.rightInsert(tree.root(), 3);
    tree.leftInsert(tree.leftNode(tree.root()), 4);
    tree.rightInsert(tree.leftNode(tree.root()), 5);
    tree.leftInsert(tree.rightNode(tree.root()), 6);
    tree.rightInsert(tree.rightNode(tree.root()), 7);
    tree.leftInsert(tree.leftNode(tree.leftNode(tree.root())), 8);
    tree.rightInsert(tree.leftNode(tree.leftNode(tree.root())), 9);
    tree.leftInsert(tree.rightNode(tree.leftNode(tree.root())), 10);
    tree.rightInsert(tree.rightNode(tree.leftNode(tree.root())), 11);
    tree.leftInsert(tree.leftNode(tree.rightNode(tree.root())), 12);
    tree.rightInsert(tree.leftNode(tree.rightNode(tree.root())), 13);
    tree.leftInsert(tree.rightNode(tree.leftNode(tree.rightNode(tree.root()))), 14);

    cout << tree << endl;
    sub_mean_bin<int> sub;
    VectorList<double> list = sub.mean(tree);
    cout << list << endl;
}