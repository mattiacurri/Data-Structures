#include <iostream>
#include "grid.h"

int main() {
    grid Griglia;
    cell Cella(2, 2);
    Griglia.insert(Cella);
    cell Cella1(1, 2);
    Griglia.insert(Cella1);
    Cella.setX(1);
    Cella.setY(0);
    Griglia.insert(Cella);
    Cella.setX(0);
    Cella.setY(0);
    Griglia.insert(Cella);
    Griglia.print();
    Griglia.moveLeft(1, 2);
    Griglia.print();
    Griglia.moveRight(1, 1);
    Griglia.print();
    Griglia.moveUpper(1, 2);
    Griglia.print();
    return 0;
}