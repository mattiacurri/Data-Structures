#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>

struct PositionOutOfRange : public std::out_of_range {
    PositionOutOfRange() : out_of_range(
        "Posizione non valida.") {};
};

/*struct FullSize : public std::invalid_argument {
    FullSize() : invalid_argument(
        "Dimensione massima raggiunta.") {};
};

struct RootExists : public std::domain_error {
    RootExists() : domain_error(
        "Radice giÃ  presente.") {};
};

struct EmptyTree : public std::domain_error {
    EmptyTree() : domain_error(
        "Albero vuoto.") {};
};

struct NodeExists : public std::domain_error {
    NodeExists() : domain_error(
        "Nodo giÃ  presente.") {};
};*/


#endif