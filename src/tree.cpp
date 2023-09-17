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
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }

    z->left = T_NIL;
    z->right = T_NIL;
    z->color = RED;

    insert_fixup(z);
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
    string color = aux->color ? "RED" : "BLACK";
    std::cout << aux->key << " " << color << endl;
    pre_order(aux->right);
}

void Tree::transplant(Node* u, Node* v) {
    if (u->parent == T_NIL) {
        this->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }

    v->parent = u->parent;
}

Node* minValueNode(Node* node) {
    Node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL) current = current->left;

    return current;
}

Node* Tree::tree_minimum(Node* v) {
    Node* aux = v;

    while (aux->left != T_NIL) {
        aux = aux->left;
    }

    return aux;
}

void Tree::remove_fixup(Node* x) {
    while (x != this->root and x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;

            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(x->parent);
                w = x->parent->right;
            }

            if (w->left->color == BLACK and w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else if (w->right->color == BLACK) {
                w->left->color = BLACK;
                w->color = RED;
                right_rotate(w);
                w = w->parent->right;
            }

            w->color = x->parent->color;
            x->parent->color = BLACK;
            w->right->color = BLACK;
            left_rotate(x->parent);
            x = this->root;
        } else {
            Node* w = x->parent->left;

            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(x->parent);
                w = x->parent->left;
            }

            if (w->right->color == BLACK and w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else if (w->left->color == BLACK) {
                w->right->color = BLACK;
                w->color = RED;
                left_rotate(w);
                w = w->parent->left;
            }

            w->color = x->parent->color;
            x->parent->color = BLACK;
            w->left->color = BLACK;
            right_rotate(x->parent);
            x = this->root;
        }
    }

    x->color = BLACK;
}

void Tree::remove(Node* z) {
    Node* x;

    Node* y = z;
    bool y_original_color = y->color;

    if (z->left == T_NIL) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == T_NIL) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = tree_minimum(z->right);
        y_original_color = y->color;
        x = y->right;

        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (y_original_color == BLACK) {
        remove_fixup(x);
    }
}