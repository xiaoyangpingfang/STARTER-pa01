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
    void validateHelper(Node* node, Node* expectedParent) const;

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
	void validate() const;  // 声明
    class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* n = nullptr) : current(n) {}
        const Card& operator*() const { return current->data; }
        bool operator==(const Iterator& other) const { return current == other.current; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
        Iterator& operator++(); // in-order
        Iterator& operator--(); // reverse
    };

    Iterator begin() const;
    Iterator end() const;
    Iterator rbegin() const;
    Iterator rend() const;
};

#endif

