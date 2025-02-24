#include <iostream>
using namespace std;

int derangement(int numDerangement)
{
    if (numDerangement == 0)
        return 1;
    if (numDerangement == 1)
        return 0;

    long Dn2 = 1;
    long Dn1 = 0;
    long Dn = 0;
    for (int i = 2; i <= numDerangement; i++)
    {
        Dn = (i - 1) * (Dn1 + Dn2);
        Dn2 = Dn1;
        Dn1 = Dn;
    }
    return Dn;
}

int main()
{
    int n;
    cin >> n;
    cout << "Number of derangements for " << n << " is " << derangement(n);
}