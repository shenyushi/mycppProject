#pragma once

#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <string>

class error
{
};

class ntInsert
{
private:
    struct position
    {
        double x, y;
        position(double xx, double yy) : x(xx), y(yy) {}
        bool operator<(const position &a) { return x < a.x; }
    };
    vector<position> point;
    vector<double> a;

public:
    ntInsert() {}
    double getNum(const string &str, int &i);
    void addPoint(string str);
    double calculate(double z);
    void printN(double v);
};