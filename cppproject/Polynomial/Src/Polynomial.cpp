#include "Polynomial.h"

void Polynomial::print() const
{
    for (list<Monomial>::const_iterator it = data.begin(); it != data.end(); ++it)
    {
        if (it != data.begin() && it->coefficient > 0)
            cout << '+';

        double v = it->coefficient;
        if (abs(abs(v) - 1.0) >= 0.0001 || !it->order)
            printNum(v);
        else if (it->order && v < 0)
            cout << '-';

        if (it->order != 0 && it->order != 1)
            cout << "x^" << it->order;
        else if (it->order)
            cout << 'x';
    }
}

void printNum(double v)
{
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
        else if (integer >= 0)
            integer++;
        else
            integer--;
    }
    cout << integer << '.' << d[0] << d[1] << d[2] << d[3];
}

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

Polynomial Polynomial::subtract(const Polynomial &p1) const
{
    Polynomial result;
    list<Monomial>::const_iterator it1 = data.begin(), it2 = p1.data.begin();
    while (it1 != data.end() && it2 != p1.data.end())
    {
        if (it1->order > it2->order)
        {
            result.data.push_back(*it1);
            ++it1;
        }
        else if (it1->order < it2->order)
        {
            result.data.push_back(Monomial(-it2->coefficient, it2->order));
            ++it2;
        }
        else
        {
            if (it1->coefficient - it2->coefficient)
                result.data.push_back(Monomial(it1->coefficient - it2->coefficient, it1->order));
            ++it1;
            ++it2;
        }
    }
    while (it1 != data.end())
    {
        result.data.push_back(*it1);
        ++it1;
    }
    while (it2 != p1.data.end())
    {
        result.data.push_back(Monomial(-it2->coefficient, it2->order));
        ++it2;
    }
    return result;
}

Polynomial Polynomial::singleMultiply(const Monomial &x) const
{
    Polynomial result;
    for (list<Monomial>::const_iterator it = data.begin(); it != data.end(); ++it)
        result.data.push_back(Monomial(x.coefficient * it->coefficient, it->order + x.order));
    return result;
}

Polynomial Polynomial::divide(const Polynomial &p1, Polynomial &remainder) const
{
    if (p1.data.size() == 1 && !p1.data.begin()->order && !p1.data.begin()->coefficient)
        throw error();
    Polynomial result;
    int order1 = p1.data.begin()->order;
    int coefficient1 = p1.data.begin()->coefficient;
    remainder = *this;
    while (!remainder.isEmpty() && remainder.data.begin()->order >= order1)
    {
        double coefficient = remainder.data.begin()->coefficient / coefficient1;
        int order = remainder.data.begin()->order - order1;
        remainder = remainder.subtract(p1.singleMultiply(Monomial(coefficient, order)));
        result.data.push_back(Monomial(coefficient, order));
    }
    if (result.data.empty())
        result.data.push_back(Monomial(0, 0));
    if (remainder.data.empty())
        remainder.data.push_back(Monomial(0, 0));
    return result;
}