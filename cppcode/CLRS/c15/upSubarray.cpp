#include <iostream>

using namespace std;

void upSubarray(int a[], int al, int b[], int &bl)
{
    int *cc = new int[al], *dd = new int[al], maxn = 0;
    for (int i = 1; i < al; ++i)
        cc[i] = 0;
    cc[0] = 1;
    for (int i = 1; i < al; ++i)
    {
        int q = 0;
        for (int j = 0; j < i; ++j)
            if (a[j] < a[i] && cc[j] > q)
            {
                q = cc[j];
                dd[i] = j;
            }
        cc[i] = q + 1;
        if (q + 1 > cc[maxn])
            maxn = i;
    }
    bl = cc[maxn];
    int tmp = bl, t = maxn;
    while (tmp--)
    {
        b[tmp] = a[t];
        t = dd[t];
    }
    delete[] cc;
    delete[] dd;
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
    int *k = new int[l], kl = 0;
    upSubarray(test, l, k, kl);
    cout << kl << endl;
    for (int i = 0; i < kl; ++i)
        cout << k[i] << ' ';
    delete[] k;
    return 0;
}