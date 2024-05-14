#pragma once
#include <fstream>
#include <iostream>
#include <string>
// Node Class
template <class T> class Node {
public:
    T data;
    Node* left;
    Node* right;
    int BalanceFactor;
    int height;

public:
    // Constructor
    Node() {
        left = nullptr;
        right = nullptr;
        BalanceFactor = 0;
        height = 0;
    }
};
// Binary Tree Class
template <class T> class Tree {
public:
    Node<T>* root;
    // Constructor
    Tree() : root(nullptr) {}

    // Depth function that also balances the tree
    int Depth(Node<T>* curr, Node<T>* parent) {
        if (curr == nullptr) {
            return 0;
        }
        int Ldepth = Depth(curr->left, curr);
        int Rdepth = Depth(curr->right, curr);
        curr->BalanceFactor = Ldepth - Rdepth;
        if (Ldepth > Rdepth) {
            // Left subtree is taller
            if (curr->BalanceFactor > 1) {
                // Check if it's a left-right rotation
                if (curr->left->BalanceFactor < 0) {
                    RotateLeftRight(parent, curr);
                }
                // Right rotation
                else {
                    RotateRight(parent, curr);
                }
            }
            curr->height = Ldepth + 1;
            return Ldepth + 1;
        }
        else {
            // Right subtree is taller
            if (curr->BalanceFactor < -1) {
                // Check if it's a right-left rotation
                if (curr->right->BalanceFactor > 0) {
                    RotateRightLeft(parent, curr);
                }
                // Left rotation
                else {
                    RotateLeft(parent, curr);
                }
            }
            curr->height = Rdepth + 1;
            return Rdepth + 1;
        }
    }
    // Rotate Right
    void RotateRight(Node<T>*& parent, Node<T>*& child) {
        Node<T>* newRoot = child->left;
        child->left = newRoot->right;
        newRoot->right = child;
        // Update parent's child pointer
        if (parent == nullptr) {
            // Child is the root
            root = newRoot;
        }
        else if (child == parent->left) {
            // Child is on parent left
            parent->left = newRoot;
        }
        else {
            // Child is on parent right
            parent->right = newRoot;
        }
    }
    // Rotate Left
    void RotateLeft(Node<T>*& parent, Node<T>*& child) {
        Node<T>* newRoot = child->right;
        child->right = newRoot->left;
        newRoot->left = child;
        // Update parent's child pointer
        if (parent == nullptr) {
            // Child is the root
            root = newRoot;
        }
        else if (child == parent->right) {
            // Child is on parent right
            parent->right = newRoot;
        }
        else {
            // Child is on parent left
            parent->left = newRoot;
        }
    }
    // Rotate Left Right
    void RotateLeftRight(Node<T>*& parent, Node<T>*& child) {
        RotateLeft(child, child->left);
        RotateRight(parent, child);
    }
    // Rotate Right Left
    void RotateRightLeft(Node<T>*& parent, Node<T>*& child) {
        RotateRight(child, child->right);
        RotateLeft(parent, child);
    }

    // Insert Recursive function
    void Insert(T item, Node<T>*& self) {
        //Empty tree
        if (root == nullptr) {
            root = new Node<T>;
            root->data = item;
        }
        // Checking for empty tree
        if (self == nullptr) {
            self = new Node<T>;
            self->data = item;
            //Balancing tree
            Depth(root, nullptr);
            return;
        }
        else {
            // Checking if item is less than current node
            if (item < self->data) {
                //Balancing tree
                Depth(self->left, self);
                return Insert(item, self->left);
            }
            // Checking if item is greater than current node
            else if (item > self->data) {
                //Balancing tree
                Depth(self->right, self);
                return Insert(item, self->right);
            }
        }
    }
    // Find function
    Node<T>* Find(T item, Node<T>*& self) {
        // Check for empty tree or item not found
        if (self == nullptr || self->data == item || root == nullptr) {
            return self;
        }
        // Go left
        if (item < self->data) {
            return Find(item, self->left);
        }
        // Go right
        if (item > self->data) {
            return Find(item, self->right);
        }
        return nullptr;
    }
    // Size
    int Size(Node<T>* self) {
        // Base case
        if (self == nullptr || root == nullptr) {
            return 0;
        }
        // Recursive case
        return 1 + Size(self->left) + Size(self->right);
    }
    // GetAllAscending function
    void GetAllAscending(Node<T>* self, Node<T>** arr, int& index) {
        if (self == nullptr) {
            return;
        }
        // Traverse left subtree
        GetAllAscending(self->left, arr, index);
        // Store current node in the array
        arr[index++] = self;
        // Traverse right subtree
        GetAllAscending(self->right, arr, index);
    }
    // GetAllDescending function
    void GetAllDescending(Node<T>* self, Node<T>** arr, int& index) {
        if (self == nullptr) {
            return;
        }
        // Traverse right subtree
        GetAllDescending(self->right, arr, index);
        // Store current node in the array
        arr[index++] = self;
        // Traverse left subtree
        GetAllDescending(self->left, arr, index);
    }
    void EmptyTree(Node<T>*& self) {
        if (self == nullptr) {
            return;
        }
        EmptyTree(self->left);
        EmptyTree(self->right);
        self = nullptr;
    }
    //Remove function
    Node<T>* Remove(T item, Node<T>*& self, Node<T>* parent = nullptr) {
        // Base case: empty tree
        if (self == nullptr) {
            return nullptr;
        }
        // Recursive cases
        if (item < self->data) {
            return Remove(item, self->left, self);
        }
        else if (item > self->data) {
            return Remove(item, self->right, self);
        }
        // Node is found
        else {
            // Node has no children
            if (self->left == nullptr && self->right == nullptr) {
                // Node is the root
                if (parent == nullptr) {
                    delete self;
                    root = nullptr;
                    return nullptr;
                }
                // Node is a left child
                else if (parent->left == self) {
                    delete self;
                    parent->left = nullptr;
                }
                // Node is a right child
                else {
                    delete self;
                    parent->right = nullptr;
                }
                return parent;
            }

            //Node has one child
            if (self->left == nullptr) {
                // Only right child
                Node<T>* temp = self->right;
                delete self;
                // Node is the root
                if (parent == nullptr) {
                    root = temp;
                }
                // Node is a left child
                else if (parent->left == self) {
                    parent->left = temp;
                }
                // Node is a right child
                else {
                    parent->right = temp;
                }
                return temp;
            }
            // Only left child
            else if (self->right == nullptr) {
                Node<T>* temp = self->left;
                delete self;
                // Node is the root
                if (parent == nullptr) {
                    root = temp;
                }
                // Node is a left child
                else if (parent->left == self) {
                    parent->left = temp;
                }
                // Node is a right child
                else {
                    parent->right = temp;
                }
                return temp;
            }
            //Node has two children
            //Find the inorder successor (smallest node in the right subtree)
            Node<T>* successorParent = self;
            Node<T>* successor = self->right;
            while (successor->left != nullptr) {
                successorParent = successor;
                successor = successor->left;
            }
            // Copy the successor's data to this node
            self->data = successor->data;

            // Remove the successor from the right subtree
            if (successorParent == self) {
                // Successor is the right child of this node
                self->right = successor->right;
            }
            else {
                // Successor is not the right child of this node
                successorParent->left = successor->right;
            }
            Node<T>* temp = successor;
            delete successor;
            return temp;
        }
        // Balance the tree after removal
        Depth(root, nullptr);
        return self;
    }
    //function used to see structure of the tree
    void printS(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        std::cout << node->data << "(";
        if (node->left != nullptr) {
            std::cout << node->left->data;
        }
        else {
            std::cout << "_";
        }
        std::cout << ",";
        if (node->right != nullptr) {
            std::cout << node->right->data;
        }
        else {
            std::cout << "_";
        }
        std::cout << ")\n";
        printS(node->left);
        printS(node->right);
    }
    // Destructor
    ~Tree() { EmptyTree(root); }
};