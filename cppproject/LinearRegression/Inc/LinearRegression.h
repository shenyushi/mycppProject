#include <vector>
using namespace std;
#include <string>

class error
{
};

class notLinear
{
};

class LinearRegression
{
private:
    struct Point
    {
        double x;
        double y;
        Point(double xx, double yy) : x(xx), y(yy) {}
    };
    double x;
    vector<Point> point;
    double getNum(const string &str, int &i);
    void printNum(double v);

public:
    LinearRegression() {}
    void getX(const string& str);
    void addPoint(const string& str);
    void Regression();
};