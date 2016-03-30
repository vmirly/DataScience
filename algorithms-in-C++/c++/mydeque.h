#ifndef MYDEQUE_h
#define MYDEQUE_h

#include <cstdlib>
#include "mylinkedlist.h"

template<typename Type>
class MyDeque {
    private:
        LinkedList<Type> list;

    public:
        bool empty() const;
        Type front() const;
        Type back() const;

        void push_front(Type const &);
        void push_back(Type const &);
        Type pop_front();
        Type pop_back();
};

template<typename Type>
bool MyDeque<Type>::empty() const {
    return list.empty();
}

template<typename Type>
Type MyDeque<Type>::front() const {
    if (empty()) {
       //
    }
    return list.front();
}

template<typename Type>
Type MyDeque<Type>::back() const {
    if (empty()) {
       //
    }
    return list.back();
}

template<typename Type>
void MyDeque<Type>::push_front(Type const & e) {
    list.push_front(e);
}

template<typename Type>
void MyDeque<Type>::push_back(Type const & e) {
    list.push_back(e);
}

template<typename Type>
Type MyDeque<Type>::pop_front() {
    return list.pop_front();
}

template<typename Type>
Type MyDeque<Type>::pop_back() {
    return list.pop_back();
}


#endif
