// card.cpp
// Author: Xiaoyang Zhang

#include "card.h"
#include <string>
#include <iostream>

Card::Card(char s, const std::string& valStr) {
    suit = s;

    if (valStr == "a")
        value = 1;
    else if (valStr == "j")
        value = 11;
    else if (valStr == "q")
        value = 12;
    else if (valStr == "k")
        value = 13;
    else
        value = std::stoi(valStr);
}

char Card::getSuit() const {
    return suit;
}

int Card::getValue() const {
    return value;
}

int Card::suitRank() const {
    if (suit == 'c') return 0;
    if (suit == 'd') return 1;
    if (suit == 's') return 2;
    return 3; // 'h'
}

bool Card::operator<(const Card& other) const {
    if (suitRank() != other.suitRank())
        return suitRank() < other.suitRank();

    return value < other.value;
}

bool Card::operator>(const Card& other) const {
    return other < *this;
}

bool Card::operator==(const Card& other) const {
    return suit == other.suit && value == other.value;
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << card.suit << " ";

    if (card.value == 1)
        os << "a";
    else if (card.value == 11)
        os << "j";
    else if (card.value == 12)
        os << "q";
    else if (card.value == 13)
        os << "k";
    else
        os << card.value;

    return os;
}

