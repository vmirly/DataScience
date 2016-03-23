#ifndef SIMPLETREE_h
#define SIMPLETREE_h

#include <cstdlib>
#include "mylinkedlist.h"

template<typename Type>
class SimpleTree {
    private:
        Type _element;
        SimpleTree *_parent;
        LinkedList<SimpleTree *> _children;

    public:
        SimpleTree(Type const & = Type(), SimpleTree * = nullptr);

        Type retrieve() const;
        SimpleTree *parent() const;
        int degree() const;
        bool isroot() const;
        bool isleaf() const;
        SimpleTree *child(int n) const;
        int size() const;
        int height() const;

        void insert(Type const &);
        void attach(SimpleTree *);
        void detach();


        // tree traversal algorithms
        void depth_first_traversal() const;
        void breath_first_traversal() const;
        void print_hierarchy(int) const;
};

template<typename Type>
SimpleTree<Type>::SimpleTree(Type const &obj, SimpleTree *p):
        _element(obj),
        _parent(p) {
    // empty constructor
}

template<typename Type>
Type SimpleTree<Type>::retrieve() const {
    return _element;
}

template<typename Type>
SimpleTree<Type>* SimpleTree<Type>::parent() const {
    return _parent;
}

template<typename Type>
int SimpleTree<Type>::degree() const {
    return _children.size();
}

template<typename Type>
bool SimpleTree<Type>::isroot() const {
    return (parent() == nullptr);
}

template<typename Type>
bool SimpleTree<Type>::isleaf() const {
    return (degree() == 0);
}

template<typename Type>
SimpleTree<Type>* SimpleTree<Type>::child(int n) const {
    if(n<0 || n>=degree()) {
        return nullptr;
    }

    Node<SimpleTree *> *ptr = _children.head();
    for(int i=1; i<n; ++i) {
        ptr = ptr->next();
    }

    return ptr->retrieve();
}

template<typename Type>
int SimpleTree<Type>::size() const {
    int s = 1;
    
    for (Node<SimpleTree *> *ptr = _children.head();
         ptr != nullptr;
         ptr = ptr->next()) {
       // body of for loop
       s += ptr->retrieve()->size();
    }
    return s;
}


template<typename Type>
int SimpleTree<Type>::height() const {
    int h = 0;
    for (Node<SimpleTree *> *ptr = _children.head();
         ptr != nullptr;
         ptr = ptr->next()) {
        // body of for loop
        h += std::max(h, 1 + ptr->retrieve()->height());
    }
    return h;
}


// Mutators
template<typename Type>
void SimpleTree<Type>::insert(Type const &obj) {
    _children.push_back(new SimpleTree(obj, this));
}

template<typename Type>
void SimpleTree<Type>::attach(SimpleTree *tree) {
    if (!tree->isroot()) {
        tree->detach();
    }
    tree->_parent = this;
    _children.push_back(tree);
}

template<typename Type>
void SimpleTree<Type>::detach() {
    if(isroot()) {
        return;
    }
    parent()->_children.erase(this);
    _parent = nullptr;
}


template<typename Type>
void SimpleTree<Type>::depth_first_traversal() const {
    for (Node<SimpleTree *> *ptr = _children.head();
         ptr != nullptr;
         ptr = ptr->next()) {
        ptr->retrieve()->depth_first_traversal();
    }
    std::cout << _element << " ";
}


template<typename Type>
void SimpleTree<Type>::breath_first_traversal() const {
    std::cout << _element << " ";
    for (Node<SimpleTree *> *ptr = _children.head();
         ptr != nullptr;
         ptr = ptr->next()) {
        ptr->retrieve()->breath_first_traversal();
    }
}

void print_spaces(int n) {
    for(int i=0; i<n; ++i) {
        std::cout << "-";
    }
}


template<typename Type>
void SimpleTree<Type>::print_hierarchy(int level) const {
    print_spaces(level);
    std::cout << _element << std::endl;
    for (Node<SimpleTree *> *ptr = _children.head();
         ptr != nullptr;
         ptr = ptr->next() ) {
        ptr->retrieve()->print_hierarchy(level + 1);
    }
}
#endif
