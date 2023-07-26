#ifndef NODE_HPP
#define NODE_HPP
#include "pessoa.hpp"
template <typename T>
struct Node {
    T key;
    int height;
    Node<T> *left;
    Node<T> *right;
    Person *pessoa;
    Node<T> *next;
    // Construtor
    Node (T key, Node<T> *left = nullptr, Node<T> *right = nullptr, int height = 1, Person *pessoa = nullptr, Node<T> *next = nullptr)
        : key(key), height(height), left(left), right(right), pessoa(pessoa), next(next)
    {
    }

    // sobrecarga de operadores
    bool operator<(const Node<T>& n) const {
        if (key < n.key) {
            return true;
        }
        return false;
    }

    bool operator>(const Node<T>& n) const {
        if (key > n.key) {
            return true;
        }
        return false;
    }

    bool operator==(const Node<T>& n) const {
        if (key == n.key) {
            return true;
        }
        return false;
    }

    bool operator!=(const Node<T>& n) const {
        if (key != n.key) {
            return true;
        }
        return false;
    }

};

#endif 
