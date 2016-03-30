//
//

#include <cstdlib>
#include <iostream>
#include <ctime>
#include "mystack.h"


using namespace std;
int main() {
    MyStack<int> s;

    cout << "push 5, 43, 31" << endl;
    s.push(5);
    s.push(43);
    s.push(31);
    s.push(43);
    s.push(13);
    s.push(5);
    s.push(43);
 
    cout << "   Pop: " << endl;
    while(!s.empty()) {
        cout << s.pop() << " ";
    }
    cout << endl;

    cout << "empty: " << s.empty() << endl;

    
}
