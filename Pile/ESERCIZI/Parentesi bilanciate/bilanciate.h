#include <iostream>
#include <algorithm>
#include "../../pilavt.h"

using std::string;
using std::cout;
using std::endl;

template<class T>
class Bilanciate {
public:
    void test(string s);


private:
    Stack_vt<T> S;

    bool isBalanced(char parenthesis, int &frequency1, int &frequency2);

    void fillStack(string s);

};

template<class T>
void Bilanciate<T>::test(string s) {
    fillStack(s);
    int i = s.length(), j = 0;
    int tonde = 0;
    int quadre = 0;
    int graffe = 0;
    bool bilanciata = true;
    char c;
    while (!this->S.empty() && bilanciata) {
        c = this->S.peek();
        this->S.pop();
        switch (c) {
            case ')':
                tonde--;
                j = i + 1;
                break;
            case '(':
                tonde++;
                break;
            case ']':
                quadre--;
                j = i + 1;
                break;
            case '[':
                quadre++;
                break;
            case '}':
                graffe--;
                j = i + 1;
                break;
            case '{':
                graffe++;
                break;
            default:
                break;
        }
        if (tonde > 0 || quadre > 0 || graffe > 0) {
            bilanciata = false;
        } else {
            i--;
            j++;
        }
    }
    if (tonde < 0 || quadre < 0 || graffe < 0) {
        bilanciata = false;
    }
    if (bilanciata) {
        cout << "La stringa " << s << " e' bilanciata" << endl;
    } else {
        cout << "La stringa " << s << " non e' bilanciata -> ";
        if (tonde > 0)
            cout << "PARANTESI TONDA APERTA SENZA CHIUDERE IN POSIZIONE " << i << endl;
        else if (quadre > 0)
            cout << "PARANTESI QUADRA APERTA SENZA CHIUDERE IN POSIZIONE " << i << endl;
        else if (graffe > 0)
            cout << "PARANTESI GRAFFA APERTA SENZA CHIUDERE IN POSIZIONE " << i << endl;
        else if (tonde < 0)
            cout << "PARANTESI TONDA CHIUSA SENZA APRIRE IN POSIZIONE " << j << endl;
        else if (quadre < 0)
            cout << "PARANTESI QUADRA CHIUSA SENZA APRIRE IN POSIZIONE " << j << endl;
        else if (graffe < 0)
            cout << "PARANTESI GRAFFA CHIUSA SENZA APRIRE IN POSIZIONE " << j << endl;
    }
}

template<class T>
void Bilanciate<T>::fillStack(string s) {
    //std::reverse(s.begin(), s.end());
    //while (!S.empty()) {
    //this->S.pop();
    //}
    for (char &i: s) {
        this->S.push(i);
    }
}

