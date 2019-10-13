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
    int val[bagSize + 1][2];
    for (int i = 0; i <= bagSize; ++i)
        val[i][0] = 0;
    val[0][1] = 0;
    for (int j = 0; j < objN; ++j)
    {
        for (int i = 1; i <= bagSize; ++i)
        {
            if (i >= obj[j].weight)
                val[i][(j + 1) % 2] = max(val[i][j % 2], val[i - obj[j].weight][j % 2] + obj[j].value);
            else
                val[i][(j + 1) % 2] = val[i][j % 2];
        }
    }
    return val[bagSize][objN % 2];
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
