#include <iostream>
#include <set>
#include <vector>
using namespace std;

class Graph {
    int n;
    vector<set<int>> edges;
public:
    void set_vertices(int no_of_vertices) {
        n=no_of_vertices;
        edges.resize(no_of_vertices);
    }
    Graph operator +(Graph G2) {
        Graph unionG; 
        int N=max(n,G2.n);
        unionG.set_vertices(N);
        for (int i=0;i<N;i++) {
            if (i<n) {
                for (auto vertex:edges[i]) {
                    unionG.add_edge(i,vertex);
                }
            } if (i<G2.n) {
                for (auto vertex:G2.edges[i]) {
                    unionG.add_edge(i,vertex);
                }
            }
        }
        return unionG;
    }
    Graph operator -(Graph G2) {
        Graph intersection; 
        int N=max(n,G2.n);
        intersection.set_vertices(N);
        for (int i=0;i<min(n,G2.n);i++) {
            for (auto vertex:G2.edges[i]) {
                if (edges[i].find(vertex)!=edges[i].end())
                    intersection.add_edge(i,vertex);
            }
        }
        return intersection;
    }
    Graph operator !() {
        Graph cG;
        cG.set_vertices(n);
        for (int i=0;i<n;i++) {
            for (int j=i+1;j<n;j++) {
                if (edges[i].find(j)==edges[i].end())
                    cG.add_edge(i,j);
            }
        }
        return cG;
    }
    bool isReachable(int u,int v, vector<bool> visited) {
        if (u!=v && (edges[u].size()==0 || edges[v].size()==0))
            return false;
        if (u==v || edges[u].find(v)!=edges[u].end())
            return true;
        visited[u]=true;
        for (auto vertex:edges[u]) {
            if (!visited[vertex] && isReachable(vertex,v,visited)) {
                return true;
            }
        }
        return false;
    }
    bool isReachable(int u,int v) {
        vector<bool> visited(n,false); 
        return isReachable(u,v,visited);
    }
    void add_edge(int u,int v) {
        edges[u].insert(v);
        edges[v].insert(u);
    }
    void remove_edge(int u,int v) {
        edges[u].erase(v);
        edges[v].erase(u);
    }
    friend void operator >> (istream& stream, Graph &G) {
        int n,e,u,v;
        stream >> n >> e;
        G.set_vertices(n);
        for (int i=0;i<e;i++) {
            stream >> u >> v;
            G.add_edge(u,v);
        }
    }
    friend void operator << (ostream& stream, Graph &G) {
        for (int i=0;i<G.n;i++) {
            stream << "Vertex " << i << ":"; 
            for (auto vertex:G.edges[i]) {
                stream << " " << vertex;
            }
            stream << endl;
        }
    }
};

int main() {
    Graph G;    
    string command,s;
    cin >> command;
    while (command!="end") {
        if (command=="Graph") {
            cin >> G;
        } else if (command=="union") {
            Graph g;
            cin >> s;
            cin >> g;
            G=G+g;
        } else if (command=="intersection") {
            Graph g;
            cin >> s;
            cin >> g;
            G=G-g;
        } else if (command=="complement") {
            G=!G;
        } else if (command=="isReachable") {
            int u,v;
            cin >> u >> v;
            if (G.isReachable(u,v))
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
        } else if (command=="add_edge") {
            int u,v;
            cin >> u >> v;
            G.add_edge(u,v);
        } else if (command=="remove_edge") {
            int u,v;
            cin >> u >> v;
            G.remove_edge(u,v);
        } else if (command=="printGraph") {
            cout << G;
        }
        cin >> command;
    }
    return 0;
}