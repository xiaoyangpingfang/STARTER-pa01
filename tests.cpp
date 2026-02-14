// tests.cpp
// Author: Xiaoyang Zhang
#include "card.h"
#include "card_list.h"
#include <iostream>
#include <cassert>
using namespace std;

// ========== BST insert() 测试 ==========
void test_insert_empty() {
    CardList cards;
    cards.insert(Card('c', "a"));
    assert(cards.contains(Card('c', "a")));
    cout << "✓ test_insert_empty passed" << endl;
}

void test_insert_multiple() {
    CardList cards;
    cards.insert(Card('c', "5"));
    cards.insert(Card('c', "2"));
    cards.insert(Card('c', "8"));
    assert(cards.contains(Card('c', "5")));
    assert(cards.contains(Card('c', "2")));
    assert(cards.contains(Card('c', "8")));
    cout << "✓ test_insert_multiple passed" << endl;
}

void test_insert_ordered() {
    CardList cards;
    cards.insert(Card('c', "a"));
    cards.insert(Card('d', "3"));
    cards.insert(Card('s', "10"));
    cards.insert(Card('h', "k"));
    // Verify ordering by iterating
    auto it = cards.begin();
    assert(*it == Card('c', "a"));
    ++it;
    assert(*it == Card('d', "3"));
    ++it;
    assert(*it == Card('s', "10"));
    cout << "✓ test_insert_ordered passed" << endl;
}

void test_insert_duplicate() {
    CardList cards;
    cards.insert(Card('c', "5"));
    cards.insert(Card('c', "5"));  // Duplicate
    // Should only have one copy
    int count = 0;
    for (auto it = cards.begin(); it != cards.end(); ++it) {
        if (*it == Card('c', "5")) count++;
    }
    assert(count == 1);
    cout << "✓ test_insert_duplicate passed" << endl;
}

void test_insert_all_suits() {
    CardList cards;
    cards.insert(Card('h', "10"));
    cards.insert(Card('s', "10"));
    cards.insert(Card('d', "10"));
    cards.insert(Card('c', "10"));
    assert(cards.contains(Card('h', "10")));
    assert(cards.contains(Card('s', "10")));
    assert(cards.contains(Card('d', "10")));
    assert(cards.contains(Card('c', "10")));
    cout << "✓ test_insert_all_suits passed" << endl;
}

// ========== BST remove() 测试 ==========
void test_remove_leaf() {
    CardList cards;
    cards.insert(Card('c', "5"));
    cards.insert(Card('c', "3"));
    cards.insert(Card('c', "7"));
    cards.remove(Card('c', "3"));
    assert(!cards.contains(Card('c', "3")));
    assert(cards.contains(Card('c', "5")));
    cout << "✓ test_remove_leaf passed" << endl;
}

void test_remove_one_child() {
    CardList cards;
    cards.insert(Card('c', "5"));
    cards.insert(Card('c', "3"));
    cards.insert(Card('c', "2"));
    cards.remove(Card('c', "3"));
    assert(!cards.contains(Card('c', "3")));
    assert(cards.contains(Card('c', "2")));
    assert(cards.contains(Card('c', "5")));
    cout << "✓ test_remove_one_child passed" << endl;
}

void test_remove_two_children() {
    CardList cards;
    cards.insert(Card('c', "5"));
    cards.insert(Card('c', "3"));
    cards.insert(Card('c', "7"));
    cards.insert(Card('c', "6"));
    cards.insert(Card('c', "8"));
    cards.remove(Card('c', "7"));
    assert(!cards.contains(Card('c', "7")));
    assert(cards.contains(Card('c', "6")));
    assert(cards.contains(Card('c', "8")));
    cout << "✓ test_remove_two_children passed" << endl;
}

void test_remove_nonexistent() {
    CardList cards;
    cards.insert(Card('c', "5"));
    cards.remove(Card('c', "10"));  // Doesn't exist
    assert(cards.contains(Card('c', "5")));
    cout << "✓ test_remove_nonexistent passed" << endl;
}

