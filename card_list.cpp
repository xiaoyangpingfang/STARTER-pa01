//card_list.cpp
//Author:Xiaoyang Zhang
#include "card_list.h"
#include <iostream>
#include <stdexcept>

CardList::CardList() : root(nullptr) {}
CardList::~CardList() { destroy(root); }

void CardList::insert(const Card& card) { insert(root, card, nullptr); }

void CardList::insert(Node*& node, const Card& card, Node* parent) {
    if (!node) {
        node = new Node(card);
        node->parent = parent;
        return;
    }
    if (card < node->data)
        insert(node->left, card, node);
    else if (card > node->data)
        insert(node->right, card, node);
}

void CardList::destroy(Node* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

bool CardList::contains(const Card& card) const { return contains(root, card); }

bool CardList::contains(Node* node, const Card& card) const {
    if (!node) return false;
    if (card == node->data) return true;
    else if (card < node->data) return contains(node->left, card);
    else return contains(node->right, card);
}

CardList::Node* CardList::findMin(Node* node) const {
    while (node && node->left) node = node->left;
    return node;
}

CardList::Node* CardList::findMax(Node* node) const {
    while (node && node->right) node = node->right;
    return node;
}

void CardList::remove(const Card& card) { 
    root = remove(root, card); 
    if (root) root->parent = nullptr;
}

CardList::Node* CardList::remove(Node* node, const Card& card) {
    if (!node) return nullptr;
    
    if (card < node->data) {
        node->left = remove(node->left, card);
        if (node->left) node->left->parent = node;
        return node;
    }
    else if (card > node->data) {
        node->right = remove(node->right, card);
        if (node->right) node->right->parent = node;
        return node;
    }
    else {
        if (!node->left && !node->right) {
            delete node;
            return nullptr;
        }
        else if (!node->left) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (!node->right) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        else {
            Node* successor = findMin(node->right);
            node->data = successor->data;
            node->right = remove(node->right, successor->data);
            if (node->right) node->right->parent = node;
            return node;
        }
    }
}

void CardList::printInOrder() const { printInOrder(root); }
void CardList::printInOrder(Node* node) const {
    if (!node) return;
    printInOrder(node->left);
    std::cout << node->data << std::endl;
    printInOrder(node->right);
}

void CardList::printReverse() const { printReverse(root); }
void CardList::printReverse(Node* node) const {
    if (!node) return;
    printReverse(node->right);
    std::cout << node->data << std::endl;
    printReverse(node->left);
}

Card CardList::getSmallest() const {
    Node* n = findMin(root);
    if (!n) throw std::runtime_error("Tree empty");
    return n->data;
}

Card CardList::getLargest() const {
    Node* n = findMax(root);
    if (!n) throw std::runtime_error("Tree empty");
    return n->data;
}

bool CardList::isEmpty() const { return root == nullptr; }

// ================== 正向迭代器 ==================

CardList::Iterator CardList::begin() const {
    Node* n = root;
    if (!n) return Iterator(nullptr);
    while (n->left) n = n->left;
    return Iterator(n);
}

CardList::Iterator CardList::end() const { 
    return Iterator(nullptr); 
}

// ================== 反向迭代器 ==================

CardList::ReverseIterator CardList::rbegin() const {
    Node* n = root;
    if (!n) return ReverseIterator(nullptr);
    while (n->right) n = n->right;
    return ReverseIterator(n);
}

CardList::ReverseIterator CardList::rend() const { 
    return ReverseIterator(nullptr); 
}
