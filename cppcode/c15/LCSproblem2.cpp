#include <iostream>
using namespace std;

int LCSlength(int x[], int m, int y[], int n)
{
    int tmp = 0;
    if (m < n)
    {
        int *c = new int[m + 1];
        for (int i = 0; i < m + 1; ++i)
            c[i] = 0;
        for (int j = 1; j < n + 1; ++j)
        {
            int leftup = 0;
            for (int i = 1; i < m + 1; ++i)
            {
                int up = c[i], left = c[i - 1];
                if (x[i - 1] == y[j - 1])
                    c[i] = leftup + 1;
                else if (left < up)
                    c[i] = up;
                else
                    c[i] = left;
                leftup = up;
            }
        }
        tmp = c[m];
        delete[] c;
    }
    else
    {
        int *c = new int[n + 1];
        for (int i = 0; i < n + 1; ++i)
            c[i] = 0;
        for (int j = 1; j < m + 1; ++j)
        {
            int left = 0;
            for (int i = 1; i < n + 1; ++i)
            {
                int leftup = c[i - 1], up = c[i];
                if (y[i - 1] == x[j - 1])
                    c[i] = leftup + 1;
                else if (left < up)
                    c[i] = up;
                else
                    c[i] = left;
                left = c[i];
            }
        }
        tmp = c[n];
        delete[] c;
    }
    return tmp;
}

int main()
{
    int x[] = {1, 0, 0, 1, 0, 1, 0, 1}, y[] = {0, 1, 0, 1, 1, 0, 1, 1, 0};
    int xl = 8, yl = 9;
    int p = LCSlength(x, xl, y, yl);
    cout << p << endl;
    return 0;
}