#include <iostream>
#include <string>
#include <algorithm>

// Utility function to add two large numbers represented as strings.
std::string addStrings(const std::string& num1, const std::string& num2) {
    std::string result;
    int carry = 0;
    int i = num1.size() - 1, j = num2.size() - 1;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += num1[i--] - '0';
        if (j >= 0) sum += num2[j--] - '0';
        result.push_back(sum % 10 + '0');
        carry = sum / 10;
    }

    std::reverse(result.begin(), result.end());
    return result;
}

// Utility function to subtract two large numbers represented as strings.
std::string subtractStrings(const std::string& larger, const std::string& smaller) {
    std::string result;
    int carry = 0;
    int n1 = larger.size(), n2 = smaller.size();
    std::reverse(larger.begin(), larger.end());
    std::reverse(smaller.begin(), smaller.end());

    for (int i = 0; i < n2; i++) {
        int sub = ((larger[i] - '0') - (smaller[i] - '0') - carry);
        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        } else carry = 0;

        result.push_back(sub + '0');
    }

    for (int i = n2; i < n1; i++) {
        int sub = ((larger[i] - '0') - carry);
        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        } else carry = 0;

        result.push_back(sub + '0');
    }

    std::reverse(result.begin(), result.end());
    return result;
}

// Recursive Karatsuba multiplication for large numbers represented as strings.
std::string karatsuba(const std::string& x, const std::string& y) {
    int n = std::max(x.size(), y.size());
    if (n == 1) return std::to_string((x[0] - '0') * (y[0] - '0'));

    n = (n / 2) + (n % 2);
    std::string a = x.size() > n ? x.substr(0, x.size() - n) : "0";
    std::string b = x.size() > n ? x.substr(x.size() - n) : x;
    std::string c = y.size() > n ? y.substr(0, y.size() - n) : "0";
    std::string d = y.size() > n ? y.substr(y.size() - n) : y;

    std::string ac = karatsuba(a, c);
    std::string bd = karatsuba(b, d);
    std::string ab_cd = karatsuba(addStrings(a, b), addStrings(c, d));
    std::string ad_bc = subtractStrings(ab_cd, addStrings(ac, bd));

    for (int i = 0; i < 2 * n; i++) ac += "0";  // Equivalent to multiplying by 10^(2*n)
    for (int i = 0; i < n; i++) ad_bc += "0";  // Equivalent to multiplying by 10^n

    std::string result = addStrings(addStrings(ac, ad_bc), bd);
    return result;
}

int main() {
    std::string x, y;
    std::cout << "Enter two numbers (x and y): ";
    std::cin >> x >> y;

    std::string result = karatsuba(x, y);
    std::cout << "Result: " << result << std::endl;

    return 0;
}
