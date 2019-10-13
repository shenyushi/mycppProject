#include <iostream>
using namespace std;
#include "ntInsert.h"
#include <string>

int main()
{
    try
    {
        ntInsert nt;
        string str;
        getline(cin, str);
        int i = 0;
        double z = nt.getNum(str, i);
        while (getline(cin, str))
        {
            if (str.empty())
                break;
            nt.addPoint(str);
        }
        double result = nt.calculate(z);
        nt.printN(result);
    }
    catch (const error &e)
    {
        cout << "error";
    }
}