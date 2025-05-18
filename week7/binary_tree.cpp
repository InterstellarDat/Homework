#include <vector>
#include <queue>
#include <algorithm>

struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
};

// Helper function to compute the height of a subtree
int getHeight(NODE* node) {
    if (!node) return -1; // Empty tree has height -1
    return 1 + std::max(getHeight(node->p_left), getHeight(node->p_right));
}

// 1. Initialize a NODE from a given value
NODE* createNode(int data) {
    NODE* node = new NODE;
    node->key = data;
    node->p_left = node->p_right = nullptr;
    return node;
}

// 2. Pre-order traversal (NLR: Node, Left, Right)
std::vector<int> NLR(NODE* pRoot) {
    std::vector<int> result;
    if (!pRoot) return result;
    
    result.push_back(pRoot->key);
    std::vector<int> left = NLR(pRoot->p_left);
    result.insert(result.end(), left.begin(), left.end());
    std::vector<int> right = NLR(pRoot->p_right);
    result.insert(result.end(), right.begin(), right.end());
    
    return result;
}

// 3. In-order traversal (LNR: Left, Node, Right)
std::vector<int> LNR(NODE* pRoot) {
    std::vector<int> result;
    if (!pRoot) return result;
    
    std::vector<int> left = LNR(pRoot->p_left);
    result.insert(result.end(), left.begin(), left.end());
    result.push_back(pRoot->key);
    std::vector<int> right = LNR(pRoot->p_right);
    result.insert(result.end(), right.begin(), right.end());
    
    return result;
}

// 4. Post-order traversal (LRN: Left, Right, Node)
std::vector<int> LRN(NODE* pRoot) {
    std::vector<int> result;
    if (!pRoot) return result;
    
    std::vector<int> left = LRN(pRoot->p_left);
    result.insert(result.end(), left.begin(), left.end());
    std::vector<int> right = LRN(pRoot->p_right);
    result.insert(result.end(), right.begin(), right.end());
    result.push_back(pRoot->key);
    
    return result;
}

// 5. Level-order traversal
std::vector<std::vector<int>> LevelOrder(NODE* pRoot) {
    std::vector<std::vector<int>> result;
    if (!pRoot) return result;
    
    std::queue<NODE*> q;
    q.push(pRoot);
    
    while (!q.empty()) {
        int levelSize = q.size();
        std::vector<int> currentLevel;
        
        for (int i = 0; i < levelSize; ++i) {
            NODE* node = q.front();
            q.pop();
            currentLevel.push_back(node->key);
            
            if (node->p_left) q.push(node->p_left);
            if (node->p_right) q.push(node->p_right);
        }
        
        result.push_back(currentLevel);
    }
    
    return result;
}

// 6. Calculate the number of nodes
int countNode(NODE* pRoot) {
    if (!pRoot) return 0;
    return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}

// 7. Calculate the sum of all node values
int sumNode(NODE* pRoot) {
    if (!pRoot) return 0;
    return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
}

// 8. Calculate the height of a node with a given value
int heightNode(NODE* pRoot, int value) {
    if (!pRoot) return -1;
    
    if (pRoot->key == value) {
        return getHeight(pRoot);
    }
    
    int left = heightNode(pRoot->p_left, value);
    if (left != -1) return left;
    
    return heightNode(pRoot->p_right, value);
}

// 9. Calculate the level of a given node
int Level(NODE* pRoot, NODE* p) {
    if (!pRoot || !p) return -1;
    if (pRoot == p) return 0;
    
    int left = Level(pRoot->p_left, p);
    if (left != -1) return 1 + left;
    
    int right = Level(pRoot->p_right, p);
    if (right != -1) return 1 + right;
    
    return -1;
}

// 10. Count the number of leaf nodes
int countLeaf(NODE* pRoot) {
    if (!pRoot) return 0;
    if (!pRoot->p_left && !pRoot->p_right) return 1;
    return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}
