#include "NodeRecognition.h"
#include <iostream>
#include <algorithm>
using namespace std;

NodeRecognition::NodeRecognition()
{
    for (int i = 0; i < maxn; ++i)
    {
        key[i] = type[i] = childN[i] = 0;
        wei[i] = i;
        num[i] = 1;
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
    if (!key[n1])
        key[n1] = n1;
    if (!key[n2])
        key[n2] = n2;
    int tmp = find(n1);
    if (n2 != -1)
    {
        if (tmp == find(n2))
            type[n2] = 3;
        else
        {
            ++childN[n2];
            if (childN[n2] >= 2 && type[n2] < 2)
                type[n2] = 2;
            else if (childN[n2] < 2 && !type[n2])
                type[n2] = 1;
        }
        key[n1] = n2;
        wei[n2] += n1;
        ++num[n2];
    }
}

int NodeRecognition::find(int n)
{
    if (n != key[n])
        key[n] = find(key[n]);
    return key[n];
}

void NodeRecognition::print()
{
    vector<int> root;
    for (int i = 1; i < maxn; ++i)
    {
        if (key[i] != i)
            continue;
        root.push_back(10000 * type[i] + 100 * wei[i] + num[i]);
    }
    sort(root.begin(), root.end());
    cout << "We have recognized " << root.size() << " graphs." << endl;
    for (int i = 0; i < root.size(); ++i)
    {
        switch (root[i] / 10000)
        {
        case 0:
            cout << "--Node. ";
            break;
        case 1:
            cout << "--Binary Tree. ";
            break;
        case 2:
            cout << "--Tree. ";
            break;
        default:
            cout << "--Graph. ";
            break;
        }
        cout << "Weight: " << root[i] % 10000 / 100;
        cout << "Size:" << root[i] % 100 << endl;
    }
}