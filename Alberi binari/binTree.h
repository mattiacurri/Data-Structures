#ifndef _ALBERO_BINARIO_H
#define ALBERO_BINARIO_H

// definisco la classe template astratta albero binario
template<class T, class N>
class BinTree {
public:
    // definisco i tipi presenti
    typedef T value_type;
    typedef N treeNode;

    // definisco gli operatori che devono essere presenti in tutte le implementazioni

    // metodo che crea un nuovo albero binario
    // virtual void crea() = 0;

    // metodo che verifica se l'albero binario e' vuoto
    virtual bool empty() const = 0;

    // metodo che restituisce il treeNode radice
    virtual treeNode root() const = 0;

    // metodo che restituisce il genitore del treeNode selezionato
    virtual treeNode parent(treeNode) const = 0;

    // metodo che restituisce il treeNode di sinistra del treeNode selezionato
    virtual treeNode leftNode(treeNode) const = 0;

    // metodo che restituisce il treeNode di destra del treeNode selezionato
    virtual treeNode rightNode(treeNode) const = 0;

    // metodo per inserire un treeNode alla radice dell'albero
    virtual void insRoot(value_type) = 0;

    // metodo per inserire a sinistra un treeNode
    virtual void leftInsert(treeNode, value_type) = 0;

    // metodo per inserire a destra un treeNode
    virtual void rightInsert(treeNode, value_type) = 0;

    // metodo che elimina un treeNode dell'albero
    virtual void deleteSubBinTree(treeNode) = 0;

};

#endif