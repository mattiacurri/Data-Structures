#ifndef REALIZZAZIONI_UTIL_BIN_TREE_H
#define REALIZZAZIONI_UTIL_BIN_TREE_H

#include "../linkedBinTree.h"

class util_bin_tree {
public:

    int d3(BinTree_pt<int> &T, int k);

    //restituisce il numero di nodi il cui valore è pari
    int lp(BinTree_pt<int> &T);

    //numero di foglie il cui padre è multiplo di 5
    int l2p(BinTree_pt<int> &T);

    //numero foglie con valore pari
    int even_leafs(BinTree_pt<int> &T);

    //Modifca albero secondo il criterio
    void multipli(BinTree_pt<int> &T);

    //Numero foglie il cui parent è pari
    int leafs_with_even_parent(BinTree_pt<int> &T);

    // Numero nodi al livello K con valore dispari
    int odd(BinTree_pt<int> &T, int k);

    //A ogni foglia aggiunge un figlio (sinistro in questo caso) il cui valore è la somma dei nodi presenti nel cammino che partono dalla root e arrivano a quella foglia
    void aggiungiSommaFoglia(BinTree_pt<int> &T);

private:
    void d3(BinTree_pt<int> &T, typename BinTree_pt<int>::node n, int k, int liv, int &counter);

    void lp(BinTree_pt<int> &T, typename BinTree_pt<int>::node n, int &counter);

    void even_leafs(BinTree_pt<int> &T, typename BinTree_pt<int>::node n, int &counter);

    void l2p(BinTree_pt<int> &T, typename BinTree_pt<int>::node n, bool isMultiplo, int &counter);

    int leafs_with_even_parent(BinTree_pt<int> &T, typename BinTree_pt<int>::node n, bool isPari, int &counter);

    void modifica(BinTree_pt<int> &T, typename BinTree_pt<int>::node n);

    int odd(BinTree_pt<int> &T, typename BinTree_pt<int>::node n, int k, int liv, int &counter);

    void aggiungiSommaFoglia(BinTree_pt<int> &T, typename BinTree_pt<int>::node n);
};

//Funzione che ad ogni foglia aggiunge un figlio (sinistro in questo caso) il cui valore è la somma dei nodi presenti nel cammino che partono dalla root e arrivano a quella foglia
void util_bin_tree::aggiungiSommaFoglia(BinTree_pt<int> &T) {
    if (!T.empty()) {
        aggiungiSommaFoglia(T, T.root());
    }
}

//Funzione di modifica dell'albero
void util_bin_tree::aggiungiSommaFoglia(BinTree_pt<int> &T, typename BinTree_pt<int>::node n) {
    //il nodo non è foglia, dunque richuamo la funzione sui figli destro e sinistro (se esistono)
    if (!T.leftEmpty(n) && !T.rightEmpty(n)) {
        if (!T.leftEmpty(n)) aggiungiSommaFoglia(T, T.leftNode(n));
        if (!T.rightEmpty(n)) aggiungiSommaFoglia(T, T.rightNode(n));
    } else {
        //il nodo è foglia, quindi salvo il valore di n in una variabile di somma
        int somma = T.read(n);
        typename BinTree_pt<int>::node padre = T.parent(n);
        //RISALGO FINO ALLA RADICE e aggungo i valori dei nodi alla somma
        while (padre != T.root()) {
            somma += T.read(padre);
            padre = T.parent(padre);
        }
        //aggiungo il valore della root alla somma
        somma += T.read(padre);
        //Inserisco il figlio sinistro
        T.leftInsert(n, somma);
    }
}


//La funzione restituisce il numero di nodi al livello k il cui valore è divisibile per 3
int util_bin_tree::d3(BinTree_pt<int> &T, int k) {
    int counter = 0;
    if (!T.empty()) {
        d3(T, T.root(), k, 0, counter);
    }
    return counter;
}

//La funzione conta il numero di nodi al livello k il cui valore è divisibile per 3
void util_bin_tree::d3(BinTree_pt<int> &T, typename BinTree_pt<int>::node n, int k, int liv, int &counter) {
    if (liv == k && ((T.read(n) % 3) == 0)) counter++;
    if (!T.leftEmpty(n) && k < liv) d3(T, T.leftNode(n), k, liv++, counter);
    if (!T.rightEmpty(n) && k < liv) d3(T, T.rightNode(n), k, liv++, counter);
}


//La funzione restituisce il numero di nodi al livello k il cui valore è dispari
int util_bin_tree::odd(BinTree_pt<int> &T, int k) {
    int counter = 0;
    if (!T.empty()) {
        odd(T, T.root(), k, 0, counter);
    }
    return counter;
}

//La funzione conta il numero di nodi al livello k il cui valore è dispari
int util_bin_tree::odd(BinTree_pt<int> &T, typename BinTree_pt<int>::node n, int k, int liv, int &counter) {
    if (liv == k && ((T.read(n) % 2) == 1)) counter++;
    if (!T.leftEmpty(n) && k < liv) d3(T, T.leftNode(n), k, liv++, counter);
    if (!T.rightEmpty(n) && k < liv) d3(T, T.rightNode(n), k, liv++, counter);
}

