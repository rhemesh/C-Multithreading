#include<iostream>
#include<thread>

using namespace std;

void func(int num)
{
    while(num--)
    {
        cout<<"num = "<<num<<endl;
    }
}

int main()
{
    thread t(func,15);
    cout<<"Main"<<endl;
    //t.join();
    t.detach();

    cout<<"Main finished"<<endl;

    return 0;
}

//Here we use join to wait until thread finish its work,
//If we do not want to wait then use detach that will return control from the thread after calling to main