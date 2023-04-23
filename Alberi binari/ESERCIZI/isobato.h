#include "../linkedBinTree.h"
#ifndef REALIZZAZIONI_ISOBATO_H
#define REALIZZAZIONI_ISOBATO_H
template <class T>
class isobato
{
public:
    bool isIsobato(Bintree_pt<T> &BT);

private:
    void checkIsobato(Bintree_pt<T> &BT, typename Bintree_pt<T>::node n, bool &isobato, int height);
};

/*
 * La funzione restituisce true se l'albero è isobato, false altrimeti
 * Un albero è isobato quando tutti i cammini dalla radice alle foglie hanno la stessa lunghezza
 */
template <class T>
bool isobato<T>::isIsobato(Bintree_pt<T> &BT)
{
    if (!BT.empty())
    {
        bool isobato = true;
        // richiamo una funzione per verificare che l'albero sia isobato
        checkIsobato(BT, BT.radice(), isobato, BT.height(BT, BT.root()));
        return isobato;
    }
    // per definizione se l'albero è vuoto allora è anche isobato
    else
        return true;
}

// La funzione verifica se l'albero è isobato
template <class T>
void isobato<T>::checkIsobato(Bintree_pt<T> &BT, typename Bintree_pt<T>::node n, bool &isobato, int height)
{
    // se l'albero è isobato continuo il controllo
    if (isobato)
    {
        if (BT.leftEmpty(n) && BT.rightEmpty(n))
        {
            // se la profondità di una foglia è diversa dall'altezza dell'albero allora l'albero non è isobato
            if (BT.depth(BT, n) != height)
                isobato = false;
        }
        else
        {
            // richiamo la funzione di verifica sui figli di n (se esistono)
            if (!BT.leftEmpty(n))
                checkIsobato(BT, BT.leftNode(n), isobato, height);
            if (!BT.rightEmpty(n))
                checkIsobato(BT, BT.rightNode(n), isobato, height);
        }
    }
}
#endif // REALIZZAZIONI_ISOBATO_H
