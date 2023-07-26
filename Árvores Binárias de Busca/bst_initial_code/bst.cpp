#include <iostream>
#include "bst.h"

using namespace std;

// Essa função recebe uma raiz e uma chave
// retorna nullptr se e somente se a key não estiver na árvore 
// retorna o ponteiro para o nó caso contrário.
Node *search (Node *node, int key) { 
    if (node == nullptr || node->key == key) {
        return node;
    }
    if (node->key < key) {
        return search(node->right, key);
    } else {
        return search(node->left, key);
    }
}

bool BST::contains(int key) {
    if (search(root, key) == nullptr) {
        return false;
    } else {
        return true;
    }
}