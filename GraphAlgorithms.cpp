#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <algorithm>
#include <queue>

using namespace std;

class Event {
public:
    int index, start, finish, hypescore; // Aspects of an event during DFS
    char color;
    Event(int i, int hype) : index(i), start(-1), finish(-1), hypescore(hype), color('W') {} // Constructor
};

class GraphAlgorithm { 
protected:
    int N; // Number of events
    vector<set<int>> AdjList; // Adjacency list is used to represent the graph
    vector<Event> events; // The status of each event during DFS in stored here 
    int time;
public:
    GraphAlgorithm(int N, vector<int> &hype, vector<pair<int, int>> &edges) : N(N), AdjList(N), time(0) {
        for (int i = 0; i < N; i++) 
            events.emplace_back(i, hype[i]); // Initialising the statuses of events
        for (auto &[u, v] : edges) 
            AdjList[u - 1].insert(v - 1); // Adding all edges
    }
    virtual void Query() = 0; // Virtual function
};

// Finding if a Cycle exists in the graph
// Use DFS and return true when the algorithm visits a vertex that is gray
class isCycle : public GraphAlgorithm {
public:
    isCycle(int N, vector<int> &hype, vector<pair<int, int>> &edges) : GraphAlgorithm(N, hype, edges) {}
    bool DFSHasCycle(int u) {
        events[u].color = 'G';
        for (int v : AdjList[u]) {
            if (events[v].color == 'G') return true; // u is a descendant of v but there exists an edge from u to v, thus forming a cycle
            if (events[v].color == 'W' && DFSHasCycle(v)) return true; // Check cycle in the dfs from v
        }
        events[u].color = 'B'; // Set vertex to Black
        return false;
    }
    void Query() override {
        for (int i = 0; i < N; i++)
            events[i].color = 'W'; // Initialise color of all vertices to White
        for (int i = 0; i < N; i++) {
            if (events[i].color == 'W' && DFSHasCycle(i)) { // If vertex is black, then it has already been visited
                cout << "YES" << endl;
                return;
            }
        }
        cout << "NO" << endl;
    }
};

// Use the strongly connected components algorithm
class indepComponent : public GraphAlgorithm {
    vector<set<int>> RevAdjList; // Transpose of the graph
public:
    indepComponent(int N, vector<int> &hype, vector<pair<int, int>> &edges) : GraphAlgorithm(N, hype, edges), RevAdjList(N) {
        for (int u = 0; u < N; u++) 
            for (int v : AdjList[u]) 
                RevAdjList[v].insert(u); // Creating the transpose graph
    }
    // Topological Sort
    void FillOrder(int u, stack<int> &Stack) {
        events[u].color = 'G';
        for (int v : AdjList[u]) 
            if (events[v].color == 'W') 
                FillOrder(v, Stack); 
        Stack.push(u);
    }
    // Traversing the transpose matrix
    void DFSReverse(int u, int &size) {
        events[u].color = 'G'; 
        size++;
        for (int v : RevAdjList[u]) 
            if (events[v].color == 'W') 
                DFSReverse(v, size);
    }
    void Query() override {
        stack<int> Stack;
        for (int i = 0; i < N; i++) 
            events[i].color = 'W'; // Initialising colors of all vertices to White
        for (int i = 0; i < N; i++) 
            if (events[i].color == 'W') 
                FillOrder(i, Stack); // This creates the topological sort of the vertices
        for (int i = 0; i < N; i++)
            events[i].color = 'W'; // Reinitialising colors of all vertices to White
        int count = 0, max_size = 0; // Count is the number of SCCs and max_size is the maximum number of vertices in a SCC
        // DFS of the transpose graph using the topological order as reference for choosing the vertices
        while (!Stack.empty()) {
            int u = Stack.top();
            Stack.pop();
            if (events[u].color == 'W') { // If the vertex has already been visited, ignore
                int size = 0;
                DFSReverse(u, size);
                max_size = max(max_size, size);
                count++; // Increment the number of SCCs until now by 1
            }
        }
        cout << count << " " << max_size << endl;
    }
};

// Topological Sort
class validOrder : public GraphAlgorithm {
public:
    validOrder(int N, vector<int> &hype, vector<pair<int, int>> &edges) : GraphAlgorithm(N, hype, edges) {}
    // Kahn's algorithm
    void Query() override {
        vector<int> inDegree(N, 0), order; // Initialise indegrees to zero
        for (int u = 0; u < N; u++) 
            for (int v : AdjList[u]) 
                inDegree[v]++; // Get indegrees of all vertices
        priority_queue<int, vector<int>, greater<int>> pq; // This priority queue always stores vertices of indegree 0
        for (int i = 0; i < N; i++) 
            if (inDegree[i] == 0) 
                pq.push(i); // Push vertices of indegree 0 into the min heap
        while (!pq.empty()) {
            int u = pq.top(); // Remove the vertex with lowest index in the input from the min heap
            pq.pop();
            order.push_back(u + 1); // Insert the vertex into the order
            for (int v : AdjList[u]) 
                if (--inDegree[v] == 0) // Removing the vertex removes its out edges thereby reducing indegrees of its neighbours by 1
                    pq.push(v); // Push its neighbour if its indegree becomes 0
        }
        if (order.size() != N) 
            cout << "NO" << endl; // Kahn's algorithm ensures that for a directed cyclic graph, the number of vertices in the sort is less than the number of vertices in the graph
        else {
            for (int x : order) 
                cout << x << " ";
            cout << endl;
        }
    }
};

