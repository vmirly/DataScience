//
//

#include <cstdlib>
#include <iostream>
#include <ctime>
#include "mytree.h"


using namespace std;
int main() {
    SimpleTree<int> tree(2);

    cout << "isroot?  " << tree.isroot()  << endl;
    cout << "isleaf?  " << tree.isleaf()  << endl;

    SimpleTree<int> t1;
    t1.insert(45);

    tree.attach(&t1);

    cout << tree.isroot() << " " << tree.isleaf() << " " << tree.height() << " " << tree.size() << endl;
}
