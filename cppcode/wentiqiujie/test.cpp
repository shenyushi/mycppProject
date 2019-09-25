#include <iostream>
using namespace std;
#include <iomanip>
#include <math.h>
int main()
{
    double v;
    cin >> v;
    int integer = floor(v);
    double decimal = v - integer;
    long long int tmp = decimal * 1000000;
    int d[] = {tmp / 100000, tmp / 10000 % 10, tmp / 1000 % 10, tmp / 100 % 10, tmp / 10 % 10, tmp % 10};
    if (d[5] == 9 && d[4] == 9 && d[3] == 9)
    {
        d[3] = 0;
        int i = 2;
        for (; i >= 0 && d[i] == 9; --i)
            d[i] = 0;
        if (i >= 0)
            d[i]++;
        else if (integer >= 0)
            integer++;
        else
            integer--;
    }
    cout << integer << '.' << d[0] << d[1] << d[2] << d[3];
}