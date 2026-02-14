//card_lst.h
//Author: Xiaoyang Zhang
#ifndef CARD_LIST_H
#define CARD_LIST_H
#include "card.h"

class CardList {
private:
    struct Node {
        Card data;
        Node* left;
        Node* right;
        Node* parent;
        Node(const Card& c)
            : data(c), left(nullptr), right(nullptr), parent(nullptr) {}
    };
    Node* root;
    void insert(Node*& node, const Card& card, Node* parent = nullptr);
    bool contains(Node* node, const Card& card) const;
    Node* remove(Node* node, const Card& card);
    Node* findMin(Node* node) const;
    Node* findMax(Node* node) const;
    void printInOrder(Node* node) const;
    void printReverse(Node* node) const;
    void destroy(Node* node);

public:
    CardList();
    ~CardList();
    void insert(const Card& card);
    bool contains(const Card& card) const;
    void remove(const Card& card);
    void printInOrder() const;
    void printReverse() const;
    Card getSmallest() const;
    Card getLargest() const;
    bool isEmpty() const;

    // 正向迭代器
    class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* n = nullptr) : current(n) {}
        const Card& operator*() const { return current->data; }
        bool operator==(const Iterator& other) const { return current == other.current; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
        
        // 正向：++ 找后继（更大的）
        Iterator& operator++() {
            if (!current) return *this;
            if (current->right) {
                current = current->right;
                while (current->left) current = current->left;
            } else {
                Node* p = current->parent;
                while (p && current == p->right) { 
                    current = p; 
                    p = p->parent; 
                }
                current = p;
            }
            return *this;
        }
        
        // 反向：-- 找前驱（更小的）
        Iterator& operator--() {
            if (!current) return *this;
            if (current->left) {
                current = current->left;
                while (current->right) current = current->right;
            } else {
                Node* p = current->parent;
                while (p && current == p->left) { 
                    current = p; 
                    p = p->parent; 
                }
                current = p;
            }
            return *this;
        }
    };

    // 反向迭代器
    class ReverseIterator {
    private:
        Node* current;
    public:
        ReverseIterator(Node* n = nullptr) : current(n) {}
        const Card& operator*() const { return current->data; }
        bool operator==(const ReverseIterator& other) const { return current == other.current; }
        bool operator!=(const ReverseIterator& other) const { return current != other.current; }
        
        // 反向迭代器的 ++ 应该往更小的方向走（找前驱）
        ReverseIterator& operator++() {
            if (!current) return *this;
            if (current->left) {
                current = current->left;
                while (current->right) current = current->right;
            } else {
                Node* p = current->parent;
                while (p && current == p->left) { 
                    current = p; 
                    p = p->parent; 
                }
                current = p;
            }
            return *this;
        }
        
        // 反向迭代器的 -- 应该往更大的方向走（找后继）
        ReverseIterator& operator--() {
            if (!current) return *this;
            if (current->right) {
                current = current->right;
                while (current->left) current = current->left;
            } else {
                Node* p = current->parent;
                while (p && current == p->right) { 
                    current = p; 
                    p = p->parent; 
                }
                current = p;
            }
            return *this;
        }
    };

    // 正向迭代器方法
    Iterator begin() const;
    Iterator end() const;
    
    // 反向迭代器方法
    ReverseIterator rbegin() const;
    ReverseIterator rend() const;
};
#endif
