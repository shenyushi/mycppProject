#include "NodeRecognition.h"
#include <iostream>

using namespace std;

int find(int x)
{
    if (x != father[x])
        father[x] = find(father[x]);
    return father[x];
}

bool unionSet(int x, int y)
{
    int a = find(x), b = find(y);
    if (b != y)
        return true;
    if (a == y)
        return true;
    father[y] = x;
    return 0;
}