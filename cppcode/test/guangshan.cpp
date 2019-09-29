#include <iostream>
using namespace std;
#include <math.h>

void printN(double v)
{
    if (abs(v) < 0.0001)
    {
        cout << "0.0000";
        return;
    }
    string str = to_string(v);
    int i = 0;
    if (str[i] == '-')
    {
        cout << '-';
        ++i;
    }
    int dot = 0;
    bool decimal = false;
    while (i != str.size())
    {
        if (str[i] == '.')
            decimal = true;
        else if (decimal)
        {
            dot++;
            if (dot > 4)
                break;
        }
        cout << str[i];
        ++i;
    }
    for (int i = dot; i <= 4; ++i)
        cout << '0';
}

int main()
{
    double v;
    cin >> v;
    printN(v);
}