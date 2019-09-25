#pragma once
#include <iostream>
#include <string>

using namespace std;

class Car
{
private:
    string mName;
public:
    Car(string &&name):mName(name)
    {
        cout<<"A car:"<<mName<<"has been created!"<<endl;
    }
    ~Car()
    {
        cout<<"A car:"<<mName<<"has been destroyed!"<<endl;
    }
    void run(void);
};