// Tema: Binarny vyhladavaci strom
// Autor: Pavol Marak

#include <iostream>
#include <queue>
#include <initializer_list>

using namespace std;

// Binarny vyhladavaci strom je datova struktura
// umoznujuca rychle vyhladavanie uzlov.
//
// Vlastnost:
//	* pre lubovolny uzol U v strome plati:
//		a) uzly v lavom podstrome su mensie ako U
//		b) uzly v pravom podstrome su vacsie ako U
//	* vsetky uzly v strome su unikatne


// struktura reprezentujuca uzol BST
struct Node {
    int value; // hodnota uzla

    // smernik na laveho potomka
    // vsetky uzly v podstrome s korenom v uzle 'smaller'
    // maju mensie hodnoty ako 'value'
    Node *smaller;

    // smernik na praveho potomka
    // vsetky uzly v podstrome s korenom v uzle 'greater'
    // maju vacsie hodnoty ako 'value'
    Node *greater;
};

// struktura reprezentujuca BST
struct BinarySearchTree {
    Node *root; // koren BST
};

// rekurzivna pomocna funkcia na pridanie uzla do stromu
Node *addNode(Node *root, const int value) {
    if (!root) return new Node{value, nullptr, nullptr};
    if (value < root->value) {
        root->smaller = addNode(root->smaller, value);
    } else {
        root->greater = addNode(root->greater, value);
    }
    return root;
}

// nerekurzivna hlavna funkcia na pridanie uzla do stromu
void addNode(BinarySearchTree *bst, const int val) {
    bst->root = addNode(bst->root, val);
}

// funkcia na vytvorenie binarneho stromu z hodnot inicializacneho zoznamu
BinarySearchTree *createBST(const initializer_list<int> &i) {
    BinarySearchTree *bst{new BinarySearchTree{nullptr}};
    for (int e: i) {
        addNode(bst, e);
    }
    return bst;
}

// funkcia na pre-order prechod - rekurzivna
void preOrder(const Node *node) {
    if (node) {
        cout << node->value << " ";
        preOrder(node->smaller);
        preOrder(node->greater);
    }
}

// funkcia na pre-order prechod
void preOrder(const BinarySearchTree *bst) {
    preOrder(bst->root);
}

// funkcia na in-order prechod - rekurzivna
void inOrder(const Node *node) {
    if (node) {
        inOrder(node->smaller);
        cout << node->value << " ";
        inOrder(node->greater);
    }
}

// funkcia na in-order prechod
void inOrder(const BinarySearchTree *bst) {
    inOrder(bst->root);
}

// funkcia na post-order prechod - rekurzivna
void postOrder(const Node *node) {
    if (node) {
        postOrder(node->smaller);
        postOrder(node->greater);
        cout << node->value << " ";
    }
}

// funkcia na post-order prechod
void postOrder(const BinarySearchTree *bst) {
    postOrder(bst->root);
}

// funkcia na level-order prechod
void levelOrder(const BinarySearchTree *bst) {
    if (bst->root) {
        queue<Node *> q;
        q.push(bst->root);
        while (!q.empty()) {
            cout << q.front()->value << " ";
            if (q.front()->smaller) {
                q.push(q.front()->smaller);
            }
            if (q.front()->greater) {
                q.push(q.front()->greater);
            }
            q.pop();
        }
    }

}

// funkcia na vyhladavanie uzla s hodnotou 'val'
Node *searchNode(const BinarySearchTree *bst, const int val) {
    Node *tmp = bst->root;
    while (tmp) {
        if (tmp->value > val) {
            tmp = tmp->smaller;
        } else if (tmp->value < val) {
            tmp = tmp->greater;
        } else {
            return tmp;
        }
    }
    return nullptr;
}

// funkcia na vymazanie uzla s hodnotou 'val' (rekurzivna)
Node *deleteNode(Node *node, const int val) {
    if (!node) {
        return node;
    }
    if (node->value > val) {
        node->smaller = deleteNode(node->smaller, val);
    } else if (node->value < val) {
        node->greater = deleteNode(node->greater, val);
    }
        // nasli sme hladany uzol
    else {
        // 0 potomkov
        if (!node->greater && !node->smaller) {
            delete node;
            node = nullptr;
        }
            // ma len 'smaller' potomka
        else if (!node->greater) {
            Node *child = node->smaller;
            delete node;
            node = child;

        }
            // ma len 'greater' potomka
        else if (!node->smaller) {
            Node *child = node->greater;
            delete node;
            node = child;
        }
            // ma 2 potomkov
        else {
            // hladanie inorder nasledovnika
            Node *inOrdSucc{node->greater};
            while (inOrdSucc->smaller) {
                inOrdSucc = inOrdSucc->smaller;
            }
            // skopirovanie hodnoty inorder nasledovnika
            // do vymazavaneho uzla
            node->value = inOrdSucc->value;
            // vymazanie inorder nasledovnika
            node->greater = deleteNode(node->greater, inOrdSucc->value);
        }
    }
    return node;
}

// funkcia na vymazanie uzla s hodnotou 'val'
bool deleteNode(BinarySearchTree *bst, const int val) {
    return deleteNode(bst->root, val) != nullptr;
}

// testovanie
int main() {

    // 1. Vytvorenie stromu
    BinarySearchTree *bst{createBST({20, 10, 70, 0, 15, 50, 80, 18, 55})};

    // 2. Prechody do hlbky (DFS)

    // a. pre-order
    preOrder(bst);
    cout << endl;
    // b. in-order
    inOrder(bst);
    cout << endl;
    // c. post-order
    postOrder(bst);
    cout << endl;

    // 3. Prechod do sirky (BFS)
    levelOrder(bst);

    // 4. Vyhladavanie uzlov v BST
    Node *node{searchNode(bst, 70)};
    if (node) {
        cout << endl << node->value << endl;
    }

    // 5. Vymazavanie uzlov z BST
    cout << endl << deleteNode(bst, 20);

    return 0;
}

