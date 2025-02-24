// Fast Modular Exponent: Brute Force (Iterative)

#include <iostream>
using namespace std;

long long bruteForce(long long a, long long b, long long n) {
    long long result = 1;
    for(long long i = 0; i < b; i++) {
        result = (result * a) % n;
    }

    return result;
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

    cout << "Result using brute force: " << bruteForce(a, b, n) << endl;

    return 0;
}