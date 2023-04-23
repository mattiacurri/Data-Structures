#include <iostream>

#include "balancedTree.h"

int main() {
    BinTree_pt<int> INTalb;
    BinTree_pt<int>::node INTn;
    INTalb.insertRoot(1);
    INTn = INTalb.root();
    INTalb.leftInsert(INTn, 2);
    INTalb.rightInsert(INTn, 9);
    INTn = INTalb.leftNode(INTn);
    INTalb.leftInsert(INTn, 3);
    INTalb.rightInsert(INTn, 6);
    INTn = INTalb.leftNode(INTalb.leftNode(INTalb.root()));
    INTalb.leftInsert(INTn, 4);
    INTalb.rightInsert(INTn, 5);
    INTn = INTalb.rightNode(INTalb.leftNode(INTalb.root()));
    INTalb.leftInsert(INTn, 7);
    INTalb.rightInsert(INTn, 8);

    INTn = INTalb.rightNode(INTalb.root());
    INTalb.leftInsert(INTn, 10);
    INTalb.rightInsert(INTn, 11);
    INTn = INTalb.rightNode(INTalb.rightNode(INTalb.root()));
    INTalb.leftInsert(INTn, 12);
    INTn = INTalb.leftNode(INTalb.rightNode(INTalb.rightNode(INTalb.root())));
    INTalb.leftInsert(INTn, 13);
    cout << INTalb << endl;
    balanced_tree<int> a;
    cout << boolalpha << a.is_height_balanced(INTalb) << endl;
    cout << boolalpha << a.complete_nodes(INTalb) << endl;
    return 0;
}