#ifndef MYSTACK_h
#define MYSTACK_h

#include <cstdlib>
#include "mylinkedlist.h"

template<typename Type>
class MyStack {
    private:
        LinkedList<Type> list;

    public:
        bool empty() const;
        Type top() const;

        void push(Type const &);
        Type pop();
};

template<typename Type>
bool MyStack<Type>::empty() const {
    return list.empty();
}

template<typename Type>
Type MyStack<Type>::top() const {
    if (empty()) {
       //
    }
    return list.front();
}


template<typename Type>
void MyStack<Type>::push(Type const & e) {
    list.push_front(e);
}

template<typename Type>
Type MyStack<Type>::pop() {
    return list.pop_front();
}


#endif
