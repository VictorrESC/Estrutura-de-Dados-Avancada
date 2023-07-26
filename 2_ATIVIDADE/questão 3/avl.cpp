#include <iostream>
#include <stack>
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

// função interativa privada que recebe uma raiz de arvore
// e uma chave e insere a chave na arvore se e somente se
// ela não for repetida. Claro, tem que deixar AVL novamente
Node* avl_tree::add(Node *p, int key) {
    stack<Node*> pilha; 
    Node *q = p;       
    while (q != nullptr) { 
        pilha.push(q);    
        if (key < q->key) { 
            q = q->left;  
        } else if (key > q->key) { 
            q = q->right; 
        } else { 
            return p; 
        }
    }
    q = new Node(key, nullptr, nullptr);
    if (pilha.empty()) { 
        return q; 
    }
    Node *r = pilha.top(); 
    pilha.pop(); 
    if (key < r->key) {
        r->left = q; 
    } else { 
        r->right = q; 
    }
    fixup_node(r, key);
    while (!pilha.empty()) { 
        q = r; 
        r = pilha.top(); 
        pilha.pop(); 
        if (key < r->key) { 
            r->left = q;
        } else { 
            r->right = q; 
        }
        r = fixup_node(r, key); 
    }
    return r;

    /*
    O algoritmo percorre a árvore procurando pelo nó em que o novo nó deve ser inserido. Ele faz isso descendo na árvore até chegar ao nó em questão, armazenando cada nó visitado em uma pilha. O número de nós visitados é proporcional à altura da árvore, que é logarítmica no número de nós n, em árvores balanceadas.

    Depois que o nó correto é encontrado, o novo nó é adicionado como um filho do nó correto e a função fixup_node é chamada para balancear a árvore. 

    Em seguida, a função percorre a pilha dos nós visitados, atualizando os fatores de balanceamento e rotacionando conforme necessário para manter a árvore balanceada. Cada nó é visitado apenas uma vez nesse processo. Portanto, a complexidade total do processo de ajuste é proporcional à altura da árvore, que é logarítmica em n em árvores balanceadas.

    Dessa forma, a complexidade total da função add é O(log n) em árvores balanceadas.
    */
}

// função privada interativa que recebe uma raiz de arvore
// e uma chave e retorna o nó que contém a chave ou nullptr
// se a chave não estiver na arvore
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