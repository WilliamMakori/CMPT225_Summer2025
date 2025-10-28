#include "DynamicHeap.h"
#include <iostream>
using std::cout, std::cin, std::endl;

//A little test code followed by interactive testing with a heap
int main() {

    DynamicHeap* h = new DynamicHeap();
    cout << "Inserting 1 to 20" << endl;
    for (int i=1; i<=20; i++) {
        h->insert(i);
    }
    h->printHeap(cout);
    cout << "Removing Max 12 times" << endl;

    for (int i=0; i<12; i++) {
        h->removeMax();
    }
    h->printHeap(cout);
    cout << "One More Remove: Should Trigger CapacityReduction" << endl;
    h->removeMax();
    h->printHeap(cout);
    delete h;

    DynamicHeap* user = new DynamicHeap();
    int u = 0;
    
    while (true){
        cout << "Enter value to insert or 0 to remove max, anything negative to quit: ";
        cin >> u;
        if (u==0) {
            cout << user->removeMax() << " removed ";
        } else if (u>0) {
            user->insert(u);
        } else {
            break;
        }
        user->printHeap(cout);
    }
    delete user;

    return 0;
}
