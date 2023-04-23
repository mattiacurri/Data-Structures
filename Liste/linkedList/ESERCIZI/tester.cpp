#include <iostream>
#include "rating.h"

void testCases();

int main() {
    testCases();
    return 0;
}

void testCases() {
    recommender r;
    r.insert("u1", "p1", 1);
    r.insert("u1", "p3", 3);
    r.insert("u1", "p5", 4);
    r.insert("u2", "p1", 1);
    r.insert("u2", "p2", 3);
    r.insert("u2", "p3", 3);
    cout << r.meanUser("u2") << endl;
    cout << r.meanUser("u1") << endl;
    cout << r.meanItem("p1") << endl;
    cout << r.meanItem("p2") << endl;
    cout << r.meanItem("p3") << endl;
    cout << r.meanItem("p5") << endl;
    cout << r.rated("u1") << endl;
    cout << r.rated("u2") << endl;
    cout << r.common("u1", "u2") << endl;
    cout << r.common("u2", "u1") << endl;
    cout << r.commonEqual("u1", "u2");
}