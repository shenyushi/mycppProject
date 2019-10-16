#include <iostream>
#include "NodeRecognition.h"
#include <string>
using namespace std;

int main()
{
    string str;
    getline(cin, str);
    NodeRecognition nr(str);
    nr.print();
    return 0;
}