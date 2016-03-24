#ifndef MYBST_H
#define BST_H

template<typename Type>
class BinarySearchTree {
    private:
        class TreeNode {
            friend class BinarySearchTree;
            Type  _element;
            TreeNode *_left;
            TreeNode *_right;
        };
    public:
    
};

#endif
