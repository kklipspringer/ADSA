#include <vector>
#include <iostream>
#include <string>

// Please note, that I've replaced I1 with 'a', and I2 with 'b',

// Reads and formats input into vector forms
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

// Add leading zeroes, if digits(a) != digits(b)
void addZeroes(std::vector<int>& a, std::vector<int>& b) {
    int lenA = a.size(), lenB = b.size();
    int deltaDigits = lenA - lenB;
    if(lenA > lenB) { 
        b.insert(b.begin(), abs(deltaDigits), 0); // make 'b' longer
    } else if (lenA < lenB) { 
        a.insert(a.begin(), abs(deltaDigits), 0); // make 'a' longer
    } else {
        return; // length(a) = length(b)
    }
}

// Split a vector, into two equal parts (for Karatsuba multiplication)
std::vector<std::vector<int>> splitVec(const std::vector<int>& a) {
    size_t half = a.size() / 2;
    std::vector<int> left(a.begin(), a.begin() + half); // high
    std::vector<int> right(a.begin() + half, a.end()); // lower

    std::vector<std::vector<int>> splitParts;
    splitParts.push_back(left);
    splitParts.push_back(right);

    return splitParts;
}


// Addition (vector form) with different bases
std::vector<int> schoolAddition(std::vector<int> a, std::vector<int> b, int base) {
    std::vector<int> s; // final sum
    int carry = 0;


    for(int i = (a.size() - 1); i >= 0; i--) {
        int rawSum = a[i] + b[i] + carry;
        s.insert(s.begin(), rawSum % base); // prepend final value to the s vector
        carry = rawSum / base; // work out the next carry
    }

    // Done iterating, but there's still a carry left. Prepend that carry. 
    if(carry > 0) {
        s.insert(s.begin(), carry);
    }   

    return s;
}

// Subtraction (vector form) with different bases
std::vector<int> schoolSubtraction(std::vector<int> a, std::vector<int> b, int base) {
    std::vector<int> res;
    int borrow = 0;

    for(int i = (a.size() - 1); i >= 0; i++) {
        int sub = a[i] - b[i] - borrow;
        
        // carry over if subtraction negative
        if(sub < 0) {
            sub += base;  
            borrow = 1; 
        } else {
            borrow = 0; // reset borrow
        }

        res.insert(res.begin(), sub);
    }

    // Take away zeroes at front
    while((res.size() > 1) && (res[0] == 0)) {
        res.erase(res.begin());
    }

    return res;
}

// Karatsuba Multiplication. 
std::vector<int> karatsubaMult(std::vector<int> a, std::vector<int> b, int base) {

}


int main() {
    // Declaration of final results 
    std::vector<int> schoolRes, karatRes; 

    // Ask for input, and store in their own vectors: 
    // Access order: [0: vecA, 1:vecB, 2: Base] 
    std::vector<std::vector<int>> inputs = getInput();
    // Separate into 2 vectors. Separate base into an int
    std::vector<int> a = inputs[0], b = inputs[1];
    addZeroes(a, b); // add zeroes, if numbers are different lengths
    int base = inputs[2][0]; 

    // School Addition: 
    schoolRes = schoolAddition(a, b, base);
    size_t schoolSize = schoolRes.size();

    // Karatsuba Multiplication:
    karatRes = karatsubaMult(a, b, base);
    size_t karatSize = karatRes.size();

    // Format the outputs. Addition_Multiplication_0 (no division)
    for(size_t i = 0; i < schoolSize; i++) { 
        std::cout << schoolRes[i];
    }

    std::cout << " ";

    for(size_t i = 0; i < karatSize; i++) {
        std::cout << karatRes[i];
    }

    std::cout << " 0"; 

    return 0;
}