#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class matrix
{
private:
    int **data;
    int row, column;

public:
    matrix(int r, int c) : row(r), column(c)
    {
        srand(time(NULL));
        data = new int *[r];
        for (int i = 0; i < r; ++i)
        {
            data[i] = new int[c];
        }
    }
    ~matrix()
    {
        for (int i = 0; i < row; ++i)
        {
            delete[] data[i];
        }
        delete[] data;
    }
    void randMatrix(int max)
    {
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < column; ++j)
            {
                data[i][j] = rand() % (max + 1);
            }
        }
    }
    int getRow() { return row; }
    int getColumn() { return column; }
    matrix operator*(const matrix &a)
    {
        matrix tmp(row, a.column);
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < a.column; ++j)
            {
                int tt = 0;
                for (int k = 0; k < column; ++k)
                {
                    tt += data[i][k] * a.data[k][j];
                }
                tmp.data[i][j] = tt;
            }
        }
        return tmp;
    }
    friend ostream &operator<<(ostream &out, const matrix &m)
    {
        for (int i = 0; i < m.row; ++i)
        {
            for (int j = 0; j < m.column; ++j)
            {
                out << m.data[i][j] << '\t';
            }
            out << '\n';
        }
        return out;
    }
};

matrix multiply(matrix A[], int **s, int i, int j)
{
    if (i + 1 == j)
    {
        return A[i] * A[j];
    }
    else
    {
        return multiply(A, s, i, s[i][j - 1]) * multiply(A, s, s[i][j - 1] + 1, j);
    }
}

matrix chainMultily(matrix A[], int n)
{
    int **m, **s;     // m[i][j]:matrix i ...*... matrix j
    m = new int *[n]; // s[i][j-1]:( matrix i ...*... matrix s[i][j-1] ) * (matrix s[i][j-1]+1 ...*...matrix j)
    for (int i = 0; i < n; ++i)
    {
        m[i] = new int[n];
        m[i][i] = 0;
    }
    s = new int *[n - 1];
    for (int i = 0; i < n - 1; ++i)
    {
        s[i] = new int[n - 1];
    }

    for (int l = 2; l <= n; ++l) // l: chain length
    {
        for (int i = 0; i <= n - l; ++i) //i:start matrix
        {
            int j = i + l - 1; // j:end matrix
            m[i][j] = 2147483647;
            for (int k = i; k < j; ++k) // i~k, k+1~j
            {
                int q = m[i][k] + m[k + 1][j] + A[i].getRow() * A[k].getColumn() * A[j].getColumn();
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j - 1] = k;
                }
            }
        }
    }
    for (int i = 0; i < n; ++i)
    {
        delete[] m[i];
    }
    delete[] m;
    matrix tmp = multiply(A, s, 0, n - 1);
    for (int i = 0; i < n - 1; ++i)
    {
        delete[] s[i];
    }
    delete[] s;
    return tmp;
}

int main()
{
    matrix A[] = {matrix(5, 10), matrix(10, 3), matrix(3, 12), matrix(12, 5), matrix(5, 50), matrix(50, 6)};
    int n = 6;
    for (int i = 0; i < n; ++i)
    {
        A[i].randMatrix(2);
    }
    clock_t c1 = clock();
    matrix m = chainMultily(A, n);
    cout << (clock() - c1) * 1.0 / CLOCKS_PER_SEC * 1000000 << endl;
    cout << m;

    clock_t c2 = clock();
    matrix t1 = A[0] * A[1];
    matrix t2 = t1 * A[2];
    matrix t3 = t2 * A[3];
    matrix t4 = t3 * A[4];
    matrix t5 = t4 * A[5];
    cout << (clock() - c2) * 1.0 / CLOCKS_PER_SEC * 1000000 << endl;
    cout << t5;

    return 0;
}