#include "AVL.hpp"
template <typename Key, typename Data>
AVLNode<Key, Data>::AVLNode(const Key& key, const Data& data) : key(key), data(data), height(1), left(nullptr), right(nullptr) {
}

template <typename Key, typename Data>
AVLTree<Key, Data>::AVLTree() : root(nullptr) {
}

template <typename Key, typename Data>
int AVLTree<Key, Data>::Height(AVLNode<Key, Data>* node) {
    if (node == nullptr) {
       return 0;
    }
    return node->height;
}

template <typename Key, typename Data>
int AVLTree<Key, Data>::BalanceFactor(AVLNode<Key, Data>* node) {
    if (node == nullptr) {
        return 0;
    }
    return Height(node->left) - Height(node->right);
}

template <typename Key, typename Data>
AVLNode<Key, Data>* AVLTree<Key, Data>::RotateRight(AVLNode<Key, Data>* y) {
    AVLNode<Key, Data>* x = y->left;
    AVLNode<Key, Data>* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = 1 + max(Height(y->left),Height(y->right));
    x->height = 1 + max(Height(x->left),Height(x->right));
    return x;
}

template <typename Key, typename Data>
AVLNode<Key, Data>* AVLTree<Key, Data>::RotateLeft(AVLNode<Key, Data>* x) {
    AVLNode<Key, Data>* y = x->right;
    AVLNode<Key, Data>* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = 1 + max(Height(x->left),Height(x->right));
    y->height = 1 + max(Height(y->left),Height(y->right));
    return y;
}

template <typename Key, typename Data>
AVLNode<Key, Data>* AVLTree<Key, Data>::Insert(AVLNode<Key, Data>* node, const Key& key, const Data& data) {
    if (node == nullptr) {
        return new AVLNode<Key, Data>(key, data);
    }
    if (key < node->key) {
        node->left = Insert(node->left, key, data);
    } else if (key > node->key) {
        node->right = Insert(node->right, key, data);
    }

    node->height = 1 + max(Height(node->left),Height(node->right));

    int balance = BalanceFactor(node);

    if (balance > 1 && key < node->left->key) {
        return RotateRight(node);
    }

    if (balance < -1 && key > node->right->key) {
        return RotateLeft(node);
    }

    if (balance > 1 && key > node->left->key) {
        node->left = RotateLeft(node->left);
        return RotateRight(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = RotateRight(node->right);
        return RotateLeft(node);
    }
    return node;
}

template <typename Key, typename Data>
void AVLTree<Key, Data>::Insert(const Key& key, const Data& data) {
    root = Insert(root, key, data);
}