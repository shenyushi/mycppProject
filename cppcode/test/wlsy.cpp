#include <iostream>
using namespace std;
#include <math.h>

int main()
{
    double data[37];
    for (int i = 0; i < 37; ++i)
    {
        cin >> data[i];
    }
    cout << endl
         << endl;
    for (int i = 0; i < 37; ++i)
    {
        data[i] = sqrt(data[i]);
        cout << data[i] << endl;
    }
    return 0;
}