#include <iostream>
#include "avl.h"

using namespace std;

int main () {
    system("chcp 65001 > nul");
    avl_tree t;

    for (int i = 0; i <= 25; i++) {
        t.add(i);
    }

    t.bshow();
}