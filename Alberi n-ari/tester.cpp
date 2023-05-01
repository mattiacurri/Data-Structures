#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include "ESERCIZI/esercizivari.h"

int main() {
    Tree_ptr<char> tree;

    Tree_ptr<char>::node n;
    tree.insertRoot('a');

    n = tree.root();
    tree.insertFirst(n, 'b');
    n = tree.firstChild(n);
    tree.insertFirst(n, 'c');
    tree.insertFirst(n, 'c');

    n = tree.root();
    tree.insertFirst(n, 'b');
    n = tree.firstChild(n);
    tree.insertFirst(n, 'c');
    tree.insertFirst(n, 'c');
    tree.insertFirst(n, 'c');
    tree.insertFirst(n, 'c');


    n = tree.firstChild(tree.firstChild(tree.root()));
    tree.insertFirst(n, 'd');
    tree.insertFirst(n, 'd');

    tree.print();

    tree.dfs(tree.root());
    //n = tree.brother(tree.firstChild(tree.root()));
    //tree.removeSubTree(n);


    tree.print();

    Tree_ptr<int> intalbero;
    Tree_ptr<int>::node pos;
    intalbero.insertRoot(4);
    pos = intalbero.root();
    intalbero.insertFirst(pos, 4);
    intalbero.insertFirst(pos, 3);
    intalbero.insertFirst(pos, 2);
    pos = intalbero.firstChild(intalbero.root());
    intalbero.insertFirst(pos, 6);
    intalbero.insertFirst(pos, 5);
    intalbero.invisita(intalbero.root());
    cout << endl;

    util_n_tree t;
    cout << "EVEN_FATHER_E: " << t.even_father_e(intalbero) << endl;
    //cout << "EVEN_FATHER_D: " << t.even_father_d(intalbero) << endl;
    //cout << "even_father: " << intalbero.even_father(intalbero) << endl;
    //cout << intalbero.max_level(intalbero) << endl;
    //cout << intalbero.somma(intalbero, 10) << endl;

    /*Tree_ptr<char> tree;
    Tree_ptr<char>::node n;*/
    /*tree.insertRoot('a');
    n = tree.root();
    tree.insertFirst(n,'l');

    n = tree.root();
    n = tree.firstChild(n);
    tree.insertFirst(n, 'e');
    tree.insertFirst(n, 'f');
    n = tree.root();
    tree.insertFirst(n,'d');
    n=tree.firstChild(n);
    tree.insertFirst(n, 'g');
    tree.insertFirst(n, 'o');
    n=tree.firstChild(n);
    tree.insertFirst(n, 'h');
    n = tree.root();
    tree.print();
    n=tree.firstChild(n);
    n=tree.brother(n);
    tree.removeSubTree(n);
    tree.print();
    cout<<tree.depth(tree) << endl;

    Tree_ptr<char> innesto;
    innesto.insertRoot('z');

    tree.insertFirstSubTree(n, innesto);
    n = tree.firstChild(tree.firstChild(tree.root()));
    tree.insertSubTree(n, innesto);

    // n = tree.root();
    // tree.removeSubTree(n);*/
    /*Tree_ptr<int> tree;
    Tree_ptr<int>::node n;
    tree.insertRoot(2);
    n = tree.root();
    tree.insertFirst(n, 3);
    tree.insertFirst(n, 4);
    tree.insertFirst(n, 4);
    tree.insertFirst(n, 4);
    tree.insertFirst(n, 4);
    //n = tree.firstChild(n);
    //tree.insertFirst(n, 6);

    cout << tree.n_leaf(tree) << endl;
    cout << tree.n_level(tree, 1) << endl;*/
    cout << tree.depth(tree) << endl;

    cout << tree.breadth(tree) << endl;
    tree.invisita(tree.root());

    return 0;
}