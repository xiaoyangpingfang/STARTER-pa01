// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
//mainset.cpp
//Author Xiaoyang Zhang
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

int main(int argc, char** argv){
    if(argc < 3){
        cout << "Please provide 2 file names" << endl;
        return 1;
    }

    ifstream cardFile1(argv[1]);
    ifstream cardFile2(argv[2]);

    if (cardFile1.fail() || cardFile2.fail()){
        cout << "Could not open file" << endl;
        return 1;
    }

    set<Card> alice;
    set<Card> bob;

    char suit;
    string value;

    // Read Alice cards
    while (cardFile1 >> suit >> value){
        alice.insert(Card(suit, value));
    }

    // Read Bob cards
    while (cardFile2 >> suit >> value){
        bob.insert(Card(suit, value));
    }

    cardFile1.close();
    cardFile2.close();

    bool foundMatch = true;

    while (foundMatch) {
        foundMatch = false;

        // Alice turn (smallest first)
        for (auto it = alice.begin(); it != alice.end(); ++it) {
            if (bob.find(*it) != bob.end()) {
                cout << "Alice picked matching card " << *it << endl;
                bob.erase(*it);
                alice.erase(it);
                foundMatch = true;
                break;
            }
        }

        if (!foundMatch) break;

        foundMatch = false;

        // Bob turn (largest first)
        for (auto it = bob.rbegin(); it != bob.rend(); ++it) {
            if (alice.find(*it) != alice.end()) {
                cout << "Bob picked matching card " << *it << endl;
                alice.erase(*it);
                bob.erase(*it);
                foundMatch = true;
                break;
            }
        }
    }

    cout << endl;
    cout << "Alice's cards:" << endl;
    for (const auto& card : alice)
        cout << card << endl;

    cout << endl;
    cout << "Bob's cards:" << endl;
    for (const auto& card : bob)
        cout << card << endl;

    return 0;
}

