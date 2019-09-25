#include <iostream>
using namespace std;
#include "LinearEquations.h"

int main()
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
    catch (const error &e)
    {
        cout << "error";
    }
}