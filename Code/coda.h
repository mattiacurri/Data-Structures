#ifndef _CODA_H
#define _CODA_H

// creo la classe template virtuale coda
template <class T>
class Queue
{
public:
    typedef T value_type;

    // metodo per verificare se la coda e' vuota
    virtual bool empty() const = 0;

    // metodo per leggere l'elemento in testa alla coda
    virtual value_type read() const = 0;

    // metodo per estrarre l'elemento in testa alla coda
    virtual void pop() = 0;

    // metodo per inserire un elemento in coda
    virtual void push(const value_type&) = 0;

};

#endif