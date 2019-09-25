#include <vector>

#include <iostream>
using namespace std;

struct event
{
    int n;
    int start, end;
    event() {}
};

class Room
{
private:
    vector<event> e;
    int endTime;

public:
    Room() : endTime(-1) {}
    void insert(const event &a)
    {
        e.push_back(a);
        endTime = a.end;
    }
    int getKey() const { return endTime; }
    void print()
    {
        for (vector<event>::iterator it = e.begin(); it != e.end(); it++)
            cout << it->n << ' ';
        cout << endl;
    }
};

class Heap
{
private:
    int maxN, curN;
    Room *data;
    void percolateDown(int hole)
    {
        Room tmp = data[hole];
        while (2 * hole + 1 < curN && data[2 * hole + 1].getKey() < tmp.getKey())
        {
            int child = 2 * hole + 1;
            if (child + 1 < curN && data[child + 1].getKey() < data[child].getKey())
                ++child;
            data[hole] = data[child];
            hole = child;
        }
        data[hole] = tmp;
    }
    void doubleSpace()
    {
        Room *tmp = data;
        maxN *= 2;
        data = new Room[maxN];
        for (int i = 0; i < curN; ++i)
            data[i] = tmp[i];
        delete[] tmp;
    }
    void buildHeap()
    {
        for (int i = maxN / 2 - 1; i >= 0; --i)
            percolateDown(i);
    }

public:
    Heap(int n = 20) : maxN(n), curN(0), data(new Room[maxN]) {}
    ~Heap() { delete[] data; }
    void insert(const event &e)
    {
        if (curN == 0 || e.start < data[0].getKey())
        {
            Room a;
            a.insert(e);
            if (curN == maxN)
                doubleSpace();
            int tmp = curN++;
            for (; tmp > 0 && a.getKey() < data[(tmp - 1) / 2].getKey(); tmp = (tmp - 1) / 2)
                data[tmp] = data[(tmp - 1) / 2];
            data[tmp] = a;
        }
        else
        {
            data[0].insert(e);
            percolateDown(0);
        }
    }
    int getSize() const { return curN; }
    void print()
    {
        for (int i = 0; i < curN; ++i)
            data[i].print();
    }
};

void sort(event e[], int left, int right)
{
    if (left >= right)
        return;
    int i = left, j = left;
    int key = e[right].start;
    for (; j < right; ++j)
    {
        if (e[j].start < key)
        {
            swap(e[i], e[j]);
            ++i;
        }
    }
    swap(e[i], e[right]);
    sort(e, left, i - 1);
    sort(e, i + 1, right);
}

int leastRoom(event e[], int n)
{
    Heap hotel;
    sort(e, 0, n - 1);
    for (int i = 0; i < n; ++i)
    {
        hotel.insert(e[i]);
    }
    hotel.print();
    return hotel.getSize();
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
    int roomN = leastRoom(e, n);
    cout << roomN << endl;
    delete[] e;
    return 0;
}