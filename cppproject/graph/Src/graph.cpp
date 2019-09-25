#include "graph.hpp"

#include <iostream>
using namespace std;

#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

void Graph::print() const
{
    for (int i = 0; i < vNum; ++i)
    {
        cout << vList[i].ver << '\t';
        eNode *tmp = vList[i].head;
        while (tmp != NULL)
        {
            cout << tmp->vN << ' ';
            tmp = tmp->next;
        }
        cout << endl;
    }
}

void Graph::outD(int outD[]) const
{
    for (int i = 0; i < vNum; ++i)
    {
        int n = 0;
        eNode *tmp = vList[i].head;
        while (tmp != NULL)
        {
            tmp = tmp->next;
            ++n;
        }
        outD[i] = n;
    }
}

void Graph::inD(int inD[]) const
{
    for (int i = 0; i < vNum; ++i)
        inD[i] = 0;
    for (int i = 0; i < vNum; ++i)
    {
        eNode *tmp = vList[i].head;
        while (tmp != NULL)
        {
            inD[tmp->vN]++;
            tmp = tmp->next;
        }
    }
}

void Graph::makeT()
{
    eNode *tmp[vNum];
    for (int i = 0; i < vNum; ++i)
        tmp[i] = NULL;
    for (int i = 0; i < vNum; ++i)
    {
        eNode *t = vList[i].head;
        int start = i;
        while (t != NULL)
        {
            int end = t->vN;
            tmp[end] = new eNode(start, t->weight, tmp[end]);
            t = t->next;
        }
    }
    for (int i = 0; i < vNum; ++i)
    {
        eNode *t1 = vList[i].head, *t2;
        while (t1 != NULL)
        {
            t2 = t1;
            t1 = t1->next;
            delete t2;
        }
        vList[i].head = tmp[i];
    }
}

void Graph::simplify()
{
    for (int i = 0; i < vNum; ++i)
    {
        bool memo[vNum];
        for (int i = 0; i < vNum; ++i)
            memo[i] = 0;
        eNode *tmp = vList[i].head, *t2 = NULL;
        memo[i] = true;
        while (tmp != NULL && t2 == NULL)
        {
            if (memo[tmp->vN])
            {
                vList[i].head = tmp->next;
                delete tmp;
                tmp = vList[i].head;
            }
            else
            {
                t2 = tmp;
                tmp = tmp->next;
            }
        }
        while (tmp != NULL)
        {
            if (memo[tmp->vN])
            {
                t2->next = tmp->next;
                delete tmp;
                tmp = t2->next;
            }
            else
            {
                t2 = tmp;
                tmp = tmp->next;
            }
        }
    }
}

void Graph::BFS(bool print)
{
    for (int i = 0; i < vNum; ++i)
    {
        vList[i].flag = false;
        vList[i].parent = NULL;
    }
    for (int i = 0; i < vNum; ++i)
        if (!vList[i].flag)
            bfsVisit(&vList[i], print);
}

void Graph::bfsVisit(vNode *u, bool print)
{
    u->flag = true;
    u->deepth = 0;
    queue<vNode *> q;
    q.push(u);
    while (!q.empty())
    {
        vNode *t1 = q.front();
        if (print)
            cout << t1->ver << ' ';
        q.pop();
        eNode *tmp = t1->head;
        while (tmp != NULL)
        {
            vNode *t2 = &vList[tmp->vN];
            if (!t2->flag)
            {
                t2->flag = true;
                t2->deepth = t1->deepth + 1;
                t2->parent = t1;
                q.push(t2);
            }
            tmp = tmp->next;
        }
    }
}

void Graph::printPath(int x, int y)
{
    for (int i = 0; i < vNum; ++i)
        vList[i].parent = NULL;
    int start = find(x), end = find(y);
    bfsVisit(&vList[start], false);
    if (vList[end].parent == NULL)
    {
        cout << "no path" << endl;
        return;
    }
    stack<vNode *> st;
    vNode *tmp = &vList[end];
    while (tmp != NULL)
    {
        st.push(tmp);
        tmp = tmp->parent;
    }
    while (!st.empty())
    {
        cout << st.top()->ver << ' ';
        st.pop();
    }
}

void Graph::DFS(bool print)
{
    for (int i = 0; i < vNum; ++i)
    {
        vList[i].flag = false;
        vList[i].parent = NULL;
    }
    int time = 0;
    for (int i = 0; i < vNum; ++i)
        if (!vList[i].flag)
            dfsVisit(&vList[i], time, print);
}

