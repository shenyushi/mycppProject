#pragma once
#include <iostream>
using namespace std;

class Graph
{
private:
public:
    struct eNode
    {
        int weight;
        int vN;
        eNode *next;
        eNode() {}
        eNode(int e, int w, eNode *n = NULL) : vN(e), weight(w), next(n) {}
    };
    struct vNode
    {
        int ver;
        eNode *head;
        bool flag;
        int deepth;
        vNode *parent;
        int d, f;
        vNode() : head(NULL) {}
    };
    int vNum, eNum;
    vNode *vList;
    int find(int x) const
    {
        for (int i = 0; i < vNum; ++i)
            if (vList[i].ver == x)
                return i;
        return -1;
    }

public:
    Graph(int vN) : vNum(vN), vList(new vNode[vN]) {}
    Graph(int vN, const int ver[]) : vNum(vN), eNum(0), vList(new vNode[vN])
    {
        for (int i = 0; i < vN; ++i)
            vList[i].ver = ver[i];
    }
    ~Graph()
    {
        for (int i = 0; i < vNum; ++i)
        {
            eNode *t1 = vList[i].head, *t2;
            while (t1 != NULL)
            {
                t2 = t1;
                t1 = t1->next;
                delete t2;
            }
        }
        delete[] vList;
    }
    void insertE(int x, int y, int weight = 1)
    {
        int start = find(x), end = find(y);
        if (start >= 0 && end >= 0)
        {
            vList[start].head = new eNode(end, weight, vList[start].head);
            ++eNum;
        }
    }
    void print() const;
    void outD(int oD[]) const;
    void inD(int iD[]) const;
    void makeT();
    void simplify();
    void BFS(bool print = true);
    void bfsVisit(vNode *u, bool print = true);
    void printPath(int x, int y);
    void DFS(bool print = true);
    void dfsVisit(vNode *u, int &time, bool print = true);
    void strongComponent();
    int nOfRoute(int x, int y);
    bool singleConnected();
    bool isLoop();
    void topSort();
    void topSort2();
    Graph simpleSCC();
};