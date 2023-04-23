#include <iostream>
#include "eo_strings.h"

using std::string;
using std::cout;
using std::endl;

int main() {
    eo_strings stringhe;
    string a = "calamari";
    string b = "calamarataasasasa";
    string c = "calamarataaas";
    string d = "aad";
    stringhe.inserisci(b);
    stringhe.inserisci(a);
    stringhe.inserisci(c);
    stringhe.inserisci(d);
    // stringhe.rimuovi(a);
    stringhe.visualizza_dispari();

    return 0;
}
