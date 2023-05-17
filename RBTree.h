#pragma once
#include "timer.h"
#include "Structure.h"
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class UniversityRBTree {
    UniversityRBTreeNode* root;

public:
    UniversityRBTree();
    ~UniversityRBTree();

    void insert(UniversityStruct* element, string key);
    void remove(string institution);
    UniversityRBTreeNode* search(string institution, int method = 0);
    void print();
    void preOrder();
    void inOrder();
    void postOrder();
    void printTreeShape();


private:
    void leftRotate(UniversityRBTreeNode*& root, UniversityRBTreeNode* x);
    void rightRotate(UniversityRBTreeNode*& root, UniversityRBTreeNode* y);
    void destroy(UniversityRBTreeNode*& root);
    void insert(UniversityRBTreeNode*& root, UniversityRBTreeNode* node, string key);
    void insertBalance(UniversityRBTreeNode*& root, UniversityRBTreeNode* node);

    void remove(UniversityRBTreeNode*& root, UniversityRBTreeNode* node);
    void removeBalance(UniversityRBTreeNode*& root, UniversityRBTreeNode* node, UniversityRBTreeNode* parent);

    UniversityRBTreeNode* recursiveSearch(UniversityRBTreeNode* node, string institution) const;
    UniversityRBTreeNode* iterativeSearch(UniversityRBTreeNode* node, string institution) const;
    void print(UniversityRBTreeNode* node) const;
    void preOrderTraversal(UniversityRBTreeNode* tree) const;
    void inOrderTraversal(UniversityRBTreeNode* tree) const;
    void postOrderTraversal(UniversityRBTreeNode* tree) const;
    void displayInfo(UniversityRBTreeNode* tree) const;
    void setTextColor(const string& color = "WHITE");
    string getNodeColor(const UniversityRBTreeNode* node);
    void printRedBlackTree(UniversityRBTreeNode* node, const std::string& prefix, bool isLeft);
};

UniversityRBTree::UniversityRBTree() :root(nullptr) {}

UniversityRBTree::~UniversityRBTree() {
    destroy(root);
}

/*              |                               |
 *             <x>            left             <y>
 *            /   \         rotation          /   \
 *          <a>   <y>       ========>       <x>   <c>
 *               /   \                     /   \
 *             <b>   <c>                 <a>   <b>
 * */

void UniversityRBTree::leftRotate(UniversityRBTreeNode*& root, UniversityRBTreeNode* x) {
    UniversityRBTreeNode* y = x->rightChild;
    x->rightChild = y->leftChild;
    if (y->leftChild) y->leftChild->parent = x;

    y->parent = x->parent;
    if (!x->parent) root = y;
    else {
        if (x == x->parent->leftChild) x->parent->leftChild = y;
        else x->parent->rightChild = y;
    }
    y->leftChild = x;
    x->parent = y;
}

/*              |                               |
 *             <y>           right             <x>
 *            /   \         rotation          /   \
 *          <x>   <c>       ========>       <a>   <y>
 *         /   \                                 /   \
 *       <a>   <b>                             <b>   <c>
 * */

void UniversityRBTree::rightRotate(UniversityRBTreeNode*& root, UniversityRBTreeNode* y) {
    UniversityRBTreeNode* x = y->leftChild;
    y->leftChild = x->rightChild;
    if (x->rightChild) x->rightChild->parent = y;

    x->parent = y->parent;
    if (!y->parent) root = x;
    else {
        if (y == y->parent->rightChild) y->parent->rightChild = x;
        else y->parent->leftChild = x;
    }
    x->rightChild = y;
    y->parent = x;
}

void UniversityRBTree::insert(UniversityStruct* element, string key) {
    auto* newNode = new UniversityRBTreeNode(element, Red, nullptr, nullptr, nullptr);
    insert(root, newNode, key);
}

void UniversityRBTree::insert(UniversityRBTreeNode*& root, UniversityRBTreeNode* node, string key) {
    UniversityRBTreeNode* x = root;
    UniversityRBTreeNode* y = nullptr;

    if (key == "Institution") {
        while (x) {
            y = x;
            if (node->element->institution > x->element->institution) x = x->rightChild;
            else x = x->leftChild;
        }
        node->parent = y;
        if (y) {
            if (node->element->institution > y->element->institution) y->rightChild = node;
            else y->leftChild = node;
        }
        else root = node;
        node->color = Red;
        insertBalance(root, node);
    }
}

