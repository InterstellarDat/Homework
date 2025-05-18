#include <algorithm>
#include <cmath>

struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
    int height;
};

// Helper function to get the height of a node
int getHeight(NODE* node) {
    return node ? node->height : 0;
}

// Helper function to get balance factor of a node
int getBalance(NODE* node) {
    return node ? getHeight(node->p_left) - getHeight(node->p_right) : 0;
}

// Function to create a new node
NODE* createNode(int data) {
    NODE* node = new NODE;
    node->key = data;
    node->p_left = node->p_right = nullptr;
    node->height = 1;
    return node;
}

// Right rotation
NODE* rightRotate(NODE* y) {
    NODE* x = y->p_left;
    NODE* T2 = x->p_right;
    x->p_right = y;
    y->p_left = T2;
    y->height = std::max(getHeight(y->p_left), getHeight(y->p_right)) + 1;
    x->height = std::max(getHeight(x->p_left), getHeight(x->p_right)) + 1;
    return x;
}

// Left rotation
NODE* leftRotate(NODE* x) {
    NODE* y = x->p_right;
    NODE* T2 = y->p_left;
    y->p_left = x;
    x->p_right = T2;
    x->height = std::max(getHeight(x->p_left), getHeight(x->p_right)) + 1;
    y->height = std::max(getHeight(y->p_left), getHeight(y->p_right)) + 1;
    return y;
}

// Insert a node into the AVL tree
void Insert(NODE*& pRoot, int x) {
    if (!pRoot) {
        pRoot = createNode(x);
        return;
    }
    if (x < pRoot->key)
        Insert(pRoot->p_left, x);
    else if (x > pRoot->key)
        Insert(pRoot->p_right, x);
    else
        return; // Duplicate values ignored

    pRoot->height = std::max(getHeight(pRoot->p_left), getHeight(pRoot->p_right)) + 1;
    int balance = getBalance(pRoot);

    // Left Left
    if (balance > 1 && x < pRoot->p_left->key)
        pRoot = rightRotate(pRoot);
    // Right Right
    else if (balance < -1 && x > pRoot->p_right->key)
        pRoot = leftRotate(pRoot);
    // Left Right
    else if (balance > 1 && x > pRoot->p_left->key) {
        pRoot->p_left = leftRotate(pRoot->p_left);
        pRoot = rightRotate(pRoot);
    }
    // Right Left
    else if (balance < -1 && x < pRoot->p_right->key) {
        pRoot->p_right = rightRotate(pRoot->p_right);
        pRoot = leftRotate(pRoot);
    }
}

// Find the node with minimum value in a subtree
NODE* minValueNode(NODE* node) {
    while (node->p_left)
        node = node->p_left;
    return node;
}

// Remove a node from the AVL tree
void Remove(NODE*& pRoot, int x) {
    if (!pRoot)
        return;

    if (x < pRoot->key)
        Remove(pRoot->p_left, x);
    else if (x > pRoot->key)
        Remove(pRoot->p_right, x);
    else {
        // Node with one or no child
        if (!pRoot->p_left || !pRoot->p_right) {
            NODE* temp = pRoot->p_left ? pRoot->p_left : pRoot->p_right;
            if (!temp) {
                temp = pRoot;
                pRoot = nullptr;
            } else
                *pRoot = *temp;
            delete temp;
        } else {
            // Node with two children
            NODE* temp = minValueNode(pRoot->p_right);
            pRoot->key = temp->key;
            Remove(pRoot->p_right, temp->key);
        }
    }

    if (!pRoot)
        return;

    pRoot->height = std::max(getHeight(pRoot->p_left), getHeight(pRoot->p_right)) + 1;
    int balance = getBalance(pRoot);

    // Left Left
    if (balance > 1 && getBalance(pRoot->p_left) >= 0)
        pRoot = rightRotate(pRoot);
    // Left Right
    else if (balance > 1 && getBalance(pRoot->p_left) < 0) {
        pRoot->p_left = leftRotate(pRoot->p_left);
        pRoot = rightRotate(pRoot);
    }
    // Right Right
    else if (balance < -1 && getBalance(pRoot->p_right) <= 0)
        pRoot = leftRotate(pRoot);
    // Right Left
    else if (balance < -1 && getBalance(pRoot->p_right) > 0) {
        pRoot->p_right = rightRotate(pRoot->p_right);
        pRoot = leftRotate(pRoot);
    }
}

// Check if the tree is an AVL tree
bool isAVL(NODE* pRoot) {
    if (!pRoot)
        return true;

    int balance = getBalance(pRoot);
    if (std::abs(balance) > 1)
        return false;

    return isAVL(pRoot->p_left) && isAVL(pRoot->p_right);
}
