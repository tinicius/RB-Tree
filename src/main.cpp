#include <stdlib.h>

#include <iostream>
#include <vector>

#include "tree.hpp"

using namespace std;

int main() {
    Tree rb;

    // vector<int> a = {1, 2, 3, 5, 24, 25};
    vector<int> a = {5, 4, 1, 3, 2};

    for (auto i : a) {
        Node* aux = rb.initialize_node(i);

        rb.insert(aux);
        // rb.pre_order(rb.root);
        // cout << endl;
    }

    rb.pre_order(rb.root);
}