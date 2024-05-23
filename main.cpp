#include <iostream>
#include <vector>
#include <sstream>

// country, build, destroy

using namespace std;

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token; 
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Return 2D vectors. Do necessary conversion from letters to numbers. 
    /*
                   _______
        abc,def    |a b c|
                   |d e f|
    */
vector<vector<int>> stringTo2DVector(string splitLine) {
    vector<vector<int>> intVector;
    vector<string> rows = split(splitLine, ',');
    for(string row : rows) {
        vector<int> intRow;
        for(char c : row) {
            if(isdigit(c)) {
                intRow.push_back(c - '0'); // character to integer
            } 
            
            if(isalpha(c)) {
                intRow.push_back(c - 'A'); // letter to number
            } 
        }
        intVector.push_back(intRow);
    }
    return intVector;
}

vector<vector<int>> makeGraph(vector<vector<int>> country, vector<vector<int>> build, vector<vector<int>> destroy) {
    // Connection at Country[x][y]?
        // Yes: What is the destroy cost? 
        // No: What is the build cost? 

    // Doing this to initialise the final graph, and I'm considering build to be the default state. 
    vector<vector<int>> finalGraph = build; 
    
    for(size_t i = 0; i < country.size(); i++) {
        for(size_t j = 0; j < country[i].size(); j++) {
            if(country[i][j] == 1) {
                finalGraph[i][j] = (destroy[i][j] * -1);
            } 
            // if(country[i][j] == 0) {
            //     finalGraph[i][j] = build[i][j];
            // } 
        }
    }

    return finalGraph;
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

    // Construct Graph. 
    vector<vector<int>> graph = makeGraph(country, build, destroy);

    for(size_t i = 0; i < graph.size(); i++) {
        for(size_t j = 0; j < graph[i].size(); j++) {
            cout << graph[i][j] << " ";
        }
        cout << endl; 
    }

    // Perform Kruskal's on Graph.
    return 0; 
}