//La funzione restituisce il numero di foglie il cui valori è pari
int util_bin_tree::even_leafs(BinTree_pt<int> &T) {
    int counter = 0;
    if (!T.empty()) {
        even_leafs(T, T.root(), counter);
    }
    return counter;
}

//La funzione conta il numero di foglie il cui valore è pari
void util_bin_tree::even_leafs(BinTree_pt<int> &T, typename BinTree_pt<int>::node n, int &counter) {
    if ((T.read(n) % 2) == 0 && T.leftEmpty(n) && T.rightEmpty(n)) counter++;
    if (!T.leftEmpty(n)) even_leafs(T, T.leftNode(n), counter);
    if (!T.rightEmpty(n)) even_leafs(T, T.rightNode(n), counter);
}


//La funzione restituisce il numero di foglie il cui padre ha un valore multiplo di 5
int util_bin_tree::l2p(BinTree_pt<int> &T) {
    int counter = 0;
    if (!T.empty()) {
        bool isMultiplo = ((T.read(T.root()) % 5) == 0);
        if (!T.leftEmpty(T.root())) l2p(T, T.leftNode(T.root()), isMultiplo, counter);
        if (!T.rightEmpty(T.root())) l2p(T, T.rightNode(T.root()), isMultiplo, counter);
    }
    return counter;
}

//La funzione conta il numero di foglie il cui padre ha un valore multiplo di 5
void util_bin_tree::l2p(BinTree_pt<int> &T, typename BinTree_pt<int>::node n, bool isMultiplo, int &counter) {
    if (isMultiplo && T.leftEmpty(n) && T.rightEmpty(n)) counter++;
    isMultiplo = (((T.read(n)) % 5) == 0);
    if (!T.leftEmpty(n)) l2p(T, T.leftNode(n), isMultiplo, counter);
    if (!T.rightEmpty(n)) l2p(T, T.rightNode(n), isMultiplo, counter);

}

//la funzione restituisce il numero di foglie il cui padre è un numero pari
int util_bin_tree::leafs_with_even_parent(BinTree_pt<int> &T) {
    int counter = 0;
    if (!T.empty()) {
        bool isPari = ((T.read(T.root()) % 2) == 0);
        if (!T.leftEmpty(T.root())) leafs_with_even_parent(T, T.leftNode(T.root()), isPari, counter);
        if (!T.rightEmpty(T.root())) leafs_with_even_parent(T, T.rightNode(T.root()), isPari, counter);
    }
}

//La funzione conta il numero di foglie il cui padre ha un valore pari di 5
int
util_bin_tree::leafs_with_even_parent(BinTree_pt<int> &T, typename BinTree_pt<int>::node n, bool isPari, int &counter) {
    if (isPari && T.leftEmpty(n) && T.rightEmpty(n)) counter++;
    isPari = (((T.read(n)) % 2) == 0);
    if (!T.leftEmpty(n)) l2p(T, T.leftNode(n), isPari, counter);
    if (!T.rightEmpty(n)) l2p(T, T.rightNode(n), isPari, counter);
}

//La funzione restituisce il numero di nodi il cui valore è pari
int util_bin_tree::lp(BinTree_pt<int> &T) {
    int counter = 0;
    if (!T.empty()) {
        lp(T, T.root(), counter);
    }
    return counter;
}

//La funzione conta il numero di nodi con valore pari
void util_bin_tree::lp(BinTree_pt<int> &T, typename BinTree_pt<int>::node n, int &counter) {
    if ((T.read(n) % 2) == 0) counter++;
    if (!T.leftEmpty(n)) lp(T, T.leftNode(n), counter);
    if (!T.rightEmpty(n)) lp(T, T.rightNode(n), counter);
}

//La funzione modifica il contenuto dell'albero, facendo in modo che ogni nodo memorizzi il numero di nodi pari presenti nel suo sottoalbero
void util_bin_tree::multipli(BinTree_pt<int> &T) {
    if (!T.empty()) {
        modifica(T, T.root());
    }
}

//Funzione di modifica
void util_bin_tree::modifica(BinTree_pt<int> &T, typename BinTree_pt<int>::node n) {
    if (T.leftEmpty(n) && T.rightEmpty(n)) {
        if ((T.read(n) % 2) == 0) T.write(n, 1);
        else T.write(n, 0);
        return;
    } else {
        int counter = 0;
        lp(T, n, counter);
        //Scrivo nel nodo il numero di nodi del suo sottoalbero con valore pari
        T.write(n, counter);
        //richiamo la funzione sui figli destro e sinistro (se esistono)
        if (!T.leftEmpty(n)) modifica(T, T.leftNode(n));
        if (!T.rightEmpty(n)) modifica(T, T.rightNode(n));
    }
}

#endif //REALIZZAZIONI_UTIL_BIN_TREE_H
