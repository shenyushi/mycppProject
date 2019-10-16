#include "NodeRecognition.h"
#include <vector>
#include <algorithm>
#include <iostream>

NodeRecognition::NodeRecognition(string str)
{
    int n1 = -1, n2 = -1;
    Map::iterator it1, it2;
    Map::iterator p1, p2;
    for (int i = 0; i < str.size(); ++i)
    {
        switch (str[i])
        {
        case '<':
            break;
        case '>':
            it1 = m.find(n1);
            if (n1 > 0 && it1 == m.end())
            {
                m.insert(Pair(n1, Node(n1, n1)));
                it1 = m.find(n1);
            }
            if (n2 >= 0)
            {
                it2 = m.find(n2);
                if (it2 == m.end())
                {
                    m.insert(Pair(n2, Node(n2, n2)));
                    it2 = m.find(n2);
                }
                p1 = m.find(findp(n1));
                p2 = m.find(findp(n2));
                ++p2->second.childN;
                if (p1 == p2)
                    p2->second.type = 3;
                else
                {
                    if (it2->second.childN > 2 && p2->second.type < 2)
                        p2->second.type = 2;
                    else if (it2->second.childN <= 2 && !p2->second.type)
                        p2->second.type = 1;
                }
                p1->second.pwei = p2->second.wei;
            }
            n1 = n2 = -1;
            break;
        case ' ':
            break;
        default:
            int tmp = 0;
            while (str[i] != '>' && str[i] != ' ')
            {
                tmp = tmp * 10 + str[i] - '0';
                ++i;
            }
            --i;
            if (n1 < 0)
                n1 = tmp;
            else
                n2 = tmp;
        }
    }
}
int NodeRecognition::findp(int n)
{
    Map::iterator it = m.find(n);
    if (it->second.pwei != n)
        it->second.pwei = findp(it->second.pwei, n);
    return it->second.pwei;
}
int NodeRecognition::findp(int n, const int start)
{
    if (n == start)
        return n;
    Map::iterator it = m.find(n);
    if (it->second.pwei != n)
        it->second.pwei = findp(it->second.pwei, start);
    return it->second.pwei;
}
void NodeRecognition::print()
{
    vector<Node> tmp;
    Map::iterator pp;
    for (Map::iterator it = m.begin(); it != m.end(); ++it)
        if (it->second.wei != it->second.pwei)
        {
            pp = m.find(findp(it->second.pwei));
            pp->second.num++;
            pp->second.swei += it->second.wei;
        }
    for (Map::iterator it = m.begin(); it != m.end(); ++it)
        if (it->second.wei == it->second.pwei)
            tmp.push_back(it->second);
    sort(tmp.begin(), tmp.end());
    if (tmp.size() > 1)
        cout << "We have recognized " << tmp.size() << " graphs.";
    else
        cout << "We have recognized " << tmp.size() << " graph.";
    if (!tmp.empty())
        cout << endl;
    for (int i = 0; i < tmp.size(); ++i)
    {
        switch (tmp[i].type)
        {
        case 0:
            cout << "--Node. ";
            break;
        case 1:
            cout << "--Binary tree. ";
            break;
        case 2:
            cout << "--Tree. ";
            break;
        default:
            cout << "--Graph. ";
        }
        cout << "Weight: " << tmp[i].swei << ". Size: " << tmp[i].num << '.';
        if (i != tmp.size() - 1)
            cout << endl;
    }
}