#ifndef linkedlist_h
#define linkedlist_h

#include<cstdlib>

class Node {
    private:
         int element;
         Node *next_node;
    public:
         Node(int = 0, Node * = nullptr);

         int retrieve() const;
         Node *next() const();
}


Node::Node(int e, Node *n):
    element(e),
    next_node( n ) {
    //empty constructor
}


int Node::retrieve() const {
    return element;
}


Node *Node::next() const {
    return next_node;
}
#endif
