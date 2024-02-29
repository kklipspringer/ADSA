#include <iostream>
#include <string>
#include <vector>
#include <cmath> // For pow function

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

std::vector<int> toBase10(const std::vector<int>& number, int base) {
    int result = 0;
    int power = 0; // Start from the least significant digit

    for (auto it = number.rbegin(); it != number.rend(); it++) {
        result += *it * std::pow(base, power++);
    }

    std::vector<int> resultVec;
    if (result == 0) {
        resultVec.push_back(0);
    } else {
        while (result > 0) {
            resultVec.insert(resultVec.begin(), result % 10);
            result /= 10;
        }
    }
    return resultVec;
}

std::vector<int> fromBase10(const std::vector<int>& number, int base) {
    int value = 0;
    for (size_t i = 0; i < number.size(); i++) {
        value = value * 10 + number[i];
    }

    std::vector<int> res;
    if (value == 0) {
        res.push_back(0);
    } else {
        while (value > 0) {
            res.insert(res.begin(), value % base);
            value /= base;
        }
    }

    return res;
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

std::vector<int> karatsubaMult(std::vector<int> a, std::vector<int> b) {

}

int main(void) {
    std::vector<int> schoolRes, karatRes;

    std::vector<std::vector<int>> inputs = getInput();
    std::vector<int> a = inputs[0], b = inputs[1];
    int base = inputs[2][0];

    schoolRes = schoolAddition(a, b, base);

    std::vector<int> aNewBase = toBase10(a, base);
    std::vector<int> bNewBase = toBase10(b, base);


    karatRes = karatsubaMult(aNewBase, bNewBase);
    karatRes = fromBase10(karatRes, base); 

    for(size_t i = 0; i < schoolRes.size(); i++) {
        std::cout << schoolRes[i];
    }
    
    std::cout << " ";

    for(size_t i = 0; i < karatRes.size(); i++) {
        std::cout << karatRes[i];
    }

    return 0;
}
