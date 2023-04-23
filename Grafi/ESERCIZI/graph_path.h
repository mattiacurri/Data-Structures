#ifndef GRAPH_PATH
#define GRAPH_PATH

#include "../grafoMatrice.h"

typedef struct {
    nodoG node;
    bool visited;
} nVisit;

class graph_path {
public:
// dato l’intero sum e due nodi a e b, determina se esiste un cammino semplice, ovvero
// senza nodi ripetuti, avente le seguenti propriet`a:
// 1) parte dal nodo a e termina sul nodo b
// 2) la somma delle etichette dei nodi nella sequenza dei nodi del cammino `e minore
// dell’intero sum dato in input
    bool sumPath(grafoMat<int, int>&, int sum, typename grafoMat<int, int>::nodo a, typename grafoMat<int, int>::nodo b);

private:
    // grafoMat<int, int> G;

    bool bfs_sumPath(grafoMat<int, int>&, int sum, typename grafoMat<int, int>::nodo a, typename grafoMat<int, int>::nodo b, bool &exists);

    int nPos(typename grafoMat<int, int>::nodo n, nVisit visited[]);

};

bool graph_path::sumPath(grafoMat<int, int>& G, int sum, typename grafoMat<int, int>::nodo a, typename grafoMat<int, int>::nodo b) {
    if (!G.empty()) {
        bool exists = false;
        return bfs_sumPath(G, sum, a, b, exists);
    } else {
        return false;
    }
}

bool graph_path::bfs_sumPath(grafoMat<int, int>& G,int sum, typename grafoMat<int, int>::nodo a, typename grafoMat<int, int>::nodo b,
                             bool &exists) {
    int sum_path = 0;
    nVisit n;
    VectorList<nodoG> nodesList = G.nodesList();
    VectorList<nodoG> adjacencyList;
    nVisit visited[G.numNodi()];
    VectorList<nodoG>::position p = nodesList.begin();
    for (int i = 0; i < G.numNodi(); i++) {
        n.node = nodesList.read(p);
        n.visited = false;
        visited[i] = n;
        p = nodesList.next(p);
    }
    Queue_vt<nodoG> q;
    q.push(a);
    nodoG currentNode;
    while (!q.empty() && !exists && sum_path < sum) {
        currentNode = q.read();
        sum_path += G.leggiEtichetta(currentNode);
        q.pop();
        visited[nPos(currentNode, visited)].visited = true;
        adjacencyList = G.adiacenti(currentNode);
        p = adjacencyList.begin();
        while (!adjacencyList.end(p) && !exists && sum_path < sum) {
            nodoG v = adjacencyList.read(p);
            if (v == b) {
                sum_path += G.leggiEtichetta(v);
                exists = true;
            } else {
                if (!visited[nPos(v, visited)].visited && !q.exists(v)) {
                    q.push(v);
                }
                p = adjacencyList.next(p);
            }
        }
    }
    if (sum_path >= sum) {
        exists = false;
    }
}

int graph_path::nPos(typename grafoMat<int, int>::nodo a, nVisit visited[]) {
    bool found = false;
    int i = 0;
    while (!found) {
        if (visited[i].node == a) {
            found = true;
        } else {
            i++;
        }
    }
    return i;
}

#endif //GRAPH_PATH