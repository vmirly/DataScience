#ifndef CTREE_H
#define CTREE_H

#include <iostream> 
#include <queue>
#include <cstdlib>

using namespace std;


template<class T> 
class CTree{
    public:
        class Node{
            private:
                Node* _left_node;
                Node* _right_node;
                T member;
            public: 
                friend class CTree;
                Node();
                Node(const T&);
                ~Node();
                bool isempty() const;
                bool isleaf() const;
                bool isfull() const;
                Node* left() const;
                Node* right() const;
                const T& Data() const;
                const T& retrieve() const;
                const T& front() const;
                const T& back() const;
                int depth() const;
                Node* find(const T&) const;
                void pre_order_traversal(std::ostream &) const;
                void insert(const T&, Node *&);
                void erase(const T&, Node *&);
        };

        CTree();
        Node* root();

        void Insert(const T& );
        void Preorder(std::ostream &);
        const Node *Find(const T &) const;
        void RemoveNode(const T&);
        int GetDepth();
        void LevelOrderTraverse();

    private:
        Node* _root;
        int _depth;
        int _curr; // 
};

template<class T>
CTree<T>::Node::Node():
    _left_node(nullptr),
    _right_node(nullptr) {
      // empty costructor
   }

template<class T>
CTree<T>::Node::Node(const T& element):
    member(element),
    _left_node(nullptr),
    _right_node(nullptr) {
    // empty constructor
}

template<class T>
CTree<T>::Node::~Node(){ delete _left_node; delete _right_node; }

template<class T>
bool CTree<T>::Node::isempty() const {return (this == nullptr);}

template<class T>
bool CTree<T>::Node::isfull() const {return (!isempty() && !left()->isempty() && !right()->isempty());}

template<class T>
bool CTree<T>::Node::isleaf() const {return (!isempty() && left()->isempty() && right()->isempty());}

template<class T>
typename CTree<T>::Node* CTree<T>::Node::left() const {return _left_node;}

template<class T>
typename CTree<T>::Node* CTree<T>::Node::right() const {return _right_node;}

template<class T>
const T& CTree<T>::Node::Data() const { return member;}
template<class T>
const T& CTree<T>::Node::retrieve() const { return member;}

template<class T>
const T& CTree<T>::Node::front() const { return left()->isempty() ? retrieve() : left()->front();}

template<class T>
const T& CTree<T>::Node::back() const { return right()->isempty() ? retrieve() : right()->back();}

template<class T>
int CTree<T>::Node::depth() const {
    return (isempty() ? -1 : 1 + std::max(left()->depth(), right()->depth())); 
}

template<class T>
typename CTree<T>::Node* CTree<T>::Node::find(const T& data) const {
    if (data == retrieve()) {
        return this;
    } else if (data < retrieve()){
        return left()->find(data);
    } else {
        return right()->find(data);
    }
}

template<class T>
void CTree<T>::Node::pre_order_traversal(std::ostream &p_str) const {
    if (!isempty()) {
        p_str << member << " ";
        if (!left()->isempty()) left()->pre_order_traversal(p_str);
        if (!right()->isempty()) right()->pre_order_traversal(p_str);
    }
}

template<class T>
void CTree<T>::Node::insert(const T& data, CTree<T>::Node *& ptr_to_this){
    if (isempty() ) {
        ptr_to_this = new CTree<T>::Node(data);
    } else if (data < retrieve()) {
       left()->insert(data, _left_node);
    } else if (data > retrieve()) {
       right()->insert(data, _right_node);
    }
}

template<class T>
void CTree<T>::Node::erase(const T& data, CTree<T>::Node *& ptr_to_this) {
    if (isempty()) {
       return;
    } else if (data < retrieve()) {
       left()->erase(data, _left_node);
    } else if (data > retrieve()) {
       right()->erase(data, _right_node);
    } else {
       if ( isleaf() ) {         // leaf node
            delete this;
            ptr_to_this = nullptr;
       } else if ( isfull() ) {  // full node
            member = right()->front();
            right()->erase(retrieve(), _right_node);
       } else {                  // node having only one child
            ptr_to_this = (!left()->isempty()) ? left() : right();
            delete this;
       }
    }
}



/*******************************/
// CTree member functions
template<class T>
CTree<T>::CTree(){
    _root = nullptr;
    _depth = 0;
    _curr = 0;
}

template<class T>
typename CTree<T>::Node* CTree<T>::root() {
    return _root;
}

template<class T>
void CTree<T>::Insert(const T& data) {
    root()->insert(data, _root);
}

template<class T>
void CTree<T>::Preorder(std::ostream &p_str) {
    root()->pre_order_traversal(p_str);
}

template<class T>
const typename CTree<T>::Node * CTree<T>::Find(const T &t) const {
    return root()->find(t);
}

template<class T>
void CTree<T>::RemoveNode(const T&t) {
    root()->erase(t, _root);
}

template<class T>
int CTree<T>::GetDepth() {
    return root()->depth();
}

template<class T>
void CTree<T>::LevelOrderTraverse() {

}




/*** define Queue class ***/
/*   for breadth-first-traversal */
template<class T>
class List {
    public:
        class Node {
            friend class List;
            private:
                T _element;
                Node* _next_node;
            public:
                Node(const T& e = 0, Node *next=nullptr): _element(e), _next_node(next) {}
                T retrieve() const {return _element;}
                Node* next() const {return _next_node;}
        };

        List():_list_head(nullptr), _list_tail(nullptr) {}
        bool isempty() const {return (_list_head == nullptr);}
        Node* head() const {return _list_head;}
        Node* tail() const {return _list_tail;}
        T front() const {return head()->retrieve();}
        T back() const {return tail()->retrieve();}
        void push_front(const T& e) {
            Node *node = new Node(e, head());
            if (isempty()) _list_tail = node;
            _list_head = node;
        }
        void push_back(const T& e) {
            Node * ptr = tail();
            Node * node = new Node(e, nullptr);
            if (isempty()) 
                _list_head = node;
            _list_tail = node;
            if (ptr != nullptr) {
                ptr->_next_node = node;
            }
        }
        const T pop_front() {
            Node * ptr = head();
            T e = front();
            _list_head = head()->next();
            if (isempty()) _list_tail = nullptr;
            delete ptr;
            return e;
        }
    private:
        Node* _list_head;
        Node* _list_tail;
};

template<class T>
class Queue {
    private:
        List<T> *list;
    public:
        Queue() {list = new List<T>;}
        void push(const T & e) { list->push_back(e); }
        T pop() { return list->pop_front(); }
        
};





#endif // !CTREE_H
