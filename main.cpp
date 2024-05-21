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



int main() {
    // Get input. First split by spaces. 
    string input;
    getline(cin, input); 
    vector<string> parts = split(input, ' ');

    // Then examine each character and add as entries. 
    return 0;
}
