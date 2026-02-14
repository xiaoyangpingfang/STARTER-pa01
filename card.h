#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <string>
class Card {
private:
    char suit;   // 'c', 'd', 's', 'h'
    int value;   // 1–13 (a=1, j=11, q=12, k=13)
    int suitRank() const;   // helper for ordering
public:
    Card() : suit('c'), value(1) {}  // 添加默认构造函数
    Card(char s, const std::string& valStr);
    char getSuit() const;
    int getValue() const;
    bool operator<(const Card& other) const;
    bool operator>(const Card& other) const;
    bool operator==(const Card& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Card& card);
};
#endif
