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
    if (!file1 || !file2) { 
        cout << "Could not open files\n"; 
        return 1; 
    }
    
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
        // Alice's turn
        bool aliceFound = false;
        Card toRemove;
        
        for (auto it = alice.begin(); it != alice.end(); ++it) {
            if (bob.contains(*it)) {
                toRemove = *it;  // 复制卡片数据
                aliceFound = true;
                break;
            }
        }
        
        if (aliceFound) {
            cout << "Alice picked matching card " << toRemove << endl;
            alice.remove(toRemove);
            bob.remove(toRemove);
        } else {
            break;  // 没找到，游戏结束
        }

        // Bob's turn
        bool bobFound = false;
        
        for (auto it = bob.rbegin(); it != bob.rend(); ++it) {
            if (alice.contains(*it)) {
                toRemove = *it;  // 复制卡片数据
                bobFound = true;
                break;
            }
        }
        
        if (bobFound) {
            cout << "Bob picked matching card " << toRemove << endl;
            alice.remove(toRemove);
            bob.remove(toRemove);
        } else {
            break;  // 没找到，游戏结束
        }
    }

    cout << "\nAlice's cards:" << endl;
    alice.printInOrder();
    cout << "\nBob's cards:" << endl;
    bob.printInOrder();
    return 0;
}
