
#ifndef REALIZZAZIONI_LEVELGREEN_H
#define REALIZZAZIONI_LEVELGREEN_H
#include "../linkedBinTree.h"
#include <string>
using namespace std;
class green_redBin
{
public:
    int green_leafs(BinTree_pt<string> &BT);
    int level_red(BinTree_pt<string> &BT);

private:
    int green_leafs(BinTree_pt<string> &BT, const typename BinTree_pt<string>::node n);
    int level_red(BinTree_pt<string> &BT, const typename BinTree_pt<string>::node n, int level);
};

// La funzione restituisce il numero di foglie verdi in un albero
int green_redBin::green_leafs(BinTree_pt<string> &BT)
{
    if (BT.alberoBinVuoto())
        return 0;
    else
        return green_leafs(BT, BT.root());
}

// la funzione conta il numero di foglie il cui valore è verde
int green_redBin::green_leafs(BinTree_pt<string> &BT, const typename BinTree_pt<string>::node n)
{
    int sx = 0, dx = 0;
    if (BT.leftEmpty(n) && BT.rightEmpty(n))
    {
        // se il nodo è foglia restituisco 1 se ha come valore verde, 0 altrimenti
        return (BT.read(n) == "verde");
    }
    else
    {
        // se il nodo non è foglia restituisco richiamo la funzione ricorsivamente sui suoi figli (se esistono)
        if (!BT.leftEmpty(n))
            sx = green_leafs(BT, BT.leftNode(n));
        if (!BT.rightEmpty(n))
            dx = green_leafs(BT, BT.rightNode(n));
        // return del numero di foglie verdi
        return (sx + dx);
    }
}

// restituisce il numero di nodi di livello pari il cui valore è "rosso" e che hanno almeno un figlio il cui valore è "bianco";
int green_redBin::level_red(BinTree_pt<string> &BT)
{
    if (BT.alberoBinVuoto())
        return 0;
    else
        return level_red(BT, BT.root(), 0);
}

// calcola il numero di nodi di livello pari il cui valore è "rosso" e che hanno almeno un figlio il cui valore è "bianco";
int green_redBin::level_red(BinTree_pt<string> &BT, const int n, int level)
{
    int sx = 0, dx = 0, c = 0;
    if (BT.leftEmpty(n) && BT.rightEmpty(n))
        return 0;
    else
    {
        if ((livello % 2) == 0 && BT.read(n) == "rosso")
        {
            if (!BT.leftEmpty(n) && (BT.read(BT.leftNode(n)) == "bianco"))
                c = 1;
            if (!BT.rightEmpty(n) && (BT.read(BT.rightNode(n)) == "bianco"))
                c = 1;
        }
        if (!BT.leftEmpty(n))
            sx = level_red(BT, BT.leftNode(n), (level++));
        if (!BT.rightEmpty(n))
            dx = level_red(BT, BT.rightNode(n), (level++));
        return (sx + dx + c);
    }
}
#endif // REALIZZAZIONI_LEVELGREEN_H
