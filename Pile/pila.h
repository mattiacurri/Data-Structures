#ifndef Stack_H
#define Stack_H

// definisco la classe template Stack
template <class T>
class Stack
{
public:
    typedef T valuetype; // tipo di dato dello stack

    // metodo che controlla se lo stack e' vuoto
    virtual bool empty() const = 0;

    // metodo per leggere l'elemento in cima allo stack
    virtual valuetype peek() const = 0;

    // metodo per estrarre un elemento dalla cima dello stack
    virtual valuetype pop() = 0;

    // metodo per inserire un elemento in cima allo stack
    virtual void push(valuetype) = 0;
};

#endif