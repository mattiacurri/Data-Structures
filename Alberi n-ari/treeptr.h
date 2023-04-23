#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include "Tree.h"

using std::cout;
using std::endl;
using std::vector;

template<class T>
class Tree_ptr;

template<class T>
class treeNode {
    friend class Tree_ptr<T>;

public:
    // costruttori
    treeNode() {
        parent = nullptr;
        child = nullptr;
        brother = nullptr;
    }

    treeNode(T val) {
        value = val;
        parent = nullptr;
        brother = nullptr;
        child = nullptr;
    }

    // metodo per scrivere un node
    void write(T val) {
        value = val;
    }

private:
    T value;
    // int level;
    treeNode<T> *parent;
    treeNode<T> *child;
    treeNode<T> *brother;
};

template<class T>
class Tree_ptr : public Tree<T, treeNode<T> *> {
public:
    typedef T valuetype;
    typedef treeNode<T> *node;

    Tree_ptr();

    ~Tree_ptr() = default;

    // Metodo che verifica se l'albero e' vuoto
    bool empty() const;

    // Metodo che inserisce la radice
    void insertRoot(valuetype);

    // Metodo che inserisce il primo figlio di un nodo
    void insertFirst(node, valuetype);

    // Metodo che restituisce il valore della radice
    node root() const;

    // Metodo che restituisce il genitore di un nodo
    node parent(node) const;

    // Metodo che verifica se un nodo e' foglia
    bool isLeaf(node) const;

    // Metodo che restituisce il primo figlio di un nodo secondo la relazione d'ordine
    node firstChild(node) const;

    // Metodo che verifica l'esistenza del primo figlio di un nodo
    bool firstChildEmpty(node) const;

    // Metodo che verifica se un nodo e' l'ultimo figlio
    bool isLastSibling(node) const;

    // Metodo che restituisce il fratello di un nodo
    node nextSibling(node) const;

    // Metodo che inserisce un sottoalbero la cui radice e' il primo figlio del nodo
    void insertFirstSubTree(node, Tree<T, node> &);

    // Metodo che inserisce un sottoalbero la cui radice e' il fratello dell'ultimo figlio del nodo
    void insertSubTree(node, Tree<T, node> &);

    // Metodo che rimuove il sottoalbero con radice il nodo da parametro
    void removeSubTree(node);

    // Metodo che scrive un valore nel nodo
    void writeNode(node, valuetype);

    // Metodo che restituisce il valore di un nodo
    valuetype read(node) const;

    // Metodo per stampare l'albero
    void print() const;

    // Metodo per stampare l'albero
    void print(node) const;

    int depth(const Tree_ptr<T> &);

    // algoritmo DFS
    void dfs(node) const;

    // algoritmo di visita simmetrica
    void invisita(node) const;

    int breadth(Tree_ptr<T>);

private:
    node rootTree;

    int depth(const Tree_ptr<T> &, node);

    void breadthLevel(Tree_ptr<T>, node, vector<int> &, int);

};

template<class T>
typename Tree_ptr<T>::node Tree_ptr<T>::nextSibling(node n) const {
    return n->brother;
}

template<class T>
Tree_ptr<T>::Tree_ptr() {
    rootTree = nullptr;
}

template<class T>
bool Tree_ptr<T>::empty() const { return (rootTree == nullptr); }

template<class T>
void Tree_ptr<T>::insertRoot(valuetype v) {
    if (empty()) {
        node q = new treeNode<T>(v);
        // q->level = 0;
        rootTree = q;
    } else {
        throw std::logic_error("L'ALBERO HA GIA' UNA RADICE");
    }
}

template<class T>
typename Tree_ptr<T>::node Tree_ptr<T>::root() const {
    return rootTree;
}

template<class T>
typename Tree_ptr<T>::node Tree_ptr<T>::parent(node n) const {
    return n->parent;
}

template<class T>
typename Tree_ptr<T>::node Tree_ptr<T>::firstChild(node n) const {
    if (!firstChildEmpty(n)) {
        return n->child;
    } else {
        throw std::out_of_range("Primo figlio non esiste");
    }
}

template<class T>
bool Tree_ptr<T>::firstChildEmpty(node n) const {
    return (n->child == nullptr);
}

template<class T>
bool Tree_ptr<T>::isLeaf(node n) const {
    return (n->child == nullptr);
}

