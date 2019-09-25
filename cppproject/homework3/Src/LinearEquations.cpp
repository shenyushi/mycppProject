#include "LinearEquations.h"
#include "math.h"

LinearEquations::LinearEquations()
{
    for (int i = 0; i <= 100; ++i)
        haveX[i] = 0;
}

void LinearEquations::addEquation(string str)
{
    tmp.push_back(vector<part>());
    vector<vector<part>>::iterator it = tmp.end() - 1;
    bool first = true;
    double b1;
    int i = 0;
    while (true)
    {
        if (first || str[i] == '+' || str[i] == '-')
        {
            bool minus = false;
            double decimal = 0;
            double coefficient = 0;
            if (str[i] == '-')
                minus = true;
            if (first)
                first = false;
            else
                ++i;
            while (str[i] >= '0' && str[i] <= '9' || str[i] == '.')
            {
                if (str[i] == '.')
                    decimal = 10;
                else if (!decimal)
                    coefficient = coefficient * 10 + str[i] - '0';
                else
                {
                    coefficient += (str[i] - '0') / decimal;
                    decimal *= 10;
                }
                ++i;
            }
            if (str[i] == '+' || str[i] == '-' || str[i] == '=')
                b1 += coefficient;
            else if (str[i] == 'x')
            {
                if (!coefficient)
                    coefficient = 1;
                if (str[++i] != '_')
                    throw error2();
                ++i;
                int xN = 0;
                while (str[i] >= '0' && str[i] <= '9')
                {
                    xN = xN * 10 + str[i] - '0';
                    ++i;
                }
                if (!xN)
                    throw error2();
                if (minus)
                    coefficient *= -1;
                it->push_back(part(coefficient, xN));
                haveX[xN] = 1;
            }
            else
                throw error2();
        }
        else if (str[i] == '=')
        {
            bool minus = false;
            double decimal = 0;
            double b = 0;
            ++i;
            if (str[i] == '-')
                minus = true;
            while (i < str.length() && (str[i] >= '0' && str[i] <= '9' || str[i] == '.'))
            {
                if (str[i] == '.')
                    decimal = 10;
                else if (!decimal)
                    b = b * 10 + str[i] - '0';
                else
                {
                    b += (str[i] - '0') / decimal;
                    decimal *= 10;
                }
                ++i;
            }
            if (i != str.length())
                throw error2();
            this->b.push_back(b - b1);
            break;
        }
        else
            throw error2();
    }
}

void LinearEquations::calculate()
{
    int column = 0;
    for (int i = 0; i <= 100; ++i)
        if (haveX[i])
            haveX[i] = ++column;
    int row = tmp.size();
    if (row < column) //无穷解
        throw error2();
    A = new double[row * column];
    for (int i = 0; i < row * column; ++i)
        A[i] = 0;
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < tmp[i].size(); ++j)
        {
            int t = haveX[tmp[i][j].xNum];
            A[i * column + (t - 1)] += tmp[i][j].coefficient;
        }
    }
    tmp.clear();
    int *map = new int[row];
    for (int i = 0; i < row; ++i)
        map[i] = i;
    for (int i = 0; i < column - 1; ++i)
    {
        if (!A[map[i] * column + i])
        {
            int j = i + 1;
            while (j < row && !A[map[j] * column + i])
                ++j;
            if (j == row)
                throw error2();
            map[i] = j;
            map[j] = i;
        }
        double k1 = A[map[i] * column + i];
        for (int j = i + 1; j < row; ++j)
        {
            if (!A[j * column + i])
                continue;
            double k2 = A[j * column + i] / k1;
            for (int k = i; k < column; ++k)
                A[j * column + k] -= A[i * column + k] * k2;
            b[j] -= b[i] * k2;
        }
    }
    if (!A[map[column - 1] * column + column - 1])
        throw error2();
    for (int i = column; i < row; ++i) //秩大于n
    {
        if (b[i])
            throw error2();
        for (int j = 0; j < column; ++j)
            if (A[map[i] * column + j])
                throw error2();
    }
    solution = new double[column];
    for (int i = column - 1; i >= 0; --i)
    {
        double k1 = 0;
        for (int j = i + 1; j < column; ++j)
            k1 += A[map[i] * column + j] * solution[j];
        solution[i] = (b[i] - k1) / A[map[i] * column + i];
    }
    for (int i = 0; i < column; ++i)
    {
        printN(solution[i]);
		if(i!=column-1)
        	cout << ' ';
    }
}

void LinearEquations::printN(double v)
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
    if (d[5] == 9 && d[4] == 9 && d[3] == 9)
    {
        d[3] = 0;
        int i = 2;
        for (; i >= 0 && d[i] == 9; --i)
            d[i] = 0;
        if (i >= 0)
            d[i]++;
        else
            integer++;
    }
    if (minus)
        cout << '-';
    cout << integer << '.' << d[0] << d[1] << d[2] << d[3];
}