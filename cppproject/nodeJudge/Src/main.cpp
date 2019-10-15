#include <iostream>
#include "NodeRecognition.h"

using namespace std;

int main()
{
    cout<<"Hello World!"<<endl;

    Car *myCar=new Car("OldDriver");
    myCar->run();
    delete myCar;

    return 0;
}