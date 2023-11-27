#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stack>
using namespace std;

struct NodeBinary {
    int data;
    NodeBinary* left;
    NodeBinary* right;

    NodeBinary(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    NodeBinary* root;

    BinaryTree() : root(nullptr) {}

    void insert(int value) {
        root = insertRecursive(root, value);
    }

    NodeBinary* insertRecursive(NodeBinary* current, int value) {
        if (current == nullptr) {
            return new NodeBinary(value);
        }

        if (value < current->data) {
            current->left = insertRecursive(current->left, value);
        }
        else if (value > current->data) {
            current->right = insertRecursive(current->right, value);
        }

        return current;
    }

    void printInOrder() {
        printf("Двочное лерево, обход центр лево право: ");
        printInOrderRecursive(root);
        printf("\n");
    }

    //string GetTreeData() {
    //    return GetTreeDataRecursive(root);
    //}

    //string GetTreeDataRecursive(NodeBinary* current) {
    //    if (current != nullptr) {
    //        printInOrderRecursive(current->right);
    //        printInOrderRecursive(current->left);
    //        return to_string(current->data);
    //    }
    //}

    void printInOrderRecursive(NodeBinary* current) {
        if (current != nullptr) {
            cout << current->data << " ";
            printInOrderRecursive(current->left);
            printInOrderRecursive(current->right);
        }
    }

    void parseTree(string str) {
        if (str.length() == 0) {
            this->root = NULL;
        }

        stack<NodeBinary*> st;
        NodeBinary* root = NULL;
        NodeBinary* temp = NULL;
        bool isLeftChild = false;
        short count = 0;
        for (int i = 0; i < str.length(); i++) {
            if (str[i] != ')' && !isdigit(str[i]) && str[i] != '(' && str[i] != ' ') {
                printf("Неправильные символы!");
                exit(-1);
            }
            else if (str[i] == '(') {
                if (!isdigit(str[i + 1])) {
                    printf("Не двоичное дерево!");
                    exit(-1);
                }
                count++;
            }
            else if (str[i] == ')') {
                count--;
            }
        }

        if (count != 0) {
            printf("Неправильно расставлены скобки!");
            exit(-1);
        }

        for (int i = 0; i < str.length(); i++) {
            if (str[i] == '(') {
                st.push(temp);
                isLeftChild = true;
            }
            else if (str[i] == ')') {
                st.pop();
            }
            else if (str[i] != ' ') {
                int num = 0;
                while (i < str.length() && isdigit(str[i])) {
                    num = num * 10 + (int)(str[i] - '0');
                    i++;
                }
                i--;
                temp = createNode(num);

                if (root == NULL) {
                    root = temp;
                }
                else {
                    if (isLeftChild) {
                        st.top()->left = temp;
                        isLeftChild = false;
                    }
                    else {
                        st.top()->right = temp;
                    }
                }
            }
        }
   
        this->root = root;
    }

    NodeBinary* createNode(int value) {
        NodeBinary* newNode = new NodeBinary(0);
        if (!newNode) {
            cout << "Ошибка при выделении памяти" << endl;
            return NULL;
        }
        newNode->data = value;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

};

