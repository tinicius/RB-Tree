#ifndef TREE
#define TREE

#include <stdlib.h>
#include <iostream>

using namespace std;

#define RED 1
#define BLACK 0

typedef struct Node {
    bool color;
    int key;

    Node* parent;
    Node* left;
    Node* right;

} Node;

class Tree {
   private:
   
    Node* T_NIL;

   public:
    Node* root;
    Node* initialize_node(int key);
    void left_rotate(Node* x);
    void right_rotate(Node* y);
    void insert(Node* z);
    void insert_fixup(Node* z);
    void pre_order(Node* root);
    Tree();
    ~Tree();
};

#endif