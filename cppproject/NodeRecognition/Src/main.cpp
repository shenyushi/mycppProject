#include <iostream>
#include <string>
#include "NodeRecognition.h"

using namespace std;

int main()
{
    string str;
    getline(cin,str);
    NodeRecognition nr(str);
    return 0;
}