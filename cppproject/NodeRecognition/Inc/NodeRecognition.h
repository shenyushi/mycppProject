#include <iostream>
#include <vector>
using namespace std;

class NodeRecognition
{
    struct Pair
    {
        int data;
        int key;
        Pair(int d, int p) : data(d), key(p) {}
    };
    vector<Pair> arr;
    vector<int> map;
    int exist(int x);

public:
    NodeRecognition(string str);
    void calculate();
};