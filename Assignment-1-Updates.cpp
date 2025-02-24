#include <iostream>
using namespace std;

double calculateAverageUpdates(int n)
{
    int totalUpdates = n;
    for (int i = 1; i <= n - 1; i++)
    {
        totalUpdates += i * (i + 1);
    }

    long long factorial = 1;
    for (int i = 2; i <= n; i++)
    {
        factorial *= i;
    }

    cout << totalUpdates << "/" << factorial << endl;
    return static_cast<double> (totalUpdates / factorial);
}

int main() {

    int n;
    cin >> n;
    double averageUpdates = calculateAverageUpdates(n);
    cout << "Average number of updates to the max variable per permutation for n = " << n << " is: " << averageUpdates << endl;
    return 0;
}