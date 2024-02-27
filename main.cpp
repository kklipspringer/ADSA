#include <vector>
#include <iostream>
#include <string>

// Please note, that I've replaced I1 with 'a', and I2 with 'b',

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

int schoolAddition(std::vector<int> a, std::vector<int> b, int base) {
    // Add leading zeroes, if digits(a) != digits(b) 
    int lenA = a.size(), lenB = b.size();
    int deltaDigits = lenA - lenB;
    if(deltaDigits > 0) {
        // all leading zeroes to a
        for() {

        }
    } else if (deltaDigits < 0) {
        // add leading zeroes to b
        for() {
            
        }
    } 
}

int main() {
    // DECLARATION OF FINAL RESULTS:
    int schoolRes, karatRes, divRes;

    // INPUT: /////////////////////////////////////////////////////////////////
    // Ask for input, and store in their own vectors: 
    // Access order: [0: vecA, 1:vecB, 2: Base] 
    std::vector<std::vector<int>> inputs = getInput();
    // Seperate into 2 vectors. Seperate base into an int
    std::vector<int> a = inputs[0], b = inputs[1];
    int base = inputs[2][0]; 

    // SCHOOL ADDITION: /////////////////////////////////////////////////////////////////


    return 0;
}
