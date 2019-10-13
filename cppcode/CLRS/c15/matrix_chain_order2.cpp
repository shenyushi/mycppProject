#include <iostream>
using namespace std;

int lookupChain(int **m, int p[], int i, int j)
{
    if (m[i][j] < 2147483647)
    {
        return m[i][j];
    }
    if (i == j)
    {
        m[i][j] = 0;
    }
    else
    {
        for (int k = i; k < j; ++k)
        {
            int q = lookupChain(m, p, i, k) + lookupChain(m, p, k + 1, j) + p[i] * p[k + 1] * p[j + 1];
            if (q < m[i][j])
                m[i][j] = q;
        }
    }
    return m[i][j];
}

int memoizedMatrixChain(int p[], int l)
{ 
    int n = l - 1;
    int **m = new int *[n];
    for (int i = 0; i < n; ++i)
    {
        m[i] = new int[n];
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = i; j < n; ++j)
        {
            m[i][j] = 2147483647;
        }
    }
    return lookupChain(m, p, 0, n - 1);
}

int main()
{
    int p[] = {5, 10, 3, 12, 5, 50, 6}, l = 7;
    cout << memoizedMatrixChain(p, l);
    return 0;
}