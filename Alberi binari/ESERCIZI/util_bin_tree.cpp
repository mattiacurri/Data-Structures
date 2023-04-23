#include <iostream>
#include "../linkedBinTree.h"
#include "util_bin_tree.h"

int main() {
    BinTree_pt<int> tree;
    util_bin_tree a;
    tree.insertRoot(10);
    tree.leftInsert(tree.root(), 20);
    tree.rightInsert(tree.root(), 30);
    cout << a.d3(tree, 0) << endl;
    cout << a.lp(tree) << endl;
    cout << a.l2p(tree) << endl;
    return 0;
}

