int binarySearch(int b[], int key, int end)
{
    int start = 0, mid;
    while (true)
    {
        mid = (start + end) / 2;
        if (key < b[mid])
        {
            if (key > b[mid - 1])
                return mid;
            end = mid - 1;
        }
        else if (key > b[mid])
        {
            if (key < b[mid + 1])
                return mid + 1;
            start = mid + 1;
        }
        else
            return mid;
    }
}

int LISproblem(int a[], int l, int b[])
{
    int len = 0;
    b[0] = a[0];
    for (int i = 1; i < l; ++i)
    {
        if (a[i] <= b[0])
            b[0] = a[i];
        else if (a[i] > b[len])
            b[++len] = a[i];
        else
            b[binarySearch(b, a[i], len)] = a[i];
    }
    int tl = 0;
    b[0] = a[0];
    for (int i = 1; i < l; ++i)
    {
        if (tl == len)
            break;
        if (a[i] <= b[0])
            b[0] = a[i];
        else if (a[i] > b[tl])
            b[++tl] = a[i];
        else
            b[binarySearch(b, a[i], tl)] = a[i];
    }
    return len + 1;
}

#include <cstdio>
#include <cstdlib>
#include <ctime>
int main()
{
    srand(time(NULL));
    int n = 100000;
    int *a = new int[n], *b = new int[n];
    for (int i = 0; i < n; ++i)
        a[i] = rand() % n;
    int bn = LISproblem(a, n, b);
    printf("%d\n", bn);
    for (int i = 0; i < bn; ++i)
        printf("%d ", b[i]);
    delete[] a;
    delete[] b;
    return 0;
}