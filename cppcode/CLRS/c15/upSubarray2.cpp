#include <iostream>
#include <algorithm>
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
    cout << c[m][n] << endl;
    LCSprint(b, x, m, n);
    for (int i = 0; i < m + 1; ++i)
    {
        delete[] b[i];
        delete[] c[i];
    }
    delete[] b;
    delete[] c;
}

void quickSort(int a[], int start, int end)
{
    if (start >= end)
        return;
    int key = a[end];
    int i = start, j = start;
    for (; j <= end; ++j)
    {
        if (a[j] < key)
        {
            int tmp = a[i];
            a[i++] = a[j];
            a[j] = tmp;
        }
    }
    a[end] = a[i];
    a[i] = key;
    quickSort(a, start, i - 1);
    quickSort(a, i + 1, end);
}

void quickSort(int a[], int l)
{
    quickSort(a, 0, l - 1);
}

void upSubarray(int a[], int al)
{
    int *c = new int[al];
    for (int i = 0; i < al; ++i)
        c[i] = a[i];
    quickSort(a, al);
    LCSlength(a, al, c, al);
}

#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(NULL));
    int l = 1000;
    int test[l];
    for (int i = 0; i < 1000; ++i)
        test[i] = rand() % 1000;
    upSubarray(test, l);
    return 0;
}