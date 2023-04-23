#include "../linkedBinTree.h"
#ifndef REALIZZAZIONI_evenOdd_H
#define REALIZZAZIONI_evenOdd_H
template <class T>
class evenOdd
{
public:
    bool isEvenOdd(BinTree_pt<T> &BT);

private:
    void checkisEvenOdd(BinTree_pt<T> &BT, typename BinTree_pt<T>::node n, int level, bool &evenOdd);
};

/*
 * La funzione restituisce true se l'albero è paridispari, false altrimenti
 * Un albero è paridispari quando tutti i nodi di livello pari hanno valore pari e tutti i nodi di livello dispari hanno valore dispari
 */
template <class T>
bool evenOdd<T>::isEvenOdd(BinTree_pt<T> &BT)
{
    if (!BT.empty())
    {
        bool evenOdd = true;
        checkisEvenOdd(BT, BT.radice(), 0, evenOdd);
        return evenOdd;
    }
    // se l'albero è vuoto allora non è paridispari
    else
        return false;
}

template <class T>
void evenOdd<T>::checkisEvenOdd(BinTree_pt<T> &BT, typename BinTree_pt<T>::node n, int level, bool &evenOdd)
{
    // se l'albero non è paridispari, esco dalla funzione
    if (evenOdd)
    {
        if (BT.read(n) % 2 == 0)
        {
            // se il nodo è a level pari ma ha valore dispari l'albero non è evenOdd ed esco dalla funzione
            if (level % 2 != 0)
                evenOdd = false;
        }
        else
        {
            // se il nodo è a level dispari ma ha valore pari l'albero non è evenOdd ed esco dalla funzione
            if (level % 2 == 0)
                evenOdd = false;
        }
        if (evenOdd)
        {
            if (!BT.leftEmpty(n))
                checkisEvenOdd(BT, BT.leftNode(n), level + 1, evenOdd);
            if (!BT.rightEmpty(n))
                checkisEvenOdd(BT, BT.rightNode(n), level + 1, evenOdd);
        }
    }
}
#endif // REALIZZAZIONI_evenOdd_H
