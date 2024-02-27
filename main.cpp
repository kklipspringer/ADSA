#include <vector>
#include <iostream>
#include <string>

std::vector<std::vector<int>> getInput() {
    // Read inputs 'a' and 'b' as strings
    // Read input B (Base) as an int
    std::string a, b;
    int B;
    std::cin >> a >> b >> B; 

    // Chop up strings a, and b, into vectors with integer elements
    std::vector<int> vecA, vecB;
    for (char &digit : a) {
        vecA.push_back(digit - '0'); 
    }
    for (char &digit : b) {
        vecB.push_back(digit - '0'); 
    }
    std::vector<int> vecBase; // Single element vector, containing B (Base). B is between [2, 10]
    vecBase.push_back(B);

    // return vector<vector<int>> (contains a, b, and base, in their own vectors)
    std::vector<std::vector<int>> result;
    result.push_back(vecA);
    result.push_back(vecB);
    result.push_back(vecBase);

    return result;
}

int main() {
    // Ask for input, and store in their own vectors: 
    // Access order: [vecA, vecB, Base] 
    //               [   0,   1,    2 ]
    std::vector<std::vector<int>> inputs = getInput();

    int lenVecA = ;
    int lenVec B = ;

    if() {
        
    }

    return 0;
}
