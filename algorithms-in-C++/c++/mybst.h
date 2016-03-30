#ifndef MYBST_H
#define BST_H

template<typename Comparable>
class BinarySearchTree {
    private:
        class TreeNode {
            friend class BinarySearchTree;
            Comparable  _element;
            TreeNode *_left;
            TreeNode *_right;

            TreeNode(Comparable value, TreeNode *left=nullptr, TreeNode *right=nullptr) {
                _element = value;
                _left = left;
                _right = right;
            }
        };

        TreeNode *root = nullptr;

    public:

       BinarySearchTree();

       void displayInOrder();
       void displayInOrder(TreeNode *);

       void insert(Comparable);
       void insert(Comparable, TreeNode *&);

};


template<typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree() {
    // empty constructor
}

template<typename Comparable>
void BinarySearchTree<Comparable>::insert(Comparable value, TreeNode * &tree) {
    if (!tree) {
        tree = new TreeNode(value, nullptr, nullptr);
        std::cout << "inserted " << value << std::endl;
        return;
    }

    if (value < tree->_element) 
        insert(value, tree->_left);
    else if(value > tree->_element) 
        insert(value, tree->_right);
    else
        ; // duplicate value: do nothing

}


template<typename Comparable>
void BinarySearchTree<Comparable>::insert(Comparable value) {
    insert(value, root);
}


template<typename Comparable>
void BinarySearchTree<Comparable>::displayInOrder(TreeNode *tree) {
    if (tree) {
        displayInOrder(tree->_left);
        std::cout << tree->_element << " ";
        displayInOrder(tree->_right);
    }
}

template<typename Comparable>
void BinarySearchTree<Comparable>::displayInOrder() {
    displayInOrder(root);
}

#endif
