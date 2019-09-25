#include "graph.hpp"
#include <iostream>
using namespace std;

int main()
{
    int ver[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}, n = 9;
    Graph g(n, ver); 
    g.insertE(1, 2);
    g.insertE(2, 3);
    g.insertE(3, 4);
    g.insertE(4, 5);
    //g.insertE(5, 6);
    g.insertE(6, 7);
    g.insertE(7, 8);
    g.insertE(8, 9);
    g.topSort();
    cout<<endl;
    g.topSort2();
}