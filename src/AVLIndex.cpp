#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#include<iomanip>
#define pow2(n) (1 << (n))
using namespace std;

struct Node {
   int d;
   struct Node *l;
   struct Node *r;
} *r;


//AVL tree
class avl_tree{
    public:
    avl_tree() {
        r = NULL;
    }

    int height(Node * tree) {
        int h = 0;
        if (tree != NULL) {
        int l_height = height(tree->l);
        int r_height = height(tree->r);
        int max_height = max(l_height, r_height);
        h = max_height + 1;
        }
        return h;
    }

    int difference(Node *t) {
    int l_height = height(t->l);
    int r_height = height(t->r);
    int b_factor = l_height - r_height;
    return b_factor;
    }
    Node *rr_rotat(Node *parent) {
    Node *t;
    t = parent->r;
    parent->r = t->l;
    t->l = parent;
    // cout<<"Right-Right Rotation";
    return t;
    
    }

    Node *ll_rotat(Node *parent) {
    Node *t;
    t = parent->l;
    parent->l = t->r;
    t->r = parent;
    // cout<<"Left-Left Rotation";
    return t;
    }
    Node *lr_rotat(Node *parent) {
    Node *t;
    t = parent->l;
    parent->l = rr_rotat(t);
    // cout<<"Left-Right Rotation";
    return ll_rotat(parent);
    }

    Node *rl_rotat(Node *parent) {
    Node *t;
    t = parent->r;
    parent->r = ll_rotat(t);
    // cout<<"Right-Left Rotation";
    return rr_rotat(parent);
    }

    Node *balance(Node *t) {
    int bal_factor = difference(t);
    if (bal_factor > 1) {
        if (difference(t->l) > 0)
            t = ll_rotat(t);
        else
            t = lr_rotat(t);
    } else if (bal_factor < -1) {
        if (difference(t->r) > 0)
            t = rl_rotat(t);
        else
            t = rr_rotat(t);
    }
    return t;
    }

    Node *insert(Node *r, int v) {
    if (r == NULL) {
        r = new Node;
        r->d = v;
        r->l = NULL;
        r->r = NULL;
        return r;
    } else if (v< r->d) {
        r->l = insert(r->l, v);
        r = balance(r);
    } else if (v >= r->d) {
        r->r = insert(r->r, v);
        r = balance(r);
    } return r;
    }

    void show(Node *p, int l) {
    int i;
    if (p != NULL) {
        show(p->r, l+ 1);
        cout<<" ";
        if (p == r)
            cout << "Root -> ";
        for (i = 0; i < l&& p != r; i++)
             cout << " ";
             cout << p->d;
            show(p->l, l + 1);
    }
    }

    void inorder(Node *t) {
    if (t == NULL)
        return;
        inorder(t->l);
        cout << t->d << " ";
        inorder(t->r);
    }

    void printTree(Node* root, int level = 0, char branch = '-')
    {
        if (root == nullptr)
            return;

        printTree(root->r, level + 1, '/');
        cout << setw(level * 4) << branch << root->d << endl;
        printTree(root->l, level + 1, '\\');
    }

    bool search(Node *r, int value) {
        if (r == nullptr) {
            return false; // Tree is empty, value not found
        }
        if (r->d == value) {
           // cout<<"found"<<endl;
            return true; // Value found
        }
        if (value < r->d) {
           // cout<<"left";
            return search(r->l, value); // Search in the left subtree
        } else {
           // cout<<"right";
            return search(r->r, value); // Search in the right subtree
        }
    }

    bool search(int value) {
        return search(r, value); // Start searching from the root node
    }
    void updateHeight(Node* node) {
        if (node != nullptr) {
            int l_height = height(node->l);
            int r_height = height(node->r);
            int h = max(l_height, r_height) + 1;
        }
    }

    Node* minValueNode(Node* node) {
        Node* current = node;

        // Loop down to find the leftmost leaf
        while (current->l != nullptr) {
            current = current->l;
        }

        return current;
    }

    Node* deleteNode(Node* root, int key) {
        if (root == nullptr) {
            return root; // Tree is empty or node not found
        }

        // Perform standard BST delete
        if (key < root->d) {
            root->l = deleteNode(root->l, key);
        } else if (key > root->d) {
            root->r = deleteNode(root->r, key);
        } else {
            // Node with only one child or no child
            if (root->l == nullptr) {
                Node* temp = root->r;
                delete root;
                return temp;
            } else if (root->r == nullptr) {
                Node* temp = root->l;
                delete root;
                return temp;
            }

            // Node with two children: Get the inorder successor (smallest in the right subtree)
            Node* temp = minValueNode(root->r);

            // Copy the inorder successor's content to this node
            root->d = temp->d;

            // Delete the inorder successor
            root->r = deleteNode(root->r, temp->d);
        }

        // If the tree had only one node then return
        if (root == nullptr) {
            return root;
        }

        // Update height of the current node
        updateHeight(root);

        // Get the balance factor of this node (to check whether this node became unbalanced)
        int balance = difference(root);

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && difference(root->l) >= 0) {
            return ll_rotat(root);
        }

        // Left Right Case
        if (balance > 1 && difference(root->l) < 0) {
            return lr_rotat(root);
        }

        // Right Right Case
        if (balance < -1 && difference(root->r) <= 0) {
            return rr_rotat(root);
        }

        // Right Left Case
        if (balance < -1 && difference(root->r) > 0) {
            return rl_rotat(root);
        }

        return root;
    }
};