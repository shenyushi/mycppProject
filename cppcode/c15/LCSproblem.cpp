#include <iostream>
using namespace std;

void LCSprint(int **b, int x[], int i, int j)
{
    if (i == 0 && j == 0)
    {
        return;
    }
    if (b[i][j] == 1)
    {
        LCSprint(b, x, i - 1, j - 1);
        cout << x[i - 1] << ' ';
    }
    else if (b[i][j] == 2)
    {
        LCSprint(b, x, i - 1, j);
    }
    else if (b[i][j] == 3)
    {
        LCSprint(b, x, i, j - 1);
    }
}

void LCSlength(int x[], int m, int y[], int n)
{
    int **b = new int *[m + 1], **c = new int *[m + 1];
    for (int i = 0; i < m + 1; ++i)
    {
        b[i] = new int[n + 1];
        c[i] = new int[n + 1];
    }
    for (int i = 0; i < m + 1; ++i)
    {
        c[i][0] = 0;
    }
    for (int j = 1; j < n + 1; ++j)
    {
        c[0][j] = 0;
    }
    for (int i = 1; i < m + 1; ++i)
    {
        for (int j = 1; j < n + 1; ++j)
        {
            if (x[i - 1] == y[j - 1])
            {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 1; //left-up
            }
            else if (c[i - 1][j] > c[i][j - 1])
            {
                c[i][j] = c[i - 1][j];
                b[i][j] = 2; //up
            }
            else
            {
                c[i][j] = c[i][j - 1];
                b[i][j] = 3; //left
            }
        }
    }
    LCSprint(b, x, m, n);
    for (int i = 0; i < m + 1; ++i)
    {
        delete[] b[i];
        delete[] c[i];
    }
    delete[] b;
    delete[] c;
}

int main()
{
    int x[] = {1, 2, 3, 2, 4, 1, 2}, y[] = {2, 4, 3, 1, 2, 1};
    int xl = 7, yl = 6;
    LCSlength(x, xl, y, yl);
    return 0;
}