#include <iostream>
using namespace std;

struct event
{
    int n;
    int start, end;
    event() {}
};

void swap(event &a, event &b)
{
    int tn = b.n, ts = b.start, te = b.end;
    b.n = a.n;
    b.start = a.start;
    b.end = a.end;
    a.n = tn;
    a.start = ts;
    a.end = te;
}

void sort(event e[], int left, int right)
{
    if (left >= right)
        return;
    int i = left, j = left;
    int key = e[right].start, other = e[right].end;
    for (; j < right; ++j)
    {
        if (e[j].start > key)
        {
            swap(e[i], e[j]);
            ++i;
        }
    }
    swap(e[i], e[right]);
    sort(e, left, i - 1);
    sort(e, i + 1, right);
}

void mostEvent(event e[], int n) //end increase
{
    sort(e, 0, n - 1);
    int *ss = new int[n], sl = 0;
    int k = 0;
    ss[sl++] = e[0].n;
    for (int m = 1; m < n; ++m)
    {
        if (e[m].end <= e[k].start)
        {

            k = m;
            ss[sl++] = e[k].n;
        }
    }
    for (int i = sl - 1; i >= 0; --i)
        cout << ss[i] << ' ';
    delete[] ss;
}

int main()
{
    int start[] = {1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
    int end[] = {4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16};
    int n = 11;
    event *e = new event[n];
    for (int i = 0; i < n; ++i)
    {
        e[i].n = i + 1;
        e[i].start = start[i];
        e[i].end = end[i];
    }
    mostEvent(e, n);
    return 0;
}