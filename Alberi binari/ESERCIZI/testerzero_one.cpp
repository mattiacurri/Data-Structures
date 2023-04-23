#include <iostream>
#include "zero_one_binary_tree.h"

using std::cout;
using std::endl;
using std::boolalpha;

int main() {
    zero_one_binary_tree<int> alb;
    BinTree_pt<int>::node n;
    alb.insertRoot(0);
    n = alb.root();
    alb.insertLeft(n, 1);
    alb.insertRight(n, 1);
    n = alb.nodeLeft(n);
    alb.insertLeft(n, 0);
    alb.insertRight(n, 0);
    n = alb.nodeLeft(n);
    alb.insertLeft(n, 1);
    alb.insertRight(n, 1);
    n = alb.nodeRight(alb.nodeLeft(alb.root()));
    alb.insertLeft(n, 1);
    alb.insertRight(n, 1);
    n = alb.nodeRight(alb.root());
    alb.insertLeft(n, 0);
    alb.insertRight(n, 0);

    n = alb.nodeRight(alb.nodeRight(alb.root()));
    alb.insertRight(n, 1);

    cout << boolalpha << alb.is_zero_one(alb) << endl;
    cout << alb.zero_nodes(alb) << endl;

    return 0;
}