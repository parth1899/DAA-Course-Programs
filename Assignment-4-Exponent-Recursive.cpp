// Fast Modular Exponent (Recursive)

#include <iostream>
using namespace std;

long long recursive(long long a, long long b, long long n) {
    if(b == 0) return 1;
    if(b == 1) return a % n;

    if(b % 2 == 0) {
        // power is even
        long long temp = recursive(a, b / 2, n);
        return (temp * temp) % n;
    }
    else {
        // power is odd
        return (a * recursive(a, b - 1, n)) % n;
    }
}

int main() {
    long long a, b, n;

    // Input: a, b, n
    // Output: a^b mod n

    cout << "Enter the base: ";
    cin >> a;
    cout << "Enter the exponent: ";
    cin >> b;
    cout << "Enter the modulus: ";
    cin >> n;

    cout << "Result using brute force: " << recursive(a, b, n) << endl;
}