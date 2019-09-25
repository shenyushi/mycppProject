#include <iostream>
using namespace std;

int fbnq(int n)
{
    int *r = new int[n + 1];
    r[0] = 0;
    r[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        r[i] = r[i - 1] + r[i - 2];
    }
    int tmp = r[n];
    delete[] r;
    return tmp;
}

int main()
{
    int f = fbnq(40);
    cout << f << endl;
    return 0;
}