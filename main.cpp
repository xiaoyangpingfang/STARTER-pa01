// main.cpp
// Author: Xiaoyang Zhang
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "card.h"
#include "card_list.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Please provide 2 file names" << endl;
        return 1;
    }

    CardList alice;
    CardList bob;

    ifstream cardFile1(argv[1]);
    ifstream cardFile2(argv[2]);

    if (cardFile1.fail() || cardFile2.fail()) {
        cout << "Could not open file(s)" << endl;
        return 1;
    }

    // Read Alice's cards
    string line;
    while (getline(cardFile1, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        char suit;
        string value;
        ss >> suit >> value;
        alice.insert(Card(suit, value));
    }
    cardFile1.close();

    // Read Bob's cards
    while (getline(cardFile2, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        char suit;
        string value;
        ss >> suit >> value;
        bob.insert(Card(suit, value));
    }
    cardFile2.close();

    // Game loop: Alice (smallest) -> Bob (largest)
    bool foundMatch = true;
    while (foundMatch) {
        foundMatch = false;

        // Alice's turn: pick smallest matching card
        if (!alice.isEmpty()) {
            Card smallest = alice.getSmallest();
            if (bob.contains(smallest)) {
                cout << "Alice picked matching card " << smallest << endl;
                alice.remove(smallest);
                bob.remove(smallest);
                foundMatch = true;
            }
        }

        if (!foundMatch) break; // No match, end game

        foundMatch = false;

        // Bob's turn: pick largest matching card
        if (!bob.isEmpty()) {
            Card largest = bob.getLargest();
            if (alice.contains(largest)) {
                cout << "Bob picked matching card " << largest << endl;
                bob.remove(largest);
                alice.remove(largest);
                foundMatch = true;
            }
        }
    }

    // Print final cards
    cout << endl;
    cout << "Alice's cards:" << endl;
    alice.printInOrder();

    cout << endl;
    cout << "Bob's cards:" << endl;
    bob.printInOrder();

    return 0;
}

