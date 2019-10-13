#include <iostream>
using namespace std;

void mostEvent(int start[], int end[], int n) //end increase
{
    int k = 0;
    cout << k+1 << ' ';
    for (int m = 1; m < n; ++m)
        if (end[k] <= start[m])
        {
            k = m;
            cout << k+1 << ' ';
        }
}

int main()
{
    int start[] = {1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
    int end[] = {4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16};
    int n = 11;
    mostEvent(start, end, n);
    return 0;
}