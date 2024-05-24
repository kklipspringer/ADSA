#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct Edge {
    int u;
    int v;
    int cost; 
    Edge(int uIn, int vIn, int costIn) {
        u = uIn;
        v = vIn;
        cost = costIn;
    }
};

bool compareEdges(const Edge& a, const Edge& b) {
    return a.cost < b.cost;
}

class UnionFind {
private:
    vector<int> parent, rank;
    
public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        for(int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if(parent[u] != u)
            parent[u] = find(parent[u]);
        return parent[u];
    }

    bool unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if(rootU != rootV) {
            if(rank[rootU] > rank[rootV])
                parent[rootV] = rootU;
            else {
                parent[rootU] = rootV;
                if (rank[rootU] == rank[rootV])
                    rank[rootV]++;
            }
            return true;
        }
        return false;
    }
};

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token; 
    istringstream tokenStream(s);
    while(getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Convert characters to integers
// System is:
    // [A,B] = [0, 25]
    // [a,b] = [27, 53]

int charToCost(char c) {
    if('0' <= c && c <= '9') {
        return c - '0';
    }
    if('A' <= c && c <= 'Z') {
        return c - 'A';
    }
    if('a' <= c && c <= 'z') {
        return c - 'a' + 26;
    }

    return 0; 
}

// Return 2D vectors. Do necessary conversion from letters to numbers. 
    /*
                   _______
        abc,def    |a b c|
                   |d e f|
    */
vector<vector<int>> stringTo2DVector(const string& splitLine) {
    vector<string> rows = split(splitLine, ',');
    vector<vector<int>> finalVector(rows.size(), vector<int>(rows[0].size())); 

    for(size_t i = 0; i < rows.size(); i++) {
        for(size_t j = 0; j < rows[i].size(); j++) {
            finalVector[i][j] = charToCost(rows[i][j]);
        }
    }

    return finalVector;
}

vector<Edge> makeEdgeList(const vector<vector<int>>& country, const vector<vector<int>>& build, const vector<vector<int>>& destroy) {
    vector<Edge> edges;
    int n = country.size();
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(country[i][j] == 1) {
                edges.emplace_back(i, j, -destroy[i][j]); 
            }

            if(country[i][j] == 0) {
                edges.emplace_back(i, j, build[i][j]);
            }
        }
    }
    return edges;
}

bool isEdgeInMST(int u, int v, const vector<Edge>& mst) {
    for(const Edge& edge : mst) {
        if ((edge.u == u && edge.v == v) || (edge.u == v && edge.v == u)) {
            return true;
        }
    }
    return false;
}

int main() {
    // Parse Input
    // Example 1: 000,000,000 ABD,BAC,DCA ABD,BAC,DCA
    // Example 2: 011,101,110 ABD,BAC,DCA ABD,BAC,DCA
    string input;
    getline(cin, input); 
    vector<string> parts = split(input, ' ');

    vector<vector<int>> country = stringTo2DVector(parts[0]);
    vector<vector<int>> build = stringTo2DVector(parts[1]);
    vector<vector<int>> destroy = stringTo2DVector(parts[2]);

    vector<Edge> edges = makeEdgeList(country, build, destroy);
    sort(edges.begin(), edges.end(), compareEdges);

    UnionFind uf(country.size());
    vector<Edge> mst;
    int mstCost = 0;

    for(const Edge& edge : edges) {
        if(uf.find(edge.u) != uf.find(edge.v)) {
            uf.unionSets(edge.u, edge.v);
            mst.push_back(edge);
            mstCost += edge.cost;
        }
    }

    int cost = 0;

    for (const Edge& edge : mst) {
        if(country[edge.u][edge.v] == 0) {
            cost += build[edge.u][edge.v];
        }
    }

    for(size_t i = 0; i < country.size(); i++) {
        for(size_t j = i + 1; j < country.size(); j++) {
            if(country[i][j] == 1 && !isEdgeInMST(i, j, mst)) {
                cost += destroy[i][j];
            }
        }
    }

    cout << cost << endl;

    return 0;
}