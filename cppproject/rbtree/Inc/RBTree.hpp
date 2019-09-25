#pragma once

#include <iostream>

using namespace std;

enum Color
{
    RED,
    BLACK
};

struct RBNode
{
    int data;
    RBNode *left;
    RBNode *right;
    RBNode *parent;
    Color color;
    static RBNode *const nil;
    RBNode(Color col) : color(col) {}
    RBNode(int d, Color col, RBNode *p) : data(d), color(col), parent(p), left(nil), right(nil) {}
};

class RBTree
{
private:
    RBNode *root;
    RBNode *findd(int d) const;
    void leftRotate(RBNode *x);
    void rightRotate(RBNode *x);
    void insertFix(RBNode *z);
    void removeFix(RBNode *x);
    void transplant(RBNode *u, RBNode *v);

public:
    RBTree();
    ~RBTree();
    void preOrder() const;
    void midOrder() const;
    void postOrder() const;
    void levelOrder() const;
    void display() const;
    bool find(int d) const;
    void insert(int d);
    void remove(int d);
};