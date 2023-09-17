#include <stdlib.h>

#include <iostream>
#include <unordered_map>
#include <vector>

#include "tree.hpp"

using namespace std;

int main() {
    Tree rb;

    // vector<int> a = {1, 2, 3, 5, 24, 25};
    vector<int> a = {10, 2, 9, 16, 4, 14, 11, 15, 3, 13};

    unordered_map<int, Node*> items;

    for (auto i : a) {
        Node* aux = rb.initialize_node(i);

        items[i] = aux;

        rb.insert(aux);
        // rb.pre_order(rb.root);
        // cout << endl;
    }
    rb.pre_order(rb.root);
    cout << endl <<endl;

    rb.remove(items[11]);

    rb.pre_order(rb.root);
}