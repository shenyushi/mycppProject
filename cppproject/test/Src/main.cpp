#include <iostream>
#include <cstdlib>
#include "car.hpp"

using namespace std;

int main()
{
    cout<<"Hello World!"<<endl;

    Car *myCar=new Car("OldDriver");
    myCar->run();
    delete myCar;

    return 0;
}