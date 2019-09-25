#include <iostream>
using namespace std;
#include <iomanip>
#include "newtown.h"

int main()
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
    catch (const error &e)
    {
        cout << "error";
    }
}

