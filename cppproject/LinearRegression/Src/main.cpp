#include <iostream>
using namespace std;
#include <string>
#include "LinearRegression.h"

int main()
{
    try
    {
        LinearRegression lr;
        string str;
        getline(cin,str);
        lr.getX(str);
        while (getline(cin, str))
        {
            if (str.empty())
                break;
            lr.addPoint(str);
        }
        lr.Regression();
    }
    catch (const error &e)
    {
        cout << "error" << endl
             << "error" << endl
             << "error";
    }
    catch (const notLinear &nl)
    {
        cout << "error" << endl
             << "error";
    }
}