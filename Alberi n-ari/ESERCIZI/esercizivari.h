#ifndef ES
#define ES

#include "../treeptr.h"


class util_n_tree {
public:

    int n_leaf(Tree_ptr<int> &);

    int n_level(Tree_ptr<int> &, int k);

    /* Dato un albero n-ario, even_father_ere i sottoalberi che hanno somma dei nodi pari ad un intero k */
    int somma(Tree_ptr<int> t, int k);

    // int even_father(Tree_ptr<int> tree);

    int even_father_e(Tree_ptr<int> &);

private:
    int n_leaf(Tree_ptr<int> &, typename Tree_ptr<int>::node);

    int n_level(Tree_ptr<int> &, int, typename Tree_ptr<int>::node, int);

    int even_father_d(Tree_ptr<int> &t, typename Tree_ptr<int>::node n);

    void even_father_e(Tree_ptr<int> &T, typename Tree_ptr<int>::node n, int &counter);

    int somma(Tree_ptr<int>, int, typename Tree_ptr<int>::node, int &);

};

class maxLevelSum {
public:
    int max_level(Tree_ptr<int>);

private:
    int max_level(Tree_ptr<int>, typename Tree_ptr<int>::node, int, int &);

    int somma_livello(Tree_ptr<int> &tree, int k, typename Tree_ptr<int>::node n, int current_depth);
};

class modTree {
public:
    void modify(Tree_ptr<int> &T);

private:
    int modify(Tree_ptr<int> &T, Tree_ptr<int>::node n);
};

//La funzione modifica il contenuto di ogni nodo di un albero n-ario (che non sia isLeaf)
void modTree::modify(Tree_ptr<int> &T) {
    if (!T.empty())
        modify(T, T.root());
}

//Ogni nodo assume come valore la somma dei valori dei nodi appartenenti al sottoalbero di cui esso è root (per le foglie il valore rimane invariato)
int modTree::modify(Tree_ptr<int> &T, Tree_ptr<int>::node n) {
    if (T.isLeaf(n))
        //se un nodo è isLeaf restituisco il suo valore
        return T.read(n);
    else {
        //inizializzo una variabile di somma per memorizzare la somma dei valori dei nodi presenti nel sottoalbero di cui n è root
        int somma = 0;
        Tree_ptr<int>::node c;
        c = T.firstChild(n);
        //richiamo la funzione modifica sul primo figlio di un nodo
        somma += modify(T, c);
        while (!T.isLastSibling(c)) {
            //richiamo la funzione di somma su tutti i fratelli di un nodo
            c = T.nextSibling(c);
            somma += modify(T, T.nextSibling(c));
        }
        somma += modify(T, T.nextSibling(c));
        //aggiorno il valore di un nodo
        T.writeNode(n, somma);
        //ritorno il valore della somma (serve per le chiamate ricorsive)
        return somma;
    }
}

int util_n_tree::n_leaf(Tree_ptr<int> &tree) {
    int x = 0;
    if (tree.root() != nullptr) {
        x = n_leaf(tree, tree.root());
    }
    return x;
}

int util_n_tree::n_leaf(Tree_ptr<int> &tree, typename Tree_ptr<int>::node n) {
    int x = 0;
    if (!tree.isLastSibling(n)) {
        x += n_leaf(tree, tree.nextSibling(n));
    }
    if (!tree.firstChildEmpty(n)) {
        x += n_leaf(tree, tree.firstChild(n));
    } else {
        x += 1;
    }
    return x;
}

int util_n_tree::n_level(Tree_ptr<int> &tree, int k) {
    if (tree.root() != nullptr && k <= tree.depth(tree)) {
        return n_level(tree, k, tree.root(), 0);
    } else {
        return 0;
    }
}

int util_n_tree::n_level(Tree_ptr<int> &tree, int k, typename Tree_ptr<int>::node n, int current_depth) {
    int x = 0;
    if (tree.nextSibling(n) != nullptr) {
        x += n_level(tree, k, tree.nextSibling(n), current_depth);
    }
    if (!tree.firstChildEmpty(n)) {
        x += n_level(tree, k, tree.firstChild(n), current_depth + 1);
    }
    if (current_depth == k) {
        x++;
    }
    return x;
}

