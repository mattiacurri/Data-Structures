#include <stdexcept>
#include <ostream>
#include "grafo.h"


#ifndef REALIZZAZIONI_GRAFOMATRICE_H
#define REALIZZAZIONI_GRAFOMATRICE_H
using namespace std;

template<class E, class P>
class grafoMat;


template<class P>
class infoArco {
public:
    P peso;
    bool empty;

    infoArco() {
        empty = true;
    }
};


template<class E, class P>
class infoNodo {
    friend class grafoMat<E, P>;

public:
    E etichetta;
    bool empty;
    infoArco<P> *archi;

    infoNodo() {
        empty = true;
    }

    ~infoNodo() {
        if (empty)
            delete[] archi;
    }

private:
    int id;
};


class nodoG {
public:
    nodoG(int i) {
        nodoId = i;
    }

    nodoG() {
    }

    int getId() const { return nodoId; }

    void setId(const int id) { nodoId = id; }

    bool operator==(nodoG n1) {
        return this->nodoId == n1.nodoId;
    }

    friend ostream &operator<<(ostream &os, nodoG &n) {
        os << n.getId() << " ";
        return os;
    }

private:
    int nodoId;
};


template<class E, class P>
class grafoMat : public grafo<E, P, nodoG> {
public:
    typedef E etichetta;
    typedef P peso;
    typedef nodoG nodo;
    typedef arco<peso, nodo> arco;
    typedef typename grafo<E, P, nodoG>::listaNodi listaNodi;
    typedef typename grafo<E, P, nodoG>::listaArchi listaArchi;
    typedef typename grafo<E, P, nodoG>::positionListaNodi positionListaNodi;
    typedef typename grafo<E, P, nodoG>::positionListaArchi positionListaArchi;

    grafoMat();

    grafoMat(int);

    ~grafoMat();

    bool empty() const;

    void insNodo(nodoG &);

    void insArco(const nodo, const nodo, const peso);

    void cancNodo(nodo);

    void cancArco(nodo, nodo);

    bool existsNodo(nodo) const;

    bool existsArco(arco) const;

    listaNodi adiacenti(nodo) const;

    listaNodi nodesList() const;

    etichetta leggiEtichetta(nodo) const;

    void scriviEtichetta(nodo, etichetta);

    peso leggiPeso(nodo, nodo) const;

    void scriviPeso(nodo, nodo, peso);

    int numNodi() {
        return nodi;
    };

    int numArchi() {
        return archi;
    };

    //ALGORITMI DI VISITA
    void bfs(nodo) const;

    void dfs(nodo) const;

    //FUNZIONI AGGIUNTIVE

    //NUMERO ARCHI ENTRANTI NEL NODO N
    int inDegree(nodo n);

    //NUMERO ARCHI USCENTI DAL NODO N
    int outDegree(nodo n);

    //MEDIA DEL NUMERO DI ARCHI USCENTI PER OGNI NODO DEL GRAFO
    double meanOutDegree();

    //SE ESISTE UN PERCORSO TRA N E D LO STAMPA
    void findPath(nodo n, nodo d);


private:
    infoNodo<E, P> *matrice;
    int dimensione;
    int nodi; //numero nodi
    int archi;//numero archi

    //FUNZIONI DI SERVIZIO NON ACCESSIBILI ALL'UTENTE
    void dfs(nodo, int[]) const;

    listaNodi getPath(nodo n1, nodo n2);
};

/*
 * CREAZIONE DI UN GRAFO
 * POST CONDIZIONE: Grafo empty
 */
template<class E, class P>
grafoMat<E, P>::grafoMat() {
    dimensione = 20; //dimensione arbitraria
    nodi = 0;
    archi = 0;
    matrice = new infoNodo<E, P>[dimensione];
    for (int i = 0; i < dimensione; i++) {
        matrice[i].archi = new infoArco<P>[dimensione];
    }
}

/*
 * CREAZIONE DI UN GRAFO
 * POST CONDIZIONE: Grafo empty
 */
template<class E, class P>
grafoMat<E, P>::grafoMat(int dimensione) {
    this->dimensione = dimensione; //dimensione decisa dall'utente
    nodi = 0;
    archi = 0;
    matrice = new infoNodo<E, P>[dimensione];
    for (int i = 0; i < dimensione; i++) {
        matrice[i].archi = new infoArco<P>[dimensione];
    }
}

