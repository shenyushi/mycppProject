#include <iostream>
using namespace std;
#include <vector>

class error2{};

class LinearEquations
{
private:
    struct part
    {
        double coefficient;
        int xNum;
        part(double c, int n) : coefficient(c), xNum(n) {}
    };
    vector<vector<part>> tmp;
    vector<double> b;
    double *A;
    int haveX[101];
    double *solution;
    void printN(double);

public:
    LinearEquations();
    void addEquation(string str);
    void calculate();
};