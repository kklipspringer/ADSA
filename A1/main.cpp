#include <iostream>
#include <string>
#include <vector>
#include <cmath> // For pow 
#include "InfInt.h" // For longer C++ integers. External library.

// Get and format input
std::vector<std::vector<int>> getInput() {
    std::string a, b;
    int B;
    std::cin >> a >> b >> B;

    std::vector<int> vecA, vecB;
    for (char& digit : a) {
        vecA.push_back(digit - '0');
    }
    for (char& digit : b) {
        vecB.push_back(digit - '0');
    }
    std::vector<int> vecBase; 
    vecBase.push_back(B);

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

std::string vecToString(const std::vector<int>& vecIn) {
    std::string result;
    for(int digit : vecIn) {
        // btwn [0,9]
        if((digit >= 0) && (digit <= 9)) {
            result += '0' + digit;
        }
    }
    return result;
}

InfInt toBase10(const InfInt& num, int base) {
    if(base == 10) {
        return num;
    }

    InfInt res = 0;
    InfInt mult = 1;
    InfInt tempNum = num;
    while(tempNum > 0) {
        InfInt digit = tempNum % 10;
        res = res + (digit * mult);
        mult = mult * base;
        tempNum /= 10;
    }

    return res;
}

InfInt fromBase10(const InfInt& num, int base) {
    if(base == 10) {
        return num;
    }

    InfInt res = 0;
    InfInt tempNum = num;
    InfInt mult = 1;

    while(tempNum > 0) {
        InfInt remainder = tempNum % base;
        res += remainder * mult;
        mult = mult * 10; 
        tempNum /= base;
    }

    return res;
}

InfInt karatsuba(const InfInt& x, const InfInt& y) {
    // base case
    if (x < 10 || y < 10) {
        return x * y;
    }

    // Size of nums
    size_t size = std::max(x.numberOfDigits(), y.numberOfDigits());
    size_t half = size / 2;

    // Split
    InfInt high1 = x / InfInt("1" + std::string(half, '0')); 
    InfInt low1 = x % InfInt("1" + std::string(half, '0')); 
    InfInt high2 = y / InfInt("1" + std::string(half, '0')); 
    InfInt low2 = y % InfInt("1" + std::string(half, '0')); 

    // products
    InfInt z0 = karatsuba(low1, low2);
    InfInt z1 = karatsuba((low1 + high1), (low2 + high2));
    InfInt z2 = karatsuba(high1, high2);
    // return final product
    return z2 * InfInt("1" + std::string(2 * half, '0')) + (z1 - z2 - z0) * InfInt("1" + std::string(half, '0')) + z0;
}


int main(void) {
    std::vector<int> schoolRes;

    std::vector<std::vector<int>> inputs = getInput();
    std::vector<int> a = inputs[0], b = inputs[1];
    int base = inputs[2][0];

    schoolRes = schoolAddition(a, b, base);
    
    // I'm first converting a and b, from vectors to strings. 
    // ..those strings are converted to a base of 10. 
    // ..then karatsuba is performed on those numbers in Base 10.     
    // ..then finally, I convert it to the original base. 
    //-----------------------------------------------------------
    InfInt stringA = vecToString(a);
    InfInt stringB = vecToString(b);

    InfInt baseTenA = toBase10(stringA, base);
    InfInt baseTenB = toBase10(stringB, base);

    InfInt karatRes = karatsuba(baseTenA, baseTenB);

    InfInt karatFinal = fromBase10(karatRes, base);
    //-----------------------------------------------------------

    // print school addition result 
    for(size_t i = 0; i < schoolRes.size(); i++) {
        std::cout << schoolRes[i];
    }
    
    std::cout << " " << karatFinal << " 0";

    // debug
    // std::cout << "A: " << regularA << " ";
    // std::cout << "B:" << regularB;

    return 0;
}