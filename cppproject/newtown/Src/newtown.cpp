#include "newtown.h"

Polynomial::Polynomial(const string &str)
{
    int i = 0;

    while (i < str.length())
    {
        bool first = true;
        bool minus = false;
        bool haveN = false;
        double coefficient = 0.0;
        int decimal = 0;
        int order = 0;
        while (i < str.length() && (first || (str[i] != '-' && str[i] != '+' && str[i] != 'x')))
        {
            if (first && str[i] == 'x')
                break;
            if (first)
                first = false;
            if (str[i] == '-')
                minus = true;
            else if (str[i] >= '0' && str[i] <= '9')
            {
                if (!haveN)
                    haveN = true;
                if (decimal)
                {
                    coefficient += double(str[i] - '0') / decimal;
                    decimal *= 10;
                }
                else
                    coefficient = coefficient * 10 + str[i] - '0';
            }
            else if (str[i] == '.' && !decimal)
                decimal = 10;
            else if (str[i] != '+')
                throw error();
            ++i;
        }
        if (i < str.length() && (str[i] == '+' || str[i] == '-') && !haveN)
            throw error();
        if (str[i] == 'x')
        {
            if (!haveN)
                coefficient = 1;
            if (str[i + 1] != '^')
            {
                order = 1;
                ++i;
            }
            else if (str[i + 2] > '9' || str[i + 2] < '0')
                throw error();
            else
            {
                i += 2;
                while (str[i] >= '0' && str[i] <= '9')
                {
                    order = order * 10 + str[i] - '0';
                    ++i;
                }
            }
        }
        if (minus)
            coefficient *= -1;
        data.push_back(Monomial(coefficient, order));
    }
    data.sort(decreasingOrder());
    list<Monomial>::iterator lastit = data.end();
    for (list<Monomial>::iterator it = data.begin(); it != data.end();)
    {
        if (lastit != data.end() && it->order == lastit->order)
        {
            while (it != data.end() && it->order == lastit->order)
            {
                lastit->coefficient += it->coefficient;
                it = data.erase(it);
            }
            if (!lastit->coefficient)
            {
                lastit = data.erase(lastit);
                ++it;
            }
        }
        else
        {
            lastit = it;
            ++it;
        }
    }
    if (data.size() == 1 && !data.begin()->coefficient)
        data.begin()->order = 0;
    if (data.empty())
        data.push_back(Monomial(0, 0));
}

Polynomial Polynomial::derivation() const
{
    Polynomial derivative;
    for (list<Monomial>::const_iterator it = data.begin(); it != data.end(); ++it)
        if (it->order)
            derivative.data.push_back(Monomial(it->order * it->coefficient, it->order - 1));
    if (derivative.data.empty())
        derivative.data.push_back(Monomial(0, 0));
    return derivative;
}

double Polynomial::value(double x) const
{
    double result = 0.0;
    for (list<Monomial>::const_iterator it = data.begin(); it != data.end(); ++it)
        result += it->coefficient * pow(x, it->order);
    return result;
}

NewTown::NewTown(const Polynomial &p, double a, double b) : formula(p), a(a), b(b) {}

double NewTown::calculate()
{
    double t1 = formula.value(a) * formula.value(b);
    if (t1 > 0 || t1 == 0)
        throw error();
    Polynomial df = formula.derivation();
    if (df.value(a) * df.value(b) < 0)
        throw error();
    Polynomial ddf = formula.derivation();
    if (ddf.value(a) * ddf.value(b) < 0)
        throw error();
    /*double t2 = a - formula.value(a) / df.value(a), t3 = b - formula.value(b) / df.value(b);
    if (t2 > b || t3 < a)
        throw error();*/
    double k = b, k1;
    double e = 1e-8;
    while (true)
    {
        double fk = formula.value(k), dfk = df.value(k);
        k1 = -fk / dfk + k;
        if (abs(k1 - k) < e)
            break;
        k = k1;
    }
    return k1;
}

void NewTown::printNum(double v)
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
    int d[] = {tmp / 100000, tmp / 10000 % 10, tmp / 1000 % 10, tmp / 100 % 10, tmp / 10 % 10, tmp % 10};
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