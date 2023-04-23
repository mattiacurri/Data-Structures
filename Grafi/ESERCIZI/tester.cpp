#include <iostream>

// #include "graph_color.h"
// #include "one_label_path.h"
#include "graph_path.h"

int main() {
    // tester graph_color
    /* graph_color a;
    grafoMat<string, int> x;
    nodoG nodo;
    nodoG nodo1;
    nodoG nodo2;
    nodoG nodo3;
    nodoG nodo4;
    nodoG nodo5;
    nodoG nodo6;
    nodoG nodo7;
    nodoG nodo8;

    x.insNodo(nodo);
    x.insNodo(nodo1);
    x.insNodo(nodo2);
    x.insNodo(nodo3);
    x.insNodo(nodo4);
    x.insNodo(nodo5);
    x.insNodo(nodo6);
    x.insNodo(nodo7);
    x.insNodo(nodo8);
    x.scriviEtichetta(nodo, "rosso");
    x.scriviEtichetta(nodo1, "verde");
    x.scriviEtichetta(nodo2, "bianco");
    x.scriviEtichetta(nodo3, "rosso");
    x.scriviEtichetta(nodo4, "verde");
    x.scriviEtichetta(nodo5, "bianco");
    x.scriviEtichetta(nodo6, "verde");
    x.scriviEtichetta(nodo7, "rosso");
    x.scriviEtichetta(nodo8, "verde");
    x.insArco(nodo1, nodo2, 1);
    x.insArco(nodo1, nodo3, 1);
    x.insArco(nodo2, nodo, 1);
    x.insArco(nodo3, nodo5, 1);
    x.insArco(nodo, nodo3, 1);
    x.insArco(nodo4, nodo5, 1);
    x.insArco(nodo5, nodo6, 1);
    x.insArco(nodo6, nodo4, 1);
    x.insArco(nodo6, nodo7, 1);
    x.insArco(nodo7, nodo3, 1);
    x.insArco(nodo7, nodo8, 1);

    cout << boolalpha << a.sameColorPath(x, nodo3, nodo8) << endl;
    cout << boolalpha << a.uniformColorPath(x, nodo3, nodo8) << endl;
    */

    /*grafoMat<int, int> x;
    w_graph<int> l;
    nodoG nodo;
    nodoG nodo1;
    nodoG nodo2;
    nodoG nodo3;
    nodoG nodo4;
    nodoG nodo5;
    nodoG nodo6;
    nodoG nodo7;
    nodoG nodo8;

    x.insNodo(nodo);
    x.insNodo(nodo1);
    x.insNodo(nodo2);
    x.insNodo(nodo3);
    x.insNodo(nodo4);
    x.insNodo(nodo5);
    x.insNodo(nodo6);
    x.insNodo(nodo7);
    x.insNodo(nodo8);


    x.insArco(nodo1, nodo2, 1);
    x.insArco(nodo1, nodo3, 1);
    x.insArco(nodo2, nodo, 1);
    x.insArco(nodo3, nodo5, 1);
    x.insArco(nodo, nodo3, 1);
    x.insArco(nodo4, nodo5, 1);
    x.insArco(nodo5, nodo6, 1);
    x.insArco(nodo6, nodo4, 1);
    x.insArco(nodo6, nodo7, 1);
    x.insArco(nodo7, nodo3, 1);
    x.insArco(nodo7, nodo8, 1);
    wPath w;
    w = l.one_label_path(x, nodo, nodo3);
    cout << w.mLength << " " << w.nPaths << endl;*/
    grafoMat<int, int> x;

    nodoG nodo;
    nodoG nodo1;
    nodoG nodo2;
    nodoG nodo3;
    nodoG nodo4;
    nodoG nodo5;
    nodoG nodo6;
    nodoG nodo7;
    nodoG nodo8;

    x.insNodo(nodo);
    x.insNodo(nodo1);
    x.insNodo(nodo2);
    x.insNodo(nodo3);
    x.insNodo(nodo4);
    x.insNodo(nodo5);
    x.insNodo(nodo6);
    x.insNodo(nodo7);
    x.insNodo(nodo8);
    x.scriviEtichetta(nodo, 2);
    x.scriviEtichetta(nodo1, 3);
    x.scriviEtichetta(nodo2, 4);
    x.scriviEtichetta(nodo3, 2);
    x.scriviEtichetta(nodo4, 6);
    x.scriviEtichetta(nodo5, 1);
    x.scriviEtichetta(nodo6, 1);
    x.scriviEtichetta(nodo7, 1);
    x.scriviEtichetta(nodo8, 1);

    x.insArco(nodo1, nodo2, 1);
    x.insArco(nodo1, nodo3, 1);
    x.insArco(nodo2, nodo, 1);
    x.insArco(nodo3, nodo5, 1);
    x.insArco(nodo, nodo3, 1);
    x.insArco(nodo4, nodo5, 1);
    x.insArco(nodo5, nodo6, 1);
    x.insArco(nodo6, nodo4, 1);
    x.insArco(nodo6, nodo7, 1);
    x.insArco(nodo7, nodo8, 1);
    graph_path a;

    cout << boolalpha << a.sumPath(x, 10, nodo3, nodo8) << endl;
    return 0;
}