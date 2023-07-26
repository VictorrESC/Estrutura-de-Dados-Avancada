#ifndef NODE_HPP
#define NODE_HPP

struct Node {
    // atributos
    int key;
    int height;
    Node *left;
    Node *right;

    // Construtor
    Node (int key, Node *left, Node *right, int height = 1)
        : key(key), height(height), left(left), right(right)
    {
    }
};

#endif 
