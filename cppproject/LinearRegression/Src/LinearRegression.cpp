#include "LinearRegression.h"
#include <math.h>
#include <iostream>
using namespace std;

double LinearRegression::getNum(const string &str, int &i)
{
    double result = 0;
    bool minus = false;
    double dot = 0.0;
    for (; i < str.length(); ++i)
    {
        char cur = str[i];
        if (cur == '+')
            ;
        if (cur == '-')
            minus = true;
        else if (cur >= '0' && cur <= '9')
        {
            if (!dot)
                result = result * 10 + cur - '0';
            else
            {
                result += (cur - '0') / dot;
                dot *= 10;
            }
        }
        else if (cur == '.')
            dot = 10;
        else if (cur == ' ')
            break;
        else
            throw error();
    }
    if (minus)
        result *= -1;
    return result;
}

void LinearRegression::getX(const string &str)
{
    int i = 0;
    x = getNum(str, i);
}

void LinearRegression::addPoint(const string &str)
{
    int i = 0;
    double x = getNum(str, i);
    ++i;
    double y = getNum(str, i);
    point.push_back(Point(x, y));
}

void LinearRegression::Regression()
{
    double sumX = 0, sumY = 0;
    for (int i = 0; i < point.size(); ++i)
    {
        sumX += point[i].x;
        sumY += point[i].y;
    }
    double avgX = sumX / point.size(), avgY = sumY / point.size();
    double Lxy = 0, Lxx = 0, Lyy = 0;
    for (int i = 0; i < point.size(); ++i)
    {
        Lxy += (point[i].x - avgX) * (point[i].y - avgY);
        Lxx += (point[i].x - avgX) * (point[i].x - avgX);
        Lyy += (point[i].y - avgY) * (point[i].y - avgY);
    }
    double r = Lxy / sqrt(Lxx * Lyy);
    printNum(r);
    cout << endl;
    if (abs(r) < 0.75)
        throw notLinear();
    double b = Lxy / Lxx;
    double a = avgY - b * avgX;
    cout << "y=";
    printNum(b);
    cout << "*x";
    if (a > 0)
        cout << '+';
    printNum(a);
    cout << endl;
    double result = b * x + a;
    printNum(result);
}

void LinearRegression::printNum(double v)
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