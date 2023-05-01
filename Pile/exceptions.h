#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>

// TODO: verificare se lasciare
class IndexOutOfBoundException : public std::exception {
private:
    std::string _msg;

public:
    IndexOutOfBoundException(std::size_t userIndex, std::size_t maxIndex, uint32_t codeLine, const char *fileName) {
        this->_msg = "IndexOutOfBound: Accesso con indice negativo o con indice superiore al massimo.\n";
        this->_msg += "Riga: " + std::to_string(codeLine) + "\n";
        this->_msg += "File: " + std::string(fileName) + "\n";
        this->_msg += "Il tuo indice: " + std::to_string(userIndex) + "\n";
        this->_msg += "L'indice minimo: 0\n";
        this->_msg += "L'indice massimo: " + std::to_string(maxIndex) + "\n";
    }

    const char *what() {
        return this->_msg.c_str();
    }
};

class EmptyStackException : public std::exception {
private:
    std::string msg;
public:
    EmptyStackException() {
        std::cout << "Stack vuoto" << std::endl;
    }
};

#endif