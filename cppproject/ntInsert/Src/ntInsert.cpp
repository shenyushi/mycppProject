#include "ntInsert.h"

int factorial(int i)
{
    int result = 1;
    while (i)
        result *= i--;
    return result;
}

double pow(double x, int a)
{
    double result = 1;
    while (a--)
        result *= x;
    return result;
}

double ntInsert::getNum(const string &str, int &i)
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

void ntInsert::addPoint(string str)
{
    int i = 0;
    double x = getNum(str, i);
    ++i;
    double y = getNum(str, i);
    point.push_back(position(x, y));
}

double ntInsert::calculate(double z)
{
    int l = point.size();
    if (l < 2)
        throw error();
    sort(point.begin(), point.end());
    double dx = point[1].x - point[0].x;
    double e = 1e-10;
    for (int i = 2; i < l; ++i)
        if (abs(point[i].x - point[i - 1].x - dx) > e)
            throw error();
    double tmp[l][l];
    for (int i = 0; i < l; ++i)
        tmp[i][0] = point[i].y;
    for (int j = 1; j < l; ++j)
        for (int i = j; i < l; ++i)
            tmp[i][j] = tmp[i][j - 1] - tmp[i - 1][j - 1];
    for (int i = 0; i < l; ++i)
        a.push_back(tmp[i][i] / (factorial(i) * pow(dx, i)));
    double result = 0;
    for (int i = 0; i < l; ++i)
    {
        double tmp = 1;
        for (int j = 0; j < i; ++j)
            tmp *= z - point[j].x;
        result += a[i] * tmp;
    }
    return result;
}

void ntInsert::printN(double v)
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