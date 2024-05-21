#include <iostream>
#include <vector>
#include <sstream>

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
    
}

vector<vector<int>> makeGraph(vector<vector<int>> towns, vector<vector<int>> build, vector<vector<int>> destroy) {

}

int main() {
    // Parse Input
        // Example 1: 000,000,000 ABD,BAC,DCA ABD,BAC,DCA
        // Example 2: 011,101,110 ABD,BAC,DCA ABD,BAC,DCA
    string input;
    getline(cin, input); 
    vector<string> parts = split(input, ' ');

    vector<vector<int>> towns = stringTo2DVector(parts[0]);
    vector<vector<int>> build = stringTo2DVector(parts[1]);
    vector<vector<int>> destroy = stringTo2DVector(parts[2]);

    // Construct Graph. Basically if towns[i][j] exists, consider build or destroy costs. 
}