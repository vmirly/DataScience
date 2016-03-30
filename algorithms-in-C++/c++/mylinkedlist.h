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

         void setnext(Node*);
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

template<typename Type>
void Node<Type>::setnext(Node<Type>* ptr2next) {
    next_node = ptr2next;
}

/******************************/
/****** Class LinkedList ******/
template<typename Type>
class LinkedList {
    private:
        Node<Type> *list_head;
        Node<Type> *list_tail;

    public:
        LinkedList();
        //~List();

        // Accessors
        bool empty() const;
        int size() const;
        int count(Type) const;
        Type front() const;
        Type back() const;
        Node<Type> *head() const;
        Node<Type> *tail() const;
        void display() const;

        // Mutators
        void push_front(Type);
        void push_back(Type);
        Type pop_front();
        void erase(Type);
};

template<typename Type>
LinkedList<Type>::LinkedList():
    list_head(nullptr),
    list_tail(nullptr) {
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
Node<Type>* LinkedList<Type>::tail() const {
    return list_tail;
}

template<typename Type>
Type LinkedList<Type>::front() const {
    if (empty()) {
       // 
    }
    return head()->retrieve();
}

template<typename Type>
Type LinkedList<Type>::back() const {
    if (empty()) {

    }
    return tail()->retrieve();
}

// Mutators
template<typename Type>
void LinkedList<Type>::push_front(Type e) {
    Node<Type> *node = new Node<Type>(e, head());
    if(empty()) {
        list_tail = node;
    }
    list_head = node;
}


template<typename Type>
void LinkedList<Type>::push_back(Type e) {
    Node<Type>*ptr = tail();
    Node<Type> *node = new Node<Type>(e, nullptr);
    if(empty()) {
        list_head = node;
    }
    list_tail = node;

    if (ptr != nullptr) {
        ptr->setnext(list_tail);
    }
}


template<typename Type>
Type LinkedList<Type>::pop_front() {
    if (empty()) {
        // 
    }

    Type e = front();
    Node<Type> *ptr = list_head;
    list_head = list_head->next();
    if (empty()) list_tail = nullptr;
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


template<typename Type>
void LinkedList<Type>::erase(Type e) {
    Node<Type> * prev;
    for (Node<Type>* ptr=head(); ptr != nullptr; ptr=ptr->next()) {
        if(ptr->retrieve() == e) {
            if (ptr == list_head) {
                pop_front();
            }else{
                Node<Type> * pdel = ptr;
                if (pdel == tail()) {
                    list_tail = prev;
                }
                prev->setnext(ptr->next()); 
                ptr = prev;
                delete pdel;
            }
        }
        prev = ptr;
    }
}


template<typename Type>
void LinkedList<Type>::display() const {
    std::cout << std::endl;
    for (Node<Type>* ptr=head(); ptr != nullptr; ptr = ptr->next()) {
        std::cout << ptr->retrieve() << " ";
    }
    std::cout << std::endl;
}

#endif
