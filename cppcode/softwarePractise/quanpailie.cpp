#include <iostream>
using namespace std;
#include <vector>
void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void quanpailie(int arr[], int start, int end)
{
    if (start == end)
    {
        for (int i = 0; i <= end; ++i)
            cout << arr[i] << ' ';
        cout << endl;
    }
    else
    {
        for (int i = start; i <= end; ++i)
        {
            swap(arr[i], arr[start]);
           // cout << ' ' << start << ' ' << i << endl;
            quanpailie(arr, start + 1, end);
            swap(arr[i], arr[start]);
            //cout << ' ' << start << ' ' << i << endl;
        }
    }
}

int main()
{
    int n;
    cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; ++i)
        arr[i] = i + 1;
    quanpailie(arr, 0, n - 1);
    return 0;
}
