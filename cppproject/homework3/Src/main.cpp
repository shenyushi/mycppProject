#include "LinearEquations.h"
#include "Polynomial.h"
#include <iostream>
using namespace std;
#include <iomanip>

int main()
{
    bool exercise1 = true;
    if (exercise1)
    {
        string str;
        getline(cin, str);
        double a, b;
        cin >> a >> b;
        try
        {
            Polynomial p(str);
            NewTown newtown(p, a, b);
            double solution = newtown.calculate();
            newtown.printNum(solution);
        }
        catch (const error1 &e)
        {
            cout << "error";
        }
    }
    else
    {
        string str;
        LinearEquations le;
        try
        {
            while (getline(cin, str))
            {
                if (str.empty())
                    break;
                le.addEquation(str);
            }
            le.calculate();
        }
        catch (const error2 &e)
        {
            cout << "error";
        }
    }
}