void UniversityRBTree::insertBalance(UniversityRBTreeNode*& root, UniversityRBTreeNode* node) {
    UniversityRBTreeNode* parent = node->parent;
    while (node != UniversityRBTree::root && parent->color == Red) {
        UniversityRBTreeNode* grandparent = parent->parent;
        if (grandparent->leftChild == parent) {
            UniversityRBTreeNode* uncle = grandparent->rightChild;
            if (uncle && uncle->color == Red) {     // case 4
                parent->color = Black;
                uncle->color = Black;
                grandparent->color = Red;
                node = grandparent;
                parent = node->parent;
            }
            else {    // case 5 & case 6
                if (parent->rightChild == node) {
                    leftRotate(root, parent);
                    swap(node, parent);
                }
                rightRotate(root, grandparent);
                grandparent->color = Red;
                parent->color = Black;
                break;
            }
        }
        else {
            UniversityRBTreeNode* uncle = grandparent->leftChild;
            if (uncle && uncle->color == Red) {
                grandparent->color = Red;
                parent->color = Black;
                uncle->color = Black;
                node = grandparent;
                parent = node->parent;
            }
            else {
                if (parent->leftChild == node) {
                    rightRotate(root, parent);
                    swap(parent, node);
                }
                leftRotate(root, grandparent);
                parent->color = Black;
                grandparent->color = Red;
                break;
            }
        }
    }
    root->color = Black;
}

void UniversityRBTree::remove(string institution) {
    UniversityRBTreeNode* deleteNode = recursiveSearch(root, institution);
    if (deleteNode) remove(root, deleteNode);
};

void UniversityRBTree::remove(UniversityRBTreeNode*& root, UniversityRBTreeNode* node) {
    UniversityRBTreeNode* child;
    UniversityRBTreeNode* parent;
    RBTColor color;

    // The left and right nodes of the deleted node are not empty (not leaf nodes)
    if (node->leftChild && node->rightChild) {
        UniversityRBTreeNode* replace = node;
        // Find the successor node (the left node at the bottom of the right subtree of the current node)
        replace = node->rightChild;
        while (replace->leftChild) replace = replace->leftChild;
        // The deleted node is not the root node
        if (node->parent) {
            if (node->parent->leftChild == node) node->parent->leftChild = replace;
            else node->parent->rightChild = replace;
        }
        else root = replace;    // The deleted node is the root node

        // child is the right node that replaces the node, and it is the node that needs to be adjusted later
        // Because replace is a successor node, it is impossible for him to have a left child node
        // Similarly, the predecessor node cannot have a right child node
        child = replace->rightChild;
        parent = replace->parent;
        color = replace->color;

        // The case where the deleted node is the parent node of the replacement node (replace)
        if (parent == node) parent = replace;
        else {
            // child exist
            if (child) child->parent = parent;
            parent->leftChild = child;
            replace->rightChild = node->rightChild;
            node->rightChild->parent = replace;
        }
        replace->parent = node->parent;
        replace->color = node->color;
        replace->leftChild = node->leftChild;
        node->leftChild->parent = replace;
        if (color == Black) removeBalance(root, child, parent);
        cout << "Removing " << node->element->institution << "!!!" << endl;
        delete node;
        return;
    }

    // When only the left (right) node of the deleted node is empty, find the child node of the deleted node
    if (node->leftChild) child = node->leftChild;
    else child = node->rightChild;
    parent = node->parent;
    color = node->color;
    if (child) child->parent = parent;
    if (parent) {
        if (node == parent->leftChild) parent->leftChild = child;
        else parent->rightChild = child;
    }
    else UniversityRBTree::root = child;

    if (color == Black) removeBalance(root, child, parent);
    if (node) cout << "Removing " << node->element->institution << "!!!" << endl;
    delete node;
}

void UniversityRBTree::removeBalance(UniversityRBTreeNode*& root, UniversityRBTreeNode* node, UniversityRBTreeNode* parent) {
    UniversityRBTreeNode* sibling;
    while ((!node) || node->color == Black && node != UniversityRBTree::root) {
        if (parent->leftChild == node) {
            sibling = parent->rightChild;
            if (sibling->color == Red) {
                sibling->color = Black;
                leftRotate(root, parent);
                sibling = parent->rightChild;
            }
            else {
                if (!(sibling->rightChild) || sibling->rightChild->color == Black) {
                    sibling->leftChild->color = Black;
                    sibling->color = Red;
                    rightRotate(root, sibling);
                    sibling = parent->rightChild;
                }
                sibling->color = parent->color;
                parent->color = Black;
                sibling->rightChild->color = Black;
                leftRotate(root, parent);
                node = root;
                break;
            }
        }
        else {
            sibling = parent->leftChild;
            if (sibling->color == Red) {
                sibling->color = Black;
                parent->color = Red;
                rightRotate(root, parent);
                sibling = parent->leftChild;
            }
            if ((!sibling->leftChild || sibling->leftChild->color == Black) &&
                (!sibling->rightChild || sibling->rightChild->color == Black)) {
                sibling->color = Red;
                node = parent;
                parent = node->parent;
            }
            else {
                if (!(sibling->leftChild) || sibling->leftChild->color == Black) {
                    sibling->rightChild->color = Black;
                    sibling->color = Red;
                    leftRotate(root, sibling);
                    sibling = parent->leftChild;
                }
                sibling->color = parent->color;
                parent->color = Black;
                sibling->leftChild->color = Black;
                rightRotate(root, parent);
                node = root;
                break;
            }
        }
    }
    if (node) node->color = Black;
}

