#include "pqueue.h"

int main() {
    CodaP<int> C;

    C.inserisci(1);
    C.inserisci(12);
    C.inserisci(19);
    C.inserisci(7);
    C.cancellaMin();
    C.inserisci(0);
    C.inserisci(11);
    C.cancellaMin();
    C.inserisci(5);
    C.inserisci(21);
    C.inserisci(18);
    C.cancellaMin();
    C.inserisci(3);
    C.cancellaMin();
}
