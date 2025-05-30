#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <stack>
#include <algorithm>
#include <limits>

using namespace std;

// 1. Convert adjacency matrix from file to adjacency list
vector<vector<int>> convertMatrixToList(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file");
    }
    int n;
    file >> n;
    vector<vector<int>> adjList(n);
    string line;
    getline(file, line);
    for (int i = 0; i < n; ++i) {
        getline(file, line);
        stringstream ss(line);
        int j = 0;
        char val;
        while (ss >> val) {
            if (val == '1') {
                adjList[i].push_back(j);
            }
            j++;
        }
    }
    file.close();
    return adjList;
}

// 2. Convert adjacency list from file to adjacency matrix
vector<vector<int>> convertListToMatrix(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file");
    }
    int n;
    file >> n;
    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));
    string line;
    getline(file, line);
    for (int i = 0; i < n; ++i) {
        getline(file, line);
        stringstream ss(line);
        int count;
        ss >> count; // Read and ignore the neighbor count
        int v;
        while (ss >> v) {
            adjMatrix[i][v] = 1;
        }
    }
    file.close();
    return adjMatrix;
}

// 3. Check if graph is directed
bool isDirected(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adjMatrix[i][j] != adjMatrix[j][i]) {
                return true;
            }
        }
    }
    return false;
}

// 3. Count number of vertices
int countVertices(const vector<vector<int>>& adjMatrix) {
    return adjMatrix.size();
}

// 3. Count number of edges
int countEdges(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    int edges = 0;
    bool directed = isDirected(adjMatrix);
    for (int i = 0; i < n; ++i) {
        for (int j = directed ? 0 : i; j < n; ++j) {
            if (adjMatrix[i][j] != 0) {
                edges++;
            }
        }
    }
    return edges;
}

// 3. Get list of isolated vertices
vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> isolated;
    for (int i = 0; i < n; ++i) {
        bool hasEdge = false;
        for (int j = 0; j < n; ++j) {
            if (adjMatrix[i][j] != 0 || adjMatrix[j][i] != 0) {
                hasEdge = true;
                break;
            }
        }
        if (!hasEdge) {
            isolated.push_back(i);
        }
    }
    return isolated;
}

// 3. Check if undirected graph is complete
bool isCompleteGraph(const vector<vector<int>>& adjMatrix) {
    if (isDirected(adjMatrix)) {
        return false;
    }
    int n = adjMatrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                if (adjMatrix[i][j] != 0) {
                    return false; // No self-loops
                }
            } else if (adjMatrix[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

// 3. Check if undirected graph is bipartite
bool isBipartite(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> colors(n, -1); // -1: uncolored, 0: color1, 1: color2
    queue<int> q;
    for (int start = 0; start < n; ++start) {
        if (colors[start] == -1) {
            q.push(start);
            colors[start] = 0;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v = 0; v < n; ++v) {
                    if (adjMatrix[u][v] != 0) {
                        if (colors[v] == -1) {
                            colors[v] = 1 - colors[u];
                            q.push(v);
                        } else if (colors[v] == colors[u]) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

// 3. Check if undirected graph is complete bipartite
bool isCompleteBipartite(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> colors(n, -1);
    vector<int> setA, setB;
    queue<int> q;
    for (int start = 0; start < n; ++start) {
        if (colors[start] == -1) {
            q.push(start);
            colors[start] = 0;
            setA.push_back(start);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v = 0; v < n; ++v) {
                    if (adjMatrix[u][v] != 0) {
                        if (colors[v] == -1) {
                            colors[v] = 1 - colors[u];
                            (colors[v] == 0 ? setA : setB).push_back(v);
                            q.push(v);
                        } else if (colors[v] == colors[u]) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    for (int u : setA) {
        for (int v : setB) {
            if (adjMatrix[u][v] == 0) {
                return false;
            }
        }
    }
    return true;
}

// 4. Convert directed graph to undirected
vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<vector<int>> undirected = adjMatrix;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adjMatrix[i][j] != 0 || adjMatrix[j][i] != 0) {
                undirected[i][j] = undirected[j][i] = 1;
            }
        }
    }
    return undirected;
}

// 5. Generate complement graph (undirected)
vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<vector<int>> complement(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                complement[i][j] = adjMatrix[i][j] == 0 ? 1 : 0;
            }
        }
    }
    return complement;
}

// Helper function to check if undirected graph is connected
bool isConnectedUndirected(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    stack<int> s;
    s.push(0);
    visited[0] = true;
    int count = 1;
    while (!s.empty()) {
        int u = s.top();
        s.pop();
        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] && !visited[v]) {
                visited[v] = true;
                s.push(v);
                count++;
            }
        }
    }
    return count == n;
}

