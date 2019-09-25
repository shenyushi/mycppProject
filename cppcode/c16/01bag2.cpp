#include <iostream>
using namespace std;
#include <algorithm>
struct object
{
    int weight;
    int value;
};

int bagProblem(int bagSize, object obj[], int objN)
{
    int val[bagSize + 1][objN + 1];
    bool memo[bagSize][objN];
    for (int i = 0; i <= bagSize; ++i)
        val[i][0] = 0;
    for (int i = 1; i <= objN; ++i)
        val[0][i] = 0;
    for (int j = 1; j <= objN; ++j)
    {
        for (int i = 1; i <= bagSize; ++i)
        {
            int v1 = -1, v2 = val[i][j - 1];
            if (i >= obj[j - 1].weight)
                v1 = val[i - obj[j - 1].weight][j - 1] + obj[j - 1].value;
            if (v1 > v2)
            {
                val[i][j] = v1;
                memo[i - 1][j - 1] = true;
            }
            else
            {
                val[i][j] = v2;
                memo[i - 1][j - 1] = false;
            }
        }
    }
    int i = bagSize - 1;
    for (int j = objN - 1; j >= 0; --j)
    {
        if (i < 0)
            break;
        if (memo[i][j])
        {
            cout << obj[j].weight << ' ';
            i -= obj[j].weight;
        }
    }
    cout << endl;
    return val[bagSize][objN];
}

int main()
{
    int objN = 5, w[] = {5, 4, 7, 2, 6}, v[] = {12, 3, 10, 3, 6};
    int bagSize = 15;
    object obj[objN];
    for (int i = 0; i < objN; ++i)
    {
        obj[i].weight = w[i];
        obj[i].value = v[i];
    }
    cout << bagProblem(bagSize, obj, objN);
    return 0;
}
