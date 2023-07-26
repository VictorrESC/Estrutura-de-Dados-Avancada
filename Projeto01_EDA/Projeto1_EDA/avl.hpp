#ifndef AVL_HPP
#define AVL_HPP
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include "node.hpp"
#include "pessoa.hpp"

using namespace std;

template <typename T>
class avl_tree {
    private:
        Node<T> *root = nullptr;
        
        int height(Node<T> *node) {
            if (node == nullptr) {
                return 0;
            } else {
                return node->height;
            }
        }

        int balance(Node<T> *node) {
            return height(node->right) - height(node->left);
        }

        Node<T>* rightRotation(Node<T> *p) {
            Node<T> *u = p->left;
            p->left = u->right;
            u->right = p;
            // recalcular as alturas de p e de u
            p->height = 1 + max(height(p->right),height(p->left));
            u->height = 1 + max(height(u->left),height(u->right));
            return u;
        }

        Node<T>* leftRotation(Node<T> *p) {
            Node<T> *u = p->right;
            p->right = u->left;
            u->left = p;
            // recalcular as alturas de p e de u
            p->height = 1 + max(height(p->right),height(p->left));
            u->height = 1 + max(height(u->left),height(u->right));
            return u;
        }

        Node<T>* add(Node<T> *p, T key, Person *pessoa) {
            if (p == nullptr) {
                return new Node<T>(key, nullptr, nullptr, 1, pessoa, nullptr);
            }
            if (key <= p->key) {
                p->left = add(p->left, key, pessoa);
            } else {
                p->right = add(p->right, key, pessoa);
            } 

            p = fixup_node(p, key);                                        

            return p;
        }

        Node<T>* fixup_node(Node<T> *p, T key) {
            p->height = 1 + max(height(p->left), height(p->right));
            int bal = balance(p);

            if (bal >= -1 && bal <= 1) { 
                return p;
            }
            if (bal < -1 && key < p->left->key) {        // {
                p = rightRotation(p);                   // | caso 1 (a) rotação direita
            } else if (bal < -1 && key > p->left->key) { // }{
                p->left = leftRotation(p->left);        // | caso 1 (b) rotação dupla direita
                p = rightRotation(p);                   // |
            } else if (bal > 1 && key > p->right->key) { // }{
                p = leftRotation(p);                    // | caso 2 (a) rotação esquerda
            } else if (bal > 1 && key < p->right->key) { // }{
                p->right = rightRotation(p->right);     // | caso 2 (b) rotação dupla esquerda
                p = leftRotation(p);                    // }
            }                                           

            return p;
        }

