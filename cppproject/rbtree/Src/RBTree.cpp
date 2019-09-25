#include "RBTree.hpp"
#include <stack>
#include <queue>

RBNode *const RBNode::nil = new RBNode(BLACK);

RBTree::RBTree() : root(RBNode::nil) {}

RBNode *RBTree::findd(int d) const
{
    RBNode *tmp = root;
    while (tmp != RBNode::nil && tmp->data != d)
    {
        if (d < tmp->data)
            tmp = tmp->left;
        else
            tmp = tmp->right;
    }
    return tmp;
}

RBTree::~RBTree()
{
    if (root == RBNode::nil)
        return;
    queue<RBNode *> qu;
    RBNode *tmp;
    qu.push(root);
    while (!qu.empty())
    {
        tmp = qu.front();
        qu.pop();
        delete tmp;
        if (tmp->left != RBNode::nil)
            qu.push(tmp->left);
        if (tmp->right != RBNode::nil)
            qu.push(tmp->right);
    }
    root = RBNode::nil;
}

void RBTree::leftRotate(RBNode *x)
{
    RBNode *y = x->right;

    x->right = y->left;
    if (y->left != RBNode::nil)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == RBNode::nil)
        root = y;
    else if (x->parent->left == x)
        x->parent->left = y;
    else
        x->parent->right = y;

    x->parent = y;
    y->left = x;
}

void RBTree::rightRotate(RBNode *x)
{
    RBNode *y = x->left;

    x->left = y->right;
    if (y->right != RBNode::nil)
        y->right->parent = x;

    y->parent = x->parent;
    if (x->parent == RBNode::nil)
        root = y;
    else if (x->parent->left == x)
        x->parent->left = y;
    else
        x->parent->right = y;

    x->parent = y;
    y->right = x;
}

void RBTree::insertFix(RBNode *z)
{
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            RBNode *y = z->parent->parent->right;
            if (y->color == RED)
            {
                z->parent->color = y->color = BLACK;
                y->parent->color = RED;
                z = y->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        }
        else
        {
            RBNode *y = z->parent->parent->left;
            if (y->color == RED)
            {
                z->parent->color = y->color = BLACK;
                y->parent->color = RED;
                z = y->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void RBTree::removeFix(RBNode *x)
{
    while (x != root && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            RBNode *w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else if (w->left->color == RED)
            {
                w->left->color = BLACK;
                w->color = RED;
                rightRotate(w);
                w = w->parent;
            }
            w->color = w->parent->color;
            w->parent->color = BLACK;
            w->right->color = BLACK;
            leftRotate(x->parent);
            x = root;
        }
        else
        {
            RBNode *w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == RED)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = w->parent;
                }
                w->color = w->parent->color;
                w->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(w->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

void RBTree::transplant(RBNode *u, RBNode *v)
{
    if (u->parent == RBNode::nil)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

void RBTree::preOrder() const
{
    if (root == RBNode::nil)
        return;
    stack<RBNode *> st;
    RBNode *tmp = root;
    st.push(root);
    while (!st.empty())
    {
        tmp = st.top();
        st.pop();
        cout << tmp->data << '\t';
        if (tmp->right != RBNode::nil)
            st.push(tmp->right);
        if (tmp->left != RBNode::nil)
            st.push(tmp->left);
    }
}

struct nodeAndN
{
    RBNode *node;
    int n;
    nodeAndN() {}
    nodeAndN(RBNode *p, int nn = 0) : node(p), n(nn) {}
};

void RBTree::midOrder() const
{
    if (root == RBNode::nil)
        return;
    stack<nodeAndN> st;
    nodeAndN tmp;
    st.push(nodeAndN(root));
    while (!st.empty())
    {
        tmp = st.top();
        st.pop();
        if (tmp.n == 0)
        {
            tmp.n++;
            st.push(tmp);
            if (tmp.node->left != RBNode::nil)
                st.push(nodeAndN(tmp.node->left));
        }
        else
        {
            cout << tmp.node->data << '\t';
            if (tmp.node->right != RBNode::nil)
                st.push(nodeAndN(tmp.node->right));
        }
    }
}

void RBTree::postOrder() const
{
    if (root == RBNode::nil)
        return;
    stack<nodeAndN> st;
    nodeAndN tmp;
    st.push(nodeAndN(root));
    while (!st.empty())
    {
        tmp = st.top();
        st.pop();
        if (tmp.n == 0)
        {
            tmp.n++;
            st.push(tmp);
            if (tmp.node->left != RBNode::nil)
                st.push(nodeAndN(tmp.node->left));
        }
        else if (tmp.n == 1)
        {
            tmp.n++;
            st.push(tmp);
            if (tmp.node->right != RBNode::nil)
                st.push(nodeAndN(tmp.node->right));
        }
        else
            cout << tmp.node->data << '\t';
    }
}

void RBTree::levelOrder() const
{
    if (root == RBNode::nil)
        return;
    queue<RBNode *> qu;
    RBNode *tmp;
    qu.push(root);
    while (!qu.empty())
    {
        tmp = qu.front();
        qu.pop();
        cout << tmp->data << '\t';
        if (tmp->left != RBNode::nil)
            qu.push(tmp->left);
        if (tmp->right != RBNode::nil)
            qu.push(tmp->right);
    }
}

void RBTree::display() const
{
    if (root == RBNode::nil)
        return;
    queue<nodeAndN> qu;
    nodeAndN tmp;
    int deepth = 0;
    bool flag = false;
    qu.push(root);
    while (true)
    {
        tmp = qu.front();
        qu.pop();
        if (tmp.n != deepth)
        {
            if (!flag)
                return;
            flag = false;
            deepth = tmp.n;
            cout << endl;
        }
        if (tmp.node != RBNode::nil)
            cout << tmp.node->data << ' ';
        else
            cout << "@ ";
        if (tmp.node != RBNode::nil && tmp.node->left != RBNode::nil)
        {
            qu.push(nodeAndN(tmp.node->left, deepth + 1));
            flag = true;
        }
        else
            qu.push(nodeAndN(RBNode::nil, deepth + 1));
        if (tmp.node != RBNode::nil && tmp.node->right != RBNode::nil)
        {
            qu.push(nodeAndN(tmp.node->right, deepth + 1));
            flag = true;
        }
        else
            qu.push(nodeAndN(RBNode::nil, deepth + 1));
    }
}

bool RBTree::find(int d) const
{
    if (findd(d) != RBNode::nil)
        return true;
    else
        return false;
}

void RBTree::insert(int d)
{
    RBNode *z = root, *w = RBNode::nil;
    while (z != RBNode::nil && z->data != d)
    {
        w = z;
        if (d < z->data)
            z = z->left;
        else
            z = z->right;
    }
    if (w == RBNode::nil)
        root = new RBNode(d, RED, RBNode::nil);
    if (z != RBNode::nil)
        return;
    if (d < w->data)
        z = w->left = new RBNode(d, RED, w);
    else
        z = w->right = new RBNode(d, RED, w);
    insertFix(z);
}

void RBTree::remove(int d)
{
    RBNode *z = findd(d);
    if (z == RBNode::nil)
        return;
    RBNode *y = z, *x;
    Color yOriginColor = y->color;
    if (z->left == RBNode::nil)
    {
        x = z->right;
        transplant(z, x);
    }
    else if (z->right == RBNode::nil)
    {
        x = z->left;
        transplant(z, x);
    }
    else
    {
        y = z->right;
        while (y->left != RBNode::nil)
            y = y->left;
        yOriginColor = y->color;
        x = y->right;
        if (y != z->right)
        {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (yOriginColor == BLACK)
        removeFix(x);
}