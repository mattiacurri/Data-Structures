#ifndef ONE_LABEL_PATH
#define ONE_LABEL_PATH

#include "../grafoMatrice.h"

typedef struct {
    int nPaths = 0;
    double mLength = 0;
} wPath;


typedef struct {
    nodoG nodo;
    bool visited;
} nVisit;

template<class T>
class w_graph {
public:
    typedef wPath wPath;

    //Dato un arco g e due nodi "a" e "b" (i cui pesi degli archi sono 1 o -1) restituire il numero
    //di cammini da "a" a "b" tale che il peso di tutti gli archi del cammino sia 1.
    //Restituire inoltre la media della lunghezza dei cammini trovati
    wPath one_label_path(grafoMat<int, int> &, grafoMat<int, int>::nodo, grafoMat<int, int>::nodo);


private:
    int nPos(grafoMat<int, int>::nodo a, nVisit vet[]);

    void wVisit(grafoMat<T, int> &g, typename grafoMat<T, int>::nodo a, typename grafoMat<T, int>::nodo b,
                int &lunghezzaTotale, int &lunghezzaAttuale, int &nPaths, nVisit visited[]);
};

template<class T>
wPath w_graph<T>::one_label_path(grafoMat<int, int> &g, grafoMat<int, int>::nodo a, grafoMat<int, int>::nodo b) {
    nVisit n;
    // memorizzo in un vettore la lista dei nodi del grafo
    VectorList<nodoG> nList = g.nodesList();
    VectorList<nodoG> adjacency;
    // creo un vettore di nodi che andro' a visitare
    nVisit visited[g.numNodi()];
    VectorList<nodoG>::position p = nList.begin();
    wPath c;
    c.nPaths = 0;
    c.mLength = 0;
    // inizializzo il vettore dei visitati
    for (int i = 0; i < g.numNodi(); i++) {
        n.nodo = nList.read(p);
        n.visited = false;
        visited[i] = n;
        p = nList.next(p);
    }
    int nPaths = 0;
    int lunghezzaTotale = 0;
    int lunghezzaAttuale = 0;

    // cerco i cammini
    wVisit(g, a, b, lunghezzaTotale, lunghezzaAttuale, nPaths, visited);

    // aggiorno l'output
    if (nPaths > 0) {
        c.nPaths = nPaths;
        c.mLength = (double) lunghezzaTotale / nPaths;
    }

    return c;
}

template<class T>
void w_graph<T>::wVisit(grafoMat<T, int> &g, typename grafoMat<T, int>::nodo a, typename grafoMat<T, int>::nodo b,
                        int &lunghezzaTotale, int &lunghezzaAttuale, int &nPaths, nVisit visited[]) {
    VectorList<nodoG> nodi_adiacenti = g.adiacenti(a);
    // IL VETTORE VISITATI VIENE UTILIZZATO PER EVITARE DI ENTRARE IN UN CICLO
    if (!(a == b)) visited[nPos(a, visited)].visited = true;
    if (!nodi_adiacenti.empty()) {
        VectorList<nodoG>::position p = nodi_adiacenti.begin();
        while (!nodi_adiacenti.end(p)) {
            nodoG v = nodi_adiacenti.read(p);
            if (!visited[nPos(v, visited)].visited) {
                // esamino l'arco (a, v)
                if (g.leggiPeso(a, v) == 1) {
                    lunghezzaAttuale++;
                    // se v corrisponde al nodo di arrivo incrementa la lunghezza e il numero di nodi
                    if (v == b) {
                        lunghezzaTotale += lunghezzaAttuale;
                        nPaths++;
                    }
                    wVisit(g, v, b, lunghezzaTotale, lunghezzaAttuale, nPaths, visited);
                } else {
                    lunghezzaAttuale--;
                }
            }
            p = nodi_adiacenti.next(p);
            visited[nPos(a, visited)].visited = false;
        }
    }
    lunghezzaAttuale--;
}

template<class T>
int w_graph<T>::nPos(typename grafoMat<int, int>::nodo a, nVisit vet[]) {
    bool found = false;
    int i = 0;
    while (!found) {
        nVisit n = vet[i];
        if (a == n.nodo) {
            found = true;
        } else {
            i++;
        }
    }
    return i;
}

#endif // ONE_LABEL_PATH
