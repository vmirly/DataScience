#ifndef LINKEDLIST_h
#define LINKEDLIST_h

#include<cstdlib>

template<typename Type>
class Node {
    private:
         Type element;
         Node *next_node;
    public:
         Node(Type = NULL, Node * = nullptr);

         Type retrieve() const;
         Node *next() const;
};

template<typename Type>
Node<Type>::Node(Type e, Node *n):
    element(e),
    next_node( n ) {
    //empty constructor
}

template<typename Type>
Type Node<Type>::retrieve() const {
    return element;
}

template<typename Type>
Node<Type>* Node<Type>::next() const {
    return next_node;
}


/******************************/
/****** Class LinkedList ******/
template<typename Type>
class LinkedList {
    private:
        Node<Type> *list_head;

    public:
        LinkedList();
        //~List();

        // Accessors
        bool empty() const;
        int size() const;
        int count(Type) const;
        Type front() const;
        Node<Type> *head() const;

        // Mutators
        void push_front(Type);
        Type pop_front();
        int erase(Type);
};

template<typename Type>
LinkedList<Type>::LinkedList():
    list_head(nullptr) {
    // empty constructor
}

template<typename Type>
bool LinkedList<Type>::empty() const {
    return(list_head == nullptr);
}

template<typename Type>
Node<Type>* LinkedList<Type>::head() const {
    return list_head;
}

template<typename Type>
Type LinkedList<Type>::front() const {
    if (empty()) {
       // 
    }
    return head()->retrieve();
}

// Mutators
template<typename Type>
void LinkedList<Type>::push_front(Type e) {
    list_head = new Node<Type>(e, head());
}


template<typename Type>
Type LinkedList<Type>::pop_front() {
    if (empty()) {
        // 
    }

    Type e = front();
    Node<Type> *ptr = list_head;
    list_head = list_head->next();
    delete ptr;

    return e;
}


template<typename Type>
int LinkedList<Type>::size() const {
    int n = 0;
    for (Node<Type>* ptr=head(); ptr!=nullptr; ptr=ptr->next()) {
        ++n;
    }
    return n;
}


template<typename Type>
int LinkedList<Type>::count(Type e) const {
    int n = 0;
    for (Node<Type>*ptr = head(); ptr != nullptr; ptr=ptr->next()) {
        if (ptr->retrieve() == e) n++;
    }
    return n;
}

#endif
