#include "LinearEquations.h"
#include "math.h"

LinearEquations::LinearEquations()
{
    for (int i = 0; i < 100; ++i)
        haveX[i] = 0;
    A = solution = NULL;
}

LinearEquations::~LinearEquations()
{
    if (A != NULL)
        delete[] A;
    if (solution != NULL)
        delete[] solution;
}

void LinearEquations::addEquation(string str)
{
    tmp.push_back(vector<part>());
    vector<vector<part>>::iterator it = tmp.end() - 1;
    bool first = true;
    int i = 0;
    bool right = false;
    double b = 0;
    while (i < str.size())
    {
        if (first || str[i] == '+' || str[i] == '-')
        {
            bool minus = false;
            double decimal = 0;
            double coefficient = 0;
            if (str[i] == '-')
                minus = true;
            if (first && !minus)
                first = false;
            else
                ++i;
            while (str[i] >= '0' && str[i] <= '9' || str[i] == '.')
            {
                if (str[i] == '.')
                    decimal = 0.1;
                else if (!decimal)
                    coefficient = coefficient * 10 + str[i] - '0';
                else //if (decimal >= 0.0001)
                {
                    coefficient += decimal * (str[i] - '0');
                    decimal /= 10;
                }
                ++i;
            }
            if (str[i] == 'x')
            {
                if (!coefficient)
                    coefficient = 1;
                if (str[++i] != '_')
                    throw error2();
                ++i;
                int xN = 0;
                while (str[i] >= '0' && str[i] <= '9')
                    xN = xN * 10 + str[i++] - '0';
                if (i < str.size() && str[i] != '+' && str[i] != '-' && str[i] != '=')
                    throw error2();
                if (xN > 99 || !xN)
                    throw error2();
                if (minus ^ right)
                    coefficient *= -1;
                it->push_back(part(coefficient, xN));
                haveX[xN] = 1;
            }
            else if (i == str.size() || str[i] == '+' || str[i] == '-' || str[i] == '=')
            {
                if (!minus ^ right)
                    coefficient *= -1;
                b += coefficient;
            }
            else
                throw error2();
        }
        else if (str[i] == '=')
        {
            if (right)
                throw error2();
            right = true;
            first = true;
            ++i;
        }
        else
            throw error2();
    }
    if (!right)
        throw error2();
    this->b.push_back(b);
}

void LinearEquations::calculate()
{
    int column = 0;
    for (int i = 0; i <= 100; ++i)
        if (haveX[i])
            haveX[i] = ++column;
    int row = tmp.size();
    if (row < column || !column) //无穷解
        throw error2();
    A = new double[row * column];
    for (int i = 0; i < row * column; ++i)
        A[i] = 0;
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < tmp[i].size(); ++j)
        {
            int t = haveX[tmp[i][j].xNum];
            A[i * column + (t - 1)] += tmp[i][j].coefficient;
        }
    tmp.clear();
    int *map = new int[row];
    for (int i = 0; i < row; ++i)
        map[i] = i;
    for (int i = 0; i < column; ++i)
    {
        if (!A[map[i] * column + i])
        {
            int j = i + 1;
            while (j < row && !A[map[j] * column + i])
                ++j;
            if (j == row)
                throw error2();
            int ttmp = map[i];
            map[i] = map[j];
            map[j] = ttmp;
        }
        double k1 = A[map[i] * column + i];
        for (int j = i + 1; j < row; ++j)
        {
            if (!A[map[j] * column + i])
                continue;
            double k2 = A[map[j] * column + i] / k1;
            for (int k = i; k < column; ++k)
                A[map[j] * column + k] -= A[map[i] * column + k] * k2;
            b[map[j]] -= b[map[i]] * k2;
        }
    }
    if (!A[map[column - 1] * column + column - 1])
        throw error2();
    for (int i = column; i < row; ++i) //秩大于n
    {
        if (abs(b[map[i]]) > 1e-8)
            throw error2();
        for (int j = 0; j < column; ++j)
            if (abs(A[map[i] * column + j]) > 1e-8)
                throw error2();
    }
    solution = new double[column];
    for (int i = column - 1; i >= 0; --i)
    {
        double k1 = 0;
        for (int j = i + 1; j < column; ++j)
            k1 += A[map[i] * column + j] * solution[j];
        solution[i] = (b[map[i]] - k1) / A[map[i] * column + i];
    }
    for (int i = 0; i < column; ++i)
    {
        printN(solution[i]);
        if (i != column - 1)
            cout << ' ';
    }
}

void LinearEquations::printN(double v)
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