#ifndef GRAPH_COLOR_H
#define GRAPH_COLOR_H

#include "../grafoMatrice.h"

using std::string;

typedef struct {
    nodoG nodo;
    bool visitato;
} nVisit;

class graph_color {
public:
    bool sameColorPath(grafoMat<string, int> &, typename grafoMat<string, int>::nodo n1,
                       typename grafoMat<string, int>::nodo n2);

    bool uniformColorPath(grafoMat<string, int> &, typename grafoMat<string, int>::nodo n1,
                          typename grafoMat<string, int>::nodo n2);

private:
    int nPos(typename grafoMat<int, int>::nodo a, nVisit vet[]);

    bool sameColorPathVisit(grafoMat<string, int> &, typename grafoMat<string, int>::nodo n1,
                            typename grafoMat<string, int>::nodo n2);

    bool uniformColorPathVisit(grafoMat<string, int> &g, typename grafoMat<string, int>::nodo n1,
                               typename grafoMat<string, int>::nodo n2);
};

int graph_color::nPos(typename grafoMat<int, int>::nodo a, nVisit vet[]) {
    bool found = false;
    int i = 0;
    while (!found) {
        nVisit n = vet[i];
        if (a == n.nodo) {
            found = true;
        } else
            i++;
    }
    return i;
}

bool graph_color::sameColorPath(grafoMat<string, int> &g, typename grafoMat<string, int>::nodo n1,
                                typename grafoMat<string, int>::nodo n2) {
    bool result = false;
    if (!g.empty()) {
        result = sameColorPathVisit(g, n1, n2);
    }
    return result;
}

bool graph_color::uniformColorPath(grafoMat<string, int> &g, typename grafoMat<string, int>::nodo n1,
                                   typename grafoMat<string, int>::nodo n2) {
    bool result = false;
    if (!g.empty()) {
        result = uniformColorPathVisit(g, n1, n2);
    }
    return result;
}

bool graph_color::uniformColorPathVisit(grafoMat<string, int> &g, typename grafoMat<string, int>::nodo n1,
                                        typename grafoMat<string, int>::nodo n2) {
    nVisit n;
    nodoG v;
    VectorList<nodoG> nodes = g.nodesList();
    VectorList<nodoG> adjacency;
    nVisit visited[g.numNodi()];
    VectorList<nodoG>::position p = nodes.begin();
    for (int i = 0; i < g.numNodi(); i++) {
        n.nodo = nodes.read(p);
        n.visitato = false;
        visited[i] = n;
        p = nodes.next(p);
    }
    Queue_vt<nodoG> q;
    q.push(n1);
    nodoG currentNode;
    while (!q.empty()) {
        currentNode = q.read();
        if (currentNode == n2) {
            return true;
        }
        q.pop();
        visited[nPos(currentNode, visited)].visitato = true;
        adjacency = g.adiacenti(currentNode);
        p = adjacency.begin();
        while (!adjacency.end(p)) {
            v = adjacency.read(p);
            if (g.leggiEtichetta(currentNode) != g.leggiEtichetta(v) && !visited[nPos(v, visited)].visitato) {
                if (!q.exists(v)) {
                    q.push(v);
                }
            }
            p = adjacency.next(p);
        }
    }
    return false;
}

bool graph_color::sameColorPathVisit(grafoMat<string, int> &g, typename grafoMat<string, int>::nodo n1,
                                     typename grafoMat<string, int>::nodo n2) {
    nVisit n;
    nodoG v;
    VectorList<nodoG> nodes = g.nodesList();
    VectorList<nodoG> adjacency;
    nVisit visited[g.numNodi()];
    VectorList<nodoG>::position p = nodes.begin();
    for (int i = 0; i < g.numNodi(); i++) {
        n.nodo = nodes.read(p);
        n.visitato = false;
        visited[i] = n;
        p = nodes.next(p);
    }
    Queue_vt<nodoG> q;
    q.push(n1);
    nodoG currentNode;
    while (!q.empty()) {
        currentNode = q.read();
        if (currentNode == n2) {
            return true;
        }
        q.pop();
        visited[nPos(currentNode, visited)].visitato = true;
        adjacency = g.adiacenti(currentNode);
        p = adjacency.begin();
        while (!adjacency.end(p)) {
            v = adjacency.read(p);
            // escludo a priori i nodi con etichetta diversa
            if (g.leggiEtichetta(n1) == g.leggiEtichetta(v) && !visited[nPos(v, visited)].visitato) {
                if (!q.exists(v)) {
                    q.push(v);
                }
            }
            p = adjacency.next(p);
        }
    }
    return false;
}

#endif //GRAPH_COLOR_H
