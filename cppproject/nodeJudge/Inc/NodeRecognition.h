#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int maxn = 100;

class NodeRecognition
{
private:
    int key[maxn];
    int type[maxn];
    int childN[maxn];
    int wei[maxn];
    int num[maxn];
    int find(int n);

public:
    NodeRecognition();
    void getData(string str);
    void print();
};