#include<iostream>
#include<thread>
#include<mutex>

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
    t.detach();

    cout<<"Main finished"<<endl;

    return 0;
}

