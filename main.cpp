while (true) {
    bool matched = false;

    // Alice turn: pick smallest matching card
    if (!alice.isEmpty()) {
        Card smallest = alice.getSmallest();
        if (bob.contains(smallest)) {
            cout << "Alice picked matching card " << smallest << endl;
            alice.remove(smallest);
            bob.remove(smallest);
            matched = true;
        }
    }

    // Bob turn: pick largest matching card
    if (!bob.isEmpty()) {
        Card largest = bob.getLargest();
        if (alice.contains(largest)) {
            cout << "Bob picked matching card " << largest << endl;
            bob.remove(largest);
            alice.remove(largest);
            matched = true;
        }
    }

    if (!matched) break;
}

