#include <iostream>
using namespace std;

int ff(int x[], int xl, int y[], int yl, int **cc)
{
    if (xl == 0 || yl == 0)
        return 0;
    if (x[xl - 1] == y[yl - 1])
        if (cc[xl - 1][yl - 1] < 0)
            return ff(x, xl - 1, y, yl - 1, cc) + 1;
        else
            return cc[xl - 1][yl - 1] + 1;
    else
    {
        if (cc[xl][yl - 1] < 0)
            cc[xl][yl - 1] = ff(x, xl, y, yl - 1, cc);
        if (cc[xl - 1][yl] < 0)
            cc[xl - 1][yl] = ff(x, xl - 1, y, yl, cc);
        if (cc[xl][yl - 1] > cc[xl - 1][yl])
            return cc[xl][yl - 1];
        else
            return cc[xl - 1][yl];
    }
}

int LCSlength(int x[], int xl, int y[], int yl, int *&z, int &zl)
{
    int **cc = new int *[xl + 1];
    for (int i = 0; i < xl + 1; ++i)
        cc[i] = new int[yl + 1];
    for (int i = 0; i < xl + 1; ++i)
        cc[i][0] = 0;
    for (int j = 1; j < yl + 1; ++j)
        cc[0][j] = 0;
    for (int i = 1; i < xl + 1; ++i)
        for (int j = 1; j < yl + 1; ++j)
            cc[i][j] = -1;
    int tmp = ff(x, xl, y, yl, cc);
    int *tz = new int[zl], top = 0;
    int i = xl, j = yl;
    while (i > 0 && j > 0)
    {
        if (x[i - 1] == y[j - 1])
        {
            tz[top++] = x[i - 1];
            --i;
            --j;
        }
        else if (cc[i][j - 1] > cc[i - 1][j])
            --j;
        else
            --i;
    }
    while (top > 0)
        z[zl++] = tz[--top];
    for (int i = 0; i < xl + 1; ++i)
        delete[] cc[i];
    delete[] cc;
    return tmp;
}

int main()
{
    int x[] = {1, 0, 0, 1, 0, 1, 0, 1}, y[] = {0, 1, 0, 1, 1, 0, 1, 1, 0};
    int xl = 8, yl = 9;
    int *z = new int[xl], zl = 0;
    int p = LCSlength(x, xl, y, yl, z, zl);
    cout << p << endl;
    for (int i = 0; i < zl; ++i)
        cout << z[i] << ' ';
    delete[] z;
    return 0;
}