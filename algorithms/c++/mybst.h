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

        TreeNode *root;

    public:

       BinarySearchTree();
       void insert(Comparable);
       void insert(TreeNode *&, Comparable);
};


template<typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree() {
    // empty constructor
}

template<typename Comparable>
void BinarySearchTree<Comparable>::insert(TreeNode * &tree, Comparable value) {
    if (!tree) {
        tree = new TreeNode(value, nullptr, nullptr);
        return;
    }

    if (tree->_element < value) 
        insert(tree->_left, value);
    else if(tree->_element > value) 
        insert(tree->_right, value);
    else
        ; // duplicate value: do nothing
}


template<typename Comparable>
void BinarySearchTree<Comparable>::insert(Comparable value) {
    insert(root, value);
}

#endif
