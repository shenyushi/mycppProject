#include <iostream>
using namespace std;
#include <list>
#include <math.h>
#include <iomanip>

class error
{
};

class Polynomial
{
    struct Monomial
    {
        double coefficient;
        int order;
        Monomial(double con, int ord) : coefficient(con), order(ord) {}
    };
    struct decreasingOrder
    {
        bool operator()(const Monomial &s1, const Monomial &s2) { return s1.order > s2.order; }
    };
    list<Monomial> data;

public:
    Polynomial() {}
    Polynomial(const string &str);
    Polynomial derivation() const;
    double value(double x) const;
    bool isZero() const { return !data.begin()->order && !data.begin()->coefficient && data.size() == 1; }
};

class NewTown
{
private:
    Polynomial formula;
    double a, b;

public:
    NewTown(const Polynomial &p, double a, double b);
    double calculate();
    void printNum(double v);
};