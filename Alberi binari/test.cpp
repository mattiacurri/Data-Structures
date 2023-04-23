/*#include <iostream>
#include "linkedBinTree.h"
// #include "E/BinTree_pt.h"
using namespace std;



int main()
{
    treeNode<string> *n1, *n2, *n3;

    BinTree_pt<string> a1;

    a1.insertRoot("rosso");

    n1 = a1.root();
    a1.leftInsert(n1, "bianco");
    a1.rightInsert(n1, "c");

    n2 = a1.leftNode(n1);
    a1.leftInsert(n2, "d");
    a1.rightInsert(n2, "e");

    n3 = a1.leftNode(n2);
    a1.leftInsert(n3, "f");
    a1.rightInsert(n3, "verde");
    a1.stampa_albero(n1);

    cout << a1.profondita(n1);*/

/*cout << "/n/n";
a1.printTree(n1);

cout << "/n/n";

n2 = a1.node_sx(n1);
//a1.deleteSubBinTree(n2);
a1.dfs(n1);
cout << endl;
cout << endl;
int somma = a1.sumLevel(2);
cout << somma << endl;

cout << endl;
cout << endl;
cout << a1.depth(n1) << endl;
cout << a1;
cout << a1.green_leafs(a1, a1.root(), 0) << endl;
cout << a1.level_red(a1, a1.root(), 0) << endl;
return 0;
}*/

#include <iostream>
#include <string>

#include "linkedBinTree.h"

using namespace std;

int main() {
    BinTree_pt<double> alb;
    BinTree_pt<double>::node n;
    alb.insertRoot(0.3);
    n = alb.root();
    alb.leftInsert(n, 2.1);
    alb.rightInsert(n, 3.4);
    n = alb.leftNode(n);
    alb.leftInsert(n, 8.2);
    alb.rightInsert(n, 4.7);
    //n = alb.leftNode(n);
    //alb.leftInsert(n, 291);
    //alb.rightInsert(n, 1);
    //n = alb.rightNode(alb.leftNode(alb.root()));
    //alb.leftInsert(n, 2);
    //alb.rightInsert(n, 4);
    n = alb.rightNode(alb.root());
    alb.leftInsert(n, 1.9);
    alb.rightInsert(n, 2.4);
    /*n = alb.leftNode(n);
    alb.leftInsert(n, 3);
    alb.rightInsert(n, 4);
    n = alb.rightNode(alb.rightNode(alb.root()));
    alb.leftInsert(n, 1);
    alb.rightInsert(n, 2);
    n = alb.leftNode(n);
    alb.rightInsert(n, 20); */
    /*alb.insertRoot("rosso");
    n = alb.root();
    alb.leftInsert(n, "bianco");
    alb.rightInsert(n, "rosso");
    n = alb.leftNode(n);
    alb.leftInsert(n, "rosso");
    alb.rightInsert(n, "bianco");
    n = alb.leftNode(n);
    alb.leftInsert(n, "bianco");
    alb.rightInsert(n, "bianco");
    n=alb.rightNode(alb.leftNode(alb.root()));
    alb.leftInsert(n, "rosso");
    alb.rightInsert(n, "rosso");
    n=alb.rightNode(alb.root());
    alb.leftInsert(n, "bianco");
    alb.rightInsert(n, "rosso");
    n=alb.leftNode(n);
    alb.leftInsert(n, "rosso");
    alb.rightInsert(n, "rosso");
    n=alb.rightNode(alb.rightNode(alb.root()));
    alb.leftInsert(n, "bianco");
    alb.rightInsert(n, "rosso");
    n = alb.leftNode(n);
    alb.rightInsert(n, "rosso");
    cout << alb << endl;
    cout << "Level red: " << alb.level_red(alb) << endl;
    // cout << alb.green_leafs(alb, alb.root(), 0) << endl;
    cout << endl;
    n = alb.root();
    n = alb.rightNode(n);
    n = alb.rightNode(n);
    n = alb.rightNode(n);
    int altezza = alb.height(alb.root());
    cout << "Altezza: " << altezza << endl;
    cout << "Profondita': " << alb.depth(n) << endl;
    cout << endl;

    cout << endl;*/
    cout << alb << endl;
    //cout << "sumLevel: " << alb.sumLevel(1) << endl;

    VectorList<double> list(alb.getNumNodes());
    //list = alb.mean(alb);
    cout << "Medie dei livelli: " << list;

    BinTree_pt<int> bst;
    bst.insertRoot(9);
    BinTree_pt<int>::node x;
    x = bst.root();
    bst.leftInsert(x, 22);
    bst.rightInsert(x, 13);
    x = bst.leftNode(bst.root());
    bst.leftInsert(x, 1);
    x = bst.rightNode(bst.root());
    bst.leftInsert(x, 11);
    bst.rightInsert(x, 15);
    x = bst.rightNode(bst.rightNode(bst.root()));
    bst.leftInsert(x, 10);
    bst.rightInsert(x, 17);
    cout << bst;
    //cout << boolalpha << bst.isBST(bst) << endl;
    x = bst.leftNode(bst.rightNode(bst.rightNode(bst.root())));
    //cout << bst.successor(bst, x) << endl;

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

    //INTalb.multipli(INTalb);
    //cout << INTalb << endl;
    // INTalb.reverseBinTree(INTalb.root());
    cout << endl;
    cout << INTalb << endl;
    BinTree_pt<int> INTalb2;
    BinTree_pt<int>::node INTn2;
    INTalb2.insertRoot(1);
    INTn2 = INTalb2.root();
    INTalb2.leftInsert(INTn2, 2);
    INTalb2.rightInsert(INTn2, 9);
    INTn2 = INTalb2.leftNode(INTn2);
    INTalb2.leftInsert(INTn2, 3);
    INTalb2.rightInsert(INTn2, 6);
    INTn2 = INTalb2.leftNode(INTalb2.leftNode(INTalb2.root()));
    INTalb2.leftInsert(INTn2, 4);
    INTalb2.rightInsert(INTn2, 5);
    INTn2 = INTalb2.rightNode(INTalb2.leftNode(INTalb2.root()));
    INTalb2.leftInsert(INTn2, 7);
    INTalb2.rightInsert(INTn2, 8);

    INTn2 = INTalb2.rightNode(INTalb2.root());
    INTalb2.leftInsert(INTn2, 10);
    INTalb2.rightInsert(INTn2, 11);
    INTn2 = INTalb2.rightNode(INTalb2.rightNode(INTalb2.root()));
    INTalb2.leftInsert(INTn2, 12);
    INTn2 = INTalb2.leftNode(INTalb2.rightNode(INTalb2.rightNode(INTalb2.root())));
    INTalb2.leftInsert(INTn2, 13);

    //cout << "PRE: " << INTalb << INTalb2 << endl;
    // INTalb2.mutation(INTalb, INTalb2, INTalb.rightNode(INTalb.rightNode(INTalb.root())),  INTalb2.rightNode(INTalb2.rightNode(INTalb2.root())));
    //cout << "POST: " << INTalb << INTalb2 << endl;
    cout << "PRE MULTIPLI: " << INTalb << endl;
    INTalb.multipli(INTalb);
    cout << INTalb << endl;
    return 0;
}
