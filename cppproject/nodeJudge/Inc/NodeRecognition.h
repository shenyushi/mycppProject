#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int maxn = 100;

class NodeRecognition
{
private:
    bool flag[maxn];
    int key[maxn];
    int type[maxn];
    int childN[maxn];
    int find(int n);

public:
    NodeRecognition();
    void getData(string str);
};