void test_remove_all() {
    CardList cards;
    cards.insert(Card('c', "5"));
    cards.insert(Card('c', "3"));
    cards.insert(Card('c', "7"));
    cards.remove(Card('c', "5"));
    cards.remove(Card('c', "3"));
    cards.remove(Card('c', "7"));
    assert(cards.isEmpty());
    cout << "✓ test_remove_all passed" << endl;
}

// ========== BST contains() 测试 ==========
void test_contains_empty() {
    CardList cards;
    assert(!cards.contains(Card('c', "a")));
    cout << "✓ test_contains_empty passed" << endl;
}

void test_contains_single() {
    CardList cards;
    cards.insert(Card('c', "5"));
    assert(cards.contains(Card('c', "5")));
    assert(!cards.contains(Card('c', "3")));
    cout << "✓ test_contains_single passed" << endl;
}

void test_contains_multiple() {
    CardList cards;
    cards.insert(Card('c', "5"));
    cards.insert(Card('d', "3"));
    cards.insert(Card('s', "10"));
    assert(cards.contains(Card('c', "5")));
    assert(cards.contains(Card('d', "3")));
    assert(cards.contains(Card('s', "10")));
    assert(!cards.contains(Card('h', "k")));
    cout << "✓ test_contains_multiple passed" << endl;
}

void test_contains_after_remove() {
    CardList cards;
    cards.insert(Card('c', "5"));
    cards.insert(Card('c', "3"));
    cards.remove(Card('c', "3"));
    assert(cards.contains(Card('c', "5")));
    assert(!cards.contains(Card('c', "3")));
    cout << "✓ test_contains_after_remove passed" << endl;
}

void test_contains_case_sensitive() {
    CardList cards;
    cards.insert(Card('c', "k"));
    assert(cards.contains(Card('c', "k")));
    assert(!cards.contains(Card('h', "k")));  // Different suit
    cout << "✓ test_contains_case_sensitive passed" << endl;
}

// ========== Iterator 测试 ==========
void test_iterator_empty() {
    CardList cards;
    assert(cards.begin() == cards.end());
    cout << "✓ test_iterator_empty passed" << endl;
}

void test_iterator_single() {
    CardList cards;
    cards.insert(Card('c', "5"));
    auto it = cards.begin();
    assert(*it == Card('c', "5"));
    ++it;
    assert(it == cards.end());
    cout << "✓ test_iterator_single passed" << endl;
}

void test_iterator_forward() {
    CardList cards;
    cards.insert(Card('c', "5"));
    cards.insert(Card('c', "2"));
    cards.insert(Card('c', "8"));
    auto it = cards.begin();
    assert(*it == Card('c', "2"));
    ++it;
    assert(*it == Card('c', "5"));
    ++it;
    assert(*it == Card('c', "8"));
    ++it;
    assert(it == cards.end());
    cout << "✓ test_iterator_forward passed" << endl;
}

void test_iterator_reverse() {
    CardList cards;
    cards.insert(Card('c', "5"));
    cards.insert(Card('c', "2"));
    cards.insert(Card('c', "8"));
    auto it = cards.rbegin();
    assert(*it == Card('c', "8"));
    ++it;
    assert(*it == Card('c', "5"));
    ++it;
    assert(*it == Card('c', "2"));
    ++it;
    assert(it == cards.rend());
    cout << "✓ test_iterator_reverse passed" << endl;
}

void test_iterator_comparison() {
    CardList cards;
    cards.insert(Card('c', "5"));
    auto it1 = cards.begin();
    auto it2 = cards.begin();
    assert(it1 == it2);
    ++it2;
    assert(it1 != it2);
    cout << "✓ test_iterator_comparison passed" << endl;
}

// ========== Print 测试 ==========
void test_print_empty() {
    CardList cards;
    cout << "Printing empty tree (should show nothing):" << endl;
    cards.printInOrder();
    cout << "✓ test_print_empty passed" << endl;
}

void test_print_single() {
    CardList cards;
    cards.insert(Card('c', "5"));
    cout << "Printing single card:" << endl;
    cards.printInOrder();
    cout << "✓ test_print_single passed" << endl;
}

