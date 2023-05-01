#ifndef TREE_H
#define TREE_H

template<class T, class N>
class Tree {
public:
    typedef T value_type;
    typedef N node;

    // Metodo che verifica se l'albero e' vuoto
    virtual bool empty() const = 0;

    // Metodo che inserisce la radice
    virtual void insertRoot(value_type) = 0;

    // Metodo che restituisce il valore della radice
    virtual node root() const = 0;

    // Metodo che restituisce il genitore di un nodo
    virtual node parent(node) const = 0;

    // Metodo che verifica se un nodo e' foglia
    virtual bool isLeaf(node) const = 0;

    // Metodo che restituisce il primo figlio di un nodo secondo la relazione d'ordine
    virtual node firstChild(node) const = 0;

    // Metodo che verifica se un nodo e' l'ultimo figlio
    virtual bool isLastSibling(node) const = 0;

    // Metodo che restituisce il fratello di un nodo
    virtual node nextSibling(node) const = 0;

    // Metodo che inserisce un sottoalbero la cui radice e' il primo figlio del nodo
    virtual void insertFirstSubTree(node, Tree &) = 0;

    // Metodo che inserisce un sottoalbero la cui radice e' il fratello dell'ultimo figlio del nodo
    virtual void insertSubTree(node, Tree &) = 0;

    // Metodo che rimuove il sottoalbero con radice il nodo da parametro
    virtual void removeSubTree(node) = 0;

    // Metodo che scrive un valore nel nodo
    virtual void writeNode(node, value_type) = 0;

    // Metodo che restituisce il valore di un nodo
    virtual value_type read(node) const = 0;
};


#endif