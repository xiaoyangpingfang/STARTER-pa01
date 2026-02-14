//main.cpp
//Author:Xiaoyang Zhang
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "card.h"
#include "card_list.h"

using namespace std;

int main(int argc, char** argv) {
    if(argc < 3){
        cout << "Please provide 2 file names" << endl;
        return 1;
    }

    CardList alice, bob;

    ifstream file1(argv[1]), file2(argv[2]);
    if (!file1 || !file2) { cout << "Could not open files\n"; return 1; }

    string line;
    while (getline(file1, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        char suit; string value;
        ss >> suit >> value;
        alice.insert(Card(suit, value));
    }

    while (getline(file2, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        char suit; string value;
        ss >> suit >> value;
        bob.insert(Card(suit, value));
    }

    file1.close();
    file2.close();

    while (true) {
        bool aliceMatched = false;
        for (auto it = alice.begin(); it != alice.end(); ++it) {
            if (bob.contains(*it)) {
                cout << "Alice picked matching card " << *it << endl;
                bob.remove(*it);
                alice.remove(*it);
                aliceMatched = true;
                break;
            }
        }
        if (!aliceMatched) break;

        bool bobMatched = false;
        for (auto it = bob.rbegin(); it != bob.rend(); ++it) {
            if (alice.contains(*it)) {
                cout << "Bob picked matching card " << *it << endl;
                alice.remove(*it);
                bob.remove(*it);
                bobMatched = true;
                break;
            }
        }
        if (!bobMatched) break;
    }

    cout << "\nAlice's cards:" << endl;
    alice.printInOrder();
    cout << "\nBob's cards:" << endl;
    bob.printInOrder();

    return 0;
}

