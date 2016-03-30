//
//

#include <cstdlib>
#include <iostream>
#include <ctime>
#include "mydeque.h"


using namespace std;
int main() {
    MyDeque<int> dq;

    cout << "push 5, 43, 31" << endl;
    dq.push_front(5);
    cout << dq.front() << dq.back();
    dq.push_back(43);
    dq.push_front(31);
    dq.push_back(43);
    cout << "front: " << dq.front() << " back: " << dq.back() << "  pop once: " << endl;
    
    cout << dq.pop_front() << endl;
    dq.push_front(13);
    dq.push_back(5);
    dq.push_front(43);
 
    cout << "   Pop: " << endl;
    while(!dq.empty()) {
        cout << dq.pop_front() << " ";
    }
    cout << endl;

    cout << "empty: " << dq.empty() << endl;

    
}
