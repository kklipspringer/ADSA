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
    addZeroes(a, b);
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
    // Normalize the length of numbers
    addZeroes(a, b);
    size_t n = a.size();

    // Base case for recursion
    if (n == 1) {
        int product = a[0] * b[0];
        std::vector<int> result;
        if (product >= base) {
            result.push_back(product / base); // Carry
            result.push_back(product % base); // Remainder
        } else {
            result.push_back(product);
        }
        return result;
    }

    // Calculate the size of the numbers for splitting
    size_t m = n / 2;

    // Splitting the numbers into high and low parts
    std::vector<int> aLow(a.begin() + m, a.end()), aHigh(a.begin(), a.begin() + m);
    std::vector<int> bLow(b.begin() + m, b.end()), bHigh(b.begin(), b.begin() + m);

    // Ensure aHigh/aLow and bHigh/bLow are of equal length for each pair
    addZeroes(aHigh, aLow); // Not typically necessary but included for completeness
    addZeroes(bHigh, bLow); // Not typically necessary but included for completeness

    // 3 recursive calls of Karatsuba multiplication
    std::vector<int> z0 = karatsubaMult(aLow, bLow, base);
    std::vector<int> z1 = karatsubaMult(schoolAddition(aLow, aHigh, base), schoolAddition(bLow, bHigh, base), base);
    std::vector<int> z2 = karatsubaMult(aHigh, bHigh, base);

    // Ensuring z1, z0, and z2 are properly prepared for subtraction and addition
    addZeroes(z1, z0);
    addZeroes(z1, z2);

    // Subtracting the sums we don't need
    z1 = schoolSubtraction(z1, z0, base);
    z1 = schoolSubtraction(z1, z2, base);

    // Assembling the high, middle, and low parts of the multiplication
    std::vector<int> result, temp;

    // Add z2 * base^(2*m)
    temp = z2;
    temp.insert(temp.end(), 2 * m, 0);
    result = schoolAddition(result, temp, base);

    // Add z1 * base^m
    temp = z1;
    temp.insert(temp.end(), m, 0);
    result = schoolAddition(result, temp, base);

    // Add z0
    result = schoolAddition(result, z0, base);

    // Remove leading zeroes, if any
    while (result.size() > 1 && result[0] == 0) {
        result.erase(result.begin());
    }

    return result;
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