#include "NodeRecognition.h"
#include <string>
using namespace std;

NodeRecognition::NodeRecognition(string str)
{
    int n1 = 0, n2 = 0;
    bool first = true;
    for (int i = 0; i < str.size(); ++i)
    {
        switch (str[i])
        {
        case '<':
            first = true;
            break;
        case '>':
            arr.push_back(Pair(n1, n2));
            n1 = n2 = 0;
            break;
        case ' ':
            first = false;
            break;
        default:
            if (first)
                n1 = n1 * 10 + str[i] - '0';
            else
                n2 = n2 * 10 + str[i] - '0';
        }
    }
}
