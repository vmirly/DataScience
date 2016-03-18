//
//

#include <cstdlib>
#include <iostream>
#include <ctime>
#include "linked_list.h"


using namespace std;
int main() {
    LinkedList<int> mylist;

    cout << "push 5, 43, 31" << endl;
    mylist.push_front(5);
    mylist.push_front(43);
    mylist.push_front(31);
    mylist.push_front(43);
    mylist.push_front(13);
    mylist.push_front(5);
    mylist.push_front(43);

    cout << "size: " << mylist.size() << "   count(43): " << mylist.count(43) << endl;

    mylist.display();

    cout << "delete 5 ";
    mylist.erase(5) ;
    cout << mylist.size() << endl;
    mylist.display();

    cout << "   Pop: " << endl;
    int size = mylist.size();
    for(int i=0; i< size; i++) {
        cout << mylist.pop_front() << " ";
    }
    cout << endl;

    cout << "empty: " << mylist.empty() << endl;

    
}