        void bshow(Node<T> *node, std::string heranca) const {
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
        
        Node<T>* clear(Node<T> *node) {
            if(node != nullptr) {
                node->left = clear(node->left);
                delete node;
                node->right = clear(node->right);
            }
            return nullptr;
        }

        Node<T>* remove(Node<T> *node, T key) {
            if(node == nullptr) // node nao encontrado
                return nullptr; /*L\pauseL*/
            if(key < node->key) 
                node->left = remove(node->left, key);
            else if(key > node->key)
                node->right = remove(node->right, key); /*L\pauseL*/
            // encontramos no node
            else if(node->right == nullptr) { // sem filho direito
                Node<T> *child = node->left;
                delete node;
                return child;
            }
            else // tem filho direito: troca pelo sucessor
                node->right = remove_successor(node, node->right); /*L\pauseL*/
            // Atualiza a altura do node e regula o node

            node = fixup_deletion(node); 

            return node;
        }

        Node<T>* remove_successor(Node<T> *root, Node<T> *node) {
            if(node->left != nullptr)
                node->left = remove_successor(root, node->left);
            else {
                root->key = node->key;
                Node<T> *aux = node->right;
                delete node;
                return aux;
            }
            // Atualiza a altura do node e regula o node

            node = fixup_deletion(node);

            return node;
        }

        Node<T>* fixup_deletion(Node<T> *node) {
            node->height = 1 + max(height(node->left),height(node->right));
            int bal = balance(node);

            // node pode estar desregulado, ha 4 casos a considerar
            if(bal > 1 && balance(node->right) >= 0) {
                return leftRotation(node);
            }
            else if(bal > 1 && balance(node->right) < 0) {
                node->right = rightRotation(node->right);
                return leftRotation(node);
            }
            else if(bal < -1 && balance(node->left) <= 0) {
                return rightRotation(node);
            }
            else if(bal < -1 && balance(node->left) > 0) { 
                node->left = leftRotation(node->left);
                return rightRotation(node);
            }
            return node;
        } 

        void _searchCPF(Node<T> *node, string key) const {
            Node<T> *aux = node;
            while (aux != nullptr) {
                if (key == aux->key.getCpf()) {
                    cout << "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫" << endl;
                    aux->pessoa->print();
                    cout << "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫" << endl;
                    return;
                }
                else {
                    if (key < aux->key.getCpf()) {
                        aux = aux->left;
                    }
                    else {
                        aux = aux->right;
                    }
                }
            }
            cerr << "CPF não encontrado" << endl;
            /*
                Explicação de toda a função:

                Primeiro, é criado um ponteiro auxiliar que aponta para o nó raiz da árvore.
                Depois, é feito um loop que vai até que o ponteiro auxiliar seja nulo.
                Dentro do loop, é feita uma comparação entre a chave passada como parâmetro e a chave do nó atual.
                Se as chaves forem iguais, é impresso o nó atual e a função é encerrada.
                Se as chaves forem diferentes, é feita uma comparação entre as chaves.
                Se a chave passada como parâmetro for menor que a chave do nó atual, o ponteiro auxiliar passa a apontar para o filho esquerdo do nó atual, senão, o ponteiro auxiliar passa a apontar para o filho direito do nó atual.
                Se o ponteiro auxiliar for nulo, é impresso uma mensagem de erro e a função é encerrada.
            */
        }

        void _searchNome(Node<T> *node, string key) const {
            if (node == nullptr) {
                return;
            }
            _searchNome(node->left, key);
            if (isSubstringNome(node->key.getNome(), key)) {
                cout << "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫" << endl;
                node->pessoa->print();
                cout << "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫" << endl;
            }
            _searchNome(node->right, key);

            /*
                Explicação de toda a função:

                Primeiro, é feita uma verificação se o nó atual é nulo.
                Se for, a função é encerrada.
                Se não for, é feita uma chamada recursiva para o filho esquerdo do nó atual.
                Depois, é feita uma comparação entre a chave passada como parâmetro e a chave do nó atual.
                Se a chave passada como parâmetro for uma substring da chave do nó atual, é impresso o nó atual.
                Depois, é feita uma chamada recursiva para o filho direito do nó atual.

                Essa recursão é feita em ordem, ou seja, primeiro o filho esquerdo, depois o nó atual e depois o filho direito.
            */
        }

        bool isSubstringNome(const std::string str, const std::string& substr) const {
            return (str.substr(0, substr.size()) == substr);

            /*
                Utilizo a função substr para extrair uma subcadeia de caracteres de str que tenha o mesmo tamanho que substr. Em seguida, comparamos essa subcadeia com substr.
                Essa comparação verifica se a subcadeia extraída de str é igual à substr. Se forem iguais, a função retorna true; caso contrário, retorna false.
                Essa função verifica se substr está presente no início de str, comparando as duas cadeias de caracteres diretamente.
            */
        }

        void _searchData(Data inicio, Data final, Node<T> *node) const {
            if(node == nullptr) {
                return;
            }
            _searchData(inicio, final, node->left);
            if (node->key.getData() >= inicio && node->key.getData() <= final) {
                cout << "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫" << endl;
                node->pessoa->print();
                cout << "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫" << endl;
            }
            _searchData(inicio, final, node->right);

            /*
                Explicação dafunção:
                
                A lógica se dá de forma semelhante à função de busca por nome. A diferença é que, ao invés de comparar substrings, é feita uma comparação entre as datas piso e teto.
            */
        }

        Node<T>* clone_rec(Node<T> *node) {
            if(node == nullptr)
                return nullptr;
            else {
                Node<T> *aux = new Node<T>(node->key);
                aux->left = clone_rec(node->left);
                aux->right = clone_rec(node->right);
                return aux;
            }
        }

        int size_rec(Node<T> *node) {
            if(node == nullptr)
                return 0;
            else
                return 1 + size_rec(node->left) + size_rec(node->right);
        }

    public:

        avl_tree() = default;
        avl_tree(const avl_tree& t) {
            this->root = clone_rec(t.root);
        }
        avl_tree<T>& operator=(const avl_tree& t) {
            if(this != &t) {
                clear();
                this->root = clone_rec(t.root);
            }
            return *this;
        }

        avl_tree<T>& operator==(const avl_tree& t) {
            return equals_rec(this->root, t.root);
        }

        int height() {
            return root->height;
        }
        
        void bshow() const {
            bshow(root, "");
        }

        ~avl_tree() {
            clear();
        }

        void add(T key, Person* pessoa) {
            root = add(root, key, pessoa);
        }                               
        
        void clear() {
            root = clear(root);
        }                                  
        
        void remove(T key) {
            root = remove(root, key);
        } 

        int size() {
            return size_rec(root);
        } 

        void searchCPF(std::string key) {
            _searchCPF(root, key);
        }

        void searchNome(std::string key) {
            _searchNome(root, key);
        }

        void searchData(Data data_inicio, Data data_fim) {
            _searchData(data_inicio, data_fim, root);
        }   
};


#endif