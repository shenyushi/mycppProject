#include <iostream>

#include <list>

using namespace std;

int cutrod(int p[], int n, int c, list<int> &l)
{
    int *r = new int[n], *s = new int[n];
    for (int j = 0; j < n; ++j)
    {
        int q = p[j];
        s[j] = j;
        for (int i = 0; i < j; ++i)
        {
            int t = p[i] + r[j - i - 1] - c;
            if (q < t)
            {
                q = t;
                s[j] = i;
            }
        }
        r[j] = q;
    }
    int tmp = r[n - 1];
    while (n > 0)
    {
        l.push_back(s[n - 1] + 1);
        n = n - s[n - 1] - 1;
    }
    delete[] r;
    delete[] s;
    return tmp;
}

int main()
{
    int p[] = {1, 5, 8, 9, 10, 17, 17, 20, 23, 24}, n = 10, c = 1;
    list<int> l;
    int pmax = cutrod(p, n, c, l);
    cout << pmax << endl;
    list<int>::iterator lit;
    for (lit = l.begin(); lit != l.end(); ++lit)
    {
        cout << *lit << ' ';
    }
    return 0;
}
