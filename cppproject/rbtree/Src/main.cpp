#include <iostream>
#include <cstdlib>
#include <ctime>
#include "RBTree.hpp"

using namespace std;

int main()
{
    srand(time(NULL));
    RBTree tree;

    for (int i = 0; i < 20; ++i)
        tree.insert(i + 1);
    tree.display();
    cout << endl;
    for (int i = 20; i > 0; --i)
    {
        tree.remove(i);
        tree.display();
        cout << endl;
    }
    return 0;
}