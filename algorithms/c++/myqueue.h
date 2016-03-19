#ifndef MYQUEUE_h
#define MYQUEUE_h

#include <cstdlib>
#include "mylinkedlist.h"

template<typename Type>
class MyQueue {
    private:
        LinkedList<Type> list;

    public:
        bool empty() const;
        Type top() const;

        void push(Type const &);
        Type pop();
};

template<typename Type>
bool MyQueue<Type>::empty() const {
    return list.empty();
}

template<typename Type>
Type MyQueue<Type>::top() const {
    if (empty()) {
       //
    }
    return list.front();
}


template<typename Type>
void MyQueue<Type>::push(Type const & e) {
    list.push_back(e);
}

template<typename Type>
Type MyQueue<Type>::pop() {
    return list.pop_front();
}


#endif
