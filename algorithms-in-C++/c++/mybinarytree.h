#ifndef SIMPLETREE_h
#define SIMPLETREE_h

#include <cstdlib>
#include "mylinkedlist.h"

template<typename Type>
class BinaryNode {
    private:
        Type _element;
        BinaryNode *_left_tree;
        BinaryNode *_ritht_tree;

    public:
        BinaryNode(Type const & = Type());

        Type retrieve() const;
        BinaryNode *left() const;
        BinaryNode *right() const;

        bool isempty() const;
        bool isleaf() const;
        int size() const;
        int height() const;

        void clear(BinaryNode *&);

        // tree traversal algorithms
        void pre_order_traversal() const;
        void post_order_traversal() const;
        void in_order_traversal() const;
        void print(int) const;
};

template<typename Type>
BinaryNode<Type>::BinaryNode(Type const &obj):
        _element( obj ),
        _left_tree( nullptr ),
        _right_tree ( nullptr ) {
    // empty constructor
}

template<typename Type>
Type BinaryNode<Type>::retrieve() const {
    return _element;
}

template<typename Type>
BinaryNode<Type>* BinaryNode<Type>::left() const {
    return _left_tree;
}

template<typename Type>
BinaryNode<Type>* BinaryNode<Type>::right() const {
    return _right_tree;
}

template<typename Type>
bool BinaryNode<Type>::isempty() const {
    return (this == nullptr);
}

template<typename Type>
bool BinaryNode<Type>::isleaf() const {
    return (!isempty() && left()->isempty() && right()->isempty());
}


template<typename Type>
int BinaryNode<Type>::size() const {
    return isempty() ? 0 :
        1 + left()->size() + right()->size();
}


template<typename Type>
int BinaryNode<Type>::height() const {
    return isempty() ? -1 :
        1 + std::max(left()->height(), right()->height())
}

// traversals

template<typename Type>
void BinaryNode<Type>::in_order_traversal() const {
    if (isempty()) {
        return;
    }

    left()->in_order_traversal();
    std::cout << retrieve() << " ";
    right()->in_order_traversal();
}


// Mutators

template<typename Type>
void clear(BinaryNode *&ptr_to_this) {
    if (isempty()) {
        return;
    }

    left()->clear( );
}

#endif
