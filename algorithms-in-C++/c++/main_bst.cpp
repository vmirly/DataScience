//
//

#include <cstdlib>
#include <iostream>
#include <ctime>
#include "mybst.h"


using namespace std;
int main() {
    BinarySearchTree<int> mytree;

    mytree.insert(5);
    mytree.insert(8);
    mytree.insert(12);
    mytree.insert(3);

    mytree.displayInOrder();
}
