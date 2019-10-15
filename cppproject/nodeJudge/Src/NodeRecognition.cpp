#include "NodeRecognition.h"
#include <iostream>
#include <cstdlib>

using namespace std;

NodeRecognition::NodeRecognition()
{
    for (int i = 0; i < maxn; ++i)
    {
        flag[i] = false;
        type[i] = childN[i] = 0;
    }
}

void NodeRecognition::getData(string str)
{
    int n1 = 0, n2 = 0, i;
    for (i = 1; str[i] != ' ' && str[i] != '>'; ++i)
        n1 = n1 * 10 + str[i] - '0';
    if (str[i] == '>')
        n2 = -1;
    else
        for (++i; str[i] != '>'; ++i)
            n2 = n2 * 10 + str[i] - '0';
    if (!flag[n1])
    {
        flag[n1] = true;
        key[n1] = n1;
    }
    int tmp = find(n1);
    if (n2 != -1)
    {
        if (tmp == find(n2))
            type[tmp] = 3;
        else
        {
            if (childN[n2] >= 2 && type[tmp] < 2)
                type[tmp] = 2;
            else if (childN[n2] < 2 && !type[tmp])
                type[tmp] = 1;
            ++childN[n2];
        }
        key[n1] = n2;
    }
}

int NodeRecognition::find(int n)
{
    if (n != key[n])
        key[n] = find(key[n]);
    return key[n];
}