template<class T>
void Tree_ptr<T>::dfs(node n) const {
    cout << n->value << " ";
    if (!firstChildEmpty(n)) {
        n = firstChild(n);
        while (!isLastSibling(n)) {
            dfs(n);
            n = nextSibling(n);
        }
        dfs(n);
    }

}


template<class T>
void Tree_ptr<T>::invisita(node n) const {
    if (isLeaf(n)) {
        cout << n->value << " ";
    } else {
        node c = firstChild(n);
        invisita(c);
        cout << n->value << " ";
        while (!isLastSibling(c)) {
            c = nextSibling(c);
            invisita(c);
        }
    }
}



template<class T>
bool Tree_ptr<T>::isLastSibling(node n) const {
    return (n->brother == nullptr);
}

template<class T>
void Tree_ptr<T>::insertFirstSubTree(node n, Tree<T, node> &tree) {
    if (!empty() && !tree.empty()) {
        node l = tree.root();
        l->parent = n;
        l->brother = n->child;
        //l->level = l->parent->level + 1;
        n->child = l;
    }
}

template<class T>
void Tree_ptr<T>::insertSubTree(node n, Tree<T, node> &tree) {
    if (!empty() && !tree.empty()) {
        if (n != root()) {
            node l = tree.root();
            l->brother = n->brother;
            l->parent = n->parent;
            //l->level = l->parent->level + 1;
            n->brother = l;
        }
    }
}

template<class T>
void Tree_ptr<T>::removeSubTree(node n) {
    if (n != root()) {
        while (!isLeaf(n)) {
            removeSubTree(firstChild(n));
        }

        if (n->brother == nullptr) {
            n->parent->child->brother = nullptr;
        }
        if (n->parent->child == n) n->parent->child = n->brother;

    }
    delete n;
}

template<class T>
void Tree_ptr<T>::insertFirst(node n, valuetype v) {
    node q = new treeNode<T>;
    q->brother = n->child;
    q->parent = n;
    q->value = v;
    q->child = nullptr;
    //q->level = q->parent->level + 1;
    n->child = q;
}

template<class T>
void Tree_ptr<T>::writeNode(node n, valuetype v) {
    if (n != nullptr) {
        n->value = v;
    } else {
        throw std::out_of_range("Nodo non esistente");
    }
}

template<class T>
typename Tree_ptr<T>::valuetype Tree_ptr<T>::read(node n) const {
    if (n != nullptr) {
        return n->value;
    } else {
        throw std::out_of_range("Nodo non esistente");
    }
}

template<class T>
void Tree_ptr<T>::print() const {
    if (root() != nullptr) {
        cout << "[ ";
        print(root());
        cout << "]" << endl;
    }
}

template<class T>
void Tree_ptr<T>::print(node n) const {
    if (n != nullptr) cout << n->value << " ";
    if (n->brother != nullptr) {
        print(n->brother);
    }
    if (!firstChildEmpty(n)) {
        print(n->child);
    }

}

template<class T>
int Tree_ptr<T>::depth(const Tree_ptr<T> &tree) {
    if (!empty()) return depth(tree, tree.root());
}

template<class T>
int Tree_ptr<T>::depth(const Tree_ptr<T> &tree, node n) {
    if (tree.isLeaf(n)) return 1;
    int m = 0;
    int c;
    node k = tree.firstChild(n);
    while (!tree.isLastSibling(k)) {
        c = depth(tree, k);
        if (c > m) {
            m = c;
        }
        k = tree.nextSibling(k);
    }
    c = depth(tree, k);
    if (c > m) {
        m = c;
    }
    return (m + 1);
}

template<class T>
int Tree_ptr<T>::breadth(Tree_ptr<T> tree) {
    if (!empty()) {
        vector<int> numNodes;
        breadthLevel(tree, tree.root(), numNodes, 0);
        std::sort(numNodes.begin(), numNodes.end());
        return numNodes[numNodes.size() - 1];
    } else {
        return 1;
    }
}


template<class T>
void Tree_ptr<T>::breadthLevel(Tree_ptr<T> tree, node n, vector<int> &numNodes, int current_depth) {
    if (current_depth >= numNodes.size()) {
        numNodes.push_back(1);
    } else {
        numNodes[current_depth] += 1;
    }
    if (!tree.firstChildEmpty(n)) {
        breadthLevel(tree, n->child, numNodes, current_depth + 1);
    }
    if (n->brother != nullptr) {
        breadthLevel(tree, n->brother, numNodes, current_depth);
    }
}