void Graph::dfsVisit(vNode *u, int &time, bool print)
{
    struct pp
    {
        vNode *vv;
        eNode *ee;
        pp(vNode *v, eNode *e) : vv(v), ee(e) {}
    };
    stack<pp> st;
    u->flag = true;
    u->d = time++;
    u->parent = NULL;
    st.push(pp(u, u->head));
    while (!st.empty())
    {
        pp tpp = st.top();
        st.pop();
        if (tpp.ee != NULL)
        {
            st.push(pp(tpp.vv, tpp.ee->next));
            vNode *t1 = &vList[tpp.ee->vN];
            if (!t1->flag)
            {
                t1->flag = true;
                t1->parent = tpp.vv;
                t1->d = time++;
                st.push(pp(t1, t1->head));
            }
        }
        else
        {
            tpp.vv->f = time++;
            if (print)
                cout << tpp.vv->ver << ' '; /////////////////////////
        }
    }
}

void Graph::strongComponent()
{
    DFS(false);
    struct tmp
    {
        int ii;
        int ff;
        tmp(int i, int f) : ii(i), ff(f) {}
        bool operator<(const tmp &right) { return ff < right.ff; }
    };
    vector<tmp> t;
    for (int i = 0; i < vNum; ++i)
        t.push_back(tmp(i, vList[i].f));
    sort(t.begin(), t.end());
    makeT();
    for (int i = 0; i < vNum; ++i)
        vList[i].flag = false;
    int time = 0;
    for (vector<tmp>::iterator it = t.end() - 1; it >= t.begin(); --it)
    {
        int k = it->ii;
        if (!vList[k].flag)
        {
            dfsVisit(&vList[k], time);
            cout << endl;
        }
    }
    makeT();
}

int Graph::nOfRoute(int x, int y)
{
    int n = 0;
    for (int i = 0; i < vNum; ++i)
        vList[i].flag = false;
    int start = find(x), end = find(y);
    stack<vNode *> st;
    vList[start].flag = true;
    st.push(&vList[start]);
    while (!st.empty())
    {
        vNode *tmp = st.top();
        st.pop();
        if (tmp == &vList[end])
            ++n;
        eNode *e = tmp->head;
        while (e != NULL)
        {
            if (vList[e->vN].flag && e->vN == end)
                ++n;
            else if (!vList[e->vN].flag)
            {
                vList[e->vN].flag = true;
                st.push(&vList[e->vN]);
            }
            e = e->next;
        }
    }
    return n;
}

bool Graph::singleConnected()
{
    for (int i = 0; i < vNum; ++i)
        vList[i].flag = false;
    int time = 0;
    for (int i = 0; i < vNum; ++i)
    {
        if (vList[i].flag)
            continue;
        struct ppp
        {
            vNode *vv;
            eNode *ee;
            ppp(vNode *v, eNode *e) : vv(v), ee(e) {}
        };
        stack<ppp> st;
        vList[i].flag = true;
        vList[i].d = time++;
        vList[i].parent = NULL;
        st.push(ppp(&vList[i], vList[i].head));
        while (!st.empty())
        {
            ppp tmp = st.top();
            st.pop();
            if (tmp.ee != NULL)
            {
                st.push(ppp(tmp.vv, tmp.ee->next));
                vNode *t = &vList[tmp.ee->vN];
                if (!t->flag)
                {
                    t->d = time++;
                    t->flag = true;
                    t->parent = tmp.vv;
                    st.push(ppp(t, t->head));
                }
                else if (tmp.vv->d < t->d || (tmp.vv->d > t->d && t->d > vList[i].d))
                    return false;
            }
            else
                tmp.vv->f = time++;
        }
    }
    return true;
}

bool Graph::isLoop()
{
    for (int i = 0; i < vNum; ++i)
    {
        vList[i].flag = false;
        vList[i].f = 0;
    }
    int time = 0;
    for (int i = 0; i < vNum; ++i)
    {
        if (vList[i].flag)
            continue;
        struct ppp
        {
            vNode *vv;
            eNode *ee;
            ppp(vNode *v, eNode *e) : vv(v), ee(e) {}
        };
        stack<ppp> st;
        vList[i].flag = true;
        vList[i].d = time++;
        vList[i].parent = NULL;
        st.push(ppp(&vList[i], vList[i].head));
        while (!st.empty())
        {
            ppp tmp = st.top();
            st.pop();
            if (tmp.ee != NULL)
            {
                st.push(ppp(tmp.vv, tmp.ee->next));
                vNode *t = &vList[tmp.ee->vN];
                if (!t->flag)
                {
                    t->d = time++;
                    t->flag = true;
                    t->parent = tmp.vv;
                    st.push(ppp(t, t->head));
                }
                else if (t->f == 0)
                    return true;
            }
            else
                tmp.vv->f = time++;
        }
    }
    return false;
}

