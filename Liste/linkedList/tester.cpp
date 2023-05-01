#include "linkedList.h"
#include <iostream>

using namespace std;

int main() {
    LinkedList<int> list1, list2;
    LinkedList<int>::position iter;

    int x;

    /* inserting three elements into the list list1 */
    x = 1;
    iter = list1.begin();
    list1.insert(x, iter);
    iter = list1.next(iter);
    x = 2;
    list1.insert(x, iter);
    iter = list1.next(iter);
    x = 3;
    list1.insert(x, iter);
    iter = list1.next(iter);
    x = 4;
    list1.insert(x, iter);
    iter = list1.begin();
    iter = list1.next(iter);
    list1.erase(iter);

    /* visualizing the list list1 */
    cout << "list1 = ";
    cout << list1;

    /* assigning the list list1 to the list list2.
     * Here we are using the operator =
     */
    list2 = list1;
    /* visualizing the list list2 */
    cout << "After list2 = list1, list2 = ";
    cout << list2;
    // throw exception PositionOutOfRange: cout << list2.read(-2);

    /* comparing for equality the lists list1 and list2 */
    if (list1 == list2)
        cout << "list1 == list2" << endl;
    else
        cout << "list1 != list2" << endl;

    /* erasing the first element from the list list2 */
    list2.erase(list2.begin());
    /* visualizing the list list2 */
    cout << "After erasing the first element, list2 = ";
    cout << list2;
    /* comparing for equality the lists list1 and list2 */
    if (list1 == list2)
        cout << "list1 == list2" << endl;
    else
        cout << "list1 != list2" << endl;

    // test metodo headInsert
    x = 7;
    list1.headInsert(x);
    cout << list1 << endl;

    // test metodo tailInsert
    x = 11;
    list2.tailInsert(x);
    cout << list2 << endl;

    // test costruttore di copia
    cout << list1.getLength() << endl;
    LinkedList<int> list3(list1);
    cout << list1.getLength() << endl;
    cout << list3.getLength() << endl;

    cout << "Lista 3: " << list3;

    // test metodo empty
    cout << boolalpha << list1.empty() << endl;
    LinkedList<int> list5;
    cout << boolalpha << list5.empty() << endl;

    list3.headErase();
    cout << "Lista 3 dopo headErase: " << list3 << endl;
    list3.headErase();
    cout << "Lista 3 dopo headErase: " << list3 << endl;
    list3.headErase();
    cout << "Lista 3 dopo headErase: " << list3 << endl;

    list3.tailErase();
    cout << "Lista 3 dopo tailErase: " << list3 << endl;

    list3.tailErase();
    cout << "Lista 3 dopo tailErase: " << list3 << endl;

    list3.tailErase();
    cout << "Lista 3 dopo tailErase: " << list3 << endl;

    list3.tailErase();
    cout << "Lista 3 dopo tailErase: " << list3 << endl;

}
