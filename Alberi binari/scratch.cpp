#include <iostream>
#include "linkedBinTree.h"

int main() {
    BinTree_pt<int> tree;
    tree.insertRoot(3);
    BinTree_pt<int>::node n;
    n = tree.root();
    tree.insertLeft(n, 5);
    tree.insertRight(n, 1);
    n = tree.nodeLeft(tree.root());
    tree.insertLeft(n, 6);
    tree.insertRight(n, 2);
    n = tree.nodeRight(tree.root());
    tree.insertLeft(n, 0);
    tree.insertRight(n, 8);
    tree.printTree(tree.root());
    return 0;
}