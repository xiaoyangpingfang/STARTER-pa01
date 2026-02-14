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
        // Alice turn - 先保存匹配的卡片
        Card matchedCard('c', "a"); // 临时初始化
        for (auto it = alice.begin(); it != alice.end(); ++it) {
            if (bob.contains(*it)) {
                matchedCard = *it;  // 保存卡片副本
                aliceMatched = true;
                break;
            }
        }
        if (aliceMatched) {
            cout << "Alice picked matching card " << matchedCard << endl;
            bob.remove(matchedCard);    // 使用副本删除
            alice.remove(matchedCard);  // 使用副本删除
        } else {
            break;
        }

        bool bobMatched = false;
        // Bob turn - 先保存匹配的卡片
        for (auto it = bob.rbegin(); it != bob.rend(); ++it) {
            if (alice.contains(*it)) {
                matchedCard = *it;  // 保存卡片副本
                bobMatched = true;
                break;
            }
        }
        if (bobMatched) {
            cout << "Bob picked matching card " << matchedCard << endl;
            alice.remove(matchedCard);  // 使用副本删除
            bob.remove(matchedCard);    // 使用副本删除
        } else {
            break;
        }
    }

    cout << "\nAlice's cards:" << endl;
    alice.printInOrder();
    cout << "\nBob's cards:" << endl;
    bob.printInOrder();
    return 0;
}