// Find SCC graph by taking all vertices in a SCC in a single vertex and adding up the hypes and then find the maximum hype path
class maxHype : public GraphAlgorithm {
    vector<set<int>> RevAdjList; // Transpose graph
public:
    maxHype(int N, vector<int> &hype, vector<pair<int, int>> &edges) : GraphAlgorithm(N, hype, edges), RevAdjList(N) {
        for (int u = 0; u < N; u++) 
            for (int v : AdjList[u]) 
                RevAdjList[v].insert(u); // Creating the Transpose graph
    }
    // Topological Sort
    void FillOrder(int u, stack<int> &Stack) {
        events[u].color = 'G';
        for (int v : AdjList[u]) 
            if (events[v].color == 'W') 
                FillOrder(v, Stack);
        Stack.push(u);
    }
    // DFS on the Transpose graph while getting the vertices in each SCC in a separate vector
    void DFSReverse(int u, int &totalHype, vector<int> &component) {
        events[u].color = 'G';
        totalHype += events[u].hypescore;
        component.push_back(u);
        for (int v : RevAdjList[u]) 
            if (events[v].color == 'W') 
                DFSReverse(v, totalHype, component);
    }
    void Query() override {
        stack<int> Stack;
        for (int i = 0; i < N; i++) 
            events[i].color = 'W'; // Initialising colors of all vertices to White
        for (int i = 0; i < N; i++) 
            if (events[i].color == 'W') 
                FillOrder(i, Stack); // This creates the topological sort of the vertices
        
        for (int i = 0; i < N; i++) 
            events[i].color = 'W'; // Reinitialising colors of all vertices to White
        
        vector<int> SCC_Hype; // Hype of each SCC 
        vector<int> SCC_Index(N); // This vector stores the SCC index of each vertex
        vector<vector<int>> SCCGraph; // SCC graph
        int idx = 0;
        while (!Stack.empty()) {
            int u = Stack.top();
            Stack.pop();
            if (events[u].color == 'W') { // If the vertex has already been visited, ignore
                int totalHype = 0;
                vector<int> component;
                DFSReverse(u, totalHype, component); // Populate the component vector with vertices in the SCC and set totalHype to sum of hypescores of each vertex in the SCC
                for (int v : component) 
                    SCC_Index[v] = idx; // Setting the vertex v to be present in SCC idx
                SCC_Hype.push_back(totalHype); // SCC_Hype[idx] = totalHype
                SCCGraph.emplace_back(); // Creates an vector in SCCGraph
                idx++;
            }
        }
        vector<int> inDegree(idx, 0); // Setting indegree of each SCC to 0
        // Creating the SCC graph
        for (int u = 0; u < N; u++) {
            for (int v : AdjList[u]) {
                int sccU = SCC_Index[u], sccV = SCC_Index[v]; // Getting SCC indices of u and v
                if (sccU != sccV && find(SCCGraph[sccU].begin(), SCCGraph[sccU].end(), sccV) == SCCGraph[sccU].end()) { // sccU == sccV then both u and v are present in the same SCC
                    // If u and v are present in different SCCs and there exists an edge between u and v which hasn't been recorded in the SCC graph, then add an edge between sccU and sccV
                    SCCGraph[sccU].push_back(sccV);
                    inDegree[sccV]++;
                }
            }
        }
        queue<int> q;
        vector<int> maxHypeScore(idx, 0); // Set maxHypeScore of all vertices to 0
        for (int i = 0; i < idx; i++) {
            if (inDegree[i] == 0) { // A path can only start with a vertex of indegree 0
                q.push(i); // Push SCC i into the queue
                maxHypeScore[i] = SCC_Hype[i]; // For SCCs with indegree 0, a potential path can only have them as the starting vertex and hence their maxHypeScores are equal to their Hypescores
            }
        }
        int maxHype = 0; // Track maximum hype score
        while (!q.empty()) {
            int u = q.front(); // Remove the front SCC from the queue
            q.pop();
            for (int v : SCCGraph[u]) {
                maxHypeScore[v] = max(maxHypeScore[v], maxHypeScore[u] + SCC_Hype[v]); // maxHypeScore will be maximum in either a path starting with v or v having u as a predecessor in the path
                // Removing the SCC u removes its out edges and hence decrement indegree of SCC v by 1
                if (--inDegree[v] == 0) // If indegree of v becomes 0, push it into the queue
                    q.push(v); // This step ensures that v is encountered only once during the algorithm
            }
            maxHype = max(maxHype, maxHypeScore[u]);
        }
        cout << maxHype << endl;
    }
};

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> hype(N);
    vector<pair<int, int>> edges(M);
    for (int i = 0; i < N; i++) 
        cin >> hype[i];
    for (int i = 0; i < M; i++) 
        cin >> edges[i].first >> edges[i].second;
    int Q, QueryType;
    cin >> Q;
    while (Q--) {
        cin >> QueryType;
        GraphAlgorithm *Graph; // Base pointer
        if (QueryType == 1) 
            Graph = new isCycle(N, hype, edges); // Base pointer points to isCycle object
        else if (QueryType == 2) 
            Graph = new indepComponent(N, hype, edges); // Base pointer points to indepComponent object
        else if (QueryType == 3) 
            Graph = new validOrder(N, hype, edges); // Base pointer points to validOrder object
        else 
            Graph = new maxHype(N, hype, edges); // Base pointer points to maxHype object
        Graph->Query(); // According to the child class object, the appropriate query is called
        delete Graph;
    }
}