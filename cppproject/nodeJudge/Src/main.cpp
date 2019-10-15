#include <iostream>
#include "NodeRecognition.h"
#include <string>
using namespace std;

int main()
{
    string str;
    NodeRecognition nr;
    while(getline(cin,str)){
        if(str.empty())
            break;
        nr.getData(str);
    }
    nr.print();
    return 0;
}