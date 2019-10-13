#include <iostream>
using namespace std;

struct Event
{
    int n;
    int value;
    int start, end;
};

void sort(Event e[], int left, int right)
{
    if (left >= right)
        return;
    int i = left, j = left;
    int key = e[right].end;
    for (; j < right; ++j)
    {
        if (e[j].end < key)
        {
            swap(e[i], e[j]);
            ++i;
        }
    }
    swap(e[i], e[right]);
    sort(e, left, i - 1);
    sort(e, i + 1, right);
}

int valueRoom(Event event[], int n)
{
    sort(event, 0, n - 1);
    struct maxVal
    {
        int sumV;
        int endT;
        maxVal() {}
    };
    maxVal mV[n];
    for (int i = 0; i < n; ++i)
    {
        mV[i].sumV = event[i].value;
        mV[i].endT = event[i].end;
        for (int j = i - 1; j >= 0; --j)
        {
            if (event[i].start >= mV[j].endT && mV[i].sumV < mV[j].sumV + event[i].value)
            {
                mV[i].sumV = mV[j].sumV + event[i].value;
                mV[i].endT = event[i].end;
                break;
            }
            else if (event[i].start < mV[j].endT && mV[i].sumV < mV[j].sumV)
            {
                mV[i].sumV = mV[j].sumV;
                mV[i].endT = mV[j].endT;
            }
        }
    }
    return mV[n - 1].sumV;
}

int main()
{
    int start[] = {1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
    int end[] = {4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16};
    int n = 11;
    Event *e = new Event[n];
    for (int i = 0; i < n; ++i)
    {
        e[i].n = i + 1;
        e[i].start = start[i];
        e[i].end = end[i];
        e[i].value = 1;
    }
    int a = valueRoom(e, n);
    cout << a << endl;
    return 0;
}