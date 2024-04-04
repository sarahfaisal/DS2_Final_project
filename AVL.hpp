#pragma once

template <typename Key, typename Data>
class AVLNode {
public:
    Key key;
    Data data;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(const Key& key, const Data& data);
};

template <typename Key, typename Data>
class AVLTree {
private:
    AVLNode<Key, Data>* root;

public:
    AVLTree();

    void Insert(const Key& key, const Data& data);

private:
    int Height(AVLNode<Key, Data>* node);
    int BalanceFactor(AVLNode<Key, Data>* node);
    AVLNode<Key, Data>* RotateRight(AVLNode<Key, Data>* y);
    AVLNode<Key, Data>* RotateLeft(AVLNode<Key, Data>* x);
    AVLNode<Key, Data>* Insert(AVLNode<Key, Data>* node, const Key& key, const Data& data);
};