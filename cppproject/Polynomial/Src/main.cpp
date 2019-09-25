#include <iostream>
using namespace std;
#include <iomanip>
#include "Polynomial.h"

int main()
{
    bool exercise1 = true;
    if (exercise1)
    {
        string str;
        getline(cin, str);
        double x;
        cin >> x;
        try
        {
            Polynomial p(str);
            p.print();
            cout << endl;
            Polynomial dp = p.derivation();
            dp.print();
            cout << endl;
            double v = p.value(x);
            printNum(v);
        }
        catch (const error &e)
        {
            cout << "error" << endl
                 << "error" << endl
                 << "error";
        }
    }
    else
    {
        string str1, str2;
        getline(cin, str1);
        getline(cin, str2);
        try
        {
            Polynomial p1(str1);
            Polynomial p2(str2);
            Polynomial remainder;
            Polynomial result = p1.divide(p2, remainder);
            result.print();
            cout << endl;
            remainder.print();
        }
        catch (const error &r)
        {
            cout << "error" << endl
                 << "error";
        }
    }
    return 0;
}