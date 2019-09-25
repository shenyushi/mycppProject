#include <fstream>
using namespace std;
#include <iostream>
#include <string>

int main()
{
    string str;
    ifstream infile;
    char tmp;
    infile.open("testfile.txt");
    if(!infile)
        cerr<<"error!";
    while(infile>>tmp)
        str.push_back(tmp);
    cout<<str<<endl;
    return 0;
}