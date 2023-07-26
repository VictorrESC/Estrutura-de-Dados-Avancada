#include <iostream>
#include "avl.h"

using namespace std;

int main () {
    system("chcp 65001 > nul");
    avl_tree *t1 = new avl_tree;
    avl_tree *t2 = new avl_tree;

    for (int i = 1; i <= 5; i++) {
        t1->add(i);
    }

    for (int i = 6; i <= 15; i++) {
        t2->add(i);
    }
    
    cout << "Árvore 1:" << endl;
    t1->bshow();
    cout << endl << "Árvore 2:" << endl;
    t2->bshow();

    avl_tree *t3 = t3->mergetree(*t1, *t2);
    cout << endl << "Árvore 3:" << endl;
    t3->bshow();
}