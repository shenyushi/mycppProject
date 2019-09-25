#include <iostream>
using namespace std;
#include <vector>
#include <cstdlib>

struct location
{
    int row;
    int column;
    location(int r, int c) : row(r), column(c) {}
};

bool bahuanghou(int row, vector<location> &queen, const int n)
{
    if (row > n)
    {
        int map[n + 1][n + 1];
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                map[i][j] = 0;
        for (vector<location>::iterator it = queen.begin(); it != queen.end(); ++it)
            map[it->row][it->column] = 1;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
                cout << map[i][j] << ' ';
            cout << endl;
        }
        return true;
    }
    else
    {
        for (int column = 1; column <= n; ++column)
        {
            bool flag = true;
            for (vector<location>::iterator it = queen.begin(); it != queen.end(); ++it)
                if (it->column == column || abs(it->row - row) == abs(column - it->column))
                {
                    flag = false;
                    break;
                }
            if (flag)
            {
                queen.push_back(location(row, column));
                bool flag1 = bahuanghou(row + 1, queen, n);
                if (flag1)
                    return true;
                queen.pop_back();
            }
        }
    }
    return false;
}

int main()
{
    int n;
    cin >> n;
    vector<location> queen;
    bahuanghou(1, queen, n);
}