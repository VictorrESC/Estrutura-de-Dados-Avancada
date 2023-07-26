#include <iostream>
#include <vector>
#include "node.h"
#include "avl.h"
using namespace std;

// retorna a altura do nó
//se a arvore for vazia ela tem altura 0
//caso contrario, retorna o valor que está no campo height
int avl_tree::height(Node *node) {
    return (node == nullptr) ? 0 : node->height;  
}

int avl_tree::balance(Node *node) {
    return height(node->right) - height(node->left);
}

Node* avl_tree::rightRotation(Node *p) {
    Node *u = p->left;
    p->left = u->right;
    u->right = p;
    // recalcular as alturas de p e de u
    p->height = 1 + max(height(p->left), height(p->right));
    u->height = 1 + max(height(u->left), height(u->right));
    return u;
}

Node* avl_tree::leftRotation(Node *p) {
    Node *u = p->right;
    p->right = u->left;
    u->left = p;
    // recalcular as alturas de p e de u
    p->height = 1 + max(height(p->left), height(p->right));
    u->height = 1 + max(height(u->left), height(u->right));
    return u;
}

// função pública que recebe uma chave e a insere
// somente se ela não for repetida
void avl_tree::add(int key) {
    root = add(root, key);
}

// função recursiva privada que recebe uma raiz de arvore
// e uma chave e insere a chave na arvore se e somente se
// ela não for repetida. Claro, tem que deixar AVL novamente
Node* avl_tree::add(Node *p, int key) {
    if (p == nullptr) {
        return new Node (key, nullptr, nullptr);
    }
    if (key == p->key) {
        return p;
    }
    if (key < p->key) {
        p->left = add(p->left, key);
    } else {
        p->right = add(p->right, key);
    }
    
    p = fixup_node(p, key);

    return p;
}

Node* avl_tree::fixup_node(Node *p, int key) {
    p->height = 1 + max(height(p->left), height(p->right));
    int bal = balance(p);

    if (bal >= -1 && bal <= 1) { 
        return p;
    }
    if (bal <-1 && key < p->left->key) {        // {
        p = rightRotation(p);                   // | caso 1 (a) rotação direita
    } else if (bal <-1 && key > p->left->key) { // }{
        p->left = leftRotation(p->left);        // | caso 1 (b) rotação dupla direita
        p = rightRotation(p);                   // |
    } else if (bal >1 && key > p->right->key) { // }{
        p = leftRotation(p);                    // | caso 2 (a) rotação esquerda
    } else if (bal >1 && key < p->right->key) { // }{
        p->right = rightRotation(p->right);     // | caso 2 (b) rotação dupla esquerda
        p = leftRotation(p);                    // }
    }                                           

    return p;
}

//inorder
void avl_tree::inorder(Node *node, vector<int>& keys) {
    if (node == nullptr) {
        return;
    }
    inorder(node->left, keys);
    keys.push_back(node->key);
    inorder(node->right, keys);
}

avl_tree *avl_tree::mergetree(avl_tree &t1, avl_tree &t2) {
     // Nova árvore
    avl_tree *newTree = new avl_tree();

    // Percorre as duas arvores em ordem simétrica e armazena as chaves em vetores
    vector<int> keys1, keys2;
    inorder(t1.root, keys1);
    inorder(t2.root, keys2);

    int i = 0, j = 0;
    while (i < keys1.size() && j < keys2.size()) {
        if (keys1[i] < keys2[j]) {
            newTree->root = add(newTree->root, keys1[i]);
            i++;
        } else {
            newTree->root = add(newTree->root, keys2[j]);
            j++;
        }
    }

    // Insere as chaves restantes da primeira árvore
    while (i < keys1.size()) {
        newTree->root = add(newTree->root, keys1[i]);
        i++;
    }

    // Insere as chaves restantes da segunda árvore
    while (j < keys2.size()) {
        newTree->root = add(newTree->root, keys2[j]);
        j++;
    }

    return newTree;

    /*
    O algoritmo de mesclagem de árvores AVL consiste em duas partes principais: a primeira parte envolve a criação de dois vetores ordenados contendo as chaves de cada árvore, respectivamente. A segunda parte envolve a mesclagem desses dois vetores em uma nova árvore AVL.

    A criação desses dois vetores pode ser feita em tempo linear, O(m+n), em que m e n são o número de nós nas duas árvores. Para isso, basta percorrer cada árvore em ordem simétrica e adicionar as chaves em um vetor. Isso é feito usando a função "inorder", que percorre a árvore em ordem simétrica em tempo O(m) ou O(n), dependendo do tamanho da árvore.

    A mesclagem dos dois vetores ordenados também pode ser feita em tempo linear, O(m+n), em que m e n são os tamanhos dos vetores. Para isso, basta percorrer os dois vetores simultaneamente e adicionar a menor chave na nova árvore AVL. Isso é feito usando um loop while que percorre os vetores e adiciona as chaves na nova árvore, usando a função "add" que tem complexidade O(log(n)) para inserir cada chave na nova árvore AVL.

    Portanto, o tempo total do algoritmo é O(m+n) para criar os vetores e O(m+n) para mesclá-los, resultando em uma complexidade de tempo O(m+n) para a mesclagem das duas árvores AVL.
    */
}

void avl_tree::clear() {
    root = clear(root);
}

Node *avl_tree::clear(Node *node) {
    if(node != nullptr) {
        node->left = clear(node->left);
        node->right = clear(node->right);
        delete node;
    }
    return nullptr;
}

avl_tree::~avl_tree() {
    clear();
}

void avl_tree::bshow() const {
    bshow(root, "");
}

void avl_tree::bshow(Node *node, std::string heranca) const {
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->right , heranca + "r");
    for(int i = 0; i < (int) heranca.size() - 1; i++)
        std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
    if(heranca != "")
        std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
    if(node == nullptr){
        std::cout << "#" << std::endl;
        return;
    }
    std::cout << node->key << std::endl;
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->left, heranca + "l");
}