//Distruttore
template<class E, class P>
grafoMat<E, P>::~grafoMat() {
    for (int i = 0; i < dimensione; i++) {
        if (matrice[i].empty == false) {
            delete[] matrice[i].archi;
        }
    }
    delete[] matrice;
}

/*
 * Controlla se un grafo è empty
 * POST CONDIZIONE: Return TRUE se il grafo è empty, FALSE altrimenti
 */
template<class E, class P>
bool grafoMat<E, P>::empty() const {
    return (nodi == 0);
}

/*
 * Inserimento di un nodo in un grafo
 * POST CONDIZIONE: Grafo con nodo inserito
 */
template<class E, class P>
void grafoMat<E, P>::insNodo(nodoG &n) {
    if (nodi < dimensione) {
        int i = 0;
        while (matrice[i].empty == false) {
            i++;
        }
        matrice[i].empty = false;
        n.setId(i);
        nodi++;
    } else throw out_of_range("GRAFO COMPLETO, IMPOSSIBILE INSERIRE ALTRI NODI");
}

/*
 * Inserimento di un arco
 * PRE CONDIZIONE:Arco tra il nodo u e il nodo v non exists
 * POST CONDIZIONE: Grafo con arco tra nodo u e v aggiunto
 */
template<class E, class P>
void grafoMat<E, P>::insArco(const nodo u, const nodo v, const peso p) {
    arco a(u, v);
    if (!existsArco(a)) {
        matrice[u.getId()].archi[v.getId()].empty = false;
        matrice[u.getId()].archi[v.getId()].peso = p;
        archi++;
    }
}

/*
 * Cancellazione di un nodo da un grafo
 * PRE CONDIZIONE: Il nodo è isolato (non vi sono archi uscenti dal nodo o entranti nel nodo)
 * POST CONDIZIONE: Grafo con nodo eliminato
 */
template<class E, class P>
void grafoMat<E, P>::cancNodo(nodo n) {
    int eliminato = true;
    int i = 0;
    int j = 0;

    //VERIFICO CHE NON VI SIANO ARCHI USCENTI
    while (i < dimensione && eliminato == true) {
        if (matrice[n.getId()].archi[i].empty == false) eliminato = false;
        else i++;
    }

    //VERIFICO CHE NON VI SIANO ARCHI ENTRANI
    while (j < dimensione && eliminato == true) {
        if (!matrice[j].empty && matrice[j].archi[n.getId()].empty == false) eliminato = false;
        else j++;
    }
    if (eliminato) {
        matrice[n.getId()].empty = true;
        nodi--;
        delete matrice[n.getId()].archi;
    } else cout << "IMPOSSIBILE ELIMINARE NODO, VI SONO ARCHI A ESSO COLLEGATI" << endl;
}

/*
 * Cancellazione di un arco da un grafo
 * PRE CONDIZIONE: L'arco tra il nodo u e il nodo v exists
 * POST CONDIZIONE: Grafo con arco tra nodo u e v eliminato
 */
template<class E, class P>
void grafoMat<E, P>::cancArco(nodo u, nodo v) {
    arco a(u, v);
    if (existsArco(a)) {
        matrice[u.getId()].archi[v.getId()].empty = true;
        archi--;
    } else throw std::out_of_range("ARCO NON ESISTENTE");
}

/*
 * Resituisce la lista dei nodi adiacenti a un nodo n
 * POST CONDIZIONE: La lista contiene tutti i nodi v per cui exists un arco uscente da n e entrante in v
 */
template<class E, class P>
typename grafoMat<E, P>::listaNodi grafoMat<E, P>::adiacenti(nodo n) const {
    listaNodi list;
    for (int i = 0; i < dimensione; i++) {
        if (matrice[n.getId()].archi[i].empty == false) {
            nodo v(i);
            list.headInsert(v);
        }
    }
    return list;
}

/*
 * La funzione restituisce una lista di tutti i nodi del grafo
 */