void test_print_multiple() {
    CardList cards;
    cards.insert(Card('c', "5"));
    cards.insert(Card('c', "2"));
    cards.insert(Card('c', "8"));
    cout << "Printing multiple cards (should be c 2, c 5, c 8):" << endl;
    cards.printInOrder();
    cout << "✓ test_print_multiple passed" << endl;
}

void test_print_reverse() {
    CardList cards;
    cards.insert(Card('c', "5"));
    cards.insert(Card('c', "2"));
    cards.insert(Card('c', "8"));
    cout << "Printing reverse (should be c 8, c 5, c 2):" << endl;
    cards.printReverse();
    cout << "✓ test_print_reverse passed" << endl;
}

void test_print_all_suits() {
    CardList cards;
    cards.insert(Card('h', "5"));
    cards.insert(Card('s', "5"));
    cards.insert(Card('d', "5"));
    cards.insert(Card('c', "5"));
    cout << "Printing all suits (should be c 5, d 5, s 5, h 5):" << endl;
    cards.printInOrder();
    cout << "✓ test_print_all_suits passed" << endl;
}

// ========== Game Logic 测试 ==========
void test_game_common_cards() {
    cout << "\n=== Test: Common cards ===" << endl;
    CardList alice, bob;
    alice.insert(Card('c', "3"));
    alice.insert(Card('c', "5"));
    bob.insert(Card('c', "3"));
    bob.insert(Card('d', "2"));
    
    // Simulate one round
    bool found = false;
    Card toRemove;
    for (auto it = alice.begin(); it != alice.end(); ++it) {
        if (bob.contains(*it)) {
            toRemove = *it;
            found = true;
            break;
        }
    }
    assert(found);
    assert(toRemove == Card('c', "3"));
    cout << "✓ test_game_common_cards passed" << endl;
}

void test_game_no_common() {
    cout << "\n=== Test: No common cards ===" << endl;
    CardList alice, bob;
    alice.insert(Card('c', "3"));
    alice.insert(Card('c', "5"));
    bob.insert(Card('d', "2"));
    bob.insert(Card('h', "10"));
    
    bool found = false;
    for (auto it = alice.begin(); it != alice.end(); ++it) {
        if (bob.contains(*it)) {
            found = true;
            break;
        }
    }
    assert(!found);
    cout << "✓ test_game_no_common passed" << endl;
}

void test_game_empty_hand() {
    cout << "\n=== Test: Empty hand ===" << endl;
    CardList alice, bob;
    bob.insert(Card('d', "2"));
    
    assert(alice.isEmpty());
    cout << "✓ test_game_empty_hand passed" << endl;
}

// ========== Main 测试运行器 ==========
int main() {
    cout << "========== Running BST Tests ==========" << endl;
    
    cout << "\n--- insert() tests ---" << endl;
    test_insert_empty();
    test_insert_multiple();
    test_insert_ordered();
    test_insert_duplicate();
    test_insert_all_suits();
    
    cout << "\n--- remove() tests ---" << endl;
    test_remove_leaf();
    test_remove_one_child();
    test_remove_two_children();
    test_remove_nonexistent();
    test_remove_all();
    
    cout << "\n--- contains() tests ---" << endl;
    test_contains_empty();
    test_contains_single();
    test_contains_multiple();
    test_contains_after_remove();
    test_contains_case_sensitive();
    
    cout << "\n--- Iterator tests ---" << endl;
    test_iterator_empty();
    test_iterator_single();
    test_iterator_forward();
    test_iterator_reverse();
    test_iterator_comparison();
    
    cout << "\n--- Print tests ---" << endl;
    test_print_empty();
    test_print_single();
    test_print_multiple();
    test_print_reverse();
    test_print_all_suits();
    
    cout << "\n--- Game logic tests ---" << endl;
    test_game_common_cards();
    test_game_no_common();
    test_game_empty_hand();
    
    cout << "\n========== All tests passed! ==========" << endl;
    return 0;
}
