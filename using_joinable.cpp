#include<iostream>
#include<thread>

using namespace std;

void func(int n)
{
    while(n--)
    {
        cout<<"n = "<<n<<endl;
    }
}

int main()
{
    thread t(func,10);
    cout<<"Main"<<endl;
    //t.join();
    if(t.joinable())
    {
        cout<<"Inside if"<<endl;
        t.join();
    }
    cout<<"Main finished"<<endl;

}

//Here if we use multiple join() or detach() that creates run time error and may program terminate.
//so, use joinable that checks whether initially it is joined/detached and if it is joined/detached before then it will ignore or else it will execute join()/detach().