UniversityRBTreeNode* UniversityRBTree::search(string institution, int method) {
    if (!method) return recursiveSearch(root, institution);
    else return iterativeSearch(root, institution);
}

UniversityRBTreeNode* UniversityRBTree::recursiveSearch(UniversityRBTreeNode* node, string institution) const {
    if (!node || node->element->institution == institution) return node;
    else {
        if (institution > node->element->institution) return recursiveSearch(node->rightChild, institution);
        else return recursiveSearch(node->leftChild, institution);
    }
}

UniversityRBTreeNode* UniversityRBTree::iterativeSearch(UniversityRBTreeNode* node, string institution) const {
    while (node && (node->element->institution != institution)) {
        if (institution < node->element->institution) node = node->leftChild;
        else node = node->rightChild;
    }
    return node;
}

void UniversityRBTree::preOrder() {
    if (!root)
        cout << "University data does not exist" << endl;
    else {
        preOrderTraversal(root);
    }
}

void UniversityRBTree::preOrderTraversal(UniversityRBTreeNode* tree) const {
    if (tree) {
        displayInfo(tree);
        preOrderTraversal(tree->leftChild);
        preOrderTraversal(tree->rightChild);
    }
}

void UniversityRBTree::inOrder() {
    if (!root)
        cout << "University data does not exist" << endl;
    else {
        inOrderTraversal(root);
    }
}



void UniversityRBTree::postOrder() {
    if (!root)
        cout << "University data does not exist" << endl;
    else {
        postOrderTraversal(root);
    }
}

void UniversityRBTree::inOrderTraversal(UniversityRBTreeNode* tree) const {
    if (tree) {
        inOrderTraversal(tree->leftChild);
        displayInfo(tree);
        inOrderTraversal(tree->rightChild);
    }
}

void UniversityRBTree::postOrderTraversal(UniversityRBTreeNode* tree) const {
    if (tree) {
        postOrderTraversal(tree->leftChild);
        postOrderTraversal(tree->rightChild);
        displayInfo(tree);
    }
}

void UniversityRBTree::displayInfo(UniversityRBTreeNode* tree) const {
    cout << std::left << setw(8) << tree->element->rank;
    cout << std::left << setw(55) << tree->element->institution;
    cout << std::left << setw(5) << tree->element->locationCode;
    cout << std::left << setw(10) << tree->element->location << endl;
}

void UniversityRBTree::destroy(UniversityRBTreeNode*& root) {
    if (!root) return;
    destroy(root->leftChild);
    destroy(root->rightChild);
    delete root;
    root = nullptr;
}

void UniversityRBTree::print() {
    if (!root) cout << "University data does not exist" << endl;
    else print(root);
}

void UniversityRBTree::print(UniversityRBTreeNode* node) const {
    if (!node) return;
    if (!node->parent)
        cout << std::left << setw(50) << node->element->institution << " (" << node->color << ") is root" << endl;
    else if (node->parent->leftChild == node)
        cout << std::left << setw(50) << node->element->institution << " (" << node->color << ") is " << node->parent->element->institution << "'s " << "left child" << endl;
    else cout << std::left << setw(50) << node->element->institution << " (" << node->color << ") is " << node->parent->element->institution << "'s " << "right child" << endl;
    print(node->leftChild);
    print(node->rightChild);
}

void UniversityRBTree::setTextColor(const string& color) {
    if (color == "BLUE") {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    }
    else if (color == "RED") {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
    }
    else if (color == "WHITE") {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
            FOREGROUND_GREEN | FOREGROUND_BLUE);//设置三色相加
    }
}

string UniversityRBTree::getNodeColor(const UniversityRBTreeNode* node) {
    if (node == nullptr) {
        setTextColor();
        return "B";
    }
    else if (node->color == RBTColor::Red) {
        setTextColor("RED");
        return "R";
    }
    else {
        setTextColor();
        return "B";
    }
}

void UniversityRBTree::printRedBlackTree(UniversityRBTreeNode* node, const string& prefix, bool isLeft) {
    if (node == nullptr)
        return;

    setTextColor("BLUE");

    cout << prefix;
    cout << (isLeft ? "├──" : "└──");

    cout << getNodeColor(node) << ":" << node->element->rank << endl;

    setTextColor("BLUE");

    const string newPrefix = prefix + (isLeft ? "│   " : "    ");
    printRedBlackTree(node->leftChild, newPrefix, true);
    printRedBlackTree(node->rightChild, newPrefix, false);
}

void UniversityRBTree::printTreeShape() {
    printRedBlackTree(root, "", true);
    setTextColor();
}