#include <fstream>
#include "AVLTree.h"
using namespace std;



int main() {
    setlocale(0, "");

    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cout << "Ошибка при открытии файла" << endl;
        return 0;
    }

    string treeString;
    getline(inputFile, treeString);
    inputFile.close();

    BinaryTree tree;
    tree.parseTree(treeString);
    //tree.insert(5);
    //tree.insert(3);
    //tree.insert(7);
    //tree.insert(2);
    //tree.insert(4);

    tree.printInOrder(); // Output: 2 3 4 5 7

    cout << endl;

    AVLTree treeAVL;
    //treeAVL.insert(5);
    //treeAVL.insert(3);
    //treeAVL.insert(7);
    //treeAVL.insert(2);
    //treeAVL.insert(4);
    treeAVL.setTree(tree.root);

    treeAVL.printTree();

    return 0;
}