// Helper function to check if directed graph is strongly connected
bool isStronglyConnected(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    auto dfs = [&](int start, vector<bool>& visited) {
        stack<int> s;
        s.push(start);
        visited[start] = true;
        while (!s.empty()) {
            int u = s.top();
            s.pop();
            for (int v = 0; v < n; ++v) {
                if (adjMatrix[u][v] && !visited[v]) {
                    visited[v] = true;
                    s.push(v);
                }
            }
        }
    };
    // Check reachability from vertex 0
    vector<bool> visited(n, false);
    dfs(0, visited);
    for (bool v : visited) {
        if (!v) return false;
    }
    // Check reverse graph
    vector<vector<int>> transpose(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            transpose[j][i] = adjMatrix[i][j];
        }
    }
    visited.assign(n, false);
    dfs(0, visited);
    for (bool v : visited) {
        if (!v) return false;
    }
    return true;
}

// 6. Find Euler cycle using Hierholzer's algorithm
vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    bool directed = isDirected(adjMatrix);
    vector<vector<int>> edges = adjMatrix; // Copy to track used edges
    vector<int> cycle;

    // Step 1: Check if Eulerian cycle is possible
    if (directed) {
        // Directed: in-degree must equal out-degree for each vertex
        vector<int> inDegree(n, 0), outDegree(n, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (edges[i][j]) {
                    outDegree[i]++;
                    inDegree[j]++;
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if (inDegree[i] != outDegree[i]) {
                return {}; // No Eulerian cycle
            }
        }
        // Check strong connectivity (ignore vertices with no edges)
        if (!isStronglyConnected(adjMatrix)) {
            return {};
        }
    } else {
        // Undirected: all vertices must have even degree
        for (int i = 0; i < n; ++i) {
            int degree = 0;
            for (int j = 0; j < n; ++j) {
                degree += edges[i][j];
            }
            if (degree % 2 != 0) {
                return {}; // No Eulerian cycle
            }
        }
        // Check connectivity (ignore vertices with no edges)
        if (!isConnectedUndirected(adjMatrix)) {
            return {};
        }
    }

    // Step 2: Hierholzer's algorithm
    stack<int> path;
    int start = -1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (edges[i][j]) {
                start = i;
                break;
            }
        }
        if (start != -1) break;
    }
    if (start == -1) return {}; // No edges

    path.push(start);
    while (!path.empty()) {
        int u = path.top();
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (edges[u][j]) {
                v = j;
                break;
            }
        }
        if (v == -1) {
            // No outgoing edges, add to cycle
            cycle.push_back(u);
            path.pop();
        } else {
            // Follow edge
            path.push(v);
            edges[u][v]--;
            if (!directed) edges[v][u]--; // Remove reverse edge for undirected
        }
    }

    // Step 3: Verify all edges used
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (edges[i][j] > 0) {
                return {}; // Not all edges used
            }
        }
    }

    reverse(cycle.begin(), cycle.end());
    return cycle;
}

// 7. DFS spanning tree (undirected)
vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
    int n = adjMatrix.size();
    vector<vector<int>> tree(n, vector<int>(n, 0));
    vector<bool> visited(n, false);
    stack<int> s;
    s.push(start);
    visited[start] = true;
    while (!s.empty()) {
        int u = s.top();
        s.pop();
        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] != 0 && !visited[v]) {
                tree[u][v] = tree[v][u] = 1;
                s.push(v);
                visited[v] = true;
            }
        }
    }
    return tree;
}

// 7. BFS spanning tree (undirected)
vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
    int n = adjMatrix.size();
    vector<vector<int>> tree(n, vector<int>(n, 0));
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] != 0 && !visited[v]) {
                tree[u][v] = tree[v][u] = 1;
                q.push(v);
                visited[v] = true;
            }
        }
    }
    return tree;
}

// 8. Check connectivity between two vertices
bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    stack<int> s;
    s.push(u);
    visited[u] = true;
    while (!s.empty()) {
        int curr = s.top();
        s.pop();
        if (curr == v) {
            return true;
        }
        for (int i = 0; i < n; ++i) {
            if (adjMatrix[curr][i] != 0 && !visited[i]) {
                s.push(i);
                visited[i] = true;
            }
        }
    }
    return false;
}

// 9. Dijkstra's algorithm for shortest path (weighted graph)
vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> dist(n, numeric_limits<int>::max());
    vector<int> prev(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    dist[start] = 0;
    pq.push({0, start});
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] > 0) { // Weight > 0 indicates edge
                int weight = adjMatrix[u][v];
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }
    vector<int> path;
    if (dist[end] == numeric_limits<int>::max()) {
        return path;
    }
    for (int at = end; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

// 9. Bellman-Ford algorithm for shortest path (weighted graph)
vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> dist(n, numeric_limits<int>::max());
    vector<int> prev(n, -1);
    dist[start] = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (adjMatrix[u][v] > 0) {
                    int weight = adjMatrix[u][v];
                    if (dist[u] != numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                        prev[v] = u;
                    }
                }
            }
        }
    }
    // Check for negative cycles
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] > 0) {
                int weight = adjMatrix[u][v];
                if (dist[u] != numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                    throw runtime_error("Negative cycle detected");
                }
            }
        }
    }
    vector<int> path;
    if (dist[end] == numeric_limits<int>::max()) {
        return path;
    }
    for (int at = end; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}