/* Dato un albero n-ario, even_father_ere i sottoalberi che hanno somma dei nodi pari ad un intero k */
int util_n_tree::somma(Tree_ptr<int> t, int k) {
    int sum = 0;
    somma(t, k, t.root(), sum);
    return sum;
}

int util_n_tree::somma(Tree_ptr<int> t, int k, typename Tree_ptr<int>::node n, int &s) {
    int acc = t.read(n);
    while (!t.isLeaf(n)) {
        Tree_ptr<int>::node child;
        child = t.firstChild(n);
        while (!t.isLastSibling(child)) {
            acc += somma(t, k, child, s);
            child = t.nextSibling(child);
        }
        acc += somma(t, k, t.nextSibling(child), s);
    }
    if (acc == k) {
        s++;
    }
    return acc;
}

/* Funzione che restituisce il livello con somma dei nodi massima*/
int maxLevelSum::max_level(Tree_ptr<int> t) {
    int k = 0;
    int max = 0;
    if (!t.empty()) {
        k = max_level(t, t.root(), 0, max);
    }
    return k;
}

/* Funzione che somma il valore dei nodi di un livello */
int maxLevelSum::somma_livello(Tree_ptr<int> &tree, int k, Tree_ptr<int>::node n, int current_depth) {
    int somma = 0;
    if (!tree.isLastSibling(n)) {
        somma += somma_livello(tree, k, tree.nextSibling(n), current_depth);
    }
    if (!tree.firstChildEmpty(n)) {
        somma += somma_livello(tree, k, tree.firstChild(n), current_depth + 1);
    }
    if (current_depth == k) {
        somma += tree.read(n);
    }
    return somma;
}

int maxLevelSum::max_level(Tree_ptr<int> t, typename Tree_ptr<int>::node n, int current_depth, int &max) {
    int somma = t.read(n);
    int k = 0;
    if (!t.isLeaf(n)) {
        k = max_level(t, t.firstChild(n), current_depth + 1, max);
    }
    somma = somma_livello(t, current_depth, n, current_depth);
    if (somma > max) {
        k = current_depth;
        max = somma;
    }
    return k;
}

/*
int util_n_tree::even_father(Tree_ptr<int> tree) {
    int counter = 0;
    if (!tree.empty()) {
        counter = even_father(tree, tree.root());
    }
    return counter;
}


template<class T>
int util_n_tree::even_father(Tree_ptr<int> tree, Tree_ptr<int>::node n) {
    int counter = 0;
    if (isLeaf(n)) {
        if (tree.parent(n)->value % 2 == 0) {
            counter++;
        }
    } else {
        node c = firstChild(n);
        counter = even_father(tree, c);
        if (n != tree.root()) {
            if (tree.parent(n)->value % 2 == 0) {
                counter++;
            }
        }

        while (!tree.isLastSibling(c)) {
            c = nextSibling(c);
            counter = even_father(tree, c);
        }

    }
    return counter;
}*/

int util_n_tree::even_father_e(Tree_ptr<int> &t) {
    int counter = 0;
    if (!t.empty()) {
        even_father_e(t, t.root(), counter);
    }
    return counter;
}


//Viene effettuata una visita simmetrica per i=1 dell'albero n-ario visitando prima il primo figlio e poi, nell'ordine, tutti i fratelli successivi.
void util_n_tree::even_father_e(Tree_ptr<int> &T, typename Tree_ptr<int>::node n, int &counter) {
    Tree_ptr<int>::node c;
    //SE IL NODO E' PARI INCREMENTO IL COUNTER
    if (n!=T.root())
    {
        if ((T.read(T.parent(n))%2)==0) counter++;
    }
    if (!T.isLeaf(n)) {
        c = T.firstChild(n);
        while (!T.isLastSibling(c))
        {
            even_father_e(T,c,counter);
            c=T.nextSibling(c);
        }
        even_father_e(T,c,counter);
    }
}

int util_n_tree::even_father_d(Tree_ptr<int> &t, typename Tree_ptr<int>::node n) {
    if (t.isLeaf(n)) return t.read(t.parent(n)) % 2 == 0;
    int figli = 0;
    Tree_ptr<int>::node cur = t.firstChild(n);
    while (!t.isLastSibling(cur)) {
        figli += even_father_d(t, cur);
        cur = t.nextSibling(cur);
    }
    figli += even_father_d(t, cur);
    return figli + (n != t.root() ? t.read(t.parent(n)) % 2 == 0 : 0);
}

#endif // ES