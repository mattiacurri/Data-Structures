#ifndef GRID_GRID_H
#define GRID_GRID_H

#include <iostream>
#include "../../linkedList.h"

class cell {
public:
    cell() {
        x = 0;
        y = 0;
    }

    cell(int init_x, int init_y) {
        x = init_x;
        y = init_y;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    void setX(int new_x) {
        x = new_x;
    }

    void setY(int new_y) {
        y = new_y;
    }

    bool operator==(const cell &c) {
        return ((c.x == this->x) && (c.y == this->y));
    }

    bool operator!=(const cell &c) {
        return !(this->operator==(c));
    }

private:
    int x;
    int y;
};

class grid {
public:
// inserisce una cella viva nella griglia
    void insert(cell &);

// rimuove una cella nella griglia
    void remove(cell &);

// sposta a sinistra di una posizione la cella viva presente in posizione (x,y)
    void moveLeft(int x, int y);

// sposta a destra di una posizione la cella viva presente in posizione (x,y)
    void moveRight(int x, int y);

// sposta in alto di una posizione la cella viva presente in posizione (x,y)
    void moveUpper(int x, int y);

// sposta in basso di una posizione la cella viva presente in posizione (x,y)
    void moveDown(int x, int y);

// stabilisce se la cella viva presente in posizione (x,y) `e circondata,
// ovvero tutte le celle vicine alla cella data sono vive
    bool surrounded(int x, int y);

// rimuove dalla griglia tutte le celle circondate
    void removeSurrounded();

    // funzioni accessorie
    void print();

private:
    LinkedList<cell> cells;
};

void grid::insert(cell &c) {
    bool found = false;
    LinkedList<cell>::position p = cells.begin();

    while (!found && !cells.end(p)) {
        if (c.getX() == cells.read(p).getX() && c.getY() == cells.read(p).getY()) {
            found = true;
        }
        p = cells.next(p);
    }
    if (!found) {
        cells.tailInsert(c);
    }
}

void grid::remove(cell &c) {
    LinkedList<cell>::position p = cells.begin();
    while (!cells.end(p)) {
        if (c.getX() == cells.read(p).getX() && c.getY() == cells.read(p).getY()) {
            cells.erase(p);
            break;
        }
        p = cells.next(p);
    }
}

void grid::moveLeft(int x, int y) {
    LinkedList<cell>::position p = cells.begin();
    cell c(x, y);
    while (cells.read(p) != c) {
        p = cells.next(p);
    }
    y--;
    c.setY(y);
    if (!cells.exists(c)) {
        cells.write(c, p);
    } else {
        cells.erase(p);
    }
}

void grid::moveRight(int x, int y) {
    LinkedList<cell>::position p = cells.begin();
    cell c(x, y);
    while (cells.read(p) != c) {

        p = cells.next(p);
    }
    y++;
    c.setY(y);
    if (!cells.exists(c)) {
        cells.write(c, p);
    } else {
        cells.erase(p);
    }
}

void grid::moveUpper(int x, int y) {
    LinkedList<cell>::position p = cells.begin();
    cell c(x, y);
    while (cells.read(p) != c) {
        p = cells.next(p);
    }
    x++;
    c.setX(x);
    if (!cells.exists(c)) {
        cells.write(c, p);
    } else {
        cells.erase(p);
    }
}

void grid::moveDown(int x, int y) {
    LinkedList<cell>::position p = cells.begin();
    cell c(x, y);
    while (cells.read(p) != c) {

        p = cells.next(p);
    }
    x--;
    c.setX(x);
    if (!cells.exists(c)) {
        cells.write(c, p);
    } else {
        cells.erase(p);
    }
}



bool grid::surrounded(int x, int y) {
    int neighbour_counter = 0;
    LinkedList<cell>::position p = cells.begin();
    while (!cells.end(p)) {
        if (cells.read(p).getX() == x && cells.read(p).getY() == y) {
            neighbour_counter++;
        } else if (cells.read(p).getX() == x + 1 && cells.read(p).getY() == y) {
            neighbour_counter++;
        } else if (cells.read(p).getX() == x && cells.read(p).getY() == y + 1) {
            neighbour_counter++;
        } else if (cells.read(p).getX() == x && cells.read(p).getY() == y - 1) {
            neighbour_counter++;
        }
        p = cells.next(p);
    }
    if (neighbour_counter == 4) {
        return true;
    }
    return false;
}

void grid::print() {
    LinkedList<cell>::position p = cells.begin();
    while (!cells.end(p)) {
        cout << "X: " << cells.read(p).getX() << " Y: " << cells.read(p).getY() << endl;
        p = cells.next(p);
    }
    cout << endl;
}


#endif //GRID_GRID_H
