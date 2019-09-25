#include <iostream>
using namespace std;
#include <list>
#include <iomanip>
#include <math.h>

class error
{
};

class Polynomial
{
private:
    struct Monomial
    {
        double coefficient;
        int order;
        Monomial(double co, int ord) : coefficient(co), order(ord) {}
    };
    struct decreasingOrder
    {
        bool operator()(const Monomial &s1, const Monomial &s2) { return s1.order > s2.order; }
    };
    list<Monomial> data;

public:
    Polynomial(){};
    Polynomial(const string &str)
    {
        int i = 0;
        double coefficient = 0.0;
        bool minus = false;
        int decimal = 0;
        bool flag = false;
        while (i < str.length())
        {
            char cur = str[i];
            if (cur == '-' || cur == '+')
            {
                if (flag)
                {
                    if (minus)
                        coefficient *= -1;
                    data.push_back(Monomial(coefficient, 0));
                    flag = false;
                    minus = false;
                    decimal = false;
                    coefficient = 0;
                }
                if (cur == '-')
                    minus = true;
            }
            else if (cur == '.')
                decimal = 10;
            else if (cur >= '0' && cur <= '9')
            {
                flag = true;
                int n = cur - '0';
                if (!n)
                    ;
                else if (decimal)
                {
                    coefficient += double(n) / decimal;
                    decimal *= 10;
                }
                else
                    coefficient = coefficient * 10 + n;
            }
            else if (cur == 'x')
            {
                if (!coefficient)
                    coefficient = 1;
                if (minus)
                    coefficient *= -1;
                int order;
                if (str[i + 1] == '^')
                {
                    i += 2;
                    if (str[i] > '9' || str[i] < '0')
                        throw error();
                    order = str[i] - '0';
                }
                else
                    order = 1;
                data.push_back(Monomial(coefficient, order));
                flag = false;
                coefficient = 0;
                decimal = false;
                minus = false;
            }
            else
                throw error();
            ++i;
        }
        if (flag)
            data.push_back(Monomial(coefficient, 0));
        data.sort(decreasingOrder());
        list<Monomial>::iterator lastit = data.end();
        for (list<Monomial>::iterator it = data.begin(); it != data.end(); ++it)
        {
            if (lastit != data.end() && it->order == lastit->order)
            {
                lastit->coefficient += it->coefficient;
                data.erase(it);
                it = lastit;
            }
            else
                lastit = it;
        }
    }
    Polynomial derivation() const
    {
        Polynomial derivative;
        for (list<Monomial>::const_iterator it = data.begin(); it != data.end(); ++it)
            if (it->order)
                derivative.data.push_back(Monomial(it->order * it->coefficient, it->order - 1));
        return derivative;
    }
    double value(double x) const
    {
        double result = 0.0;
        for (list<Monomial>::const_iterator it = data.begin(); it != data.end(); ++it)
            result += it->coefficient * pow(x, it->order);
        return result;
    }
    friend ostream &operator<<(ostream &out, const Polynomial &x)
    {
        out << setiosflags(ios::fixed) << setprecision(4);
        for (list<Monomial>::const_iterator it = x.data.begin(); it != x.data.end(); ++it)
        {
            if (it != x.data.begin() && it->coefficient > 0)
                out << '+';

            out << it->coefficient;

            if (it->order != 0 && it->order != 1)
                out
                    << "x^" << it->order;
            else if (it->order)
                out
                    << 'x';
        }
        return out;
    }
};

int main()
{
    //请打开文件目录修改Polynomial.h，Polynomial.cpp，和exercise_2.cpp
    /********** Begin **********/
    
    bool exercise1=true;
    if(exercise1)    {
    //第一关执行代码
    string str;          
    getline(cin,str);    
    double x;
    cin >> x;
    try
    {
        Polynomial p(str);
        cout << p << endl;
        Polynomial dp = p.derivation();
        cout << dp << endl;
        cout << p.value(x);
    }
    catch (const error &e)
    {
        cerr << "error" << endl
             << "error" << endl
             << "error";
    }
   
    }   else     {
    //第二关执行代码


    }
	/********** End **********/
  	return 0;
}

