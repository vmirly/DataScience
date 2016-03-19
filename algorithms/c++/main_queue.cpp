//
//

#include <cstdlib>
#include <iostream>
#include <ctime>
#include "myqueue.h"


using namespace std;
int main() {
    MyQueue<int> q;

    cout << "push 5, 43, 31" << endl;
    q.push(5);
    cout << q.top();
    q.push(43);
    q.push(31);
    q.push(43);
    cout << "top: " << q.top() << "  pop once: " << endl;
    
    cout << q.pop() << endl;
    q.push(13);
    q.push(5);
    q.push(43);
 
    cout << "   Pop: " << endl;
    while(!q.empty()) {
        cout << q.pop() << " ";
    }
    cout << endl;

    cout << "empty: " << q.empty() << endl;

    
}
