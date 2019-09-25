#include <iostream>
using namespace std;
#include <list>
#include <math.h>
#include <iomanip>

void printNum(double v);

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
    Polynomial subtract(const Polynomial &p1) const;
    Polynomial singleMultiply(const Monomial &x) const;

public:
    Polynomial() {}
    Polynomial(const string &str);
    Polynomial derivation() const;
    double value(double x) const;
    bool isEmpty() const { return data.empty(); }
    void print() const;
    Polynomial divide(const Polynomial &p1, Polynomial &remainder) const;
};