template<class E, class P>
typename grafoMat<E, P>::listaNodi grafoMat<E, P>::nodesList() const {
    listaNodi list;
    for (int i = 0; i < dimensione; i++) {
        if (matrice[i].empty == false) {
            nodo n;
            n.setId(i);
            list.headInsert(n);
        }
    }
    return list;
}

/*
 * La funzione restituisce true se il nodo exists, false altrimenti
 */
template<class E, class P>
bool grafoMat<E, P>::existsNodo(nodo n) const {
    return !matrice[n.getId()].empty;

}

/*
 * La funzione restituisce TRUE se l arco exists, false altrimenti
 */
template<class E, class P>
bool grafoMat<E, P>::existsArco(arco a) const {
    return !matrice[a.nodo1.getId()].archi[a.nodo2.getId()].empty;
};

/*
 * Viene restituita l'etichetta associata a un nodo n
 */
template<class E, class P>
typename grafoMat<E, P>::etichetta grafoMat<E, P>::leggiEtichetta(nodo n) const {
    if (existsNodo(n)) {
        return matrice[n.getId()].etichetta;
    } else throw std::out_of_range("NODO NON ESISTENTE");
}

/*
 * Viene scritta l'etichetta e nel nodo n
 */
template<class E, class P>
void grafoMat<E, P>::scriviEtichetta(nodo n, etichetta e) {
    if (existsNodo(n)) {
        matrice[n.getId()].etichetta = e;
    }
}

/*
 * Viene restituito il peso dell'arco tra il nodo u e il nodo v (se exists)
 */
template<class E, class P>
typename grafoMat<E, P>::peso grafoMat<E, P>::leggiPeso(nodo u, nodo v) const {
    arco a(u, v);
    if (existsArco(a)) {
        return matrice[u.getId()].archi[v.getId()].peso;
    } else throw std::out_of_range("L'ARCO NON ESISTE");
}

/*
 * Viene scritto il peso dell'arco tra il nodo u e il nodo v (se exists)
 */
template<class E, class P>
void grafoMat<E, P>::scriviPeso(nodo u, nodo v, peso p) {
    arco a(u, v);
    if (existsArco(a)) {
        matrice[u.getId()].archi[v.getId()].peso = p;
    } else throw std::out_of_range("L'ARCO NON ESISTE");
}


template<class E, class P>
void grafoMat<E, P>::dfs(nodo n) const {
    cout << "[";
    if (!empty() && existsNodo(n)) {
        int visitato[dimensione];
        for (int i = 0; i < dimensione; i++) {
            if (!matrice[i].empty)
                visitato[i] = 0; //NODO ESISTENTE MA NON VISITATO
            else
                visitato[i] = -1; //NODO NON ESISTE
        }
        dfs(n, visitato);

    }
    cout << "]" << endl;
}

template<class E, class P>
void grafoMat<E, P>::dfs(nodo n, int visitato[]) const {
    listaNodi nodiAdiacenti;
    nodiAdiacenti = adiacenti(n);
    cout << " " << leggiEtichetta(n);
    visitato[n.getId()] = 1;
    if (!nodiAdiacenti.empty()) {
        positionListaNodi p = nodiAdiacenti.begin();
        while (!nodiAdiacenti.end(p)) {
            nodo v = nodiAdiacenti.read(p);
            if (visitato[v.getId()] == 0)
                dfs(v, visitato);
            p = nodiAdiacenti.next(p);
        }
    }

}

template<class E, class P>
void grafoMat<E, P>::bfs(nodo n) const {
    cout << "[";
    if (!empty() && existsNodo(n)) {
        //PASSAGGI PRELIMINARI
        listaNodi ln;
        positionListaNodi p;
        nodo v;
        int visitato[dimensione];
        for (int i = 0; i < dimensione; i++) {
            if (!matrice[i].empty)
                visitato[i] = 0; //NODO ESISTENTE MA NON VISITATO
            else
                visitato[i] = -1; //NODO NON ESISTE
        }
        //ALGORITMO DI BFS
        Queue_vt<nodo> q;
        q.push(n);
        while (!q.empty()) {
            n = q.read();
            q.pop();
            if (visitato[n.getId()] == 0)
                cout << leggiEtichetta(n) << " ";
            visitato[n.getId()] = 1;
            ln = adiacenti(n);
            p = ln.begin();
            while (!ln.end(p)) {
                v = ln.read(p);
                if (visitato[v.getId()] == 0 && !q.exists(v)) {
                    q.push(v);
                }
                p = ln.next(p);
            }
        }
    }
    cout << "]" << endl;
}

