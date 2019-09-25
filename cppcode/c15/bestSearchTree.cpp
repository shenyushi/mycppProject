#include <cstdio>
#include <ctime>
#include <cstdlib>

void printTree(int **root, int left, int mid, int right)
{
    if (left != mid)
    {
        int midL = root[left][mid - 1];
        printf("%d为%d的左儿子\n", midL, mid);
        printTree(root, left, midL, mid - 1);
    }
    if (mid != right)
    {
        int midR = root[mid + 1][right];
        printf("%d为%d的右儿子\n", midR, mid);
        printTree(root, mid + 1, midR, right);
    }
}

double bestSearchTree(double p[], double q[], int n)             //  p[i]  p[i+1]
{                                                                //q[i] q[i+1] q[i+2] //i=0,1...n
    double **e = new double *[n + 1], **w = new double *[n + 1]; //e[i][j]->q[i],p[i]...p[j-1],q[j]
    int **root = new int *[n];                                   //root[i][j] p[i]...p[j]
    for (int i = 0; i < n + 1; ++i)
    {
        e[i] = new double[n + 1];
        w[i] = new double[n + 1];
    }
    for (int i = 0; i < n; ++i)
        root[i] = new int[n];
    for (int i = 0; i < n + 1; ++i)
        e[i][i] = w[i][i] = q[i];
    for (int l = 1; l <= n; ++l) //l=j-i+1
    {
        for (int i = 0; i <= n - l; ++i)
        {
            int j = i + l - 1;
            e[i][j + 1] = 100.0;
            w[i][j + 1] = w[i][j] + p[j] + q[j + 1];
            for (int r = i; r <= j; ++r)
            {
                double tmp = e[i][r] + w[i][j + 1] + e[r + 1][j + 1];
                if (tmp < e[i][j + 1])
                {
                    e[i][j + 1] = tmp;
                    root[i][j] = r;
                }
            }
        }
    }
    double tmp = e[0][n];

    int rootN = root[0][n - 1];
    printf("%d为根\n", rootN);
    printTree(root, 0, rootN, n - 1);

    for (int i = 0; i < n + 1; ++i)
    {
        delete[] e[i];
        delete[] w[i];
    }
    for (int i = 0; i < n; ++i)
        delete[] root[i];
    delete[] e;
    delete[] w;
    delete[] root;
    return tmp;
}

int main()
{
    int n = 100;
    double *p = new double[n], *q = new double[n + 1];
    int *tmp = new int[2 * n + 1], sum = 0;
    srand(time(NULL));
    for (int i = 0; i < 2 * n + 1; ++i)
    {
        tmp[i] = rand() % 100;
        sum += tmp[i];
    }
    for (int i = 0; i < n; ++i)
        p[i] = tmp[i] / double(sum);
    for (int i = 0; i < n + 1; ++i)
        q[i] = tmp[n + i] / double(sum);
    double e = bestSearchTree(p, q, n);
    printf("%f", e);
    delete[] tmp;
    delete[] p;
    delete[] q;
}