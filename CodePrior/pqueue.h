#ifndef _CODAP_H_
#define _CODAP_H_

#include "assert.h"

template<class T>
class CodaP {

public:
    typedef T _tipoelem;

    CodaP();

    CodaP(int);

    ~CodaP();

    void creaPrioriCoda();

    void inserisci(_tipoelem);

    _tipoelem min();

    void cancellaMin();

private:
    int MAXLUNG;
    _tipoelem *heap;
    int ultimo;

    void fixUp();

    void fixDown(int, int);
};


template<class T>
CodaP<T>::CodaP():MAXLUNG(100) {
    heap = new _tipoelem[MAXLUNG];
    creaPrioriCoda();
};

template<class T>
CodaP<T>::CodaP(int maxN): MAXLUNG(maxN) {
    heap = new _tipoelem[MAXLUNG];
    creaPrioriCoda();
};

template<class T>
CodaP<T>::~CodaP() {
    delete[]heap;
};

template<class T>
void CodaP<T>::creaPrioriCoda() {
    ultimo = 0;
};

template<class T>
void CodaP<T>::inserisci(_tipoelem e) {
    assert (ultimo < MAXLUNG);
    heap[++ultimo - 1] = e;
    fixUp();
};

template<class T>
typename CodaP<T>::_tipoelem CodaP<T>::min() {
    assert (ultimo != 0);
    return (heap[0]);
};

template<class T>
void CodaP<T>::cancellaMin() {
    assert (ultimo != 0);

    heap[0] = heap[ultimo - 1];

    ultimo--;
    fixDown(1, ultimo);

};


/* Per ripristinare i vincoli dello heap quando la priorità di un nodo è      *
 * cresciuta, ci spostiamo nello heap verso l'alto, scambiando, se necessario,*
 * il nodo in posizione k con il suo nodo padre (in posizione k/2),           *
 * continuando fintanto che heap[k]<heap[k/2] oppure fino a quando            *
 * raggiungiamo la cima dello heap.                                           */

template<class T>
void CodaP<T>::fixUp() {
    int k = ultimo;

    while (k > 1 && heap[k - 1] < heap[k / 2 - 1]) {
        _tipoelem tmp;
        tmp = heap[k - 1];
        heap[k - 1] = heap[k / 2 - 1];
        heap[k / 2 - 1] = tmp;
        k = k / 2;
    }

}

// TODO
/* Per ripristinare i vincoli dello heap quando la priorità di un nodo si è   *
 * ridotta, ci spostiamo nello heap verso il basso, scambiando, se necessario,*
 * il nodo in posizione k con il minore dei suoi nodi figli e arrestandoci    *
 * quando il nodo al posto k non è più grande di almeno uno dei suoi figli    *
 * oppure quando raggiungiamo il fondo dello heap. Si noti che se N è pari e  *
 * k è N/2, allora il nodo in posizione k ha un solo figlio: questo caso      *
 * particolare deve essere trattato in modo appropriato.                      */
template<class T>
void CodaP<T>::fix_down(int corrente, int last) {
    bool scambio = true;
    tipoelem tmp;
    while (corrente <= last / 2 && scambio) {
        int j;
        //controllo se ha entrambi i figli, nel caso mi posiziono in quello con priorità minore
        if (corrente * 2 + 1 > ultimo) {
            if (elementi[corrente * 2] < elementi[corrente * 2 + 1])
                j = corrente * 2;
            else j = corrente * 2 + 1;
        } else j = corrente * 2;
        if (j < last && elementi[j - 1] > elementi[j])
            j++;
        scambio = elementi[j - 1] < elementi[corrente - 1];
        if (scambio) {
            tmp = elementi[corrente - 1];
            elementi[corrente - 1] = elementi[j - 1];
            elementi[j - 1] = tmp;
            corrente = j;
        }
    }
}

/* sort */
/* [4, 2, 1, 3, 5]
 * leggimin: 1
 * [1]
 * cancellamin : [4, 2, 3, 5]
 * [1]
 * leggimin: 2
 * [1, 2]
 * ... */
/* heap sort
 * posso usare lo stesso array come un heap
 * */
template<class T>
void heapsort(T *a, int dim) {
    for (int i = 1; i < dim; i++) {
        CodaP<T>::fixUp();
    }
    for (int i = 0; i < dim; i++) {
        swap(a, 0, dim - i);
        CodaP<T>::fixDown(1, dim - 1 - i);
    }
}

#endif /* _CODAP_H_ */