template<class E, class P>
int grafoMat<E, P>::inDegree(nodo n) {
    if (existsNodo(n)) {
        int counter = 0;
        for (int j = 0; j < dimensione; j++) {
            if (matrice[j].archi[n.getId()].empty == false) counter++;
        }
        return counter;
    } else return -1;
}

template<class E, class P>
int grafoMat<E, P>::outDegree(nodo n) {
    if (existsNodo(n)) {
        return adiacenti(n).lunghezza();
    } else return -1;
}


template<class E, class P>
double grafoMat<E, P>::meanOutDegree() {
    if (archi > 0) {
        int counter = 0;
        for (int i = 0; i < dimensione; i++) {
            if (!matrice[i].empty) {
                nodo n;
                n.setId(i);
                counter += adiacenti(n).lunghezza();
            }
        }
        return (double) counter / numNodi();
    } else return 0;
}


template<class E, class P>
void grafoMat<E, P>::findPath(nodo n, nodo d) {
    if (existsNodo(n) && existsNodo(d)) {
        listaNodi percorso = getPath(n, d);
        if (percorso.lunghezza() > 0) {
            cout << "[ ";
            positionListaNodi p = percorso.begin();
            while (!percorso.end(p)) {
                int id = percorso.read(p).getId();
                cout << matrice[id].etichetta << " ";
                p = percorso.next(p);
            }
            cout << "]" << endl;
        } else cout << "NON ESISTE CAMMINO" << endl;
    }
}


template<class E, class P>
typename grafoMat<E, P>::listaNodi grafoMat<E, P>::getPath(nodo n1, nodo n2) {
    // PASSAGGI PRELIMINARI
    int visitato[dimensione];
    nodo padre[dimensione]; // NUOVO ARRAY PER SALVARE IL PADRE DI OGNI NODO
    for (int i = 0; i < dimensione; i++) {
        if (!matrice[i].empty) {
            visitato[i] = 0; // NODO ESISTENTE MA NON VISITATO
            padre[i] = nodo(-1); // NODO NON HA PADRE
        } else {
            visitato[i] = -1; // NODO NON ESISTE
        }
    }

    // CREA UNA CODA VUOTA
    Queue_vt<nodo> s;

    // AGGIUNGO IL NODO DI PARTENZA ALLA CODA
    s.push(n1);
    // RIPETI FINCHE LA CODA NON E' VUOTA
    while (!s.empty()) {
// PRENDI IL PRIMO NODO DALLA CODA E ELIMINALO
        nodo n = s.read();
        s.pop();
        //MARCA IL NODO COME VISITATO
        visitato[n.getId()] = 1;

        // SE IL NODO E' IL NODO "DESTINAZIONE", RISALI IL PERCORSO USANDO L'ARRAY "PADRE"
        // E RITORNA LA LISTA DEI NODI VISITATI
        if (n.getId() == n2.getId()) {
            listaNodi percorso;
            percorso.inserisciCoda(n);
            while (!(padre[n.getId()] == -1)) {
                n = padre[n.getId()];
                percorso.headInsert(n);
            }
            return percorso;
        }

        // AGGIUNGI I VICINI NON VISITATI ALLA CODA E SALVA IL LORO PADRE
        listaNodi vicini = adiacenti(n);
        positionListaNodi i = vicini.begin();
        while (!vicini.end(i)) {
            nodo vicino = vicini.read(i);
            if (visitato[vicino.getId()] == 0 && !s.exists(vicino)) {
                s.push(vicino);
                padre[vicino.getId()] = n; // SALVA IL NODO PADRE
            }
            i = vicini.next(i);
        }
    }

// SE LA CODA DIVENTA VUOTA PRIMA CHE IL NODO "DESTINAZIONE" SIA TROVATO, RITORNA UNA LISTA VUOTA
    return listaNodi();
}

#endif //REALIZZAZIONI_GRAFOMATRICE_H
