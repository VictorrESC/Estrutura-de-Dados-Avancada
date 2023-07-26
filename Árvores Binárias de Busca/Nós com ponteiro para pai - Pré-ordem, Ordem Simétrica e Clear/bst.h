#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>
#include <stack>
using namespace std;

/******************************
 * Definicao do struct Node
 ******************************/
struct Node {
    int key;
    Node *left;
    Node *right;
    Node *parent;

    // Construtor
    Node(int k, Node* l = nullptr, Node* r = nullptr, Node* p = nullptr) {
        this->key = k;
        this->left = l;
        this->right = r;
        this->parent = p;
    }
    // Destrutor
    ~Node() {
        cout << "Node removed: " << this->key << endl;
    }
};

/***********************************
 * Declaracao da classe
 ***********************************/
class BST {
public:
    BST();
    BST(int k);
    void bshow();
    bool add(int k);
    void preorder();  // --> Implementar
    void inorder();   // --> Implementar
    void clear();     // --> Implementar
    ~BST();
private:
    Node *root;
    void bshow(Node *node, std::string heranca);
};

/***********************************
 * Implementacao da classe
 ***********************************/
BST::BST() {
    root = nullptr;
}
 
BST::BST(int k) {
    root = new Node(k);
}

void BST::bshow(){
    bshow(root, "");
}

void BST::bshow(Node *node, std::string heranca) {
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

BST::~BST() {
    clear();
}

// Funcao publica 'add'
// Esta funcao deve obrigatoriamente ser iterativa.
// Esta funcao adiciona um no com chave k na arvore e: 
// (1) devolve true em caso de sucesso;
// (2) devolve false caso contrario.
// Lembre-se que nao podem haver chaves repetidas na nossa arvore.
bool BST::add(int k) {
    //TODO: adicione aqui o codigo feito no primeiro exercicio
        if (root == nullptr) {
        root = new Node(k);
        return true;
    }
    Node *aux = root;
    Node *prev = root;
    while (aux != nullptr) {
        prev = aux;
        if (k < aux->key) {
            aux = aux->left;
        } else if (k > aux->key) {
            aux = aux->right;
        } else {
            return false;
        }
    }
    if (k < prev->key) {
        prev->left = new Node(k);
    } else {
        prev->right = new Node(k);
    }
    return true;
}

// Funcao publica 'preorder'
// Percorre os nos da arvore em pre-ordem imprimindo os 
// valores das chaves. Dica: use a estrutura de dados pilha (stack)
void BST::preorder() {
    std::stack<Node*> stack;
    if (root != nullptr) {
        stack.push(root);
    }
    while (!stack.empty()) {
        Node* node = stack.top();
        stack.pop();
        std::cout << node->key << " ";
        if (node->right != nullptr) {
            stack.push(node->right);
        }
        if (node->left != nullptr) {
            stack.push(node->left);
        }
    }
    std::cout << std::endl;
}

// Funcao publica 'inorder'
// Percorre os nos da arvore em ordem simetrica imprimindo os 
// valores das chaves. Dica: use a estrutura de dados pilha (stack)
void BST::inorder() {
    std::stack<Node*> stack;
    Node* node = root;
    while (node != nullptr || !stack.empty()) {
        while (node != nullptr) {
            stack.push(node);
            node = node->left;
        }
        node = stack.top();
        stack.pop();
        std::cout << node->key << " ";
        node = node->right;
    }
    std::cout << std::endl;
}

// Funcao publica 'clear'
// Libera todos os nos da arvore deixando ela vazia.
// Dica: use a estrutura de dados pilha (stack)
void BST::clear() {
    std::stack<Node*> stack;
    Node* node = root;
    while (node != nullptr || !stack.empty()) {
        while (node != nullptr) {
            stack.push(node);
            node = node->left;
        }
        node = stack.top();
        stack.pop();
        Node* right = node->right;
        delete node;
        node = right;
    }
    root = nullptr;
}

#endif 