#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

int memoized_cutrod(int p[], int j, int c, int r[], int s[])
{
    if (r[j] >= 0)
        return r[j];
    int q;
    q = p[j];
    s[j] = j;
    for (int i = 0; i < j; ++i)
    {
        int tmp = memoized_cutrod(p, j - i - 1, c, r, s) + p[i] - c;
        if (q < tmp)
        {
            q = tmp;
            s[j] = i;
        }
    }
    r[j] = q;
    return q;
}

int cutrod(int p[], int n, int c, list<int> &l)
{
    int *r = new int[n], *s = new int[n];
    for (int i = 0; i < n; ++i)
        r[i] = -1;
    int tmp = memoized_cutrod(p, n - 1, c, r, s);
    while (n > 0)
    {
        l.push_back(s[n - 1] + 1);
        n -= s[n - 1] + 1;
    }
    delete[] r;
    delete[] s;
    return tmp;
}

int main()
{
    int p[] = {1, 5, 8, 9, 10, 17, 17, 20, 23, 24}, n = 10, c = 1;
    list<int> l;
    list<int>::iterator lit;
    int a = cutrod(p, n, c, l);
    cout << a << '\n';
    for (lit = l.begin(); lit != l.end(); ++lit)
    {
        cout << *lit << ' ';
    }
    return 0;
}