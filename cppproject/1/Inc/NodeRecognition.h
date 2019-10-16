#include <string>
#include <map>
using namespace std;

struct Node
{
    int wei, pwei, num, swei, childN, type;
    Node(int w, int pw) : wei(w), pwei(pw), num(1), childN(0), type(0) { swei = wei; }
    bool operator<(const Node &x)
    {
        return type < x.type || type == x.type && swei < x.swei || type == x.type && swei == x.swei && num < x.num;
    }
};
typedef map<int, Node> Map;
typedef pair<int, Node> Pair;

class NodeRecognition
{
private:
    Map m;
    int findp(int n);
    int findp(int n, const int start);

public:
    NodeRecognition(string str);
    void print();
};
