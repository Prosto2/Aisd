#pragma once
#include <queue>
#include "Binarytree.h"
using namespace std;

class AVLNode {
public:
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class AVLTree {
private:
    AVLNode* root;

    int getHeight(AVLNode* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int getBalance(AVLNode* node) {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    void updateHeight(AVLNode* node) {
        if (node != nullptr) {
            node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        }
    }

    AVLNode* rotateRight(AVLNode* node) {
        AVLNode* newRoot = node->left;
        AVLNode* temp = newRoot->right;

        newRoot->right = node;
        node->left = temp;

        updateHeight(node);
        updateHeight(newRoot);

        return newRoot;
    }

    AVLNode* rotateLeft(AVLNode* node) {
        AVLNode* newRoot = node->right;
        AVLNode* temp = newRoot->left;

        newRoot->left = node;
        node->right = temp;

        updateHeight(node);
        updateHeight(newRoot);

        return newRoot;
    }

    AVLNode* balance(AVLNode* node) {
        updateHeight(node);

        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0) {
            return rotateRight(node);
        }
        if (balance < -1 && getBalance(node->right) <= 0) {
            return rotateLeft(node);
        }
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    AVLNode* insert(AVLNode* node, int value) {
        if (node == nullptr) {
            return new AVLNode(value);
        }

        if (value > node->data) {
            node->left = insert(node->left, value);
        }
        else if (value < node->data) {
            node->right = insert(node->right, value);
        }
        else {
            return node;
        }

        return balance(node);
    }

public:
    AVLTree() {
        root = nullptr;
    }

    void setTree(/*Node* currentAvl, */NodeBinary* currentBine) {
        if (currentBine != nullptr) {
            insert(currentBine->data);
            setTree(/*currentAvl->right, */currentBine->right);
            setTree(/*currentAvl->right, */currentBine->left);
        }
    }

    void insert(int value) {
        root = insert(root, value);
    }

    void printTree() {
        printf("Обход лево центр право: ");
        printTreeRecursiveLCR(root);
        printf("\n");
        printf("Обход центр лево право: ");
        printTreeRecursiveCLR(root);
        printf("\n");
        printf("Обход лево право центр: ");
        printTreeRecursiveLRC(root);
        printf("\n");
        printf("Обход в ширину: ");
        printTreeRecursiveBreadth(root);
        printf("\n");
    }

    void printTreeRecursiveBreadth(AVLNode* root) {
        if (root == nullptr)
            return;

        queue<AVLNode*> que;
        que.push(root);

        while (!que.empty()) {
            AVLNode* current = que.front();
            que.pop();

            std::cout << current->data << " ";

            if (current->left)
                que.push(current->left);

            if (current->right)
                que.push(current->right);

        }
    }

    void printTreeRecursiveCLR(AVLNode* root) {
        if (root != nullptr) {
            cout << root->data << " ";
            printTreeRecursiveCLR(root->left);
            printTreeRecursiveCLR(root->right);
        }
    }

    void printTreeRecursiveLRC(AVLNode* root) {
        if (root != nullptr) {
            printTreeRecursiveLRC(root->left);
            printTreeRecursiveLRC(root->right);
            cout << root->data << " ";
        }
    }

    void printTreeRecursiveLCR(AVLNode* root) {
        if (root != nullptr) {
            printTreeRecursiveLCR(root->left);
            cout << root->data << " ";
            printTreeRecursiveLCR(root->right);
        }
    }

    AVLNode* deleteNode(AVLNode* root, int key) {
        if (root == nullptr) {
            return root;
        }

        if (key < root->data) {
            root->left = deleteNode(root->left, key);
        }
        else if (key > root->data) {
            root->right = deleteNode(root->right, key);
        }
        else {
            if (root->left == nullptr || root->right == nullptr) {
                AVLNode* temp = root->left ? root->left : root->right;

                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                }
                else {
                    *root = *temp;
                }

                delete temp;
            }
            else {
                AVLNode* temp = minValueNode(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }
        }

        if (root == nullptr) {
            return root;
        }

        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0) {
            return rotateRight(root);
        }

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0) {
            return rotateLeft(root);
        }

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* current = node;

        while (current->left != nullptr) {
            current = current->left;
        }

        return current;
    }

};

