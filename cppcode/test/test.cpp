#include <iostream>
using namespace std;
#include <math.h>

void printNum(double v)
{
    bool minus = false;
    if (v < 0)
    {
        minus = true;
        v = -v;
    }
    long long int integer = floor(v);
    double decimal = v - integer;
    long long int tmp = decimal * 1000000;
    int d[] = {int(tmp / 100000), int(tmp / 10000 % 10), int(tmp / 1000 % 10), int(tmp / 100 % 10), int(tmp / 10 % 10), int(tmp % 10)};
    if (d[5] == 9 && d[4] == 9)
    {
        int i = 3;
        for (; i >= 0 && d[i] == 9; --i)
            d[i] = 0;
        if (i >= 0)
            d[i]++;
        else
            integer++;
    }
    if (minus )//&& (integer || d[0] || d[1] || d[2] || d[3]))
        cout << '-';
    cout << integer << '.' << d[0] << d[1] << d[2] << d[3];
}

int main()
{
    printNum(-0.00005);
}