#include <algorithm>
#include <limits>

struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
};

// 1. Find and return a node with a specified value
NODE* Search(NODE* pRoot, int x) {
    if (!pRoot || pRoot->key == x) return pRoot;
    if (x < pRoot->key) return Search(pRoot->p_left, x);
    return Search(pRoot->p_right, x);
}

// 2. Add a node with a specified value
void Insert(NODE*& pRoot, int x) {
    if (!pRoot) {
        pRoot = new NODE{x, nullptr, nullptr};
        return;
    }
    if (x < pRoot->key) Insert(pRoot->p_left, x);
    else if (x > pRoot->key) Insert(pRoot->p_right, x);
    // Ignore duplicates
}

// 3. Delete a node with a given value
void Remove(NODE*& pRoot, int x) {
    if (!pRoot) return;

    if (x < pRoot->key) {
        Remove(pRoot->p_left, x);
    } else if (x > pRoot->key) {
        Remove(pRoot->p_right, x);
    } else {
        // Node with one or no child
        if (!pRoot->p_left || !pRoot->p_right) {
            NODE* temp = pRoot->p_left ? pRoot->p_left : pRoot->p_right;
            NODE* toDelete = pRoot;
            pRoot = temp;
            delete toDelete;
        } else {
            // Node with two children
            NODE* successor = pRoot->p_right;
            while (successor->p_left) successor = successor->p_left;
            pRoot->key = successor->key;
            Remove(pRoot->p_right, successor->key);
        }
    }
}

// 4. Initialize a BST from a given array
NODE* createTree(int a[], int n) {
    NODE* root = nullptr;
    for (int i = 0; i < n; ++i) {
        Insert(root, a[i]);
    }
    return root;
}

// 5. Delete the entire BST
void removeTree(NODE*& pRoot) {
    if (!pRoot) return;
    removeTree(pRoot->p_left);
    removeTree(pRoot->p_right);
    delete pRoot;
    pRoot = nullptr;
}

// 6. Calculate the height of the BST
int Height(NODE* pRoot) {
    if (!pRoot) return -1;
    return 1 + std::max(Height(pRoot->p_left), Height(pRoot->p_right));
}

// 7. Count nodes with keys less than x
int countLess(NODE* pRoot, int x) {
    if (!pRoot) return 0;
    if (pRoot->key >= x) return countLess(pRoot->p_left, x);
    return 1 + countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);
}

// 8. Count nodes with keys greater than x
int countGreater(NODE* pRoot, int x) {
    if (!pRoot) return 0;
    if (pRoot->key <= x) return countGreater(pRoot->p_right, x);
    return 1 + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
}

// 9. Check if the tree is a BST
bool isBSTUtil(NODE* node, long long min, long long max) {
    if (!node) return true;
    if (node->key <= min || node->key >= max) return false;
    return isBSTUtil(node->p_left, min, node->key) &&
           isBSTUtil(node->p_right, node->key, max);
}

bool isBST(NODE* pRoot) {
    return isBSTUtil(pRoot, std::numeric_limits<long long>::min(),
                     std::numeric_limits<long long>::max());
}

// 10. Check if the tree is a full BST
bool isFullBST(NODE* pRoot) {
    if (!pRoot) return true;
    if (!isBST(pRoot)) return false;
    if ((pRoot->p_left && !pRoot->p_right) || (!pRoot->p_left && pRoot->p_right)) return false;
    return isFullBST(pRoot->p_left) && isFullBST(pRoot->p_right);
}
