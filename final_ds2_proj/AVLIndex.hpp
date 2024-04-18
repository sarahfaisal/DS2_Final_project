#ifndef AVLIndex_HPP
#define AVLIndex_HPP

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

template<typename KeyType, typename IndexType>
class AVLIndex {
public:
    struct Node {
        KeyType key;
        IndexType index;
        std::vector<IndexType> indices;
        int height;
        Node* left;
        Node* right;

        Node(const KeyType& k, IndexType idx) : key(k), index(idx), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    AVLIndex() : root(nullptr) {}

    void Add( const KeyType& key, const IndexType index) {
        root = Insert(root, index, key);
    }

    void PrintTree() {
        TraversePrint(root, 0);
    }

    Node* getRoot() {
        return root;
    }

    // Additional auxiliary methods
    int NodeCount(Node* node) {
        if (node == nullptr) return 0;
        return 1 + NodeCount(node->left) + NodeCount(node->right);
    }

    void UpdateHeight(Node* node) {
        node->height = 1 + std::max(Height(node->left), Height(node->right));
    }

    Node* BalanceNode(Node* node, const KeyType& key) {
        int balance = Balance(node);

        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rotateRight(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    int TreeDepth(Node* node) {
        if (node == nullptr) return 0;
        return 1 + std::max(TreeDepth(node->left), TreeDepth(node->right));
    }

    void ClearTree(Node* node) {
        if (node != nullptr) {
            ClearTree(node->left);
            ClearTree(node->right);
            delete node;
        }
    }

    int MaxDepth() {
        return TreeDepth(root);
    }

    Node* search(Node* node, const KeyType& key) {
        if (node == nullptr || node->key == key) {
            return node;
        }

        if (key < node->key) {
            return search(node->left, key);
        } else {
            return search(node->right, key);
        }
    }

    Node* searchKey(const KeyType& key) {
        return search(root, key);
    }

private:
    Node* Insert(Node* node, const IndexType index, const KeyType& key) {
        if (node == nullptr) {
            return new Node(key, index);
        }

        if (key < node->key) {
            node->left = Insert(node->left, index, key);
        } else if (key > node->key) {
            node->right = Insert(node->right, index, key);
        } else {
            node->indices.push_back(index);
            return node;
        }

        UpdateHeight(node);

        return BalanceNode(node, key);
    }

    int Height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int Balance(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return Height(node->left) - Height(node->right);
    }

    Node* rotateRight(Node* node) {
        Node* x = node->left;
        Node* y = x->right;

        x->right = node;
        node->left = y;

        UpdateHeight(node);
        UpdateHeight(x);

        return x;
    }

    Node* rotateLeft(Node* node) {
        Node* x = node->right;
        Node* y = x->left;

        x->left = node;
        node->right = y;

        UpdateHeight(node);
        UpdateHeight(x);

        return x;
    }

    void TraversePrint(Node* node, int indent) {
        if (node == nullptr) return;

        if (node->right) TraversePrint(node->right, indent + 4);

        std::cout << std::string(indent, ' ') << node->key << " (";
        for (IndexType idx : node->indices)  // Ensure printing all indices
            std::cout << idx << " ";
        std::cout << ")\n";

        if (node->left) TraversePrint(node->left, indent + 4);
    }
};
#endif // AVL_HPP
