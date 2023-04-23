
#ifndef REALIZZAZIONI_UTIL_GRAFO_H
#define REALIZZAZIONI_UTIL_GRAFO_H

#include "../grafoMatrice.h"

typedef struct {
    nodoG node;
    bool visited;
} nVisit;

class util_grafo {
public:
    //Restituisce il numero di nodi raggiungibili da n1 e con la stessa etichetta
    int countSame(grafoMat<int, int> &g, typename grafoMat<int, int>::nodo n1);

    //Restituisce la media dei valori delle etichette dei nodi raggiungibili da n1 con cammini di length 2
    double meanN2(grafoMat<int, int> &g, typename grafoMat<int, int>::nodo n1);

private:
    int nPos(typename grafoMat<int, int>::nodo a, nVisit vet[]);

    void visita2(grafoMat<int, int> &g, typename grafoMat<int, int>::nodo n, int &somma, int &counter, int &length,
                 nVisit visitati[]);

};

int util_grafo::countSame(grafoMat<int, int> &g, typename grafoMat<int, int>::nodo n1) {
    //operazioni preliminari
    nVisit n;
    nodoG v;
    VectorList<nodoG> lista_nodi = g.nodesList();
    VectorList<nodoG> lista_adiacenti;
    nVisit visitati[g.numNodi()];
    VectorList<nodoG>::position p = lista_nodi.begin();
    int counter = 0;
    int i = 0;
    while (i < g.numNodi()) {
        n.node = lista_nodi.read(p);
        n.visited = false;
        visitati[i] = n;
        p = lista_nodi.next(p);
        i++;
    }
    //VISITA
    Queue_vt<nodoG> q;
    q.push(n1);
    nodoG currentNode;
    while (!q.empty()) {
        currentNode = q.read();
        q.pop();
        visitati[nPos(currentNode, visitati)].visited = true;
        lista_adiacenti = g.adiacenti(currentNode);
        p = lista_adiacenti.begin();
        while (!lista_adiacenti.end(p)) {
            v = lista_adiacenti.read(p);
            if (g.leggiEtichetta(n1) == g.leggiEtichetta(v) && !visitati[nPos(v, visitati)].visited)
                counter++;
            if (!visitati[nPos(v, visitati)].visited && !q.exists(v)) {
                q.push(v);
            }
            p = lista_adiacenti.next(p);
        }
    }
    return counter;
}

#endif //REALIZZAZIONI_UTIL_GRAFO_H

int util_grafo::nPos(typename grafoMat<int, int>::nodo a, nVisit vet[]) {
    bool trovato = false;
    int i = 0;
    while (!trovato) {
        nVisit n = vet[i];
        if (a == n.node) {
            trovato = true;
        } else i++;
    }
    return i;
}


double util_grafo::meanN2(grafoMat<int, int> &g, typename grafoMat<int, int>::nodo n1) {
    int counter = 0;
    if (!g.empty()) {
        //OPERAZIONE PRELIMINARE DI VISITA
        nVisit n;
        VectorList<nodoG> lista_nodi = g.nodesList();
        nVisit visitati[g.numNodi()];
        VectorList<nodoG>::position p = lista_nodi.begin();
        int i = 0;
        while (i < g.numNodi()) {
            n.node = lista_nodi.read(p);
            n.visited = false;
            visitati[i] = n;
            p = lista_nodi.next(p);
            i++;
        }

        int somma = 0;
        int length = 0;
        visita2(g, n1, somma, counter, length, visitati);
        if (counter > 0) {
            return (double) somma / counter;
        } else {
            return 0;
        }
    } else return 0;
}

void util_grafo::visita2(grafoMat<int, int> &g, typename grafoMat<int, int>::nodo n, int &somma, int &counter,
                         int &length, nVisit visitati[]) {
    if (length < 2) {
        //VISITO IL GRAFO
        VectorList<nodoG> nodiAdiacenti = g.adiacenti(n);
        visitati[nPos(n, visitati)].visited = true;
        if (!nodiAdiacenti.empty()) {
            VectorList<nodoG>::position p = nodiAdiacenti.begin();
            while (!nodiAdiacenti.end(p)) {
                nodoG v = nodiAdiacenti.read(p);
                if (!visitati[nPos(v, visitati)].visited) {
                    length++;
                    visita2(g, v, somma, counter, length, visitati);
                }
                p = nodiAdiacenti.next(p);
            }
        }
    } else if (length == 2) {
        somma += g.leggiEtichetta(n);
        counter++;
    }
    length--;
}