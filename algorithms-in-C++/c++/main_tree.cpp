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
    SimpleTree<int> t2(7);
    t1.insert(45);
    t1.insert(33);
    t2.insert(77);
    t2.insert(79);

    tree.attach(&t1);
    tree.attach(&t2);

    cout << tree.isroot() << " " << tree.isleaf() << " " << tree.height() << " " << tree.size() << endl;



    tree.depth_first_traversal(); cout<<endl;
    tree.breadth_first_traversal(); cout<<endl << endl;

    tree.print_hierarchy(0);
}

