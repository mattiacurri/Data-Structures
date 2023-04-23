#ifndef REALIZZAZIONI_SOTTOALBERO_H
#define REALIZZAZIONI_SOTTOALBERO_H
#include "../linkedBinTree.h"
template <class T>
class subTree
{
public:
    bool isSubTree(BinTree_pt<T> &BT, BinTree_pt<T> &subBT);

private:
    void checkSubTree(BinTree_pt<T> &BT, BinTree_pt<T> &subBT, typename BinTree_pt<T>::node n, typename BinTree_pt<T>::node subR, bool &isSubTree);
};

// La funzione restituisce true se l'albero subBT è un sottoalbero dell'albero BT, false altrimenti
template <class T>
bool subTree<T>::isSubTree(BinTree_pt<T> &BT, BinTree_pt<T> &subBT)
{
    if (!BT.empty() && !subBT.empty())
    {
        bool subTree = true;
        checkSubTree(BT, subBT, BT.root(), subBT.root(), subTree);
        return subTree;
    }
    else
        return false;
}

// Funzione ricorsiva che verifica se un albero è sottoalbero di un altro
template <class T>
void subTree<T>::checkSubTree(BinTree_pt<T> &BT, BinTree_pt<T> &subBT, typename BinTree_pt<T>::node n, typename BinTree_pt<T>::node subR, bool &isSubTree)
{
    if (isSubTree)
    {
        if (BT.read(n) != subBT.read(subR))
        {
            isSubTree = false;
            // n e subR non hanno lo stesso valore, quindi per ora l'albero subBT non è un sottoalbero di BT
            //  SE il nodo n è root di BT richiamo la funzione di verifica sui suoi figli (se esistono)
            if (n == BT.root())
            {
                isSubTree = true;
                if (!BT.leftEmpty(n))
                    checkSubTree(BT, subBT, BT.leftNode(n), subBT.root(), isSubTree);
                if (!isSubTree && !BT.rightEmpty(n))
                {
                    isSubTree = true;
                    checkSubTree(BT, subBT, BT.rightNode(n), subBT.root(), isSubTree);
                }
            }
        }
        else
        {
            // se il n e subR hanno lo stesso valore allora richiamo la funzione sui figli di n (se esistono) passando come parametro i rispettivi figli (se esistono) di subBT
            if (!BT.leftEmpty(n) && !subBT.leftEmpty(subR))
                checkSubTree(BT, subBT, BT.leftNode(n), subBT.leftNode(subR), isSubTree);
            if (!BT.rightEmpty(n) && !subBT.rightEmpty(subR) && isSubTree)
                checkSubTree(BT, subBT, BT.rightNode(n), subBT.rightNode(subR), isSubTree);
        }
    }
    else
    {
        // Richiamo la funzione di verifica sui figli del nodo n (se esistono), passando come altro parametro la root di subBT
        isSubTree = true;
        if (!BT.leftEmpty(n))
            checkSubTree(BT, subBT, BT.leftNode(n), subBT.root(), isSubTree);
        if (!isSubTree && !BT.rightEmpty(n))
        {
            isSubTree = true;
            checkSubTree(BT, subBT, BT.rightNode(n), subBT.root(), isSubTree);
        }
    }
}

#endif // REALIZZAZIONI_SOTTOALBERO_H
