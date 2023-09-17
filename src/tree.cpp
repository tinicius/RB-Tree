#include "tree.hpp"

Tree::Tree() {
    Node* aux = (Node*)malloc(sizeof(Node));

    aux->color = BLACK;
    aux->key = 0;

    aux->parent = aux;
    aux->left = aux;
    aux->right = aux;

    this->T_NIL = aux;
    this->root = this->T_NIL;
}

Tree::~Tree() {}

Node* Tree::initialize_node(int key) {
    Node* aux = (Node*)malloc(sizeof(Node));

    aux->color = BLACK;
    aux->key = key;

    aux->parent = T_NIL;
    aux->left = T_NIL;
    aux->right = T_NIL;

    return aux;
}

void Tree::left_rotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;

    if (y->left != T_NIL) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == T_NIL) {
        this->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void Tree::right_rotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;

    if (y->right != T_NIL) {
        y->right->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == T_NIL) {
        this->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}

void Tree::insert(Node* z) {
    cout << "-----" << endl;

    Node* y = T_NIL;
    Node* x = this->root;

    while (x != T_NIL) {
        y = x;

        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;

    if (y == T_NIL) {
        this->root = z;
    } else if (z->key < y->key) {  // EU MEXI AQUI
        y->left = z;
    } else {
        y->right = z;
    }

    z->left = T_NIL;
    z->right = T_NIL;
    z->color = RED;

    // cout << "z.p " << z

    insert_fixup(z);

    cout << "-----" << endl;
}

void Tree::insert_fixup(Node* z) {
    while ((z != root) and z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;

            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;

                    left_rotate(z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;

                right_rotate(z->parent->parent);
            }

        } else {
            Node* y = z->parent->parent->left;

            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;

                    right_rotate(z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;

                left_rotate((z->parent->parent));
            }
        }
    }

    this->root->color = BLACK;
}

void Tree::pre_order(Node* aux) {
    if (aux == T_NIL) return;

    pre_order(aux->left);
    std::cout << aux->key << " ";
    pre_order(aux->right);
}