void Graph::topSort()
{
    stack<int> toposort;
    for (int i = 0; i < vNum; ++i)
        vList[i].flag = false;
    for (int i = 0; i < vNum; ++i)
    {
        if (vList[i].flag)
            continue;
        struct ppp
        {
            vNode *vv;
            eNode *ee;
            ppp(vNode *v, eNode *e) : vv(v), ee(e) {}
        };
        stack<ppp> st;
        vList[i].flag = true;
        st.push(ppp(&vList[i], vList[i].head));
        while (!st.empty())
        {
            ppp tmp = st.top();
            st.pop();
            if (tmp.ee != NULL)
            {
                st.push(ppp(tmp.vv, tmp.ee->next));
                vNode *t = &vList[tmp.ee->vN];
                if (!t->flag)
                {
                    t->flag = true;
                    st.push(ppp(t, t->head));
                }
            }
            else
                toposort.push(tmp.vv->ver);
        }
    }
    while (!toposort.empty())
    {
        cout << toposort.top() << ' ';
        toposort.pop();
    }
}

void Graph::topSort2()
{
    int inD[vNum];
    for (int i = 0; i < vNum; ++i)
        inD[i] = 0;
    for (int i = 0; i < vNum; ++i)
    {
        eNode *tmp = vList[i].head;
        while (tmp != NULL)
        {
            inD[tmp->vN]++;
            tmp = tmp->next;
        }
    }
    queue<int> qu;
    for (int i = 0; i < vNum; ++i)
        if (!inD[i])
            qu.push(i);
    while (!qu.empty())
    {
        int t = qu.front();
        qu.pop();
        cout << vList[t].ver << ' ';
        eNode *e = vList[t].head;
        while (e != NULL)
        {
            --inD[e->vN];
            if (!inD[e->vN])
                qu.push(e->vN);
            e = e->next;
        }
    }
}

Graph Graph::simpleSCC()
{
    Graph ttt(vNum);
    for (int i = 0; i < vNum; ++i)
        ttt.vList[i].ver = vList[i].ver;
    DFS(false);
    struct tmp
    {
        int ii;
        int ff;
        tmp(int i, int f) : ii(i), ff(f) {}
        bool operator<(const tmp &right) { return ff < right.ff; }
    };
    vector<tmp> t;
    for (int i = 0; i < vNum; ++i)
        t.push_back(tmp(i, vList[i].f));
    sort(t.begin(), t.end());
    makeT();
    for (int i = 0; i < vNum; ++i)
        vList[i].flag = false;
    int time = 0, nSCC;
    int noteSCC[vNum];
    for (vector<tmp>::iterator it = t.end() - 1; it >= t.begin(); --it)
    {
        bool connectedSCC[vNum];
        for (int i = 0; i < vNum; ++i)
            connectedSCC[i] = false;
        vNode *u = &vList[it->ii];
        int k1 = it->ii;
        int k2 = k1;
        if (!u->flag)
        {
            struct pp
            {
                vNode *vv;
                eNode *ee;
                pp(vNode *v, eNode *e) : vv(v), ee(e) {}
            };
            stack<pp> st;
            u->flag = true;
            u->d = time++;
            st.push(pp(u, u->head));
            while (!st.empty())
            {
                pp tpp = st.top();
                st.pop();
                if (tpp.ee != NULL)
                {
                    st.push(pp(tpp.vv, tpp.ee->next));
                    vNode *t1 = &vList[tpp.ee->vN];
                    if (!t1->flag)
                    {
                        t1->flag = true;
                        t1->d = time++;
                        st.push(pp(t1, t1->head));
                    }
                    else if (t1->d < u->d && !connectedSCC[t1->ver])
                    {
                        connectedSCC[t1->ver] = true;
                        ttt.vList[tpp.ee->vN].head = new eNode(find(tpp.vv->ver), 1, ttt.vList[tpp.ee->vN].head);
                    }
                }
                else
                {
                    tpp.vv->f = time++;
                    int endN = find(tpp.vv->ver);
                    ttt.vList[endN].head = new eNode(k1, 1, ttt.vList[endN].head);
                    noteSCC[endN] = nSCC;
                    k1 = endN;
                    ttt.eNum++;
                }
            }
        }
        ttt.vList[k2].head = new eNode(k1, 1, ttt.vList[k2].head);
        nSCC++;
    }
    makeT();

    return ttt;
}
